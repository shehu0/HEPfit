/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <stdexcept>
#include "NPEffective.h"
#include "NewPhysicsParams.h"

double NewPhysicsParams::computeThValue()
{
    if (name.compare("deltaGVb") == 0)
        return SM.deltaGVq(SM.BOTTOM);
    else if (name.compare("deltaGAb") == 0)
        return SM.deltaGAq(SM.BOTTOM);
    else if (name.compare("deltaGRb") == 0)
        return ( (SM.deltaGVq(SM.BOTTOM) - SM.deltaGAq(SM.BOTTOM))/2.0 );
    else if (name.compare("deltaGLb") == 0)
        return ( (SM.deltaGVq(SM.BOTTOM) + SM.deltaGAq(SM.BOTTOM))/2.0 );
    else if (name.compare("deltaRhoZb") == 0) {
        if (SM.IsFlagApproximateGqOverGb()
                && !SM.IsFlagRhoZbFromGuOverGb()
                && !SM.IsFlagRhoZbFromGdOverGb()
                && !SM.IsFlagTestSubleadingTwoLoopEW())
            // SM prediction for rho_Z^b is needed!
            throw std::runtime_error("NewPhysicsParams::computeThValue(): deltaRhoZb is not defined");
        else
        if (SM.IsFlagNotLinearizedNP())
            return ( SM.rhoZ_q(SM.BOTTOM).real()
                     - SM.StandardModel::rhoZ_q(SM.BOTTOM).real() );
        else {
            complex gAb = SM.StandardModel::gAq(SM.BOTTOM) + SM.deltaGAq(SM.BOTTOM);
            double I3b = SM.getQuarks(SM.BOTTOM).getIsospin();
            double rhoZb_full = (gAb*gAb/I3b/I3b).real();
            return ( rhoZb_full
                     - SM.StandardModel::rhoZ_q(SM.BOTTOM).real() );
        }
    } else if (name.compare("deltaKappaZb") == 0) {
        if (SM.IsFlagNotLinearizedNP())
            return ( SM.kappaZ_q(SM.BOTTOM).real()
                     - SM.StandardModel::kappaZ_q(SM.BOTTOM).real() );
        else {
            complex gVb = SM.StandardModel::gVq(SM.BOTTOM) + SM.deltaGVq(SM.BOTTOM);
            complex gAb = SM.StandardModel::gAq(SM.BOTTOM) + SM.deltaGAq(SM.BOTTOM);
            double Qb = SM.getQuarks(SM.BOTTOM).getCharge();
            double kappaZb_full = (1.0 - (gVb/gAb).real())/(4.0*fabs(Qb)*SM.sW2());
            return ( kappaZb_full
                     - SM.StandardModel::kappaZ_q(SM.BOTTOM).real() );
        }
    } else if (name.compare("cHLp_NP") == 0) {
        double cHL1p = (static_cast<const NPEffective*> (&SM))->getCHL1p();
        double cHL2p = (static_cast<const NPEffective*> (&SM))->getCHL2p();
        double cHL3p = (static_cast<const NPEffective*> (&SM))->getCHL3p();
        if ( (cHL1p == cHL2p) && (cHL2p == cHL3p) )
            return cHL1p;
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): No lepton-flavor universality!");
    } else if (name.compare("cHQp_NP") == 0) {
        double cHQ1p = (static_cast<const NPEffective*> (&SM))->getCHQ1p();
        double cHQ2p = (static_cast<const NPEffective*> (&SM))->getCHQ2p();
        double cHQ3p = (static_cast<const NPEffective*> (&SM))->getCHQ3p();
        if ( (cHQ1p == cHQ2p) && (cHQ2p == cHQ3p) )
            return cHQ1p;
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): No quark-flavor universality!");
    } else if (name.compare("cHL_NP") == 0) {
        double cHL1 = (static_cast<const NPEffective*> (&SM))->getCHL1();
        double cHL2 = (static_cast<const NPEffective*> (&SM))->getCHL2();
        double cHL3 = (static_cast<const NPEffective*> (&SM))->getCHL3();
        if ( (cHL1 == cHL2) && (cHL2 == cHL3) )
            return cHL1;
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): No lepton-flavor universality!");
    } else if (name.compare("cHQ_NP") == 0) {
        double cHQ1 = (static_cast<const NPEffective*> (&SM))->getCHQ1();
        double cHQ2 = (static_cast<const NPEffective*> (&SM))->getCHQ2();
        double cHQ3 = (static_cast<const NPEffective*> (&SM))->getCHQ3();
        if ( (cHQ1 == cHQ2) && (cHQ2 == cHQ3) )
            return cHQ1;
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): No quark-flavor universality!");
    } else if (name.compare("cHE_NP") == 0) {
        double cHE1 = (static_cast<const NPEffective*> (&SM))->getCHE1();
        double cHE2 = (static_cast<const NPEffective*> (&SM))->getCHE2();
        double cHE3 = (static_cast<const NPEffective*> (&SM))->getCHE3();
        if ( (cHE1 == cHE2) && (cHE2 == cHE3) )
            return cHE1;
        else
            throw std::runtime_error("NewPhysicsParams::computeThValue(): No lepton-flavor universality!");
    } else if (name.compare("cHU2_NP") == 0)
        return (static_cast<const NPEffective*> (&SM))->getCHU2();
    else if (name.compare("cHD3_NP") == 0)
        return (static_cast<const NPEffective*> (&SM))->getCHD3();
    else if (name.compare("cHQ1pPLUScHQ2p_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCHQ1p()
                  + (static_cast<const NPEffective*> (&SM))->getCHQ2p() );
    else if (name.compare("cHQ2pMINUScHQ2_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCHQ2p()
                  - (static_cast<const NPEffective*> (&SM))->getCHQ2() );
    else if (name.compare("cHQ3pPLUScHQ3_NP") == 0)
        return ( (static_cast<const NPEffective*> (&SM))->getCHQ3p()
                  + (static_cast<const NPEffective*> (&SM))->getCHQ3() );
    else if (name.compare("c_Ae_NP") == 0) {
        double delGVe = SM.deltaGVl(SM.ELECTRON);
        double delGAe = SM.deltaGAl(SM.ELECTRON);
        double gVe = SM.StandardModel::gVl(SM.ELECTRON).real();
        double gAe = SM.StandardModel::gAl(SM.ELECTRON).real();
        double Lam = (static_cast<const NPEffective*> (&SM))->getLambdaNP();
        return ( (gAe*delGVe - gVe*delGAe)/2.0*Lam*Lam/SM.v()/SM.v() );
    } else if (name.compare("c_GammaZ_uds_NP") == 0) {
        double delGVu = SM.deltaGVq(SM.UP);
        double delGVd = SM.deltaGVq(SM.DOWN);
        double delGVs = SM.deltaGVq(SM.STRANGE);
        double delGAu = SM.deltaGAq(SM.UP);
        double delGAd = SM.deltaGAq(SM.DOWN);
        double delGAs = SM.deltaGAq(SM.STRANGE);
        double gVu = SM.StandardModel::gVq(SM.UP).real();
        double gVd = SM.StandardModel::gVq(SM.DOWN).real();
        double gVs = SM.StandardModel::gVq(SM.STRANGE).real();
        double gAu = SM.StandardModel::gAq(SM.UP).real();
        double gAd = SM.StandardModel::gAq(SM.DOWN).real();
        double gAs = SM.StandardModel::gAq(SM.STRANGE).real();
        double Lam = (static_cast<const NPEffective*> (&SM))->getLambdaNP();
        return ( (gVu*delGVu + gAu*delGAu + gVd*delGVd + gAd*delGAd
                     + gVs*delGVs + gAs*delGAs )/2.0
                  *Lam*Lam/SM.v()/SM.v() );
    } else
        throw std::runtime_error("NewPhysicsParams::computeThValue(): "
                                 + name + " is not defined");
}

