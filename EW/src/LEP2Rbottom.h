/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef LEP2RBOTTOM_H
#define	LEP2RBOTTOM_H

#include "LEP2ThObservable.h"
#include "LEP2sigmaBottom.h"
#include "LEP2sigmaHadron.h"

/**
 * @class LEP2Rbottom
 * @ingroup EW
 * @brief A class for @f$R_b^0@f$ above the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class LEP2Rbottom : public LEP2ThObservable {
public:

    /**
     * @brief LEP2Rbottom constructor
     * @param[in] EW_i an object of EW class
     * @param[in] sqrt_s_i the CM energy of the e^+ e^- pair
     */
    LEP2Rbottom(const EW& EW_i, const double sqrt_s_i) 
    : LEP2ThObservable(EW_i, sqrt_s_i), myLEP2sigmaBottom(EW_i, sqrt_s_i), 
            myLEP2sigmaHadron(EW_i, sqrt_s_i, false, true) 
    {
        q_flavor = QCD::BOTTOM;
    }

    /**
     * @return the ratio of the b-bbar cross section to the hadronic cross section at sqrt_s
     */
    double computeThValue();

private:
    LEP2sigmaBottom myLEP2sigmaBottom;
    LEP2sigmaHadron myLEP2sigmaHadron;
    
};

#endif	/* LEP2RBOTTOM_H */
