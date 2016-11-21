/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part the SCIP-Extension                     */
/*                     System Dynamics SCIP (SD-SCIP)                        */
/*                         Homepage: sdscip.zib.de                           */
/*                                                                           */
/*    Copyright (C) 20016     Ingmar Vierhaus <mail@ingmar-vierhaus.de>      */
/*                                                                           */
/*                                                                           */
/*  SD-SCIP is distributed under the terms of the GNU Public License (GPL)   */
/*                                                                           */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file    SDproblemStructureV1.cpp
 * @brief   @todo
 * @author  Ingmar Vierhaus
 *
 */


#include "SDproblemStructureV1.h"
#include "ProbDataSD.h"
#include <scip/cons_linear.h>
#include <scip/cons_varbound.h>

static SCIP_VAR* getTransVar(SCIP* scip, SCIP_VAR* var)
{
   if(SCIPisTransformed(scip) && SCIPvarIsOriginal(var))
      return SCIPvarGetTransVar(var);

   return var;
}


namespace sdscip
{

SDproblemStructureV1::SDproblemStructureV1( SCIP *scip )  :
   SDproblemStructureInterface( scip )
{
   isTranformed_ = false;
   clear();
}

SCIP_Bool SDproblemStructureV1::isStateVar(SCIP_VAR* var)
{
   return backwardDiffVarMap_.find(var) != backwardDiffVarMap_.end();
}

int SDproblemStructureV1::getStateVarTime(SCIP_VAR* var)
{
   auto it = backwardDiffVarMap_.find(var);
   assert(it != backwardDiffVarMap_.end());
   return it->second->getTime();
}

SCIP_Bool SDproblemStructureV1::isControlVar(SCIP_VAR* var)
{
   return backwardCtrlMap_.find(var) != backwardCtrlMap_.end();
}

int SDproblemStructureV1::getControlVarBeginTime(SCIP_VAR* var)
{
   auto it = backwardCtrlMap_.find(var);
   assert(it != backwardCtrlMap_.end());
   return it->second->getTimeBegin();
}


SDproblemStructureV1::~SDproblemStructureV1() {
   for( std::size_t i = 0; i < xdot_.size(); ++i )
      SCIPexprFreeDeep(SCIPblkmem(scip_), &xdot_[i]);

   for( std::size_t i = 0; i < xdotAlgebraic_.size(); ++i )
      SCIPexprFreeDeep(SCIPblkmem(scip_), &xdotAlgebraic_[i]);

   for( std::size_t i = 0; i < algebraicExpr_.size(); ++i )
      SCIPexprFreeDeep(SCIPblkmem(scip_), &algebraicExpr_[i]);
}

bool SDproblemStructureV1::isValid() const
{
   return isValid_;
}

SCIP_RETCODE SDproblemStructureV1::setIsValid( bool _isValid )
{
   isValid_ = _isValid;
   return SCIP_OKAY;
}

bool SDproblemStructureV1::isReformulated() const
{
   return isReformulated_;
}

SCIP_RETCODE SDproblemStructureV1::setIsReformulated( bool _isReformulated )
{
   isReformulated_ = _isReformulated;
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::addCut( SCIP_CONS *cut, unsigned int time )
{
   propCuts_[time].push_back( cut );
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::clear()
{
   isValid_ = false;
   nStates_ = 0;
   nAlgebraic_ = 0;
   nControls_ = 0;
   currentTime_ = 0;
   atTimeZero_ = true;
   isReformulated_ = false;
   isXdotContinuous_ = false;
   algebraic_.clear();
   explDiff_.clear();
   control_.clear();
   algebraicBuilder_.clear();
   explDiffBuilder_.clear();
   controlBuilder_.clear();
   backwardCtrlMap_.clear();
   backwardDiffVarMap_.clear();
   backwardAlgebraicVarMap_.clear();
   minmax_map_.clear();
   isXdotContinuous_ = false;
   isSimulation_ = false;
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::checkIsSimulation()
{
   SCIPerrorMessage("not implemented");
   return SCIP_ERROR;
}

bool SDproblemStructureV1::isSimulation()
{
   SCIPerrorMessage("not implemented");
   return false;
}


SCIP_RETCODE SDproblemStructureV1::isExprContinuous(SCIP_EXPR* expr, SCIP_Bool& isContinuous)
{
   switch( SCIPexprGetOperator(expr) )
   {
   /** operands that are continuous if the right operands are const or positive */
   case  SCIP_EXPR_INTPOWER: /**< power with integer exponent (1 operand!, exponent stored in expression data) */
   case  SCIP_EXPR_SQRT: /**< square root (1 operand) */
   case  SCIP_EXPR_SIGNPOWER: /**< signed power (sign(x)|x|^a, 1 operand!, exponent is stored in expression data) */
   case  SCIP_EXPR_LOG: /**< natural logarithm (ln(x), 1 operand) */

   /* Operands that break: continuity */
   case  SCIP_EXPR_SIGN: /**< sign of value (1 operand) */
      isContinuous = FALSE;
      return SCIP_OKAY;
      break;

   default:
      /* If my operator is okay, check children */
      SCIP_Bool result;
      for( int i = 0; i < SCIPexprGetNChildren(expr); ++i )
      {
         SCIP_CALL( isExprContinuous(SCIPexprGetChildren(expr)[i], result) );
         if (result == FALSE)
         {
            isContinuous = FALSE;
            return SCIP_OKAY;
         }
      }
   }

   /* If anything had not been continuous we would have already returned */
   isContinuous = TRUE;
   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::checkXdotContinuity()
{
   SCIP_Bool isContinuous = true;
   std::vector<std::string> nonContinuousStates;
   std::vector<std::string> stateVarNames = getStateVarNames();

   for(auto it = xdot_.begin(); it != xdot_.end(); ++it)
   {
      //SCIP_CALL( isExprContinuous(*it, isContinuous));
      SCIP_CALL( isExprContinuous(*it, isContinuous) );

      if( !isContinuous)
      {
         isContinuous = false;
         int stateId = it - xdot_.begin();
         nonContinuousStates.push_back(stateVarNames[stateId] + std::string(" (") + std::to_string(stateId) + std::string(")"));
      }
   }

   if (isContinuous == false)
   {
      SCIPwarningMessage(scip_, "Derivative(s) of %s is/are not absolutely continuous.\n", implode(std::string(", "), nonContinuousStates).c_str());
      isXdotContinuous_ = false;
   }
   else
      isXdotContinuous_ = true;

   return SCIP_OKAY;
}

bool SDproblemStructureV1::isXdotContinuous()
{
   return isXdotContinuous_;
}

SCIP_RETCODE SDproblemStructureV1::doneReading()
{
   int minmax_sdVarId = std::numeric_limits<int>::min();

   for( std::pair<const std::pair<int, int>, SDCons> &minmaxCons : minmax_map_ )
   {
      int time = minmaxCons.first.first;
      int level = minmaxCons.first.second;
      algebraicBuilder_.add( minmax_sdVarId++, SDVariable( time , level, nullptr, std::move( minmaxCons.second ) ) );
   }

   minmax_map_.clear();

   algebraic_ = algebraicBuilder_.build();
   explDiff_ = explDiffBuilder_.build();
   control_ = controlBuilder_.build();

   for( SDVariable & algebraicVar : algebraic_ )
   {
      SCIP_VAR *var = algebraicVar.getScipVariable();
      SDCons &sdcons = algebraicVar.getConstraint();

      if( var )
         backwardAlgebraicVarMap_.emplace( var, &algebraicVar );

      switch( sdcons.getType() )
      {
      case SDConsType::CONST_MAX:
      case SDConsType::CONST_MIN:
      {
         SDConstMinMax *mm_data = sdcons.getSDConstMinMaxConsData();
         backwardAlgebraicVarMap_.emplace( mm_data->var_bin, &algebraicVar );
         backwardAlgebraicVarMap_.emplace( mm_data->var_pos, &algebraicVar );
         backwardAlgebraicVarMap_.emplace( mm_data->var_neg, &algebraicVar );
         break;
      }

      case SDConsType::SIMPLE:
         break;

      default:
         assert( false );
      }
   }

   for( SDVariable & explDiffVar : explDiff_ )
   {
      SCIP_VAR *var = explDiffVar.getScipVariable();

      if( var )
         backwardDiffVarMap_.emplace( var, &explDiffVar );
   }

   for( SDControl & controlVar : control_ )
   {
      SCIP_VAR *var = controlVar.getScipVariable();

      if( var )
         backwardCtrlMap_.emplace( var, &controlVar );
   }


   checkXdotContinuity();
   //checkIsSimulation();

   this->setIsValid( true );

   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::addControlVar( SCIP_VAR *var, int index, unsigned int firstTime, unsigned int lastTime, int sdVarId )
{
   controlBuilder_.add( sdVarId, SDControl( firstTime, lastTime , var ) );

   if( firstTime == 0 )
      ++nControls_;

   return SCIP_OKAY;
}

SCIP_RETCODE SDproblemStructureV1::addVariable( int index, SCIP_VAR *var, unsigned int time, SD_VAR_TYPE type, int sdVarId )
{
   if( type == sdscip::SDproblemStructureInterface::ALGEBRAIC && time == 0 )
      ++nAlgebraic_;
   else if( type == sdscip::SDproblemStructureInterface::STATE && time == 0 )
   {
      ++nStates_;
   }

   return SCIP_OKAY;
}

/*
SCIP_RETCODE SDproblemStructureV1::addAlgebraicCons( SCIP_CONS* cons, SCIP_VAR* forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId )
{
   if(minmax_ == nullptr && ( type == SDproblemStructureInterface::MIN || type == SDproblemStructureInterface::MAX ) ) {
      minmax_ = new SDConstMinMax;
      minmaxlevel_ = level;
      minmax_type_ = type == SDproblemStructureInterface::MIN ? SDConsType::CONST_MIN : SDConsType::CONST_MAX;
      minmax_time_ = time;
   }

   if(minmax_ != nullptr && level == minmaxlevel_)
   {
      if(forwardVar != nullptr) {
         minmax_->splitter = cons;
         minmax_fwd_var_ = forwardVar;
         minmax_varid_ = sdVarId;
         int nvars;
         unsigned int success;

         //TODO: VAR_POS VAR_NEG
      } else {
         //gehe variablen durch
         //suche binär -> positives vorzeichen -> max_cons
         //suche binär -> negatives vorzeichen -> min_cons
         //und speichere binär
      }
   }
   else if(minmax_ != nullptr && level != minmaxlevel_)
   {
      algebraicBuilder_.add( minmax_varid_, SDVariable( minmax_time_ , minmaxlevel_, minmax_fwd_var_, SDCons( minmax_type_, minmax_ ) ) );
      minmax_ = nullptr;
   }
   else
   {
      algebraicBuilder_.add( sdVarId, SDVariable( time, level, forwardVar, cons ) );
   }
   return SCIP_OKAY;
}
 */

SCIP_RETCODE SDproblemStructureV1::addAlgebraicCons( SCIP_CONS *cons, SCIP_VAR *forwardVar, unsigned int time, int level, SD_CONS_TYPE type, int sdVarId )
{
   //SCIPdebugMessage( "Adding cons:\n" );
   //SCIP_CALL( SCIPprintCons(scip, cons, nullptr ) );
   //SCIPinfoMessage(scip, nullptr, "\n" );
   switch( type )
   {
   case SDproblemStructureInterface::MIN:
   case SDproblemStructureInterface::MAX:
   {
      SCIPdebugMessage( "Detected MIN/MAX Level (time=%d, level=%d):\n", time, level );
      SDCons &sdcons = minmax_map_[std::make_pair( time, level )];

      if( sdcons.getType() == SDConsType::SIMPLE )
      {
         sdcons = ( type == SDproblemStructureInterface::MIN ) ? SDCons::CreateConstMin() : SDCons::CreateConstMax();
      }

      assert( sdcons.getType() == SDConsType::CONST_MIN || sdcons.getType() == SDConsType::CONST_MAX );
      SDConstMinMax *minmax_data = sdcons.getSDConstMinMaxConsData();
      int nvars;
      unsigned int success;
      std::vector<SCIP_VAR *> vars;
      SCIPgetConsNVars( scip_, cons, &nvars, &success );
      vars.resize( nvars );
      assert( success );
      SCIPgetConsVars( scip_, cons, &vars[0], vars.size(), &success );
      assert( success );

      if( SDisEquation( scip_, cons ) )
      {
         SCIPdebugMessage( "found splitter\n" );
         minmax_data->splitter = cons;
      }
      else if( std::strcmp( SCIPconshdlrGetName( SCIPconsGetHdlr( cons ) ), "linear" ) == 0 )
      {
         SCIP_Real *coeffs = SCIPgetValsLinear( scip_, cons );
         SCIPdebugMessage( "found min or max linear cons\n" );
         assert( nvars == 2 );
         SCIP_VAR *pos_or_neg_var;
         SCIP_Real binary_coeff;

         if( SCIPvarIsBinary( vars[0] ) )
         {
            if( minmax_data->var_bin == nullptr )
               minmax_data->var_bin = vars[0];

            assert( minmax_data->var_bin == vars[0] );
            binary_coeff = coeffs[0];
            pos_or_neg_var = vars[1];
         }
         else
         {
            if( minmax_data->var_bin == nullptr )
               minmax_data->var_bin = vars[1];

            assert( minmax_data->var_bin == vars[1] );
            binary_coeff = coeffs[1];
            pos_or_neg_var = vars[0];
         }

         assert( binary_coeff > 0. || binary_coeff < 0. );

         if( binary_coeff > 0. )
         {
            minmax_data->max_cons = cons;
            minmax_data->var_neg = pos_or_neg_var;
         }
         else
         {
            minmax_data->min_cons = cons;
            minmax_data->var_pos = pos_or_neg_var;
         }

      }
      else if( std::strcmp( SCIPconshdlrGetName( SCIPconsGetHdlr( cons ) ), "varbound" ) == 0 )
      {
         SCIPdebugMessage( "found min or max varbound cons\n" );
         SCIP_VAR *var = SCIPgetVbdvarVarbound( scip_, cons );
         SCIP_Real c = SCIPgetVbdcoefVarbound( scip_, cons );
         assert( SCIPvarIsBinary( var ) );
         assert( c > 0. || c < 0. );

         if( c > 0. )
         {
            SCIPdebugMessage( "Found max cons\n" );
            minmax_data->max_cons = cons;

            if( minmax_data->var_bin == nullptr )
               minmax_data->var_bin = var;

            minmax_data->var_neg = SCIPgetVarVarbound( scip_, cons );
            assert( minmax_data->var_bin == var );
         }
         else
         {
            SCIPdebugMessage( "Found min cons\n" );
            minmax_data->min_cons = cons;

            if( minmax_data->var_bin == nullptr )
               minmax_data->var_bin = var;

            minmax_data->var_pos = SCIPgetVarVarbound( scip_, cons );
            assert( minmax_data->var_bin == var );
         }
      }

      return SCIP_OKAY;
   }

   case SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS:
      algebraicBuilder_.add( sdVarId, SDVariable( time, level, forwardVar, cons ) );
      return SCIP_OKAY;

   default:
      assert( false );
      return SCIP_ERROR;
   }
}

SCIP_RETCODE SDproblemStructureV1::addExplicitDifferential( SCIP_CONS *cons, SCIP_VAR *explicitVar, int index, unsigned int time, int sdVarId )
{
   //set level to sdVarId to define order of states by id
   explDiffBuilder_.add( sdVarId, SDVariable( time, sdVarId, explicitVar, cons ) );

   return SCIP_OKAY;
}

int SDproblemStructureV1::startTimeIteration()
{
   return ( currentTime_ = 0 );
}

int SDproblemStructureV1::startTimeIteration(int time)
{
   return ( currentTime_ = time );
}

bool SDproblemStructureV1::timesLeft()
{
   return (int) currentTime_ != ( explDiff_.end() - 1 )->getTime() + 1;
}

unsigned int SDproblemStructureV1::incrementTime()
{
   return ++currentTime_;
}

unsigned int SDproblemStructureV1::getCurrentTime()
{
   return currentTime_;
}

unsigned int SDproblemStructureV1::getLastTime()
{
   return ( explDiff_.end() - 1 )->getTime();
}

void SDproblemStructureV1::startDiffConsIteration()
{
   explDiffIt_ = explDiff_.begin() + ( nStates_ * currentTime_ );

   //initial entry may contain no constraint because bounds are used to set the initial value
   while( diffConsLeft() && getDiffConsCons() == nullptr )
      ++explDiffIt_;
}

void SDproblemStructureV1::startDiffConsIteration( unsigned int time )
{
   explDiffIt_ = explDiff_.begin() + ( nStates_ * time );

   while( diffConsLeft( time ) && getDiffConsCons() == nullptr )
      ++explDiffIt_;

}

bool SDproblemStructureV1::diffConsLeft()
{
   return explDiffIt_ != explDiff_.begin() + ( currentTime_ + 1 ) * nStates_;
}

bool SDproblemStructureV1::diffConsLeft( unsigned int time )
{
   return explDiffIt_ != explDiff_.begin() + ( time + 1 ) * nStates_;
}

void SDproblemStructureV1::incrementDiffCons()
{
   ++explDiffIt_;
}

SCIP_VAR *SDproblemStructureV1::getDiffConsVar()
{
   return explDiffIt_->getScipVariable();
}

unsigned int SDproblemStructureV1::getNStates()
{
   return nStates_;
}

unsigned int SDproblemStructureV1::getNControls()
{
   return nControls_;
}

unsigned int SDproblemStructureV1::getNAlgebraic()
{
   return nAlgebraic_;
}

std::vector< SCIP_VAR * > SDproblemStructureV1::getDiffConsLastVars( int n )
{
   SDVariable *end = explDiffIt_->getNext();
   SDVariable *nthVar = &( *explDiffIt_ );

   //walk back n times
   int i;

   for( i = 1; i <= n; ++i )
   {
      SDVariable *prev = nthVar->getPrev();

      if( prev == nullptr )
         break;

      nthVar = prev;
   }

   //build vector with vars from nthVar until end is reached
   std::vector<SCIP_VAR *> vars;
   vars.reserve( i + 1 );

   while( nthVar != end )
   {
      vars.emplace_back( getTransVar(scip_, nthVar->getScipVariable()) );
      nthVar = nthVar->getNext();
   }

   return vars;
}

SCIP_CONS *SDproblemStructureV1::getDiffConsCons()
{
   return explDiffIt_->getScipConstraint();
}

void SDproblemStructureV1::startLevelIteration()
{

   algebraicIt_ = algebraic_.begin() + ( currentTime_ * nAlgebraic_ );
}

void SDproblemStructureV1::startLevelIteration( unsigned int time )
{
   algebraicIt_ = algebraic_.begin() + ( time * nAlgebraic_ );
}

bool SDproblemStructureV1::levelsLeft()
{
   return algebraicIt_ != ( algebraic_.begin() + ( ( currentTime_ + 1 ) * nAlgebraic_ ) );
}

bool SDproblemStructureV1::levelsLeft( unsigned int time )
{
   return algebraicIt_ != ( algebraic_.begin() + ( ( time + 1 ) * nAlgebraic_ ) );
}

void SDproblemStructureV1::incrementLevel()
{
   ++algebraicIt_;
}

int SDproblemStructureV1::getCurrentLevel()
{
   return algebraicIt_ - algebraic_.begin() - nAlgebraic_ * algebraicIt_->getTime();
}

void SDproblemStructureV1::startLevelConsIteration()
{
   if( algebraicIt_ == algebraic_.end() )
   {
      levelLeft_ = 0;
      return;
   }

   switch( getCurrentLevelType() )
   {
   case SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS:
      levelLeft_ = 1;
      break;

   case SDproblemStructureInterface::MIN:
   case SDproblemStructureInterface::MAX:
      levelLeft_ = 3;
      break;

   case SDproblemStructureInterface::SOS2_LOOKUP:
   default:
      assert( false );
   }
}

bool SDproblemStructureV1::levelConsLeft()
{
   return levelLeft_;
   //return algebraicConsLeft( currentTime_ );
}

void SDproblemStructureV1::incrementLevelCons()
{
   --levelLeft_;
}

SCIP_CONS *SDproblemStructureV1::getCurrentLevelConsCons()
{
   SDCons &cons = algebraicIt_->getConstraint();

   switch( getCurrentLevelType() )
   {
   case SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS:
      return cons.getScipTopLevelCons();

   case SDproblemStructureInterface::MIN:
   case SDproblemStructureInterface::MAX:
   {
      SDConstMinMax *minmax = cons.getSDConstMinMaxConsData();

      switch( levelLeft_ )
      {
      case 3:
         return minmax->max_cons;

      case 2:
         return minmax->min_cons;

      case 1:
         return minmax->splitter;

      default:
         assert( false );
         return nullptr;
      }
      break;
   }
   default:
      assert( false );
      return nullptr;
   }
}

SCIP_VAR *SDproblemStructureV1::getCurrentLevelConsVar()
{
   //TODO: This might return the same variable three times, if this is a SDproblemStructureInterface::MIN or max constraint
   return getTransVar(scip_, algebraicIt_->getScipVariable());
}

SCIP_VAR *SDproblemStructureV1::getCurrentLevelConsOrigVar()
{
   //TODO: This might return the same variable three times, if this is a SDproblemStructureInterface::MIN or max constraint
   return algebraicIt_->getScipVariable();
}

bool SDproblemStructureV1::currentLevelConsHasVar()
{
   return algebraicIt_->getScipVariable() != nullptr;
}

std::pair< unsigned int, unsigned int > SDproblemStructureV1::getVarTimes( SCIP_VAR *var )
{
   auto varIt = backwardDiffVarMap_.find( var );

   if( varIt != backwardDiffVarMap_.end() )
   {
      int varTime = varIt->second->getTime();
      return { varTime, varTime };
   }

   varIt = backwardAlgebraicVarMap_.find( var );

   if( varIt != backwardAlgebraicVarMap_.end() )
   {
      int varTime = varIt->second->getTime();
      return { varTime, varTime };
   }

   auto ctrlIt = backwardCtrlMap_.find( var );

   if( ctrlIt != backwardCtrlMap_.end() )
   {
      SDControl *ctrl = ctrlIt->second;
      return { ctrl->getTimeBegin(), ctrl->getTimeEnd() - 1 };
   }

   throw std::runtime_error( "Given SCIP_VAR not found in problem structure" );
}
SCIP_VAR *SDproblemStructureV1::getNext( SCIP_VAR *var )
{
   auto varIt = backwardDiffVarMap_.find( var );

   if( varIt != backwardDiffVarMap_.end() )
   {
      SDVariable *nextVar = varIt->second->getNext();
      return nextVar != nullptr ? getTransVar(scip_, nextVar->getScipVariable()) : nullptr;
   }

   varIt = backwardAlgebraicVarMap_.find( var );

   if( varIt != backwardAlgebraicVarMap_.end() )
   {
      SDVariable *nextVar = varIt->second->getNext();
      return nextVar != nullptr ? getTransVar(scip_, nextVar->getScipVariable()) : nullptr;
   }

   auto ctrlIt = backwardCtrlMap_.find( var );

   if( ctrlIt != backwardCtrlMap_.end() )
   {
      SDControl *nextCtrl = ctrlIt->second->getNext();
      return nextCtrl != nullptr ? getTransVar(scip_, nextCtrl->getScipVariable()) : nullptr;
   }

   throw std::runtime_error( "Given SCIP_VAR not found in problem structure" );
}

SCIP_VAR *SDproblemStructureV1::getPrevious( SCIP_VAR *var )
{
   auto varIt = backwardDiffVarMap_.find( var );

   if( varIt != backwardDiffVarMap_.end() )
   {
      SDVariable *prevVar = varIt->second->getPrev();
      return prevVar != nullptr ? getTransVar(scip_, prevVar->getScipVariable()) : nullptr;
   }

   varIt = backwardAlgebraicVarMap_.find( var );

   if( varIt != backwardAlgebraicVarMap_.end() )
   {
      SDVariable *prevVar = varIt->second->getPrev();
      return prevVar != nullptr ? getTransVar(scip_, prevVar->getScipVariable()) : nullptr;
   }

   auto ctrlIt = backwardCtrlMap_.find( var );

   if( ctrlIt != backwardCtrlMap_.end() )
   {
      SDControl *prevCtrl = ctrlIt->second->getPrev();
      return prevCtrl != nullptr ? getTransVar(scip_, prevCtrl->getScipVariable()) : nullptr;
   }

   throw std::runtime_error( "Given SCIP_VAR not found in problem structure" );
}

unsigned int SDproblemStructureV1::getConsTime( SCIP_VAR *var )
{
   auto varIt = backwardDiffVarMap_.find( var );

   if( varIt != backwardDiffVarMap_.end() )
   {
      SDVariable *_var = varIt->second;
      return _var->getTime();
   }

   varIt = backwardAlgebraicVarMap_.find( var );

   if( varIt != backwardAlgebraicVarMap_.end() )
   {
      SDVariable *_var = varIt->second;
      return _var->getTime();
   }

   //TODO: Assuming that calling getConsTime(v) for a control variable v is wrong usage of the interface

   throw std::runtime_error( "Given SCIP_VAR not found in problem structure" );
}

void SDproblemStructureV1::startCutIteration()
{
   cutsIt_ = propCuts_[currentTime_].begin();
}

void SDproblemStructureV1::startCutIteration( unsigned int time )
{
   cutsIt_ = propCuts_[time].begin();
}

bool SDproblemStructureV1::cutsLeft()
{
   return cutsIt_ != propCuts_[currentTime_].end();
}

bool SDproblemStructureV1::cutsLeft( unsigned int time )
{
   return cutsIt_ != propCuts_[time].end();
}

void SDproblemStructureV1::incrementCut()
{
   ++cutsIt_;
}

SCIP_CONS *SDproblemStructureV1::getCut()
{
   return *cutsIt_;
}

SDproblemStructureInterface::SD_CONS_TYPE SDproblemStructureV1::getCurrentLevelType()
{
   assert( algebraicIt_ != algebraic_.end() );
   SDCons &cons = algebraicIt_->getConstraint();
   SDConsType type = cons.getType();

   switch( type )
   {
   case SDConsType::CONST_MIN:
      return SDproblemStructureInterface::MIN;

   case SDConsType::CONST_MAX:
      return SDproblemStructureInterface::MAX;

   case SDConsType::SIMPLE:
      return SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS;

   default:
      SCIPerrorMessage( "unknown constraint type %i\n", type );
      return SDproblemStructureInterface::DEFAULT_ALGEBRAIC_CONS;
   }
}

void SDproblemStructureV1::startVarIteration()
{
   explDiffIt_ = explDiff_.begin() + nStates_ * currentTime_;
   varIterState = SDproblemStructureInterface::STATE;
   levelLeft_ = 3;

   if( varsLeft() && getCurrentVar().getScipVariable() == nullptr )
      incrementVar();
}

bool SDproblemStructureV1::varsLeft()
{
   return varIterState != SDproblemStructureInterface::ALGEBRAIC || algebraicIt_ != algebraic_.begin() + ( currentTime_ + 1 ) * nAlgebraic_;
}

void SDproblemStructureV1::incrementVar()
{
   do
   {
      switch( varIterState )
      {
      case SDproblemStructureInterface::STATE:
      {
         ++explDiffIt_;
         const auto current_time_end = explDiff_.begin() + ( currentTime_ + 1 ) * nStates_;

         if( explDiffIt_ == current_time_end )
         {
            varIterState = SDproblemStructureInterface::ALGEBRAIC;
            algebraicIt_ = algebraic_.begin() + currentTime_ * nAlgebraic_;
         }

         break;
      }

      case SDproblemStructureInterface::ALGEBRAIC:
         switch( algebraicIt_->getConstraint().getType() )
         {
         case SDConsType::SIMPLE:
            ++algebraicIt_;
            break;

         case SDConsType::CONST_MIN:
         case SDConsType::CONST_MAX:
            --levelLeft_;

            if( !levelLeft_ )
            {
               levelLeft_ = 3;
               ++algebraicIt_;
            }

            break;

         default:
            assert( false );
         }

         break;

      case SDproblemStructureInterface::CONTROL:
         assert( false );
      }
   }
   while( varsLeft() && getCurrentVar().getScipVariable() == nullptr );
}

SDVarBasic SDproblemStructureV1::getCurrentVar()
{
   switch( varIterState )
   {
   case SDproblemStructureInterface::STATE:
   {
      SDVariable &var = *explDiffIt_;
      return SDVarBasic( var.getScipVariable(), var.getTime(), SDproblemStructureInterface::STATE );
   }

   default:
   case SDproblemStructureInterface::ALGEBRAIC:
   {
      SDVariable &var = *algebraicIt_;

      if( var.getConstraint().getType() == SDConsType::SIMPLE )
         return SDVarBasic( var.getScipVariable(), var.getTime(), SDproblemStructureInterface::ALGEBRAIC );

      if( var.getConstraint().getType() == SDConsType::CONST_MIN || var.getConstraint().getType() == SDConsType::CONST_MAX )
      {
         SDConstMinMax *minmax = var.getConstraint().getSDConstMinMaxConsData();

         switch( levelLeft_ )
         {
         case 3:
            return SDVarBasic( minmax->var_bin, var.getTime(), SDproblemStructureInterface::ALGEBRAIC );

         case 2:
            return SDVarBasic( minmax->var_neg, var.getTime(), SDproblemStructureInterface::ALGEBRAIC );

         case 1:
            return SDVarBasic( minmax->var_pos, var.getTime(), SDproblemStructureInterface::ALGEBRAIC );
         }
      }

      assert( false );
      return SDVarBasic();
   }
   }
}
std::vector< std::string > SDproblemStructureV1::getStateVarNames()
{
   return stateVarNames_;
}
std::vector< std::string > SDproblemStructureV1::getControlVarNames()
{
   return controlVarNames_;
}
void SDproblemStructureV1::setStateVarNames( std::vector< std::string > stateVarNames )
{
   stateVarNames_ = std::move( stateVarNames );
}
void SDproblemStructureV1::setControlVarNames( std::vector< std::string > controlVarNames )
{
   controlVarNames_ = std::move( controlVarNames );
}
SCIP_EXPR **SDproblemStructureV1::getXdot()
{
   return xdot_.data();
}

SCIP_EXPR** SDproblemStructureV1::getAlgebraicExpressions()
{
   return algebraicExpr_.data();
}
SCIP_Real *SDproblemStructureV1::getXdotParams( int time )
{
   return &xdotParams_[time * nParamsPerTime_];
}

int SDproblemStructureV1::getNParamsPerTime() {
   return nParamsPerTime_;
}


void SDproblemStructureV1::setXdotParams( std::vector< SCIP_Real > xdotParams, unsigned int nParamsPerTime )
{
   xdotParams_ = std::move( xdotParams );
   nParamsPerTime_ = nParamsPerTime;
}
void SDproblemStructureV1::setXdot( std::vector< SCIP_EXPR * > xdot )
{
   xdot_ = std::move( xdot );
}
void SDproblemStructureV1::startControlVarIteration()
{
   controlIt_ = std::lower_bound( control_.begin(), control_.end(), currentTime_ );
   controlItEnd_ = std::upper_bound( controlIt_, control_.end(), currentTime_ );
}
void SDproblemStructureV1::startControlVarIteration( unsigned int time )
{
   controlIt_ = std::lower_bound( control_.begin(), control_.end(), time );
   controlItEnd_ = std::upper_bound( controlIt_, control_.end(), time );
}
bool SDproblemStructureV1::controlVarsLeft()
{
   return controlIt_ != controlItEnd_;
}
bool SDproblemStructureV1::controlVarsLeft( unsigned int time )
{
   return controlIt_ != controlItEnd_;
}
void SDproblemStructureV1::incrementControlVar()
{
   ++controlIt_;
}
SCIP_VAR *SDproblemStructureV1::getControlVar()
{
   return getTransVar(scip_, controlIt_->getScipVariable());
}
void SDproblemStructureV1::startControlVarAtTIteration()
{
   controlIt_ = std::lower_bound( control_.begin(), control_.end(), currentTime_, SDControl::CompareTime() );
   controlItEnd_ = std::upper_bound( controlIt_, control_.end(), currentTime_, SDControl::CompareTime() );
}
void SDproblemStructureV1::startControlVarAtTIteration( unsigned int time )
{
   controlIt_ = std::lower_bound( control_.begin(), control_.end(), time, SDControl::CompareTime() );
   controlItEnd_ = std::upper_bound( controlIt_, control_.end(), time, SDControl::CompareTime() );
}
bool SDproblemStructureV1::controlVarsAtTLeft()
{
   return controlIt_ != controlItEnd_;
}
bool SDproblemStructureV1::controlVarsAtTLeft( unsigned int time )
{
   return controlIt_ != controlItEnd_;
}
void SDproblemStructureV1::incrementControlVarAtT()
{
   ++controlIt_;
}
SCIP_VAR *SDproblemStructureV1::getControlVarAtT()
{
   return getTransVar(scip_, controlIt_->getScipVariable());
}

SCIP_VAR *SDproblemStructureV1::getControlVarAtTOrig()
{
   return controlIt_->getScipVariable();
}

SCIP_VAR *SDproblemStructureV1::getNthsControlVar( unsigned int n )
{
   return getTransVar(scip_, control_[n].getScipVariable());
}
void SDproblemStructureV1::startStateVarIteration()
{
   explDiffIt_ = explDiff_.begin() + currentTime_ * nStates_;
}
bool SDproblemStructureV1::stateVarsLeft()
{
   return explDiffIt_ != explDiff_.begin() + ( currentTime_ + 1 ) * nStates_;
}
void SDproblemStructureV1::incrementStateVar()
{
   ++explDiffIt_;
}
SCIP_VAR *SDproblemStructureV1::getCurrentStateVar()
{
   return getTransVar(scip_, explDiffIt_->getScipVariable());
}

SCIP_VAR *SDproblemStructureV1::getCurrentStateVarOrig()
{
   return explDiffIt_->getScipVariable();
}

int SDproblemStructureV1::getCurrentStateVarId()
{
   return explDiffIt_ - (explDiff_.begin() + currentTime_ * nStates_);
}

void SDproblemStructureV1::setTfinal(SCIP_Real _tfinal)
{
   this->tfinal = _tfinal;
}
void SDproblemStructureV1::setTinit(SCIP_Real _tinit)
{
   this->tinit = _tinit;
}
SCIP_Real SDproblemStructureV1::getTfinal()
{
   return tfinal;
}
SCIP_Real SDproblemStructureV1::getTinit()
{
   return tinit;
}
SCIP_Real SDproblemStructureV1::getTstep()
{
   return tstep;
}
void SDproblemStructureV1::setTstep(SCIP_Real _tstep)
{
   this->tstep = _tstep;
}

SCIP_Real *SDproblemStructureV1::getXdotParams(SCIP_Real time)
{
   int t(SCIPepsilon(scip_) + (time - tinit) / tstep );
   return getXdotParams(t);
}
SCIP_RETCODE SDproblemStructureV1::setIsTransformed(bool _isReformulated)
{
   if( isTranformed_ )
      return SCIP_OKAY;

   isTranformed_ = true;
   std::vector<std::pair<SCIP_VAR *, SDVariable *>> vec;
   for( const auto & entry : backwardDiffVarMap_ )
      vec.emplace_back(SCIPvarGetTransVar(entry.first), entry.second);

   backwardDiffVarMap_.insert(vec.begin(), vec.end());

   vec.clear();

   for( const auto & entry : backwardAlgebraicVarMap_ )
      vec.emplace_back(SCIPvarGetTransVar(entry.first), entry.second);

   backwardAlgebraicVarMap_.insert(vec.begin(), vec.end());

   std::vector<std::pair<SCIP_VAR *, SDControl *>> ctrlvec;

   for( const auto & entry : backwardCtrlMap_ )
      ctrlvec.emplace_back(SCIPvarGetTransVar(entry.first), entry.second);

   backwardCtrlMap_.insert(ctrlvec.begin(), ctrlvec.end());
   return SCIP_OKAY;
}
bool SDproblemStructureV1::isTranformed() const
{
   return isTranformed_;
}
void SDproblemStructureV1::setAlgebraicExpressions( std::vector< SCIP_EXPR * > algebraicExpr )
{
   algebraicExpr_ = std::move( algebraicExpr );
}
std::vector< std::string > SDproblemStructureV1::getAlgebraicVarNames()
{
   return algebraicVarNames_;
}
void SDproblemStructureV1::setAlgebraicVarNames( std::vector< std::string > algebraicVarNames )
{
   algebraicVarNames_ = std::move( algebraicVarNames );
}
void SDproblemStructureV1::setXdotAlgebraic(std::vector< SCIP_EXPR * > xdotAlgebraic)
{
   xdotAlgebraic_ = std::move(xdotAlgebraic);
}
SCIP_EXPR **SDproblemStructureV1::getXdotAlgebraic()
{
   return xdotAlgebraic_.data();
}
SDproblemStructureInterface::BoundMap SDproblemStructureV1::getStrictBounds()
{
   return boundMap_;
}
void SDproblemStructureV1::setStrictBounds(SDproblemStructureInterface::BoundMap boundMap)
{
   boundMap_ = std::move(boundMap);
   //boundMap_ = boundMap;
}

} /* namespace sdscip */
