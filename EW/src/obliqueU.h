/* 
 * File:   obliqueU.h
 * Author: mishima
 */

#ifndef OBLIQUEU_H
#define	OBLIQUEU_H

#include <ThObservable.h>
#include "EW.h"

class obliqueU : public ThObservable {
public:

    /**
     * @brief obliqueU constructor
     * @param[in] EW_i an object of EW class
     */
    obliqueU(const EW& EW_i);

    /**
     * @return the oblique parameter U
     */
    double getThValue();

private:

};

#endif	/* OBLIQUEU_H */
