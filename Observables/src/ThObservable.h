/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef THOBSERVABLE_H
#define	THOBSERVABLE_H

#include <StandardModel.h>

/**
 * @class ThObservable
 * @ingroup Observable
 * @brief A class for a model prediction of an observable. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class provides a base for the computation of the values
 * of different theory observables.
 */
class ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] SM_i a reference to an object of type StandardModel
     */
    ThObservable(const StandardModel& SM_i) 
    : SM(SM_i)
    {
        min = 0;
        max = 0;
    };

    /**
     * @brief The copy constructor.
     */
    ThObservable(const ThObservable& orig)
    : SM(orig.SM)
    {
    };

    /**
     * @brief The default destructor.
     */
    virtual ~ThObservable()
    {
    };

    /**
     * @brief A member to be overloaded by the respective theory observable.
     * class that calculates the value of the observable
     */
    virtual double computeThValue() = 0;

    void setBinMin(double min)
    {
        this->min = min;
    };

    void setBinMax(double max)
    {
        this->max = max;
    };

    double getBinMin()
    {
        return min;
    };

    double getBinMax()
    {
        return max;
    };

protected:
    const StandardModel& SM; ///< A reference to an object of StandardMode class.
    double min;
    double max;
};

#endif	/* THOBSERVABLE_H */
