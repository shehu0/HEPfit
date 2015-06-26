/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MVGAMMA_H
#define	MVGAMMA_H

#include <StandardModel.h>
#include <ThObservable.h>



/**
 * @class MVgamma
 * @ingroup flavour
 * @brief A class for the decay B -> K^*gamma. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 */
class MVgamma  : public ThObservable {
public:
    MVgamma(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i);
    virtual ~MVgamma();
    void updateParameters();
    
    double GF;            //Fermi constant
    double ale;           //alpha electromagnetic
    double MM;            //initial meson mass
    double MM2;           // square of the initial meson mass
    double MV;            //final vector meson mass
    double Mb;            //b quark mass
    double mu_b;          //b mass scale
    double width;         //initial meson width
    double Ms;            //s quark mass
    double MW;            //W boson mass
    gslpp::complex lambda_t;     //Vckm factor
    gslpp::complex h[2];         //parameter that contains the contribution from the hadronic hamiltonian
    double lambda;        //cinematic parameter
    
    /*LCSR fit parameters*/
    double r_1T1, r_2T1, m_RT1, m_fit2T1;
    
    gslpp::vector<complex> ** allcoeff;
    gslpp::vector<complex> ** allcoeffprime;
    
    gslpp::complex C_7;
    
    gslpp::complex C_7p;
    
    
    
    /**
    * @brief \f$ T_1 \f$
    * @return return the transverse form factor T_1(q^2)
    */
    double T_1();

    /**
    * @brief \f$ H_V(+) \f$ 
    * @return return the helicity amplitude H_V(+)
    */
    complex H_V_p();
    
    /**
    * @brief \f$ H_V(-) \f$ 
    * @return return the helicity amplitude H_V(-)
    */
    complex H_V_m();
    
    /**
    * @brief \f$ H_V(+) \f$ 
    * @return return the helicity amplitude H_V(+)
    */
    complex H_V_p_bar();
    
    /**
    * @brief \f$ H_V(-)\f$ 
    * @return return the helicity amplitude H_V(-)
    */
    complex H_V_m_bar();
    
    
    
private:
    StandardModel::meson meson;
    StandardModel::meson vectorM;
};


class BR_MVgamma : public MVgamma{
public:
    
    /**
    * @brief \f$ BR \f$ 
    */
    BR_MVgamma(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i);
    
    /**
    * @return return the clean observable BR_e
    */
    double computeThValue ();

private:
    StandardModel::meson meson;
    StandardModel::meson vectorM;
};

class ACP_MVgamma : public MVgamma{
public:
    
    /**
    * @brief \f$ BR \f$ 
    */
    ACP_MVgamma(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i);
    
    /**
    * @return return the clean observable BR_e
    */
    double computeThValue ();

private:
    StandardModel::meson meson;
    StandardModel::meson vectorM;
};
#endif	/* MVLL_H */

