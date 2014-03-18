/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <vector>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <EWObservables.h>
#include <StandardModelParams.h>
#include <NewPhysicsParams.h>
#include "ThFactory.h"

ThFactory::ThFactory(const StandardModel& myModel) 
: myEW(myModel), myMO(myModel)
{    
    //-----  EW precision observables  -----
    thobs["Mw"] = new Mw(myEW);
    thobs["GammaW"] = new GammaW(myEW);
    thobs["GammaZ"] = new GammaZ(myEW);
    thobs["sigmaHadron"] = new sigmaHadron(myEW);
    thobs["sin2thetaEff"] = new sin2thetaEff(myEW);
    thobs["PtauPol"] = new PtauPol(myEW);
    thobs["Alepton"] = new Alepton(myEW);
    thobs["Acharm"] = new Acharm(myEW);
    thobs["Abottom"] = new Abottom(myEW);
    thobs["AFBlepton"] = new AFBlepton(myEW);
    thobs["AFBcharm"] = new AFBcharm(myEW);
    thobs["AFBbottom"] = new AFBbottom(myEW);
    thobs["Rlepton"] = new Rlepton(myEW);
    thobs["Rcharm"] = new Rcharm(myEW);
    thobs["Rbottom"] = new Rbottom(myEW);

    //-----  Epsilon parameters  -----
    thobs["epsilon1"] = new NewPhysicsParams(myMO, "epsilon1");
    thobs["epsilon2"] = new NewPhysicsParams(myMO, "epsilon2");
    thobs["epsilon3"] = new NewPhysicsParams(myMO, "epsilon3");
    thobs["epsilonb"] = new NewPhysicsParams(myMO, "epsilonb");

    //-----  SM input parameters  -----
    thobs["Mz"] = new StandardModelParams(myMO, "Mz");
    thobs["mHl"] = new StandardModelParams(myMO, "mHl");

    //-----  NP input parameters, etc.   -----
    if (myModel.ModelName().compare("NPEffective1") == 0
            || myModel.ModelName().compare("NPEffective2") == 0 ) {
        thobs["cHQ1pPLUScHQ2p_NP"] = new NewPhysicsParams(myMO, "cHQ1pPLUScHQ2p_NP");
        thobs["cHQ2pMINUScHQ2_NP"] = new NewPhysicsParams(myMO, "cHQ2pMINUScHQ2_NP");
        thobs["cHQ3pPLUScHQ3_NP"] = new NewPhysicsParams(myMO, "cHQ3pPLUScHQ3_NP");
        thobs["c_Ae_NP"] = new NewPhysicsParams(myMO, "c_Ae_NP");
        thobs["c_GammaZ_uds_NP"] = new NewPhysicsParams(myMO, "c_GammaZ_uds_NP");
    }
    if ( (myModel.ModelName().compare("NPZbbbar") == 0)
            || (myModel.ModelName().compare("NPZbbbarLR") == 0) ) {
        thobs["deltaGVb"] = new NewPhysicsParams(myMO, "deltaGVb");
        thobs["deltaGAb"] = new NewPhysicsParams(myMO, "deltaGAb");
        thobs["deltaGLb"] = new NewPhysicsParams(myMO, "deltaGLb");
        thobs["deltaGRb"] = new NewPhysicsParams(myMO, "deltaGRb");
        thobs["deltaRhoZb"] = new NewPhysicsParams(myMO, "deltaRhoZb");
        thobs["deltaKappaZb"] = new NewPhysicsParams(myMO, "deltaKappaZb");
    }
}

ThFactory::~ThFactory() 
{
    for (std::map<std::string, ThObservable *>::iterator it = thobs.begin();
            it != thobs.end(); it++)
        if (it->second != NULL)
            delete it->second;
}

ThObservable * ThFactory::getThMethod(const std::string& name) 
{
    if (thobs.find(name) == thobs.end())
        throw std::runtime_error("ERROR: Wrong observable " + name + " passed to ThFactory");
    return (thobs[name]);
}
