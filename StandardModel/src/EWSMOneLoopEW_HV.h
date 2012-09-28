/* 
 * File:   EWSMOneLoopEW_HV.h
 * Author: mishima
 */

#ifndef EWSMONELOOPEW_HV_H
#define	EWSMONELOOPEW_HV_H

#include <PVfunctions.h>
#include "StandardModel.h"
using namespace gslpp;


/**
 * @class EWSMOneLoopEW_HV
 * @brief One-loop EW corrections in the 't Hooft-Feynman gauge
 */
class EWSMOneLoopEW_HV {
public:
    
    /**
     * @brief EWSMOneLoopEW_HV constructor
     * @param[in] SM_i reference to a StandardModel object
     */
    EWSMOneLoopEW_HV(const StandardModel& SM_i);


    ////////////////////////////////////////////////////////////////////////    

    /**
     * @param[in] l name of lepton
     * @return mass of lepton
     */
    double ml(const StandardModel::lepton l) const {
        return SM.getLeptons(l).getMass();
    }

    /**
     * @param[in] q name of quark
     * @param[in] mu renormalization scale
     * @param[in] order (=LO, NLO, NNLO, FULLNLO, FULLNNLO)
     * @return the MSbar mass of u, d, s, c, b or the pole mass of t
     */
    double mq(const StandardModel::quark q, const double mu, const orders order=FULLNLO) const {
        switch(q) {
            case StandardModel::UP:
            case StandardModel::DOWN:
            case StandardModel::STRANGE:
                return SM.Mrun(mu, SM.getQuarks(q).getMass_scale(), SM.getQuarks(q).getMass(), order);
            case StandardModel::CHARM:
            case StandardModel::BOTTOM:
                return SM.Mrun(mu, SM.getQuarks(q).getMass(), order);
            case StandardModel::TOP:
                return SM.getMtpole(); // the pole mass
            default:
                throw std::runtime_error("Error in EWSMOneLoopEW_HV::mq()"); 
        }
    }

    /**
     * @param[in] l name of lepton
     * @param[in] Mw the W-boson mass
     * @return the tree-level vector coupling for Z->l lbar
     * @attention depends on sW2
     */
    double vl(const StandardModel::lepton l, const double Mw) const {
        double sW2 = 1.0 - Mw*Mw/SM.getMz()/SM.getMz();
        return ( al(l) - 2.0*SM.getLeptons(l).getCharge()*sW2 );
    }

    /**
     * @param[in] q name of quark
     * @param[in] Mw the W-boson mass
     * @return the tree-level vector coupling for Z->q qbar
     * @attention depends on sW2
     */
    double vq(const StandardModel::quark q, const double Mw) const {
        double sW2 = 1.0 - Mw*Mw/SM.getMz()/SM.getMz();
        return ( aq(q) - 2.0*SM.getQuarks(q).getCharge()*sW2 );
    }
    
    /**
     * @param[in] l name of lepton
     * @return the tree-level axial-vector coupling for Z->l lbar
     */
    double al(const StandardModel::lepton l) const {
        return ( SM.getLeptons(l).getIsospin() );
    }

    /**
     * @param[in] q name of quark
     * @return the tree-level axial-vector coupling for Z->q qbar
     */
    double aq(const StandardModel::quark q) const {
        return ( SM.getQuarks(q).getIsospin() );
    }
    
    
    ////////////////////////////////////////////////////////////////////////    
       
    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of W boson
     */
    complex SigmaWW_bos(const double mu, const double s, const double Mw) const;
 
    /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @return fermionic contribution to the self-energy function of W boson
     */
    complex SigmaWW_fer(const double mu, const double muForMq, const double s) const;
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of Z boson
     */
    complex SigmaZZ_bos(const double mu, const double s, const double Mw) const;    
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return fermionic contribution to the self-energy function of Z boson
     */
    complex SigmaZZ_fer(const double mu, const double muForMq, const double s, 
                        const double Mw) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of photon 
     */
    complex SigmaGammaGamma_bos(const double mu, const double s, const double Mw) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @return fermionic contribution to the self-energy function of photon 
     */
    complex SigmaGammaGamma_fer(const double mu, const double muForMq, const double s) const;
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of photon 
     */
    complex PiGammaGamma_bos(const double mu, const double s, const double Mw) const;

     /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] l name of lepton
     * @return contribution to the self-energy function of photon from lepton l
     */
    complex PiGammaGamma_fer_l(const double mu, const double s, const StandardModel::lepton l) const;

     /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @param[in] q name of quark
     * @return contribution to the self-energy function of photon from quark q
     */
    complex PiGammaGamma_fer_q(const double mu, const double muForMq, 
                               const double s, const StandardModel::quark q) const;    
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @return fermionic contribution to the self-energy function of photon 
     */
    complex PiGammaGamma_fer(const double mu, const double muForMq, const double s) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of the Z-gamma mixing
     */
    complex SigmaZgamma_bos(const double mu, const double s, const double Mw) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] muForMq renormalization scale for the running quark mass
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return fermionic contribution to the self-energy function of the Z-gamma mixing
     */    
    complex SigmaZgamma_fer(const double mu, const double muForMq, 
                            const double s, const double Mw) const;

    
    ////////////////////////////////////////////////////////////////////////      

    /**
     * @param[in] s momentum-squared
     * @param[in] m1 mass 
     * @param[in] m2 mass
     * @return one-loop function F(s, m1, m2)
     */
    complex F_Hollik(const double s, const double m1, const double m2) const;

    /**
     * @param[in] muIR renormalization scale for a possible IR divergence
     * @param[in] s momentum-squared
     * @param[in] m1 mass 
     * @param[in] m2 mass
     * @return dF(s, m1, m2)/ds
     */
    complex Fprime_Hollik(const double muIR, const double s, const double m1, const double m2) const;
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of W boson
     */
    complex SigmaWW_bos_Hollik(const double mu, const double s, const double Mw) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of Z boson
     */
    complex SigmaZZ_bos_Hollik(const double mu, const double s, const double Mw) const;

    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of photon
     */
    complex SigmaGammaGamma_bos_Hollik(const double mu, const double s, const double Mw) const;
    
    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of photon
     */
    complex PiGammaGamma_bos_Hollik(const double mu, const double s, const double Mw) const;    

    /**
     * @param[in] mu renormalization scale
     * @param[in] s momentum-squared
     * @param[in] Mw the W-boson mass
     * @return bosonic contribution to the self-energy function of the Z-gamma mixing
     */
    complex SigmaZgamma_bos_Hollik(const double mu, const double s, const double Mw) const;

    
    ////////////////////////////////////////////////////////////////////////      
    
private:
    const StandardModel& SM;
    const PVfunctions PV;
    
};

#endif	/* EWSMONELOOPEW_HV_H */

