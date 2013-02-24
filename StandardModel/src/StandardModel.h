/*
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef STANDARDMODEL_H
#define	STANDARDMODEL_H

#include <gslpp.h>
#include "QCD.h"
#include "CKM.h"
#include "WilsonCoefficient.h"
#include "StandardModelMatching.h"

using namespace gslpp;
class EWSM; // forward reference to EWSM class

/**
 * @class StandardModel
 * @ingroup StandardModel
 * @brief A class for the Standard Model. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class StandardModel: public QCD {
public:
    enum lepton {NEUTRINO_1,ELECTRON,NEUTRINO_2,MU,NEUTRINO_3,TAU};
    static const int NSMvars = 22;
    static const std::string SMvars[NSMvars];
    static const int NSMflags = 7;
    static const std::string SMflags[NSMflags];
    
    StandardModel(const bool bDebug_i=false);

    virtual std::string ModelName() const 
    {
        return "StandardModel";
    }

    virtual bool Init(const std::map<std::string, double>&);

    virtual bool PreUpdate();    

    /**
     * updates the SM parameters found in the argument
     * @param a map containing the parameters (all as double) to be updated
     * "GF"
     * "mneutrino_1"
     * "mneutrino_2"
     * "mneutrino_3"
     * "melectron"
     * "mmu"
     * "mtau"
     * "lambda"
     * "A"
     * "rhob"
     * "etab"
     * "ale"
     * "dAle5Mz"
     * "mHl"
     * "muw"
     * "phiEpsK"
     * "DeltaMK"
     * "KbarEpsK"
     * "Dmk"
     * "SM_M12D" 
     * "delMw"
     * "delSin2th_l"
     */
    virtual bool Update(const std::map<std::string, double>&);
     
    virtual bool PostUpdate();
        
    virtual bool CheckParameters(const std::map<std::string, double>&);

    
    ///////////////////////////////////////////////////////////////////////////
    // Flags    
        
    virtual bool SetFlag(const std::string, const bool&);    
    
    bool IsFlagFixedAllSMparams() const
    {    
        return FlagFixedAllSMparams;
    }

    bool IsFlagEWCHMN() const
    {
        return FlagEWCHMN;
    }
    
    bool IsFlagEWABC() const
    {
        return FlagEWABC;
    }

    bool IsFlagEWABC2() const
    {
        return FlagEWABC2;
    }
    
    bool IsFlagEWBURGESS() const
    {
        return FlagEWBURGESS;
    }

    bool IsFlagR0bApproximate() const 
    {
        return FlagR0bApproximate;
    }
    
    void SetFlagR0bApproximate(bool FlagR0bApproximate)
    {
        this->FlagR0bApproximate = FlagR0bApproximate;
    }
    
    bool IsFlagWithoutNonUniversalVC() const 
    {
        return FlagWithoutNonUniversalVC;
    }

    
    ///////////////////////////////////////////////////////////////////////////
    // Initialization and Matching
    
    StandardModelMatching* myMatching;
        
    virtual bool InitializeModel();  
    
    virtual void SetEWSMflags(EWSM& myEWSM);
    
    virtual StandardModelMatching* GetMyMatching() const 
    {
        return myStandardModelMatching;
    }

    virtual void SetMyMatching(StandardModelMatching* myMatching) 
    {
        this->myStandardModelMatching = myMatching;
    }
    
    virtual const double matchingScale() const 
    {
        return muw;
    }

    
    ///////////////////////////////////////////////////////////////////////////
    // get and set methods for class members

    /**
     * @return boolean variable for debugging
     */    
    bool isBDebug() const 
    {
        return bDebug;
    }
    
    Particle getLeptons(const StandardModel::lepton p) const 
    {
        return leptons[p];
    }
    
    /**
     * @return the Fermi constant
     */
    double getGF() const 
    {
        return GF;
    }

    /**
     * @brief set the Fermi constant
     * @param GF the Fermi constant
     */
    void setGF(double GF) 
    {
        this->GF = GF;
    }

    /**
     * @return the electromagnetic coupling
     */
    double getAle() const 
    {
        return ale;
    }

    /**
     * @brief set the electromagnetic coupling
     * @param ale the electromagnetic coupling
     */
    void setAle(double ale) 
    {
        this->ale = ale;
    }

    /**
     * @return @f$\Delta\alpha_\mathrm{had}^5(M_Z)@f$
     */
    double getDAle5Mz() const 
    {
        return dAle5Mz;
    }

    /**
     * set @f$\Delta\alpha_\mathrm{had}^5(M_Z)@f$
     * @param dAle5Mz @f$\Delta\alpha_\mathrm{had}^5(M_Z)@f$
     */
    void setDAle5Mz(double dAle5Mz) 
    {
        this->dAle5Mz = dAle5Mz;
    }
    
    /**
     * @return the Higgs mass
     */
    double getMHl() const 
    {
        return mHl;
    }

    /**
     * @brief set the Higgs mass
     * @param mHl the Higgs mass
     */
    void setMHl(double mHl)
    {
        this->mHl = mHl;
    }    
    
    /**
     * @return Theoretical uncertainty in the approximate formula for M_W. 
     */
    double getDelMw() const 
    {
        return delMw;
    }

    /**
     * @return Theoretical uncertainty in the approximate formula for the leptonic weak mixing angle. 
     */
    double getDelSin2th_l() const 
    {
        return delSin2th_l;
    }
    
    /**
     * @return the CKM matrix
     */
    matrix<complex> getVCKM() const
    { 
        return VCKM; 
    }

    /**
     * @brief set the CKM matrix
     * @param VCKM the CKM matrix
     */
    void setVCKM(matrix<complex> VCKM)
    { 
        this->VCKM = VCKM; 
    }

    /**
     * @return the PMNS matrix
     */
    matrix<complex> getUPMNS() const 
    { 
        return UPMNS; 
    }

    /**
     * @brief set the PMNS matrix
     * @param UPMNS the PMNS matrix
     */
    void setUPMNS(matrix<complex> UPMNS)
    { 
        this->UPMNS = UPMNS; 
    }

    /**
     * @return up Yukawa matrix
     */
    matrix<complex> getYu() const
    {
        return Yu;
    }

    /**
     * @return down Yukawa matrix
     */
    matrix<complex> getYd() const 
    {
        return Yd;
    }

    /**
     * @return neutrino Yukawa matrix
     */
    matrix<complex> getYn() const 
    {
        return Yn;
    }

    /**
     * @return charged lepton Yukawa matrix
     */
    matrix<complex> getYe() const 
    {
        return Ye;
    }
    
    /**
     * @brief set the value Standard Model contribution to \f$ \Delta m_{K} \f$
     * @param Dmk Standard Model contribution to \f$ \Delta m_{K} \f$
     */
    void setDmk(double Dmk) 
    {
        this->Dmk = Dmk;
    }
    
    /**
     * @return the value of Standard Model contribution to \f$ \Delta m_{K} \f$
     */
    double getDmk() const 
    {
        return Dmk;
    }
    
    /**
     * @return the Standard Model amplitude of the \f$ D^{0} - \bar{D}^{0} \f$ mixing
     */
    double getSM_M12D() const
    {
        return SM_M12D;
    }

    double getMuw() const 
    {
        return muw;
    }
    
    double getKbarEpsK() const 
    {
        return KbarEpsK;
    }
    
    double getphiEpsK() const 
    {
        return phiEpsK;
    }
    
    double getDeltaMK() const 
    {
        return DeltaMK;
    }

    double GetA() const 
    {
        return A;
    }

    double GetEtab() const 
    {
        return etab;
    }

    double GetLambda() const 
    {
        return lambda;
    }

    double GetRhob() const 
    {
        return rhob;
    }
    
    CKM getCKM() const 
    {
        return myCKM;
    }

    
    ///////////////////////////////////////////////////////////////////////////
    
    /**
     * @return the VEV
     */
    double v() const;

    /**
     * @return the W boson mass at tree level
     */
    double Mw_tree() const;    
        
    /**
     * the running electromagnetic coupling alpha(mu) in the on-shell scheme, 
     * where the top-quark contribution is not included. 
     * @param[in] mu the scale @f$\mu@f$ in GeV
     * @param[in] order (=LO, FULLNLO)
     * @return @f$\alpha@f$
     */
    double ale_OS(const double mu, orders order=FULLNLO) const;
    
    
    //////////////////////////////////////////////////////////////////////// 
    
    /**
     * @return the W boson mass without weak corrections, but with alpha(Mz^2)
     */
    double Mw0() const;
    
    /**
     * @return sin^2 theta_W without weak corrections, but with alpha(Mz^2)
     */
    double s02() const;

    /**
     * @return cos^2 theta_W without weak corrections, but with alpha(Mz^2)
     */
    double c02() const;
    
    
    //////////////////////////////////////////////////////////////////////// 

    /**
     * @return pointer to EWSM object
     */
    EWSM* getEWSM() const 
    {
        return myEWSM;
    }
    
    /**
     * @param[in] s invariant mass squared 
     * @return the leptonic corrections to alpha at Mz
     */
    double DeltaAlphaLepton(const double s) const;

    /**
     * @return the sum of the leptonic and hadronic corrections to alpha at Mz
     */
    double DeltaAlphaL5q() const;
    
    /**
     * @return the total (leptonic+hadronic+top) corrections to alpha at Mz
     */
    double DeltaAlpha() const;
    
    /**
     * @brief electromagnetic coupling alpha at Mz
     * @return alpha(Mz)
     */
    double alphaMz() const;
    
    /**
     * @return the W boson mass
     */
    virtual double Mw() const;

    /**
     * @return Mw^2/Mz^2
     */
    virtual double cW2() const;
    
    /**
     * @return 1-Mw^2/Mz^2
     */
    virtual double sW2() const;
    
    /**
     * @brief effective coupling rho_Z^l
     * @param[in] l lepton
     * @return rho_Z^l
     */
    virtual complex rhoZ_l(const StandardModel::lepton l) const;
    
    /**
     * @brief effective coupling rho_Z^q
     * @param[in] q quark
     * @return rho_Z^q
     */
    virtual complex rhoZ_q(const StandardModel::quark q) const;

    /**
     * @brief effective coupling kappa_Z^l
     * @param[in] l name of lepton
     * @return kappa_Z^l in the SM
     */
    virtual complex kappaZ_l(const StandardModel::lepton l) const;

    /**
     * @brief effective coupling kappa_Z^q
     * @param[in] q name of quark
     * @return kappa_Z^q in the SM
     */
    virtual complex kappaZ_q(const StandardModel::quark q) const;       
    
    /**
     * @brief vector effective coupling for neutral-current interactions
     * @param[in] l lepton
     * @return g_V^l
     */
    virtual complex gVl(const StandardModel::lepton l) const;

    /**
     * @brief vector effective coupling for neutral-current interactions
     * @param[in] q quark
     * @return g_V^q
     */
    virtual complex gVq(const StandardModel::quark q) const;

    /**
     * @brief axial-vector effective coupling for neutral-current interactions
     * @param[in] l lepton
     * @return g_A^l
     */
    virtual complex gAl(const StandardModel::lepton l) const;

    /**
     * @brief axial-vector effective coupling for neutral-current interactions
     * @param[in] q quark
     * @return g_A^q
     */
    virtual complex gAq(const StandardModel::quark q) const; 
    
    /* 
     * @param[in] q name of a quark
     * @return non-factorizable EW-QCD corrections in GeV
     */
    double Delta_EWQCD(const StandardModel::quark q) const;
    
    /**
     * @param[in] q name of a quark
     * @return Radiator functions to the vector current due to the 
     * final-state QED and QCD corrections. 
     */    
    double RVq(const StandardModel::quark q) const;
    
    /**
     * @param[in] q name of a quark
     * @return Radiator functions to the axial-vector current due to the 
     * final-state QED and QCD corrections. 
     */    
    double RAq(const StandardModel::quark q) const;
        
    /**
     * @return Singlet vector corrections to the width of Z->hadrons
     */
    double RVh() const;

    /**
     * @return the total width of the W boson
     */
    virtual double GammaW() const;
    
    /**
     * @return NP contribution to oblique parameter S
     */
    virtual double obliqueS() const 
    {
        return 0.0;
    }
        
    /**
     * @return NP contribution to oblique parameter T
     */
    virtual double obliqueT() const 
    {
        return 0.0;
    }
    
    /**
     * @return NP contribution to oblique parameter U
     */
    virtual double obliqueU() const 
    {
        return 0.0;
    }
    
    /**
     * @return NP contribution to oblique parameter \hat{S}
     */
    virtual double obliqueShat() const 
    {
        return 0.0;
    }
        
    /**
     * @return NP contribution to oblique parameter \hat{T}
     */
    virtual double obliqueThat() const 
    {
        return 0.0;
    }
    
    /**
     * @return NP contribution to oblique parameter \hat{U}
     */
    virtual double obliqueUhat() const 
    {
        return 0.0;
    }

    /**
     * @return NP contribution to oblique parameter V
     */
    virtual double obliqueV() const 
    {
        return 0.0;
    }

    /**
     * @return NP contribution to oblique parameter W
     */
    virtual double obliqueW() const 
    {
        return 0.0;
    }

    /**
     * @return NP contribution to oblique parameter X
     */
    virtual double obliqueX() const 
    {
        return 0.0;
    }

    /**
     * @return NP contribution to oblique parameter Y
     */
    virtual double obliqueY() const 
    {
        return 0.0;
    }

    /**
     * @return SM contribution to epsilon_1
     */
    double epsilon1_SM() const;

    /**
     * @return SM contribution to epsilon_2
     */
    double epsilon2_SM() const;
    
    /**
     * @return SM contribution to epsilon_3
     */
    double epsilon3_SM() const;
    
    /**
     * @return SM contribution to epsilon_b
     */
    double epsilonb_SM() const;
    
    /**
     * @return epsilon_1
     */
    virtual double epsilon1() const;

    /**
     * @return epsilon_2
     */
    virtual double epsilon2() const;
    
    /**
     * @return epsilon_3
     */
    virtual double epsilon3() const;
    
    /**
     * @return epsilon_b
     */
    virtual double epsilonb() const;

    virtual double deltaGVb() const;

    virtual double deltaGAb() const;
    
    
    ////////////////////////////////////////////////////////////////////////
    // CKM parameters
    
    // Angles
    double getBeta() const;
    double getGamma() const;
    double getAlpha() const;
    double getBetas() const;

    // Lambda_q
    complex getlamt() const;
    complex getlamc() const;
    complex getlamu() const;

    complex getlamt_d() const;
    complex getlamc_d() const;
    complex getlamu_d() const;

    complex getlamt_s() const;
    complex getlamc_s() const;
    complex getlamu_s() const;

    // Sides
    double getRt() const;
    double getRts() const;
    double getRb() const;

    
    ////////////////////////////////////////////////////////////////////////
protected:
    double GF, ale, dAle5Mz, mHl;
    double delMw, delSin2th_l;
    matrix<complex> VCKM, UPMNS, Yu, Yd, Yn, Ye;
    double lambda, A, rhob, etab;
    double muw, KbarEpsK, phiEpsK, DeltaMK, Dmk, SM_M12D;
    Particle leptons[6];
    EWSM* myEWSM;
    CKM myCKM;
    
    virtual void SetParameter(const std::string, const double&);
    
    
    ////////////////////////////////////////////////////////////////////////    
private:
    bool bDebug; // for debugging
    bool FlagFixedAllSMparams, FlagEWCHMN, FlagEWABC, FlagEWABC2, FlagEWBURGESS;
    bool FlagR0bApproximate, FlagWithoutNonUniversalVC;
    bool computeCKM, computeYe, computeYn;
    StandardModelMatching* myStandardModelMatching;
    
};

#endif	/* STANDARDMODEL_H */

