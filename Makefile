#@file    Makefile
#@brief   Makefile for SD-SCIP, based on Makefiles of SCIP-SDP and SCIP's C++ TSP example 
#@author  Ingmar Vierhaus


#-----------------------------------------------------------------------------
# paths
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# include default project Makefile from SCIP
#-----------------------------------------------------------------------------

# save directory to be able to locate library files
ifeq ($(OSTYPE),mingw)
SDSCIPDIR	=	./
else
SDSCIPDIR	=	$(realpath .)
endif
SDSCIPLIBDIR	=	lib

SCIPDIR		= 	$(SDSCIPDIR)/lib/scip

SDSCIPGITHASH	=	$(shell git describe --always --dirty  | sed 's/^.*-g//')

OLDSDSCIPGITHASH = 	$(shell if test -e $(SDSCIPGITHASHFILE) ; then cat  $(SDSCIPGITHASHFILE) | sed 's/\#define SDSCIP_GITHASH //'; fi )

SDSCIPGITHASHFILE =       $(SDSCIPDIR)/src/githash.c

GITHASHCLASS     =      $(SDSCIPDIR)/src/SDSCIPgitHash.cpp


# check whether SCIPDIR exists
ifeq ("$(wildcard $(SCIPDIR))","")
$(error Please add a soft-link to the SCIP directory as $(SDSCIPDIR)/lib/scip)
endif

#-----------------------------------------------------------------------------
# include default project Makefile from SCIP
#-----------------------------------------------------------------------------
include $(SCIPDIR)/make/make.project

# include install/uninstall targets
-include make/make.install

VERSION		=	0.9.0


#-----------------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------------

MAINNAME	=	sdscip
UNITTESTNAME	=	unittest

MAINSRCPATH	=	cppmain.cpp \
			MdlExpressionTranslator.cpp \
			ReaderVOP.cpp \
			ExprLookup.cpp \
			ProbDataSD.cpp \
			PropOBRA.cpp \
			HeurSimODE.cpp \
			PropODE.cpp \
			ODEintegrator.cpp \
			PointODEintegrator.cpp \
			ReduceODEintegrator.cpp \
			IntervalODEintegrator.cpp \
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
			SDproblemStructureInterface.cpp \
			BoundMapHelpers.cpp \
			SDproblemStructure.cpp \
			SDproblemStructureV1.cpp \
			SDproblemStructureFactory.cpp \
			SDVarBasic.cpp \
			BaseTest.cpp \
			SDCons.cpp \
			SDSCIPtest.cpp \
			TestSDplugin.cpp \
			TestExprPiecewiseLinear.cpp \
			CopyablePointer.cpp\
			ExprPiecewiseLinear.cpp \
			SDSCIPgitHash.cpp 

UNITTESTSRCPATH =	unittests.cpp \
			MdlExpressionTranslator.cpp \
			ReaderVOP.cpp \
			ExprLookup.cpp \
			ProbDataSD.cpp \
			PropOBRA.cpp \
			HeurSimODE.cpp \
			PropODE.cpp \
			ODEintegrator.cpp \
			PointODEintegrator.cpp \
			ReduceODEintegrator.cpp \
			IntervalODEintegrator.cpp \
			BaseTest.cpp \
			SDSCIPtest.cpp \
			TestSDplugin.cpp \
			TestBSplineCurve.cpp \
			TestExprPiecewiseLinear.cpp \
			TestEstimatorTypes.cpp \
			TestODEintegrator.cpp \
			TestSBrateEvaluator.cpp \
			TestBoundMap.cpp \
			TestStatistics.cpp \
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
			CopyablePointer.cpp \
			ExprPiecewiseLinear.cpp \
			SDSCIPgitHash.cpp 


MAINSRC		= 	$(addprefix $(SRCDIR)/,$(MAINSRCPATH))
MAINOBJ		=  	$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(MAINSRCPATH)))
MAINDEP		=	$(SRCDIR)/depend.cppmain.$(OPT)

MAIN		=	$(MAINNAME).$(BASE).$(LPS)$(EXEEXTENSION)
MAINFILE	=	$(BINDIR)/$(MAIN)
MAINSHORTLINK	=	$(BINDIR)/$(MAINNAME)
MAINOBJFILES	=	$(addprefix $(OBJDIR)/,$(MAINOBJ))


UNITTESTSRC	= 	$(addprefix $(SRCDIR)/,$(UNITTESTSRCPATH))
UNITTESTOBJ	=  	$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(UNITTESTSRCPATH)))
UNITTESTDEP	=	$(SRCDIR)/depend.unittest.$(OPT)

UNITTEST	=	$(UNITTESTNAME).$(BASE).$(LPS)$(EXEEXTENSION)
UNITTESTFILE	=	$(BINDIR)/$(UNITTEST)
UNITTESTSHORTLINK	=	$(BINDIR)/$(UNITTESTNAME)
UNITTESTOBJFILES	=	$(addprefix $(OBJDIR)/,$(UNITTESTOBJ))


