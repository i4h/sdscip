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

# $(info $$SCIPDIR is ${SCIPDIR})

#-----------------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------------

MAINNAME	=	sdscip
MAINSRCPATH	=	cppmain.cpp \
			PresolCppMin.cpp \
			ProbDataCtrl.cpp \
			NLPGraph.cpp \
			PresolConsGraph.cpp \
			reader_osilc.c \
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
		$(CONTINUE) $(LOCK) "example" $(LPS) $(VALGRIND) $(CLIENTTMPDIR) $(REOPT) $(OPTCOMMAND) $(SETCUTOFF) $(MAXJOBS) $(VISUALIZE);


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
