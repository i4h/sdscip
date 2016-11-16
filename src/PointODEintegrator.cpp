//#define SCIP_DEBUG
//#define SCIP_DBG

/*
 * PointODEintegrator.cpp
 *
 *  Created on: 10.09.2015
 *      Author: bzfvierh
 */


#include "PointODEintegrator.h"
#include "PointRateEvaluator.h"


namespace sdscip
{

PointODEintegrator::PointODEintegrator(SCIP* _scip, std::string _discretization, SCIP_Real _dt, int _nIntermediateSteps, int _nStates, int _nAlgebraic, int _nControls, PointRateEvaluator::POINT_RATE_EVALUATOR_TYPE _rateEvalType) :
      ODEintegrator(_scip,_discretization, _dt, _nIntermediateSteps, _nStates, _nAlgebraic, _nControls)
      ,tAlgebraic_(0)
{
   varValues_.resize(_nStates + _nControls + _nAlgebraic, 0);
   endControls_.resize(nControls_);

   /* Factory to get selected rate Evaluator */
   SimRateEvaluator* temp;
   switch (_rateEvalType)
   {
   case PointRateEvaluator::RATE_EVALUATOR_CONST :
      rateEvaluator_ = CopyablePointer<PointRateEvaluator>(new ConstRateEvaluator(_nStates, _nAlgebraic, _nControls, _scip));
      break;
   case PointRateEvaluator::RATE_EVALUATOR_SIM :

      temp  = new SimRateEvaluator(_nStates, _nAlgebraic, _nControls, _scip);
      SCIPdbgMsg("created simrateevaluator, name is %s\n", temp->getName().c_str());

      //rateEvaluator_ = CopyablePointer<PointRateEvaluator>(new SimRateEvaluator(_nStates, _nAlgebraic, _nControls, _scip));
      rateEvaluator_ = CopyablePointer<PointRateEvaluator>(temp);
      SCIPdbgMsg("horrido\n");
      SCIPdbgMsg("created copyablepointer, states is %i\n", temp->nStates_);


      SCIPdbgMsg("created copyablepointer, name is %s\n", temp->getName().c_str());

      break;
   /* Add more Evaluators here */
   default:
      SCIPerrorMessage("Rate Evaluator type %i does not exist\n", _rateEvalType);
   }
   SCIPdebugMessage("Constructed PointODEintegrator, using %s, dt = %f, intermediateSteps = %i, nStates = %i, nControls = %i\n"
      ,discretization_.c_str()
      ,dt_
      ,nIntermediateSteps_
      ,nStates_
      ,nControls_);
}

#if 0
PointODEintegrator::~PointODEintegrator()
{
   SCIPdbgMsg("Destructing PointODEintegrator with %i states, deleting rateEvaluator_ at %i\n", nStates_, std::string(rateEvaluator_).c_str());
   delete rateEvaluator_;
}




PointODEintegrator::PointODEintegrator(const ODEintegrator &integrator )
     : ODEintegrator(integrator)
{
   std::cout << "copy constructor for base \n" << std::endl << std::flush;
}

PointODEintegrator::PointODEintegrator(const PointODEintegrator& integrator)
      : ODEintegrator(integrator)
{
   std::cout << "copy constructor !\n" << std::endl << std::flush;


}

PointODEintegrator& PointODEintegrator::operator=(PointODEintegrator &&)
{
   std::cout << "move failed!\n" << std::endl << std::flush;
}

PointODEintegrator& PointODEintegrator::operator=(const PointODEintegrator& integrator)
{
   std::cout << "assignment operator!\n" << std::endl << std::flush;

   ODEintegrator::operator=(integrator);
   varValues_ = integrator.varValues_;
   tAlgebraic_ = integrator.tAlgebraic_;
   endControls_ = integrator.endControls_;

   //rateEvaluator = new PointRateEvaluator
   //PointRateEvaluator* rateEvaluator_;
   //std::vector<SCIP_Real> ; /* To be used in the integration step */


   std::cout << "assignment failed!\n" << std::endl << std::flush;
}

#endif

CopyablePointer<PointRateEvaluator> PointODEintegrator::rateEvaluator()
{
   SCIPdbgMsg("returning rateEvaluator with name %s\n",rateEvaluator_->getName().c_str());
   return rateEvaluator_;
}

std::string PointODEintegrator::toString()
{
   /* Summarize state of integrator    */
   std::ostringstream oss;
   oss << "ODE Integrator Configuration:" << std::endl;
   oss << "# nStates = " << nStates_ << std::endl;
   oss << "# Scheme = " << discretization_ << std::endl;
   oss << "# dt = " << dt_ << std::endl;
   oss << "# intermediateSteps = " << nIntermediateSteps_ << std::endl;
   oss << "# dtIntermediate = " << dtIntermediate_<< std::endl;
   oss << "# rateEvaluator = " << rateEvaluator_->getName() << std::endl;
   oss << "ODE Integrator State:" << std::endl;
   oss << "# t = " << t_ << std::endl;
   oss << sdscip::Vector::vec2string(getStates(), std::string("# x = ")) << std::endl;
   oss << sdscip::Vector::vec2string(getControls(), std::string("# z = ")) << std::endl;
   oss << sdscip::Vector::vec2string(varValues_, std::string("# (x, z) = "));

   return oss.str();
}




std::string PointODEintegrator::statesToString()
{
   std::ostringstream oss;
   oss << "x(" << t_ << ") = (";
   int precision(8);
   for (int i = 0; i < nStates_ - 1; ++i)
   {
      oss << std::setprecision(precision) << varValues_[i] << ", ";
   }
   oss << std::setprecision(precision) << varValues_[nStates_ - 1] << ")";
   return oss.str();
}

std::string PointODEintegrator::algebraicToString()
{
   std::ostringstream oss;
   oss << "x(" << t_ << ") = (";
   int precision(8);
   for (int i = nStates_ + nControls_ ; i < nStates_ + nControls_ + nAlgebraic_ - 1; ++i)
   {
      oss << i << "-" << std::setprecision(precision) << varValues_[i] << ", ";
   }
   if (nAlgebraic_ > 0)
      oss << nStates_ + nControls_ + nAlgebraic_ - 1 << "-" << std::setprecision(precision) << varValues_[nStates_ + nControls_ + nAlgebraic_ - 1] << ")";
   return oss.str();
}


void PointODEintegrator::writeStates(std::ofstream& outFile)
{
   if( outFile.is_open())
   {
      outFile << std::setw(4) << t_ << "\t";
      for (int i = 0; i < nStates_; ++i)
         outFile << std::setw(8) << varValues_[i] << "\t";
      outFile << std::endl;
   }
}

std::string PointODEintegrator::controlsToString()
{
   std::ostringstream oss;
   oss << "x(" << t_ << ") = (";
   int precision(8);
   for (int i = nStates_; i < nStates_ + nControls_ - 1; ++i)
   {
      oss << std::setprecision(precision) << varValues_[i] << ", ";
   }

   if (nControls_ > 0)
      oss << std::setprecision(precision) << varValues_[nStates_ + nControls_ - 1] ;

   oss << ")";
   return oss.str();

}

void PointODEintegrator::printXdot()
{
   for (int i = 0; i < nStates_; ++i)
   {
      SCIPinfoMessage(scip_, NULL,"\\dot x_%i: ",i);
      SCIPexprPrint(rateEvaluator_->getXdot(i), SCIPgetMessagehdlr(scip_), NULL, NULL, NULL, NULL);
      SCIPinfoMessage(scip_, NULL,"\n");
   }
}

void PointODEintegrator::setXdots(std::vector<SCIP_EXPR*> &xDot)
{
   rateEvaluator_->setXdot(xDot);
}

void PointODEintegrator::setInitial(SCIP_Real t, std::vector<SCIP_Real> states)
{
   /* Initialize varValues (states and controls with correct number of elements) */
   varValues_ = std::vector<SCIP_Real>(nStates_ + nControls_);

   for (int i = 0; i < nStates_; ++i)
      varValues_[i] = states[i];

   t_ = t;

}

void PointODEintegrator::setInitial(SCIP_Real t, std::vector<SCIP_Real> states, std::vector<SCIP_Real> controls)
{
   /* Initialize varValues (states and controls with correct number of elements) */
   varValues_ = std::vector<SCIP_Real>(nStates_ + nControls_);

   for (int i = 0; i < nStates_; ++i)
      varValues_[i] = states[i];
   for (int i = 0; i < nControls_; ++i)
      varValues_[nStates_ + i] = controls[i];
   t_ = t;
}


std::vector<SCIP_Real> PointODEintegrator::getStates()
{
   //return states_;
   return std::vector<SCIP_Real>( varValues_.begin(), varValues_.begin() + nStates_ );
}

std::vector<SCIP_Real> PointODEintegrator::getControls()
{
   //return states_;
   return std::vector<SCIP_Real>( varValues_.begin() + nStates_, varValues_.end());
}

SCIP_Real PointODEintegrator::getState(int dim)
{
   return varValues_[dim];
}

SCIP_Real PointODEintegrator::getAlgebraic(int varId)
{
   assert(varId >= nStates_ + nControls_);
   assert(varId < nStates_ + nControls_ + nAlgebraic_);

   return varValues_[varId];
}

SCIP_Real PointODEintegrator::getControl(int varId)
{
   assert(varId >= nStates_);
   assert(varId < nStates_ + nControls_ );
   return varValues_[varId];
}


void PointODEintegrator::step()
{
   return step(NULL, NULL);
}

void PointODEintegrator::step(SCIP_Real* startParams, SCIP_Real* endParams)
{

   /* Compute values of algebraic variables at t_ */
   if (tAlgebraic_ != t_)
   {
      //SCIPdbgMsg("computing algebraic variables \n");
      rateEvaluator_->computeAlgebraic(varValues_, startParams);
      tAlgebraic_ = t_;
   }

   for (int steps = 0; steps < nIntermediateSteps_; ++steps)
   {
      /* Calculate k's successively */
      int stages = tableau_.stages();
      std::vector<std::vector<SCIP_Real> > kMatrix;

      /* k_1 is trivial */
      rateEvaluator_->getRates(t_, varValues_, startParams);
      //SCIPdbgMsg("called getRates once\n");
      kMatrix.push_back(rateEvaluator_->getRates(t_, varValues_, startParams));

      /* Calculate remaining stages */
      for (int s = 1; s < stages; ++s)
      {
         const std::vector<double>& row = *(tableau_.getRowVec(s));

         SCIP_Real newT = t_ + row[0] * dtIntermediate_;
         std::vector<double> newX(varValues_);
         for (int i = 0; i < nStates_; ++i)
         {
            for (int j = 0; j < s; ++j)
            {
               newX[i] = newX[i] + row[j+1] * dtIntermediate_ * kMatrix[j][i];
            }
         }
         if (row[0] == 1.0)
            kMatrix.push_back(rateEvaluator_->getRates(newT, newX, endParams));
         else
            kMatrix.push_back(rateEvaluator_->getRates(newT, newX, startParams));
      }

      /* Calculate next state vector using stages and last row */
      const std::vector<double>& row = *(tableau_.getRowVec(stages));
      for (int i = 0; i < nStates_; ++i)
      {
         for (int j = 0; j < stages; ++j)
         {
            varValues_[i] = varValues_[i] + row[j] * dtIntermediate_ * kMatrix[j][i];
         }
      }

      /* Move time forward */
      t_ = t_ + dtIntermediate_;
   }
}

void PointODEintegrator::computeAlgebraic(SCIP_Real* params)
{
      /* Compute values of algebraic variables at t_ */
      rateEvaluator_->computeAlgebraic(varValues_, params);
      tAlgebraic_ = t_;
}

void PointODEintegrator::setControls(const std::vector<SCIP_Interval>& controls)
{
   assert(controls.size() == std::size_t(nControls_));
   for (int i = 0; i < nControls_; ++i)
   {
      varValues_[nStates_ + i] = controls[i].inf;
   }
}

void PointODEintegrator::setEndControls(const std::vector<SCIP_Interval>& endControls)
{
   assert(endControls.size() == std::size_t(nControls_));
   for( auto it = endControls.begin(); it != endControls.end(); ++it)
      endControls_[it - endControls.begin()] = it->inf;
}

}
