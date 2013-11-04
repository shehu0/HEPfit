/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Abottom.h"


double Abottom::computeThValue() 
{
    double A_b;
    EW::EWTYPE myEWTYPE = myEW.getEWTYPE();

    if (myEWTYPE==EW::EWCHMN)  
        A_b = myEW.getMyEW_CHMN().A_q(SM.BOTTOM);
    else if (myEWTYPE==EW::EWABC || myEWTYPE==EW::EWABC2) 
        A_b = myEW.getMyEW_ABC().A_b(SM.epsilon1(),SM.epsilon3(),SM.epsilonb());
    else {
        A_b = myEW.A_q(SM.BOTTOM);

        if(myEWTYPE==EW::EWBURGESS)
            return myEW.getMyEW_BURGESS().Abottom(A_b, myEW.A_l(SM.ELECTRON));

        /* NP contribution to the Zff vertex */
        if ( !SM.IsFlagNotLinearizedNP() ) {
            double delGVf = SM.deltaGVq(SM.BOTTOM);
            double delGAf = SM.deltaGAq(SM.BOTTOM);
            if (delGVf!=0.0 || delGAf!=0.0) {
                double gVf = SM.StandardModel::gVq(SM.BOTTOM).real();
                double gAf = SM.StandardModel::gAq(SM.BOTTOM).real();
                double Gf = gVf*gVf + gAf*gAf;
                double delGVfOverGAf = (gAf*delGVf - gVf*delGAf)/gAf/gAf;

                A_b -= 2.0*(gVf*gVf - gAf*gAf)*gAf*gAf/Gf/Gf*delGVfOverGAf;
            }
        } else
            if (SM.obliqueS()!=0.0 || SM.obliqueT()!=0.0 || SM.obliqueU()!=0.0)
                throw std::runtime_error("Abottom::computeThValue(): The oblique corrections STU cannot be used with flag NotLinearizedNP=1");

        /* Debug: extract pure NP contribution */
        //A_b -= myEW.A_q(SM.BOTTOM);
    }
    
    return A_b;
}
        

