/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <stdexcept>
#include <EWSM.h>
#include "NPbase.h"
#include "NPEpsilons.h"
#include "NPEpsilons_pureNP.h"
#include "NPEffective.h"
#include "NPZbbbar.h"
#include "NewPhysicsParams.h"
#include "NPSTU.h"

double NewPhysicsParams::computeThValue()
{
    if (name.compare("epsilon1") == 0)
        if (SM.ModelName().compare("StandardModel") == 0)
            return SM.getEWSM()->epsilon1_SM();
        else if (SM.ModelName().compare("NPEpsilons") == 0)
            return (static_cast<const NPEpsilons*> (&SM))->epsilon1();
        else if (SM.ModelName().compare("NPEpsilons_pureNP") == 0)
            return (static_cast<const NPEpsilons_pureNP*> (&SM))->epsilon1();
        else if (SM.ModelName().compare("NPSTU") == 0)
            return (static_cast<const NPSTU*> (&SM))->epsilon1();
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): epsilon1 is not defined");
    else if (name.compare("epsilon2") == 0)
        if (SM.ModelName().compare("StandardModel") == 0)
            return SM.getEWSM()->epsilon2_SM();
        else if (SM.ModelName().compare("NPEpsilons") == 0)
            return (static_cast<const NPEpsilons*> (&SM))->epsilon2();
        else if (SM.ModelName().compare("NPEpsilons_pureNP") == 0)
            return (static_cast<const NPEpsilons_pureNP*> (&SM))->epsilon2();
        else if (SM.ModelName().compare("NPSTU") == 0)
            return (static_cast<const NPSTU*> (&SM))->epsilon2();
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): epsilon2 is not defined");
    else if (name.compare("epsilon3") == 0)
        if (SM.ModelName().compare("StandardModel") == 0)
            return SM.getEWSM()->epsilon3_SM();
        else if (SM.ModelName().compare("NPEpsilons") == 0)
            return (static_cast<const NPEpsilons*> (&SM))->epsilon3();
        else if (SM.ModelName().compare("NPEpsilons_pureNP") == 0)
            return (static_cast<const NPEpsilons_pureNP*> (&SM))->epsilon3();
        else if (SM.ModelName().compare("NPSTU") == 0)
            return (static_cast<const NPSTU*> (&SM))->epsilon3();
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): epsilon3 is not defined");
    else if (name.compare("epsilonb") == 0)
        if (SM.ModelName().compare("StandardModel") == 0)
            return SM.getEWSM()->epsilonb_SM();
        else if (SM.ModelName().compare("NPEpsilons") == 0)
            return (static_cast<const NPEpsilons*> (&SM))->epsilonb();
        else if (SM.ModelName().compare("NPEpsilons_pureNP") == 0)
            return (static_cast<const NPEpsilons_pureNP*> (&SM))->epsilonb();
        else if (SM.ModelName().compare("NPSTU") == 0)
            return (static_cast<const NPSTU*> (&SM))->epsilonb();
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): epsilonb is not defined");
    else if (name.compare("deltaGVb") == 0)
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) )
            return (static_cast<const NPZbbbar*> (&SM))->deltaGVq(SM.BOTTOM);
        else
            return 0.0;
    else if (name.compare("deltaGAb") == 0)
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) )
            return (static_cast<const NPZbbbar*> (&SM))->deltaGAq(SM.BOTTOM);
        else
            return 0.0;
    else if (name.compare("deltaGRb") == 0)
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) )
            return ( ((static_cast<const NPZbbbar*> (&SM))->deltaGVq(SM.BOTTOM)
                     - (static_cast<const NPZbbbar*> (&SM))->deltaGAq(SM.BOTTOM))/2.0 );
        else
            return 0.0;
    else if (name.compare("deltaGLb") == 0)
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) )
            return ( ((static_cast<const NPZbbbar*> (&SM))->deltaGVq(SM.BOTTOM)
                     + (static_cast<const NPZbbbar*> (&SM))->deltaGAq(SM.BOTTOM))/2.0 );
        else
            return 0.0;
    else if (name.compare("deltaRhoZb") == 0) {
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) ) {
            if (!SM.IsFlagNoApproximateGammaZ())
                // SM prediction for rho_Z^b is needed!
                throw std::runtime_error("NewPhysicsParams::computeThValue(): deltaRhoZb is not available");
            else
                if ((static_cast<const NPZbbbar*> (&SM))->IsFlagNotLinearizedNP())
                    return ( SM.getEWSM()->rhoZ_q(SM.BOTTOM).real()
                            - SM.getEWSM()->rhoZ_q_SM(SM.BOTTOM).real() );
                else {
                    complex gAb = SM.getEWSM()->gAq_SM(SM.BOTTOM)
                                  + (static_cast<const NPZbbbar*> (&SM))->deltaGAq(SM.BOTTOM);
                    double I3b = SM.getQuarks(SM.BOTTOM).getIsospin();
                    double rhoZb_full = (gAb*gAb/I3b/I3b).real();
                    return ( rhoZb_full
                            - SM.getEWSM()->rhoZ_q_SM(SM.BOTTOM).real() );
                }
        } else
            return 0.0;
    } else if (name.compare("deltaKappaZb") == 0) {
        if ( (SM.ModelName().compare("NPZbbbar") == 0)
                || (SM.ModelName().compare("NPZbbbarLR") == 0) ) {
            if ((static_cast<const NPZbbbar*> (&SM))->IsFlagNotLinearizedNP())
                return ( SM.getEWSM()->kappaZ_q(SM.BOTTOM).real()
                        - SM.getEWSM()->kappaZ_q_SM(SM.BOTTOM).real() );
            else {
                complex gVb = SM.getEWSM()->gVq_SM(SM.BOTTOM)
                              + (static_cast<const NPZbbbar*> (&SM))->deltaGVq(SM.BOTTOM);
                complex gAb = SM.getEWSM()->gAq_SM(SM.BOTTOM)
                              + (static_cast<const NPZbbbar*> (&SM))->deltaGAq(SM.BOTTOM);
                double Qb = SM.getQuarks(SM.BOTTOM).getCharge();
                double kappaZb_full = (1.0 - (gVb/gAb).real())/(4.0*fabs(Qb)*SM.sW2());
                return ( kappaZb_full
                        - SM.getEWSM()->kappaZ_q_SM(SM.BOTTOM).real() );
            }
        } else
            return 0.0;
    } else if (name.compare("cHQ1pPLUScHQ2p_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ1p")
                  + (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ2p") );
    else if (name.compare("cHQ2pMINUScHQ2_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ2p")
                  - (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ2") );
    else if (name.compare("cHQ3pPLUScHQ3_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ3p")
                  + (static_cast<const NPEffective*> (&SM))->getCoeff("cHQ3") );
    else if (name.compare("c_Ae_NP") == 0) {
        double delGVe = (static_cast<const NPEffective*> (&SM))->deltaGVl(SM.ELECTRON);
        double delGAe = (static_cast<const NPEffective*> (&SM))->deltaGAl(SM.ELECTRON);
        double gVe = SM.getEWSM()->gVl_SM(SM.ELECTRON).real();
        double gAe = SM.getEWSM()->gAl_SM(SM.ELECTRON).real();
        double Lam = (static_cast<const NPEffective*> (&SM))->getLambdaNP();
        return ( (gAe*delGVe - gVe*delGAe)/2.0*Lam*Lam/SM.v()/SM.v() );
    } else if (name.compare("c_GammaZ_uds_NP") == 0) {
        double delGVu = (static_cast<const NPEffective*> (&SM))->deltaGVq(SM.UP);
        double delGVd = (static_cast<const NPEffective*> (&SM))->deltaGVq(SM.DOWN);
        double delGVs = (static_cast<const NPEffective*> (&SM))->deltaGVq(SM.STRANGE);
        double delGAu = (static_cast<const NPEffective*> (&SM))->deltaGAq(SM.UP);
        double delGAd = (static_cast<const NPEffective*> (&SM))->deltaGAq(SM.DOWN);
        double delGAs = (static_cast<const NPEffective*> (&SM))->deltaGAq(SM.STRANGE);
        double gVu = SM.getEWSM()->gVq_SM(SM.UP).real();
        double gVd = SM.getEWSM()->gVq_SM(SM.DOWN).real();
        double gVs = SM.getEWSM()->gVq_SM(SM.STRANGE).real();
        double gAu = SM.getEWSM()->gAq_SM(SM.UP).real();
        double gAd = SM.getEWSM()->gAq_SM(SM.DOWN).real();
        double gAs = SM.getEWSM()->gAq_SM(SM.STRANGE).real();
        double Lam = (static_cast<const NPEffective*> (&SM))->getLambdaNP();
        return ( (gVu*delGVu + gAu*delGAu + gVd*delGVd + gAd*delGAd
                     + gVs*delGVs + gAs*delGAs )/2.0
                  *Lam*Lam/SM.v()/SM.v() );
    } else
        throw std::runtime_error("NewPhysicsParams::computeThValue(): "
                                 + name + " is not defined");
}

