#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#*                                                                           *
#*                  This file is part of the program and library             *
#*         SCIP --- Solving Constraint Integer Programs                      *
#*                                                                           *
#*    Copyright (C) 2002-2012 Konrad-Zuse-Zentrum                            *
#*                            fuer Informationstechnik Berlin                *
#*                                                                           *
#*  SCIP is distributed under the terms of the ZIB Academic Licence.         *
#*                                                                           *
#*  You should have received a copy of the ZIB Academic License              *
#*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      *
#*                                                                           *
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

#@file    Makefile
#@brief   Makefile for C++ TSP example using SCIP as a callable library
#@author  Thorsten Koch
#@author  Tobias Achterberg
#@author  Marc Pfetsch


#-----------------------------------------------------------------------------
# paths
#-----------------------------------------------------------------------------

SCIPDIR         =       ../..


#-----------------------------------------------------------------------------
# include default project Makefile from SCIP
#-----------------------------------------------------------------------------
include $(SCIPDIR)/make/make.project




#-----------------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------------

MAINNAME	=	sdscip
MAINSRCPATH	=	cppmain.cpp \
			PresolCppMin.cpp \
			GomoryHuTree.cpp \
			ProbDataTSP.cpp \
			ProbDataCtrl.cpp \
			NLPGraph.cpp \
			PresolConsGraph.cpp \
			reader_osilc.c \
			MdlExpressionTranslator.cpp \
			ReaderVOP.cpp \
			ExprLookup.cpp \
			ProbDataSD.cpp \
			ConshdlrCtrlDifferential.cpp \
			HeurSimODE.cpp \
			PropODE.cpp \
			ODEintegrator.cpp \
			PointODEintegrator.cpp \
			ReduceODEintegrator.cpp \
			IntervalODEintegrator.cpp \
			TestSDplugin.cpp \
			TestExprPiecewiseLinear.cpp \
			TestEstimatorTypes.cpp \
			TestODEintegrator.cpp \
			TestSBrateEvaluator.cpp \
			TestBoundMap.cpp \
			ConstRateEvaluator.cpp \
			SimRateEvaluator.cpp \
			SBrateEvaluator.cpp \
			PointRateEvaluator.cpp \
			BranchControlFirst.cpp \
			PropagationPattern.cpp \
			Orthant.cpp \
			OrthantList.cpp \
			HyperCube.cpp \
			HyperPlane.cpp \
			Vector.cpp \
			Point.cpp \
			Line.cpp \
			Statistics.cpp \
			TestGeom.cpp \
			SDproblemStructureInterface.cpp \
			BoundMapHelpers.cpp \
			SDproblemStructure.cpp \
			SDproblemStructureV1.cpp \
			SDproblemStructureFactory.cpp \
			SDVarBasic.cpp \
			SDCons.cpp\
			ExprPiecewiseLinear.cpp

MAINSRC		= 	$(addprefix $(SRCDIR)/,$(MAINSRCPATH))

MAINOBJ		=  	$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(MAINSRCPATH)))

MAINDEP		=	$(SRCDIR)/depend.cppmain.$(OPT)

MAIN		=	$(MAINNAME).$(BASE).$(LPS)$(EXEEXTENSION)
MAINFILE	=	$(BINDIR)/$(MAIN)
MAINSHORTLINK	=	$(BINDIR)/$(MAINNAME)
MAINOBJFILES	=	$(addprefix $(OBJDIR)/,$(MAINOBJ))

VERBOSE = true

#-----------------------------------------------------------------------------
# Include Lemon
#-----------------------------------------------------------------------------
#FLAGS         +=    -I /home/bzfvierh/lib/lemon/include -L /home/bzfvierh/lib/lemon/lib -lemon
FLAGS         +=    -I $(HOME)/lib/lemon/include -L $(HOME)/lib/lemon/lib -I $(HOME)/lib/sdotools/include -lemon -msse4.1 -std=c++11
LDFLAGS       +=    -lpthread -lboost_regex -lboost_system -lboost_filesystem -lboost_serialization -L$(HOME)/lib/sdotools/lib -lsdo -lcpplsq -lboost_locale -lblas -fopenmp


#-----------------------------------------------------------------------------
# Rules
#-----------------------------------------------------------------------------

ifeq ($(VERBOSE),false)
.SILENT:	$(MAINFILE) $(MAINOBJFILES) $(MAINSHORTLINK)
endif

