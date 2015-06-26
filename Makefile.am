ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4 --install
AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -I$(top_srcdir)/LoopFunctions/src \
 -I$(top_srcdir)/NewPhysics/src \
 -I$(top_srcdir)/MonteCarlo/src \
 -I$(top_srcdir)/HiggsExtensions/src \
 -I$(top_srcdir)/EW/src \
 -I$(top_srcdir)/gslpp/src \
 -I$(top_srcdir)/Observables/src \
 -I$(top_srcdir)/StandardModel/src \
 -I$(top_srcdir)/ComputeObservables/src \
 -I$(top_srcdir)/InputParser/src \
 -I$(top_srcdir)/Flavour/src 

bin_PROGRAMS = ExamplesSrc/LibMode_config/analysis ExamplesSrc/LibMode_header/analysis ExamplesSrc/MonteCarloMode/analysis

#nobase_pkginclude_HEADERS = 
pkginclude_HEADERS = SusyFit.h \
SusyFit_noMCMC.h \
ComputeObservables/src/ComputeObservables.h \
ComputeObservables/src/InputParameters.h \
EW/src/Abottom.h \
EW/src/Acharm.h \
EW/src/AFBbottom.h \
EW/src/AFBcharm.h \
EW/src/AFBlepton.h \
EW/src/Alepton.h \
EW/src/Epsilon1.h \
EW/src/Epsilon2.h \
EW/src/Epsilon3.h \
EW/src/Epsilonb.h \
EW/src/EWObservables.h \
EW/src/GammaW.h \
EW/src/GammaZ.h \
EW/src/Mw.h \
EW/src/PtauPol.h \
EW/src/Rbottom.h \
EW/src/Rcharm.h \
EW/src/Rlepton.h \
EW/src/sigmaHadron.h \
EW/src/sin2thetaEff.h \
Flavour/src/alpha_2a.h \
Flavour/src/alpha.h \
Flavour/src/AmpDB2.h \
Flavour/src/AmpDD2.h \
Flavour/src/AmpDK2.h \
Flavour/src/AmpDS1.h \
Flavour/src/ArgD.h \
Flavour/src/Bdmumu.h \
Flavour/src/Betas_JPsiPhi.h \
Flavour/src/BR_Bdnunu.h \
Flavour/src/BR_Bsnunu.h \
Flavour/src/BR_Kmumu.h \
Flavour/src/BR_Kp0nunu.h \
Flavour/src/BR_Kppnunu.h \
Flavour/src/bsgamma.h \
Flavour/src/Bsmumu.h \
Flavour/src/Charm_Kpnunu.h \
Flavour/src/CPenguinBox.h \
Flavour/src/CPenguinBoxMu.h \
Flavour/src/DmBd.h \
Flavour/src/DmBs.h \
Flavour/src/DmK.h \
Flavour/src/EpsilonK.h \
Flavour/src/EpsilonP_O_Epsilon.h \
Flavour/src/EvolDB1bsg.h \
Flavour/src/EvolDB1Mll.h \
Flavour/src/EvolDC1Buras.h \
Flavour/src/EvolDC1.h \
Flavour/src/EvolDF1nlep.h \
Flavour/src/EvolDF2.h \
Flavour/src/Flavour.h \
Flavour/src/FlavourObservables.h \
Flavour/src/gamma.h \
Flavour/src/HeffDB1.h \
Flavour/src/HeffDC1.h \
Flavour/src/HeffDF1bnlep.h \
Flavour/src/HeffDF1bsg.h \
Flavour/src/HeffDF2.h \
Flavour/src/HeffDS1.h \
Flavour/src/M12D.h \
Flavour/src/MPll.h \
Flavour/src/MPllObservables.h \
Flavour/src/MVgamma.h \
Flavour/src/MVll.h \
Flavour/src/MVllObservables.h \
Flavour/src/SJPsiK.h \
Flavour/src/VCKM.h \
gslpp/src/gslpp_complex.h \
gslpp/src/gslpp.h \
gslpp/src/gslpp_matrix_base.h \
gslpp/src/gslpp_matrix_complex.h \
gslpp/src/gslpp_matrix_double.h \
gslpp/src/gslpp_vector_base.h \
gslpp/src/gslpp_vector_complex.h \
gslpp/src/gslpp_vector_double.h \
HiggsExtensions/src/HiggsKvgenKf.h \
HiggsExtensions/src/HiggsKvKfgen.h \
HiggsExtensions/src/HiggsKvKf.h \
HiggsExtensions/src/HiggsThObservables.h \
InputParser/src/InputParser.h \
InputParser/src/ModelFactory.h \
InputParser/src/ThObsFactory.h \
LoopFunctions/src/BernoulliNumbers.h \
LoopFunctions/src/ClausenFunctions.h \
LoopFunctions/src/LoopToolsWrapper.h \
LoopFunctions/src/Polylogarithms.h \
LoopFunctions/src/PVfunctions.h \
MonteCarlo/src/MonteCarloEngine.h \
MonteCarlo/src/MonteCarlo.h \
NewPhysics/src/NPbase.h \
NewPhysics/src/NPEffectiveBS.h \
NewPhysics/src/NPEffectiveGIMR.h \
NewPhysics/src/NPEpsilons.h \
NewPhysics/src/NPEpsilons_pureNP.h \
NewPhysics/src/NPHiggs.h \
NewPhysics/src/NPSTU.h \
NewPhysics/src/NPSTUZbbbarLR.h \
NewPhysics/src/NPZbbbar.h \
NewPhysics/src/NPZbbbarLinearized.h \
Observables/src/CorrelatedGaussianObservables.h \
Observables/src/HiggsObservable.h \
Observables/src/ModelParameter.h \
Observables/src/Observable2D.h \
Observables/src/Observable.h \
Observables/src/ParamObs.h \
Observables/src/ThObservable.h \
StandardModel/src/BParameter.h \
StandardModel/src/CKM.h \
StandardModel/src/EWSMApproximateFormulae.h \
StandardModel/src/EWSMcache.h \
StandardModel/src/EWSMOneLoopEW.h \
StandardModel/src/EWSMThreeLoopEW2QCD.h \
StandardModel/src/EWSMThreeLoopEW.h \
StandardModel/src/EWSMThreeLoopQCD.h \
StandardModel/src/EWSMTwoLoopEW.h \
StandardModel/src/EWSMTwoLoopQCD.h \
StandardModel/src/Meson.h \
StandardModel/src/Model.h \
StandardModel/src/ModelMatching.h \
StandardModel/src/OrderScheme.h \
StandardModel/src/Particle.h \
StandardModel/src/PMNS.h \
StandardModel/src/QCD.h \
StandardModel/src/RGEvolutor.h \
StandardModel/src/StandardModel.h \
StandardModel/src/StandardModelMatching.h \
StandardModel/src/WilsonCoefficient.h \
StandardModel/src/WilsonTemplate.h 

