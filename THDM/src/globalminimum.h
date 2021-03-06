/* 
 * Copyright (C) 2015 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef GLOBALMINIMUM_H
#define	GLOBALMINIMUM_H

#include <stdexcept>
#include <ThObservable.h>
#include "THDM.h"

/**
 * @class globalminimum 
 * @ingroup THDM 
 * @brief An observable class to prevent the occurence of a panic vacuum.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to assure that our vacuum is the global minimum of the potential.
 */
class globalminimum : public ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] ?
     */
    globalminimum(const StandardModel& SM_i) 
    : ThObservable(SM_i), myTHDM(static_cast<const THDM*> (&SM_i))
    {
    };

    /**
     * @brief A condition to assure that our vacuum is global.
     * @return 
     */
    double computeThValue();

    private:
        const THDM * myTHDM;
};

#endif	/* GLOBALMINIMUM_H */

