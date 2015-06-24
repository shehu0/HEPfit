/*
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Bsmumu.h"

Bsmumu::Bsmumu(const StandardModel& SM_i, int obsFlag): ThObservable(SM_i){
    if (obsFlag > 0 and obsFlag < 5) obs = obsFlag;
    else throw std::runtime_error("obsFlag in Bsmumu(myFlavour, obsFlag) called from ThFactory::ThFactory() can only be 1 (BR) or 2 (BRbar) or 3 (Amumu) or 4 (Smumu)");
};

double Bsmumu::computeThValue(){
    computeObs(FULLNLO);
    double FBs = SM.getMesons(QCD::B_S).getDecayconst();
    double coupling = SM.getGF() * SM.alphaMz() / 4. / M_PI;
    double PRF = pow(coupling, 2.) / M_PI / SM.getMesons(QCD::B_S).computeWidth() * pow(FBs, 2.) * pow(mmu, 2.) * mBs * beta;
    ys = 0.087; // For now. To be explicitly calculated.
    timeInt = (1. + Amumu * ys) / (1. - ys * ys); // Note modification in form due to algorithm

    if (obs == 1) return( PRF * ampSq);
    if (obs == 2) return( PRF * ampSq * timeInt);
    if (obs == 3) return( Amumu );
    if (obs == 4) return( Smumu );
    
    throw std::runtime_error("Bsmumu::computeThValue(): Observable type not defined. Can be only any of (1,2,3,4)");
    return (EXIT_FAILURE);
}

void Bsmumu::computeObs(orders order){
    mmu = SM.getLeptons(StandardModel::MU).getMass();
    mBs = SM.getMesons(QCD::B_S).getMass();
    mb = SM.getQuarks(QCD::BOTTOM).getMass();
    ms = SM.getQuarks(QCD::STRANGE).getMass();
    chiral = pow(mBs, 2.) / 2. / mmu * mb / (mb + ms);
    beta = sqrt(1. - pow(2. * mmu / mBs, 2.));
    computeAmpSq(order);
    Amumu = (absP * absP * cos(2. * argP - phiNP) -  absS * absS * cos(2. * argS - phiNP)) / (absP * absP + absS * absS);
    Smumu = (absP * absP * sin(2. * argP - phiNP) -  absS * absS * sin(2. * argS - phiNP)) / (absP * absP + absS * absS);
}

double Bsmumu::computeAmumu(orders order){
    computeObs(FULLNLO);
    return(Amumu);
}

double Bsmumu::computeSmumu(orders order){
    computeObs(FULLNLO);
    return(Smumu);
}

void Bsmumu::computeAmpSq(orders order){
    if (SM.getMyFlavour()->getHDB1().getCoeffsmumu().getOrder() < order % 3){
        std::stringstream out;
        out << order;
        throw std::runtime_error("Bsmumu::computeAmpSq(): required cofficient of "
                                 "order " + out.str() + " not computed");
    }
    vector<complex> ** allcoeff = SM.getMyFlavour()->ComputeCoeffsmumu();
    
    switch(order) {
        case FULLNLO:
        {
            complex PP = (*(allcoeff[LO]) + *(allcoeff[NLO]))(0) - (*(allcoeff[LO]) + *(allcoeff[NLO]))(1)
                        + chiral * ((*(allcoeff[LO]) + *(allcoeff[NLO]))(2) - (*(allcoeff[LO]) + *(allcoeff[NLO]))(3));
            absP = PP.abs();
            argP = PP.arg();
            
            complex SS = beta * chiral * ((*(allcoeff[LO]) + *(allcoeff[NLO]))(4) - (*(allcoeff[LO]) + *(allcoeff[NLO]))(5));
            absS = SS.abs();
            argS = SS.arg();
            phiNP = 0.;
            
            ampSq = absP * absP + absS * absS;
        }
        break;
        case LO:
        {
            complex PP = (*(allcoeff[LO]))(0) - (*(allcoeff[LO]))(1)
            + chiral * ((*(allcoeff[LO]))(2) - (*(allcoeff[LO]))(3));
            absP = PP.abs();
            argP = PP.arg();
            
            complex SS = beta * chiral * ((*(allcoeff[LO]))(4) - (*(allcoeff[LO]))(5));
            absS = SS.abs();
            argS = SS.arg();
            phiNP = 0.;
            
            ampSq = absP * absP + absS * absS;
        }
        break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("Bsmumu::computeAmpSq(): order " + out.str() + " not implemented");;
    }
}