themySOURCES = ComputeObservables/src/ComputeObservables.cpp \
EW/src/Abottom.cpp \
EW/src/Acharm.cpp \
EW/src/AFBbottom.cpp \
EW/src/AFBcharm.cpp \
EW/src/AFBlepton.cpp \
EW/src/Alepton.cpp \
EW/src/GammaW.cpp \
EW/src/GammaZ.cpp \
EW/src/Mw.cpp \
EW/src/PtauPol.cpp \
EW/src/Rbottom.cpp \
EW/src/Rcharm.cpp \
EW/src/Rlepton.cpp \
EW/src/sigmaHadron.cpp \
EW/src/sin2thetaEff.cpp \
Flavour/src/alpha_2a.cpp \
Flavour/src/alpha.cpp \
Flavour/src/AmpDB2.cpp \
Flavour/src/AmpDD2.cpp \
Flavour/src/AmpDK2.cpp \
Flavour/src/AmpDS1.cpp \
Flavour/src/Bdmumu.cpp \
Flavour/src/Betas_JPsiPhi.cpp \
Flavour/src/BR_Bdnunu.cpp \
Flavour/src/BR_Bsnunu.cpp \
Flavour/src/BR_Kmumu.cpp \
Flavour/src/BR_Kp0nunu.cpp \
Flavour/src/BR_Kppnunu.cpp \
Flavour/src/bsgamma.cpp \
Flavour/src/Bsmumu.cpp \
Flavour/src/Charm_Kpnunu.cpp \
Flavour/src/CPenguinBox.cpp \
Flavour/src/CPenguinBoxMu.cpp \
Flavour/src/DmBd.cpp \
Flavour/src/DmBs.cpp \
Flavour/src/DmK.cpp \
Flavour/src/EpsilonK.cpp \
Flavour/src/EpsilonP_O_Epsilon.cpp \
Flavour/src/EvolDB1bsg.cpp \
Flavour/src/EvolDB1Mll.cpp \
Flavour/src/EvolDC1Buras.cpp \
Flavour/src/EvolDC1.cpp \
Flavour/src/EvolDF1nlep.cpp \
Flavour/src/EvolDF2.cpp \
Flavour/src/HeffDB1.cpp \
Flavour/src/HeffDC1.cpp \
Flavour/src/HeffDF1bnlep.cpp \
Flavour/src/HeffDF1bsg.cpp \
Flavour/src/HeffDF2.cpp \
Flavour/src/HeffDS1.cpp \
Flavour/src/MPll.cpp \
Flavour/src/MPllObservables.cpp \
Flavour/src/MVgamma.cpp \
Flavour/src/MVll.cpp \
Flavour/src/MVllObservables.cpp \
Flavour/src/SJPsiK.cpp \
Flavour/src/VCKM.cpp \
gslpp/src/gslpp_complex.cpp \
gslpp/src/gslpp_matrix_complex.cpp \
gslpp/src/gslpp_matrix_double.cpp \
gslpp/src/gslpp_vector_complex.cpp \
gslpp/src/gslpp_vector_double.cpp \
HiggsExtensions/src/HiggsKvgenKf.cpp \
HiggsExtensions/src/HiggsKvKf.cpp \
HiggsExtensions/src/HiggsKvKfgen.cpp \
InputParser/src/InputParser.cpp \
InputParser/src/ModelFactory.cpp \
InputParser/src/ThObsFactory.cpp \
LoopFunctions/src/BernoulliNumbers.cpp \
LoopFunctions/src/ClausenFunctions.cpp \
LoopFunctions/src/LoopToolsWrapper.cpp \
LoopFunctions/src/Polylogarithms.cpp \
LoopFunctions/src/PVfunctions.cpp \
MonteCarlo/src/MonteCarlo.cpp \
MonteCarlo/src/MonteCarloEngine.cpp \
NewPhysics/src/NPbase.cpp \
NewPhysics/src/NPEffectiveBS.cpp \
NewPhysics/src/NPEffectiveGIMR.cpp \
NewPhysics/src/NPEpsilons.cpp \
NewPhysics/src/NPEpsilons_pureNP.cpp \
NewPhysics/src/NPHiggs.cpp \
NewPhysics/src/NPSTU.cpp \
NewPhysics/src/NPSTUZbbbarLR.cpp \
NewPhysics/src/NPZbbbar.cpp \
NewPhysics/src/NPZbbbarLinearized.cpp \
Observables/src/CorrelatedGaussianObservables.cpp \
Observables/src/HiggsObservable.cpp \
Observables/src/ModelParameter.cpp \
Observables/src/Observable2D.cpp \
Observables/src/Observable.cpp \
Observables/src/ParamObs.cpp \
StandardModel/src/CKM.cpp \
StandardModel/src/EWSMApproximateFormulae.cpp \
StandardModel/src/EWSMcache.cpp \
StandardModel/src/EWSMOneLoopEW.cpp \
StandardModel/src/EWSMThreeLoopEW2QCD.cpp \
StandardModel/src/EWSMThreeLoopEW.cpp \
StandardModel/src/EWSMThreeLoopQCD.cpp \
StandardModel/src/EWSMTwoLoopEW.cpp \
StandardModel/src/EWSMTwoLoopQCD.cpp \
StandardModel/src/Meson.cpp \
StandardModel/src/Particle.cpp \
StandardModel/src/PMNS.cpp \
StandardModel/src/QCD.cpp \
StandardModel/src/RGEvolutor.cpp \
StandardModel/src/StandardModel.cpp \
StandardModel/src/StandardModelMatching.cpp \
StandardModel/src/WilsonCoefficient.cpp 