.PHONY: all
all:   		$(SCIPDIR) $(MAINFILE) $(MAINSHORTLINK)

.PHONY: lint
lint:		$(MAINSRC)
		-rm -f lint.out
		$(SHELL) -ec 'for i in $^; \
			do \
			echo $$i; \
			$(LINT) lint/$(MAINNAME).lnt +os\(lint.out\) -u -zero \
			$(FLAGS) -UNDEBUG -UWITH_READLINE -UROUNDING_FE $$i; \
			done'

.PHONY: scip
scip:
		@$(MAKE) -C $(SCIPDIR) libs $^

.PHONY: doc
doc:
		@-(cd doc && ln -fs ../$(SCIPDIR)/doc/scip.css);
		@-(cd doc && ln -fs ../$(SCIPDIR)/doc/pictures/scippy.png);
		@-(cd doc && ln -fs ../$(SCIPDIR)/doc/pictures/miniscippy.png);
		@-(cd doc && ln -fs ../$(SCIPDIR)/doc/scipfooter.html footer.html);
		cd doc; $(DOXY) $(MAINNAME).dxy

.PHONY: test
test:           $(MAINFILE)
		@-(cd check && ln -fs ../$(SCIPDIR)/check/check.sh);
		@-(cd check && ln -fs ../$(SCIPDIR)/check/evalcheck.sh);
		@-(cd check && ln -fs ../$(SCIPDIR)/check/check.awk);
		@-(cd check && ln -fs ../$(SCIPDIR)/check/getlastprob.awk);
		cd check; \
		$(SHELL) ./check.sh $(TEST) $(MAINFILE) $(SETTINGS) $(notdir $(MAINFILE)).$(HOSTNAME) $(TIME) $(NODES) $(MEM) $(THREADS) $(FEASTOL) $(DISPFREQ) $(CONTINUE) $(LOCK) $(VERSION) $(LPS);

$(MAINSHORTLINK):	$(MAINFILE)
		@rm -f $@
		cd $(dir $@) && ln -s $(notdir $(MAINFILE)) $(notdir $@)

$(OBJDIR):
		@-mkdir -p $(OBJDIR)

$(BINDIR):
		@-mkdir -p $(BINDIR)

.PHONY: clean
clean:		$(OBJDIR)
ifneq ($(OBJDIR),)
		-rm -f $(OBJDIR)/*.o
		-rmdir $(OBJDIR)
endif
		-rm -f $(MAINFILE)

.PHONY: depend
depend:		$(SCIPDIR)
		$(SHELL) -ec '$(DCXX) $(FLAGS) $(DFLAGS) $(MAINSRC) \
		| sed '\''s|^\([0-9A-Za-z\_]\{1,\}\)\.o *: *$(SRCDIR)/\([0-9A-Za-z\_]*\).cpp|$$\(OBJDIR\)/\2.o: $(SRCDIR)/\2.cpp|g'\'' \
		>$(MAINDEP)'

-include	$(MAINDEP)

$(MAINFILE):	$(BINDIR) $(OBJDIR) $(SCIPLIBFILE) $(LPILIBFILE) $(NLPILIBFILE) $(MAINOBJFILES)
		@echo "-> linking $@"
		$(LINKCXX) $(MAINOBJFILES) \
		$(LINKCXX_L)$(SCIPDIR)/lib $(LINKCXX_l)$(SCIPLIB)$(LINKLIBSUFFIX) \
                $(LINKCXX_l)$(OBJSCIPLIB)$(LINKLIBSUFFIX) $(LINKCXX_l)$(LPILIB)$(LINKLIBSUFFIX) $(LINKCXX_l)$(NLPILIB)$(LINKLIBSUFFIX) \
                $(OFLAGS) $(LPSLDFLAGS) \
		$(LDFLAGS) $(LINKCXX_o)$@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		@echo "-> compiling $@"
		$(CC) $(FLAGS) $(OFLAGS) $(BINOFLAGS) $(CFLAGS) -c $< $(CC_o)$@

$(OBJDIR)/%.o:	CXXFLAGS := $(filter-out -std=c++0x,$(CXXFLAGS))
$(OBJDIR)/%.o:  $(SRCDIR)/%.cpp
		@echo "-> compiling $@"
		$(CXX) $(OFLAGS) $(BINOFLAGS) $(CXXFLAGS)  $(FLAGS) -c $< $(CXX_o)$@

#---- EOF --------------------------------------------------------------------
