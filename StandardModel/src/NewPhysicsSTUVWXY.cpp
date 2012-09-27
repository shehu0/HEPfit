/* 
 * File:   NewPhysicsSTUVWXY.cpp
 * Author: mishima
 */

#include <stdexcept>
#include "NewPhysicsSTUVWXY.h"


const std::string NewPhysicsSTUVWXY::STUVWXYvars[NSTUVWXYvars] 
                  = {"obliqueShat", "obliqueThat", "obliqueUhat", 
                     "obliqueV", "obliqueW", "obliqueX", "obliqueY"};


NewPhysicsSTUVWXY::NewPhysicsSTUVWXY() : StandardModel() {
}


bool NewPhysicsSTUVWXY::Update(const std::map<std::string,double>& DPars) {
    for (std::map<std::string, double>::const_iterator it = DPars.begin(); it != DPars.end(); it++)
        SetParameter(it->first, it->second);
    if(!StandardModel::Update(DPars)) return (false);

    return (true);
}


bool NewPhysicsSTUVWXY::Init(const std::map<std::string, double>& DPars) {
    Update(DPars);
    return(CheckParameters(DPars)); 
}


bool NewPhysicsSTUVWXY::CheckParameters(const std::map<std::string, double>& DPars) {
    for (int i = 0; i < NSTUVWXYvars; i++) {
        if (DPars.find(STUVWXYvars[i]) == DPars.end()) {
            std::cout << "missing mandatory NewPhysicsSTUVWXY parameter " 
                      << STUVWXYvars[i] << std::endl;
            return false;
        }
    }
    return(StandardModel::CheckParameters(DPars));
}

    
void NewPhysicsSTUVWXY::SetParameter(const std::string name, const double& value) {
    if (name.compare("obliqueShat") == 0)
        myObliqueShat = value;
    else if (name.compare("obliqueThat") == 0)
        myObliqueThat = value;
    else if (name.compare("obliqueUhat") == 0)
        myObliqueUhat = value;    
    else if (name.compare("obliqueV") == 0)
        myObliqueV = value;    
    else if (name.compare("obliqueW") == 0)
        myObliqueW = value;    
    else if (name.compare("obliqueX") == 0)
        myObliqueX = value;    
    else if (name.compare("obliqueY") == 0)
        myObliqueY = value;    
    else
        StandardModel::SetParameter(name, value);       
}