ExamplesSrc_LibMode_config_analysis_SOURCES =  $(themySOURCES) ExamplesSrc/LibMode_config/libmode_config.cpp
ExamplesSrc_LibMode_header_analysis_SOURCES =  $(ExamplesSrc_LibMode_config_analysis_SOURCES) 
ExamplesSrc_MonteCarloMode_analysis_SOURCES =  $(ExamplesSrc_LibMode_config_analysis_SOURCES) 


ExamplesSrc_LibMode_config_analysis_CPPFLAGS = $(SuF_CFLAGS) $(GSL_CFLAGS) -I@ROOTINCDIR@  $(BOOST_CPPFLAGS)
ExamplesSrc_LibMode_header_analysis_CPPFLAGS = $(ExamplesSrc_LibMode_config_analysis_CPPFLAGS) 
ExamplesSrc_MonteCarloMode_analysis_CPPFLAGS = $(ExamplesSrc_LibMode_config_analysis_CPPFLAGS) 

ExamplesSrc_LibMode_config_analysis_LDADD = $(SuF_LIBS) $(FLIBS) $(GSL_LIBS) -lgslcblas  $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) -L@ROOTLIBDIR@ -lCore -lCint -lRooFitCore -lRooFit -lRooStats -lFoam -lRIO -lHist -lMathCore -lMatrix @ROOTAUXLIBS@
ExamplesSrc_LibMode_header_analysis_LDADD = $(ExamplesSrc_LibMode_config_analysis_LDADD)
ExamplesSrc_MonteCarloMode_analysis_LDADD = $(ExamplesSrc_LibMode_config_analysis_LDADD)


