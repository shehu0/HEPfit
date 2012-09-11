/* 
 * File:   ZFRcharmLEP2.h
 * Author: mishima
 */

#ifndef ZFRCHARMLEP2_H
#define	ZFRCHARMLEP2_H

#include <ThObservable.h>
#include <StandardModel.h>
#include "ZFitter.h"


class ZFRcharmLEP2 : public ThObservable {
public:

    /**
     * @brief ZFRcharmLEP2 constructor
     * @param[in] ZF_i an object of ZFitter class
     * @param[in] sqrt_s_i \sqrt{s} of the e+ e- pair in the initial state
     */
    ZFRcharmLEP2(const ZFitter& ZF_i, const double sqrt_s_i) : ThObservable(ZF_i), 
            myZF(ZF_i), sqrt_s(sqrt_s_i) {};

    /**
     * @return the ratio of the c-cbar cross section to the hadronic cross section at sqrt_s
     */
    double getThValue();
    
private:
    const ZFitter& myZF;
    const double sqrt_s;
};

#endif	/* ZFRCHARMLEP2_H */
