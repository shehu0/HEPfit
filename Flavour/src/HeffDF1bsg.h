/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HEFFDF1_H
#define	HEFFDF1_H

#include <StandardModel.h>
#include <StandardModelMatching.h>
#include <WilsonCoefficient.h>
#include "EvolDB1bsg.h"

using namespace gslpp;

class HeffDF1bsg {
public:
    /**
     * @brief constructor
     * @param SM
     * @param SM_Matching
     */
    HeffDF1bsg(const StandardModel & SM, StandardModelMatching & SM_Matching);
    
    /**
     * 
     * @brief destructor
     */
    virtual ~HeffDF1bsg();
    
    /**
     * 
     * @param mu is the low energy scale
     * @param scheme indicates the renormalization scheme
     * @return the effective hamiltonian at the scale mu B -> s gamma decay, Misiak basis, Chetyrkin et al hep-ph/9612313
     */
    vector<complex>** ComputeCoeffBsg(double mu, schemes scheme = NDR);
    
    
    EvolDB1bsg getUDF1() const {
        return evolDB1bsg;
    }

    const StandardModel& GetModel() const {
        return model;
    }
    
private :
    const StandardModel& model;
    ModelMatching& modelmatching;
    WilsonCoefficient coeffbsg;
    EvolDB1bsg evolDB1bsg;
    
};

#endif	/* HEFFDF1_H */

