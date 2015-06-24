/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef BPARAMETER_H
#define	BPARAMETER_H

#include <gslpp_vector_double.h>
#include "OrderScheme.h"

using namespace gslpp;

/**
 * @addtogroup StandardModel
 * @brief A module for the Standard %Model.
 * @{
 */

/**
 * @class BParameter
 * @brief A class for the bag paramters.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This is the class for defining bag parameters, which depend on
 * a specified scale and scheme. 
 */
class BParameter {
public:
    
    /**
     * @brief Constructor.
     * @param[in] n dimension of the vector of bag parameters
     */
    BParameter(int n)
    : bpars(n,0.)
    {};

    /**
     * @brief A get method for the vector of the bag parameters.
     * @return the vector of the bag parameters
     */
    vector<double> getBpars() const
    {
        return bpars;
    }

    /**
     * @brief A set method for a vector of the bag parameters.
     * @param[in] bpars a vector of the bag parameters
     */
    void setBpars(vector<double> bpars) 
    {
        this->bpars = bpars;
    }

    /**
     * @brief A set method for a component of the vector of bag parameters.
     * @param[in] i the index for the component of the vector of bag parameters
     * @param[in] value the value of the bag parameters
     */
    void setBpars(int i, double value) 
    {
        this->bpars(i) = value;
    }

    /**
     * @brief A get method for the scale of the bag parameters.
     * @return the scale at which the bag parameters are defined
     */
    double getMu() const
    {
        return mu;
    }

    /**
     * @brief A set method for the scale of the bag parameters.
     * @param[in] mu the scale at which the bag parameters are defined
     */
    void setMu(double mu) 
    {
        this->mu = mu;
    }
    /**
     * @brief A get method for the scheme of the bag parameters.
     * @return the scheme in which the bag parameters are defined
     */
    schemes getScheme() const
    {
        return scheme;
    }
    
    /**
     * @brief A set method for the scheme of the bag parameters.
     * @param[in] scheme the scheme in which the bag parameters are defined
     */
    void setScheme(schemes scheme) 
    {
        this->scheme = scheme;
    }

private:
    vector<double> bpars;///< A vector of bag parameters.
    double mu;///< The scale at which the bag parameters are defined. 
    schemes scheme;///< The scheme in which the bag parameters are defined.
    
};

/**
 * @}
 */

#endif	/* BPARAMETER_H */