pkglib_LTLIBRARIES = libSusyFit-@SusyFit_API_VERSION@.la
libSusyFit_@SusyFit_API_VERSION@_la_SOURCES = $(themySOURCES) 

libSusyFit_@SusyFit_API_VERSION@_la_LDFLAGS = -version-info $(SusyFit_SO_VERSION)
libSusyFit_@SusyFit_API_VERSION@_la_CPPFLAGS = $(SuF_CFLAGS) $(GSL_CFLAGS) -I@ROOTINCDIR@  $(BOOST_CPPFLAGS)
libSusyFit_@SusyFit_API_VERSION@_la_LIBDADD = $(SuF_LIBS) $(FLIBS) $(GSL_LIBS) -lgslcblas  $(BOOST_PROGRAM_OPTIONS_LIBS) $(BOOST_PROGRAM_OPTIONS_LDFLAGS) -L@ROOTLIBDIR@ -lCore -lCint -lRooFitCore -lRooFit -lRooStats -lFoam -lRIO -lHist -lMathCore @ROOTAUXLIBS@
# update to use @ROOTCONF@ --libs --ldflags 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = SusyFit-$(SusyFit_API_VERSION).pc

bin_SCRIPTS = susyfit-config

m4datadir = $(datadir)/aclocal
m4data_DATA = m4/susyfit.m4


# noinst_SCRIPTS = autogen.sh SusyFit_noMCMC_h.sh SusyFit_h.sh 
dist_noinst_SCRIPTS = ExamplesSrc/config/StandardModel.conf \
ExamplesSrc/config/input \
ExamplesSrc/config/input/rhopi_win10.root \
ExamplesSrc/config/input/rhorho_win13.root \
ExamplesSrc/config/input/pipi_sum14.root \
ExamplesSrc/config/input/su3rhoetaflat.root \
ExamplesSrc/config/input/gamma_summer14.root \
ExamplesSrc/config/Flavour.conf

DISTCLEANFILES = config.susyfit
# CLEANFILES = susyfit.pc susyfit-config
# EXTRA_DIST =  susyfit.pc.in 
