/* 
 * File:   ArgD.h
 * Author: Mauro_87
 *
 * Created on 28 novembre 2011, 18.06
 */

#ifndef ARGD_H
#define	ARGD_H

#include <ThObservable.h>
#include <Flavour.h>
#include <AmpDD2.h>

class ArgD : public ThObservable, AmpDD2 {
/**
 * @brief a class for the argument of the complex amplitude of D^{0} oscillations
 * @param Flavour an object of Flavour class
 */
public:
    /**
     * @brief ArgD constructor
     * @param Flavour an object of Flavour class
     */
    ArgD(Flavour& Flavour) : ThObservable(Flavour), AmpDD2(Flavour) {};
    /**
     * @brief a method returning the argument of the complex amplitude for 
     * the absorptive part of the \f$ | \Delta C = 2 | \f$ mixing
     * @return the argument of the complex amplitude of \f$ D^{0} \f$ oscillations 
     */
    double getThValue() {   
       return(AmpDD(NLO).arg() / M_PI * 180. );
    };
};

#endif	/* ARGD_H */