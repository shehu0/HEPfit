/* 
 * File:   AFBlepton.cpp
 * Author: mishima
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "AFBlepton.h"

AFBlepton::AFBlepton(const EW& EW_i) : ThObservable(EW_i) {
}

double AFBlepton::getThValue() {   
    
    std::cout << "Write codes!" << std::endl;
    exit(EXIT_FAILURE); 
    
    return (0.0);
}
        
