/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef LEP2AFBBOTTOM_H
#define	LEP2AFBBOTTOM_H

#include "LEP2ThObservable.h"
#include "LEP2sigmaBottom.h"


class LEP2AFBbottom : public LEP2ThObservable {
public:

    /**
     * @brief LEP2AFBbottom constructor
     * @param[in] EW_i an object of EW class
     * @param[in] sqrt_s_i the CM energy of the e^+ e^- pair
     */
    LEP2AFBbottom(const EW& EW_i, const double sqrt_s_i) : LEP2ThObservable(EW_i, sqrt_s_i),
            myLEP2sigmaBottom(EW_i, sqrt_s_i, true) {
        q_flavor = StandardModel::BOTTOM;
    }

    /**
     * @return the forward-backward asymmetry for e^+ e^- -> b bbar at sqrt_s
     */
    double getThValue();

private:
    LEP2sigmaBottom myLEP2sigmaBottom;
     
};

#endif	/* LEP2AFBBOTTOM_H */