VERBOSE = true

#-----------------------------------------------------------------------------
# Include Lemon
#-----------------------------------------------------------------------------
#FLAGS         +=    -I /home/bzfvierh/lib/lemon/include -L /home/bzfvierh/lib/lemon/lib -lemon
FLAGS         +=    -I $(HOME)/lib/lemon/include -L $(HOME)/lib/lemon/lib -I $(HOME)/lib/sdotools/include -lemon -msse4.1 -std=c++11
FLAGS         +=    -Wno-shadow
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
		@-(cd doc && ln -fs $(SCIPDIR)/doc/scip.css);
		cd doc; $(DOXY) $(MAINNAME).dxy

.PHONY: githash
githash:
		@$(SHELL) -ec ' \
			if test \"$(SDSCIPGITHASH)\" != \"$(OLDSDSCIPGITHASH)\" ; then  \
				echo "#define SDSCIP_GITHASH \"$(SDSCIPGITHASH)\"" > $(SDSCIPGITHASHFILE); \
			fi ';
		@-touch $(GITHASHCLASS);

.PHONY: test
test:           $(MAINFILE)
		@-(cd check && ln -fs $(SCIPDIR)/check/check.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/evalcheck.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/evalcheck_cluster.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/check.awk);
		@-(cd check && ln -fs $(SCIPDIR)/check/getlastprob.awk);
		@-(cd check && ln -fs $(SCIPDIR)/check/configuration_set.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/configuration_logfiles.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/configuration_tmpfile_setup_scip.sh);
		@-(cd check && ln -fs $(SCIPDIR)/check/run.sh);
		cd check; \
		$(SHELL) ./check.sh $(TEST) $(MAINFILE) $(SETTINGS) $(notdir $(MAINFILE)) $(TIME) $(NODES) $(MEM) $(THREADS) $(FEASTOL) $(DISPFREQ) \
		$(CONTINUE) $(LOCK) $(VERSION) $(LPS) $(VALGRIND) $(CLIENTTMPDIR) $(REOPT) $(OPTCOMMAND) $(SETCUTOFF) $(MAXJOBS) $(VISUALIZE) $(PERMUTE) $(SEEDS) ;

unittest:           $(UNITTESTFILE) $(UNITTESTSHORTLINK)
		cd unittest; \
		../bin/unittest ;

$(MAINSHORTLINK):	$(MAINFILE)
		@rm -f $@
		cd $(dir $@) && ln -s $(notdir $(MAINFILE)) $(notdir $@)

$(UNITTESTSHORTLINK):	$(UNITTESTFILE)
		@rm -f $@
		cd $(dir $@) && ln -s $(notdir $(UNITTESTFILE)) $(notdir $@)


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
		-rm -f $(UNITTESTFILE)

.PHONY: depend
depend:		$(SCIPDIR)
		$(SHELL) -ec '$(DCXX) $(FLAGS) $(DFLAGS) $(MAINSRC) \
		| sed '\''s|^\([0-9A-Za-z\_]\{1,\}\)\.o *: *$(SRCDIR)/\([0-9A-Za-z\_]*\).cpp|$$\(OBJDIR\)/\2.o: $(SRCDIR)/\2.cpp|g'\'' \
		>$(MAINDEP)'
		$(SHELL) -ec '$(DCXX) $(FLAGS) $(DFLAGS) $(UNITTESTSRC) \
		| sed '\''s|^\([0-9A-Za-z\_]\{1,\}\)\.o *: *$(SRCDIR)/\([0-9A-Za-z\_]*\).cpp|$$\(OBJDIR\)/\2.o: $(SRCDIR)/\2.cpp|g'\'' \
		>$(UNITTESTDEP)'

-include	$(MAINDEP)
-include	$(UNITTESTDEP)


$(info $$UNITTESTDEP is [${UNITTESTDEP}])

$(MAINFILE):	githash $(BINDIR) $(OBJDIR) $(SCIPLIBFILE) $(LPILIBFILE) $(NLPILIBFILE) $(MAINOBJFILES)
		@echo "-> linking $@"
		$(LINKCXX) $(MAINOBJFILES) \
		$(LINKCXX_L)$(SCIPDIR)/lib $(LINKCXX_l)$(SCIPLIB)$(LINKLIBSUFFIX) \
                $(LINKCXX_l)$(OBJSCIPLIB)$(LINKLIBSUFFIX) $(LINKCXX_l)$(LPILIB)$(LINKLIBSUFFIX) $(LINKCXX_l)$(NLPILIB)$(LINKLIBSUFFIX) \
                $(OFLAGS) $(LPSLDFLAGS) \
		$(LDFLAGS) $(LINKCXX_o)$@

$(UNITTESTFILE):	$(BINDIR) $(OBJDIR) $(SCIPLIBFILE) $(LPILIBFILE) $(NLPILIBFILE) $(UNITTESTOBJFILES)
		@echo "-> linking $@"
		$(LINKCXX) $(UNITTESTOBJFILES) \
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
