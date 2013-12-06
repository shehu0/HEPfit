/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <NPZbbbar.h>
#include "sin2thetaEff.h"


double sin2thetaEff::computeThValue() 
{ 
    double sin2_theta_eff = myEW.sin2thetaEff(SM.ELECTRON);
    
    /* NP contribution to the Zff vertex */
    if (myEW.checkNPZff())
        sin2_theta_eff = myEW.getMyEW_NPZff().sin2thetaEff(sin2_theta_eff);

    /* Debug: extract pure NP contribution */
    //sin2_theta_eff -= myEW.sin2thetaEff(SM.ELECTRON);

    return sin2_theta_eff;
}

