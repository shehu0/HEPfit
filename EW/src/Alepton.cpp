/* 
 * File:   Alepton.cpp
 * Author: mishima
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Alepton.h"

Alepton::Alepton(const EW& EW_i) : ThObservable(EW_i) {
}

double Alepton::getThValue() {   
    
    std::cout << "Write codes!" << std::endl;
    exit(EXIT_FAILURE); 
    
    return (0.0);
}
        
