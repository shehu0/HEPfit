/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "Flavour.h"
#include "MVll.h"
#include <gslpp_complex.h>
#include <boost/bind.hpp>


MVll::MVll(const StandardModel& SM_i, StandardModel::meson meson_i, StandardModel::meson vector_i, StandardModel::lepton lep_i) : mySM(SM_i),
        N_cache(3, 0.),
        V_cache(4, 0.),
        A0_cache(4, 0.),
        A1_cache(3, 0.),
        A2_cache(2, 0.),
        T1_cache(4, 0.),
        T2_cache(3, 0.),
        T3t_cache(2, 0.),
        k2_cache(2, 0.),
        VL0_cache(3, 0.),
        TL0_cache(2, 0.),
        SL_cache(2, 0.),
        Ycache(2, 0.),
        H_V0cache(2, 0.),
        H_V1cache(2, 0.),
        H_V2cache(2, 0.),
        H_Scache(2, 0.),
        H_Pcache(4, 0.)
{
    lep = lep_i;
    meson = meson_i;
    vectorM = vector_i;
    I0_updated = 0;
    I1_updated = 0;
    I2_updated = 0;
    I3_updated = 0;
    I4_updated = 0;
    I5_updated = 0;
    I6_updated = 0;
    I7_updated = 0;
    I8_updated = 0;
    I9_updated = 0;
    I10_updated = 0;
    I11_updated = 0;
    
    VL1_updated = 0;
    VL2_updated = 0;
    TL1_updated = 0;
    TL2_updated = 0;
    VR1_updated = 0;
    VR2_updated = 0;
    TR1_updated = 0;
    TR2_updated = 0;
    VL0_updated = 0;
    TL0_updated = 0;
    VR0_updated = 0;
    TR0_updated = 0;
    SL_updated = 0;
    SR_updated = 0;
    
    gtilde_1updated = 0;
    gtilde_2updated = 0;
    gtilde_3updated = 0;
    
    h_0updated = 0;
    h_pupdated = 0;
    h_mupdated = 0;
    
    w_sigma0 = gsl_integration_workspace_alloc (200);
    w_sigma1 = gsl_integration_workspace_alloc (200);
    w_sigma2 = gsl_integration_workspace_alloc (200);
    w_sigma3 = gsl_integration_workspace_alloc (200);
    w_sigma4 = gsl_integration_workspace_alloc (200);
    w_sigma5 = gsl_integration_workspace_alloc (200);
    w_sigma6 = gsl_integration_workspace_alloc (200);
    w_sigma7 = gsl_integration_workspace_alloc (200);
    w_sigma9 = gsl_integration_workspace_alloc (200);
    w_sigma10 = gsl_integration_workspace_alloc (200);
    w_sigma11 = gsl_integration_workspace_alloc (200);
    
    w_delta0 = gsl_integration_workspace_alloc (200);
    w_delta1 = gsl_integration_workspace_alloc (200);
    w_delta2 = gsl_integration_workspace_alloc (200);
    w_delta3 = gsl_integration_workspace_alloc (200);
    w_delta7 = gsl_integration_workspace_alloc (200);
    w_delta11 = gsl_integration_workspace_alloc (200);
    
    w_Vp = gsl_integration_workspace_alloc (200);
    w_Tp = gsl_integration_workspace_alloc (200);
    w_Vm = gsl_integration_workspace_alloc (200);
    w_Tm = gsl_integration_workspace_alloc (200);
    w_V0 = gsl_integration_workspace_alloc (200);
    w_T0 = gsl_integration_workspace_alloc (200);
    w_S = gsl_integration_workspace_alloc (200);
    
    w_gtilde_1_re = gsl_integration_workspace_alloc (1000);
    w_gtilde_1_im = gsl_integration_workspace_alloc (1000);
    w_gtilde_2_re = gsl_integration_workspace_alloc (1000);
    w_gtilde_2_im = gsl_integration_workspace_alloc (1000);
    w_gtilde_3_re = gsl_integration_workspace_alloc (1000);
    w_gtilde_3_im = gsl_integration_workspace_alloc (1000);
    
    w_h_0_re = gsl_integration_workspace_alloc (1000);
    w_h_0_im = gsl_integration_workspace_alloc (1000);
    w_h_p_re = gsl_integration_workspace_alloc (1000);
    w_h_p_im = gsl_integration_workspace_alloc (1000);
    w_h_m_re = gsl_integration_workspace_alloc (1000);
    w_h_m_im = gsl_integration_workspace_alloc (1000);
}


MVll::~MVll() {
/** Check to see if GSL pointers are released!!*/
}

void MVll::updateParameters(){
    GF = mySM.getGF();
    ale=mySM.getAle();
    Mlep=mySM.getLeptons(lep).getMass();
    MM=mySM.getMesons(meson).getMass();
    MV=mySM.getMesons(vectorM).getMass();
    mu_b = mySM.getMub();
    Mb=mySM.getQuarks(QCD::BOTTOM).getMass();    // add the PS b mass
    Mc=mySM.getQuarks(QCD::CHARM).getMass(); 
    Ms=mySM.getQuarks(QCD::STRANGE).getMass();
    MW=mySM.Mw();
    lambda_t=mySM.computelamt_s();
    width = mySM.getMesons(meson).computeWidth();
    
    switch(vectorM){
        case StandardModel::K_star :
            a_0V=mySM.geta_0V();
            a_1V=mySM.geta_1V();
            dmV=mySM.getdmV();
            
            a_0A0=mySM.geta_0A0();
            a_1A0=mySM.geta_1A0();
            dmA0=mySM.getdmA0();
            
            a_0A1=mySM.geta_0A1();
            a_1A1=mySM.geta_1A1();
            dmA1=mySM.getdmA1();
            
            a_0A12=mySM.geta_0A12();
            a_1A12=mySM.geta_1A12();
            dmA12=mySM.getdmA12();
            
            a_0T1=mySM.geta_0T1();
            a_1T1=mySM.geta_1T1();
            dmT1=mySM.getdmT1();
            
            a_0T2=mySM.geta_0T2();
            a_1T2=mySM.geta_1T2();
            dmT2=mySM.getdmT2();
            
            a_0T23=mySM.geta_0T23();
            a_1T23=mySM.geta_1T23();
            dmT23=mySM.getdmT23();
            
            r_1V=mySM.getr_1V();
            r_2V=mySM.getr_2V();
            m_RV=mySM.getm_RV();
            m_fit2V=mySM.getm_fit2V();
            
            r_2A1=mySM.getr_2A1();
            m_fit2A1=mySM.getm_fit2A1();
            
            r_1A2=mySM.getr_1A2();
            r_2A2=mySM.getr_2A2();
            m_fit2A2=mySM.getm_fit2A2();
            
            r_1A0=mySM.getr_1A0();
            r_2A0=(MM * (r_2A1 - r_1A2 - r_2A2) + MV * (r_2A1 + r_1A2 + r_2A2))/(2.*MV) - r_1A0;//mySM.getr_2A0();
            m_RA0=mySM.getm_RA0();
            m_fit2A0=mySM.getm_fit2A0();
            
            r_1T3t=mySM.getr_1T3t();
            r_2T3t=mySM.getr_2T3t();
            m_fit2T3t=mySM.getm_fit2T3t();
            
            r_2T2= mySM.getr_1T3t() + mySM.getr_2T3t();//mySM.getr_2T2();
            m_fit2T2=mySM.getm_fit2T2();
            
            r_1T1=mySM.getr_1T1();
            r_2T1=r_2T2 - r_1T1;//mySM.getr_2T1();
            m_RT1=mySM.getm_RT1();
            m_fit2T1=mySM.getm_fit2T1();
            
            b=1;
            break;
        case StandardModel::PHI :
            a_0V=mySM.geta_0Vphi();
            a_1V=mySM.geta_1Vphi();
            dmV=mySM.getdmVphi();
            
            a_0A0=mySM.geta_0A0phi();
            a_1A0=mySM.geta_1A0phi();
            dmA0=mySM.getdmA0phi();
            
            a_0A1=mySM.geta_0A1phi();
            a_1A1=mySM.geta_1A1phi();
            dmA1=mySM.getdmA1phi();
            
            a_0A12=mySM.geta_0A12phi();
            a_1A12=mySM.geta_1A12phi();
            dmA12=mySM.getdmA12phi();
            
            a_0T1=mySM.geta_0T1phi();
            a_1T1=mySM.geta_1T1phi();
            dmT1=mySM.getdmT1phi();
            
            a_0T2=mySM.geta_0T2phi();
            a_1T2=mySM.geta_1T2phi();
            dmT2=mySM.getdmT2phi();
            
            a_0T23=mySM.geta_0T23phi();
            a_1T23=mySM.geta_1T23phi();
            dmT23=mySM.getdmT23phi();
            
            r_1V=mySM.getr_1Vphi();
            r_2V=mySM.getr_2Vphi();
            m_RV=mySM.getm_RVphi();
            m_fit2V=mySM.getm_fit2Vphi();
            
            r_2A1=mySM.getr_2A1phi();
            m_fit2A1=mySM.getm_fit2A1phi();
            
            r_1A2=mySM.getr_1A2phi();
            r_2A2=mySM.getr_2A2phi();
            m_fit2A2=mySM.getm_fit2A2phi();
            
            r_1A0=mySM.getr_1A0phi();
            r_2A0=(MM * (r_2A1 - r_1A2 - r_2A2) + MV * (r_2A1 + r_1A2 + r_2A2))/(2.*MV) - r_1A0;//mySM.getr_2A0phi();
            m_RA0=mySM.getm_RA0phi();
            m_fit2A0=mySM.getm_fit2A0phi();
            
            r_1T3t=mySM.getr_1T3tphi();
            r_2T3t=mySM.getr_2T3tphi();
            m_fit2T3t=mySM.getm_fit2T3tphi();
            
            r_2T2=mySM.getr_1T3tphi() + mySM.getr_2T3tphi(); //mySM.getr_2T2phi();
            m_fit2T2=mySM.getm_fit2T2phi();
            
            r_1T1=mySM.getr_1T1phi();
            r_2T1=r_2T2 - r_1T1;//mySM.getr_2T1phi();
            m_RT1=mySM.getm_RT1phi();
            m_fit2T1=mySM.getm_fit2T1phi();
            
            b= 0.489;
            break;
        default:
            std::stringstream out;
            out << vectorM;
            throw std::runtime_error("MVll: vector " + out.str() + " not implemented");
    }
    
    
    h_0[0]=mySM.geth_0();
    h_0[1]=mySM.geth_p();
    h_0[2]=mySM.geth_m();
    
    h_1[0]=mySM.geth_0_1();
    h_1[1]=mySM.geth_p_1();
    h_1[2]=mySM.geth_m_1();
    
    h_2[0]=mySM.geth_0_2();
    h_2[1]=mySM.geth_p_2();
    h_2[2]=mySM.geth_m_2();
    
    allcoeff = mySM.getMyFlavour()->ComputeCoeffBMll(mu_b);   //check the mass scale, scheme fixed to NDR
    allcoeffprime = mySM.getMyFlavour()->ComputeCoeffprimeBMll(mu_b);   //check the mass scale, scheme fixed to NDR
    
    C_1 = ((*(allcoeff[LO]))(0) + (*(allcoeff[NLO]))(0));
    C_2 = ((*(allcoeff[LO]))(1) + (*(allcoeff[NLO]))(1));
    C_3 = ((*(allcoeff[LO]))(2) + (*(allcoeff[NLO]))(2));
    C_4 = ((*(allcoeff[LO]))(3) + (*(allcoeff[NLO]))(3));
    C_5 = ((*(allcoeff[LO]))(4) + (*(allcoeff[NLO]))(4));
    C_6 = ((*(allcoeff[LO]))(5) + (*(allcoeff[NLO]))(5));
    C_7 = ((*(allcoeff[LO]))(6) + (*(allcoeff[NLO]))(6));
    C_9 = ((*(allcoeff[LO]))(8) + (*(allcoeff[NLO]))(8));
    C_10 = ((*(allcoeff[LO]))(9) + (*(allcoeff[NLO]))(9));
    C_S = ((*(allcoeff[LO]))(10) + (*(allcoeff[NLO]))(10));
    C_P = ((*(allcoeff[LO]))(11) + (*(allcoeff[NLO]))(11));
    
    C_7p = (*(allcoeffprime[LO]))(6) + (*(allcoeffprime[NLO]))(6);
    C_9p = (*(allcoeffprime[LO]))(8) + (*(allcoeffprime[NLO]))(8);
    C_10p = (*(allcoeffprime[LO]))(9) + (*(allcoeffprime[NLO]))(9);
    C_Sp = (*(allcoeffprime[LO]))(10) + (*(allcoeffprime[NLO]))(10);
    C_Pp = (*(allcoeffprime[LO]))(11) + (*(allcoeffprime[NLO]))(11);
    
    checkCache();
    
    std::map<std::pair<double, double>, unsigned int >::iterator it;
    
    if (I0_updated == 0) for (it = sigma0Cached.begin(); it != sigma0Cached.end(); ++it) it->second = 0;
    if (I1_updated == 0) for (it = sigma1Cached.begin(); it != sigma1Cached.end(); ++it) it->second = 0;
    if (I2_updated == 0) for (it = sigma2Cached.begin(); it != sigma2Cached.end(); ++it) it->second = 0;
    if (I3_updated == 0) for (it = sigma3Cached.begin(); it != sigma3Cached.end(); ++it) it->second = 0;
    if (I4_updated == 0) for (it = sigma4Cached.begin(); it != sigma4Cached.end(); ++it) it->second = 0;
    if (I5_updated == 0) for (it = sigma5Cached.begin(); it != sigma5Cached.end(); ++it) it->second = 0;
    if (I6_updated == 0) for (it = sigma6Cached.begin(); it != sigma6Cached.end(); ++it) it->second = 0;
    if (I7_updated == 0) for (it = sigma7Cached.begin(); it != sigma7Cached.end(); ++it) it->second = 0;
    if (I9_updated == 0) for (it = sigma9Cached.begin(); it != sigma9Cached.end(); ++it) it->second = 0;
    if (I10_updated == 0) for (it = sigma10Cached.begin(); it != sigma10Cached.end(); ++it) it->second = 0;
    if (I11_updated == 0) for (it = sigma11Cached.begin(); it != sigma11Cached.end(); ++it) it->second = 0;
    
    if (I0_updated == 0) for (it = delta0Cached.begin(); it != delta0Cached.end(); ++it) it->second = 0;
    if (I1_updated == 0) for (it = delta1Cached.begin(); it != delta1Cached.end(); ++it) it->second = 0;
    if (I2_updated == 0) for (it = delta2Cached.begin(); it != delta2Cached.end(); ++it) it->second = 0;
    if (I3_updated == 0) for (it = delta3Cached.begin(); it != delta3Cached.end(); ++it) it->second = 0;
    if (I11_updated == 0) for (it = delta11Cached.begin(); it != delta11Cached.end(); ++it) it->second = 0;
    
    if (VL1_updated == 0) for (it = VpCached.begin(); it != VpCached.end(); ++it) it->second = 0;
    if (TL1_updated == 0) for (it = TpCached.begin(); it != TpCached.end(); ++it) it->second = 0;
    if (VL2_updated == 0) for (it = VmCached.begin(); it != VmCached.end(); ++it) it->second = 0;
    if (TL2_updated == 0) for (it = TmCached.begin(); it != TmCached.end(); ++it) it->second = 0;
    if (VL0_updated == 0) for (it = V0Cached.begin(); it != V0Cached.end(); ++it) it->second = 0;
    if (TL0_updated == 0) for (it = T0Cached.begin(); it != T0Cached.end(); ++it) it->second = 0;
    if (SL_updated == 0) for (it = SCached.begin(); it != SCached.end(); ++it) it->second = 0;
    
    if (gtilde_1updated == 0) for (it = gtilde_1Cached.begin(); it != gtilde_1Cached.end(); ++it) it->second = 0;
    if (gtilde_2updated == 0) for (it = gtilde_2Cached.begin(); it != gtilde_2Cached.end(); ++it) it->second = 0;
    if (gtilde_3updated == 0) for (it = gtilde_3Cached.begin(); it != gtilde_3Cached.end(); ++it) it->second = 0;
    
    if (h_0updated == 0) for (it = h_0Cached.begin(); it != h_0Cached.end(); ++it) it->second = 0;
    if (h_pupdated == 0) for (it = h_pCached.begin(); it != h_pCached.end(); ++it) it->second = 0;
    if (h_mupdated == 0) for (it = h_mCached.begin(); it != h_mCached.end(); ++it) it->second = 0;
    
}

void MVll::checkCache(){
    
    if (MM == k2_cache(0) && MV == k2_cache(1) ) {
        k2_updated = 1;
        z_updated = 1;
    } else {
        k2_updated = 0;
        z_updated = 0;
        k2_cache(0) = MM;
        k2_cache(1) = MV;
    }
    
    if (Mlep == beta_cache) {
        beta_updated = 1;
    } else {
        beta_updated = 0;
        beta_cache = Mlep;
    }
    
    lambda_updated = k2_updated;
    F_updated = lambda_updated * beta_updated;
    
    if (GF == N_cache(0) && ale == N_cache(1) && MM == N_cache(2) && lambda_t == Nc_cache ) {
        N_updated = 1;
    } else {
        N_updated = 0;
        N_cache(0) = GF;
        N_cache(1) = ale;
        N_cache(2) = MM;
        Nc_cache = lambda_t;
    }
    
    if (r_1A2 == A2_cache(0) && r_2A2 == A2_cache(1) ) {
        A2_updated = 1;
    } else {
        A2_updated = 0;
        A2_cache(0) = r_1A2;
        A2_cache(1) = r_2A2;
    }
    

    if (r_1V == V_cache(0) && r_2V == V_cache(1) ) {
        V_updated = 1;
    } else {
        V_updated = 0;
        V_cache(0) = r_1V;
        V_cache(1) = r_2V;
    }

    if (r_1A0 == A0_cache(0) && r_2A0 == A0_cache(1) ) {
        A0_updated = 1;
    } else {
        A0_updated = 0;
        A0_cache(0) = r_1A0;
        A0_cache(1) = r_2A0;
    }

    if ( r_2A1 == A1_cache(0) ) {
        A1_updated = 1;
    } else {
        A1_updated = 0;
        A1_cache(0) = r_2A1;
    }

    if (r_1T1 == T1_cache(0) && r_2T1 == T1_cache(1) ) {
        T1_updated = 1;
    } else {
        T1_updated = 0;
        T1_cache(0) = r_1T1;
        T1_cache(1) = r_2T1;
    }

    if ( r_2T2 == T2_cache(0) ) {
        T2_updated = 1;
    } else {
        T2_updated = 0;
        T2_cache(0) = r_2T2;
    }

    if (a_0V == V_cache(2) && a_1V == V_cache(3) ) {
        V_updated = V_updated * z_updated;
    } else {
        V_updated = 0;
        V_cache(2) = a_0V;
        V_cache(3) = a_1V;
    }

    if (a_0A0 == A0_cache(2) && a_1A0 == A0_cache(3) ) {
        A0_updated = A0_updated * z_updated;
    } else {
        A0_updated = 0;
        A0_cache(2) = a_0A0;
        A0_cache(3) = a_1A0;
    }

    if (a_0A1 == A1_cache(1) && a_1A1 == A1_cache(2) ) {
        A1_updated = A1_updated * z_updated;
    } else {
        A1_updated = 0;
        A1_cache(1) = a_0A1;
        A1_cache(2) = a_1A1;
    }

    if (a_0T1 == T1_cache(2) && a_1T1 == T1_cache(3) ) {
        T1_updated = T1_updated * z_updated;
    } else {
        T1_updated = 0;
        T1_cache(2) = a_0T1;
        T1_cache(3) = a_1T1;
    }

    if (a_0T2 == T2_cache(1) && a_1T2 == T2_cache(2) ) {
        T2_updated = T2_updated * z_updated;
    } else {
        T2_updated = 0;
        T2_cache(1) = a_0T2;
        T2_cache(2) = a_1T2;
    }

    
    if (r_1T3t == T3t_cache(0) && r_2T3t == T3t_cache(1) ) {
        T3t_updated = 1;
    } else {
        T3t_updated = 0;
        T3t_cache(0) = r_1T3t;
        T3t_cache(1) = r_2T3t;
    }
    
    T3_updated = k2_updated * T3t_updated * T2_updated;
    
    VL1_updated = k2_updated * lambda_updated * A1_updated * V_updated;
    VL2_updated = VL1_updated;
    
    TL1_updated = k2_updated * lambda_updated * T1_updated * T2_updated;
    TL2_updated = TL1_updated;
    
    VR1_updated = VL2_updated;
    VR2_updated = VL1_updated;
    
    TR1_updated = TL2_updated;
    TR2_updated = TL1_updated;
    
    if (Mb == SL_cache(0) && Ms == SL_cache(1) ){
        Mb_Ms_updated = 1;
        SL_updated = lambda_updated * A0_updated;
        SR_updated = SL_updated;
    } else {
        Mb_Ms_updated = 0;
        SL_updated = 0;
        SR_updated = SL_updated;
        SL_cache(0) = Mb;
        SL_cache(1) = Ms;
    }
    

    VL0_updated = k2_updated * lambda_updated * A1_updated * A2_updated;
    VR0_updated = VL0_updated;
    TL0_updated = k2_updated * lambda_updated * T2_updated * T3_updated;
    TR0_updated = TL0_updated;

    if (a_0A12 == VL0_cache(0) && a_1A12 == VL0_cache(1) && MV == VL0_cache(2) ){
        VL0_updated = VL0_updated * z_updated;
        VR0_updated = VL0_updated;
    } else {
        VL0_updated = 0;
        VR0_updated = VL0_updated;
        VL0_cache(0) = a_0A12;
        VL0_cache(1) = a_1A12;
        VL0_cache(2) = MV;
    }

    if (a_0T23 == TL0_cache(0) && a_1T23 == TL0_cache(1) ){
        TL0_updated = TL0_updated * k2_updated * z_updated;
        TR0_updated = TL0_updated;
    } else {
        TL0_updated = 0;
        TR0_updated = TL0_updated;
        TL0_cache(0) = a_0T23;
        TL0_cache(1) = a_1T23;
        VL0_cache(2) = MV;
    }
    
    
    if (C_1 == C_1_cache) {
        C_1_updated = 1;
    } else {
        C_1_updated = 0;
        C_1_cache = C_1;
    }
    
    if (C_2 == C_2_cache) {
        C_2_updated = 1;
    } else {
        C_2_updated = 0;
        C_2_cache = C_2;
    }
    
    if (C_3 == C_3_cache) {
        C_3_updated = 1;
    } else {
        C_3_updated = 0;
        C_3_cache = C_3;
    }
    
    if (C_4 == C_4_cache) {
        C_4_updated = 1;
    } else {
        C_4_updated = 0;
        C_4_cache = C_4;
    }
    
    if (C_5 == C_5_cache) {
        C_5_updated = 1;
    } else {
        C_5_updated = 0;
        C_5_cache = C_5;
    }
    
    if (C_6 == C_6_cache) {
        C_6_updated = 1;
    } else {
        C_6_updated = 0;
        C_6_cache = C_6;
    }
    
    if (C_7 == C_7_cache) {
        C_7_updated = 1;
    } else {
        C_7_updated = 0;
        C_7_cache = C_7;
    }
    
    if (C_9 == C_9_cache) {
        C_9_updated = 1;
    } else {
        C_9_updated = 0;
        C_9_cache = C_9;
    }
    
    if (C_10 == C_10_cache) {
        C_10_updated = 1;
    } else {
        C_10_updated = 0;
        C_10_cache = C_10;
    }
    
    if (C_S == C_S_cache) {
        C_S_updated = 1;
    } else {
        C_S_updated = 0;
        C_S_cache = C_S;
    }
    
    if (C_P == C_P_cache) {
        C_P_updated = 1;
    } else {
        C_P_updated = 0;
        C_P_cache = C_P;
    }
    
    if (C_7p == C_7p_cache) {
        C_7p_updated = 1;
    } else {
        C_7p_updated = 0;
        C_7p_cache = C_7p;
    }
    
    if (C_9p == C_9p_cache) {
        C_9p_updated = 1;
    } else {
        C_9p_updated = 0;
        C_9p_cache = C_9p;
    }
    
    if (C_10p == C_10p_cache) {
        C_10p_updated = 1;
    } else {
        C_10p_updated = 0;
        C_10p_cache = C_10p;
    }
    
    if (C_Sp == C_Sp_cache) {
        C_Sp_updated = 1;
    } else {
        C_Sp_updated = 0;
        C_Sp_cache = C_Sp;
    }
    
    if (C_Pp == C_Pp_cache) {
        C_Pp_updated = 1;
    } else {
        C_Pp_updated = 0;
        C_Pp_cache = C_Pp;
    }
    
    if (Mb == Ycache(0) && Mc == Ycache(1) ) {
        Yupdated = C_1_updated * C_2_updated * C_3_updated * C_4_updated * C_5_updated * C_6_updated;
    } else {
        Yupdated = 0;
        Ycache(0) = Mb;
        Ycache(1) = Mc;
    }
    
    if (h_0[0] == h0Ccache[0] && h_1[0] == h0Ccache[1] && h_2[0] == h0Ccache[2]) {
        h0_updated = 1;
    } else {
        h0_updated = 0;
        h0Ccache[0] = h_0[0];
        h0Ccache[1] = h_1[0];
        h0Ccache[2] = h_2[0];
    }
    
    if (h_0[1] == h1Ccache[0] && h_1[1] == h1Ccache[1] && h_2[1] == h1Ccache[2]) {
        h1_updated = 1;
    } else {
        h1_updated = 0;
        h1Ccache[0] = h_0[1];
        h1Ccache[1] = h_1[1];
        h1Ccache[2] = h_2[1];
    }
    
    if (h_0[2] == h2Ccache[0] && h_1[2] == h2Ccache[1] && h_2[2] == h2Ccache[2]) {
        h2_updated = 1;
    } else {
        h2_updated = 0;
        h2Ccache[0] = h_0[2];
        h2Ccache[1] = h_1[2];
        h2Ccache[2] = h_2[2];
    }
    
    if (MM == H_V0cache(0) && Mb == H_V0cache(1)) {
        H_V0updated = N_updated * C_9_updated * Yupdated * VL0_updated * C_9p_updated * VR0_updated * C_7_updated * TL0_updated * C_7p_updated * TR0_updated * h0_updated;
    } else {
        H_V0updated = 0;
        H_V0cache(0) = MM;
        H_V0cache(1) = Mb;
    }
    
    if (MM == H_V1cache(0) && Mb == H_V1cache(1)) {
        H_V1updated = N_updated * C_9_updated * Yupdated * VL1_updated * C_9p_updated * VR1_updated * C_7_updated * TL1_updated * C_7p_updated * TR1_updated * h1_updated;
    } else {
        H_V1updated = 0;
        H_V1cache(0) = MM;
        H_V1cache(1) = Mb;
    }
    
    if (MM == H_V2cache(0) && Mb == H_V2cache(1)) {
        H_V2updated = N_updated * C_9_updated * Yupdated * VL2_updated * C_9p_updated * VR2_updated * C_7_updated * TL2_updated * C_7p_updated * TR2_updated * h2_updated;
    } else {
        H_V2updated = 0;
        H_V2cache(0) = MM;
        H_V2cache(1) = Mb;
    }
    
    H_A0updated = N_updated * C_10_updated * VL0_updated * C_10p_updated * VR0_updated;
    H_A1updated = N_updated * C_10_updated * VL1_updated * C_10p_updated * VR1_updated;
    H_A2updated = N_updated * C_10_updated * VL2_updated * C_10p_updated * VR2_updated;
    
    if (Mb == H_Scache(0) && MW == H_Scache(1)) {
        H_Supdated = N_updated * C_S_updated * SL_updated * C_Sp_updated * SR_updated;
    } else {
        H_Supdated = 0;
        H_Scache(0) = Mb;
        H_Scache(1) = MW;
    }
    
    if (Mb == H_Pcache(0) && MW == H_Pcache(1) && Mlep == H_Pcache(2) && Ms == H_Pcache(3)) {
        H_Pupdated = N_updated * C_P_updated * SL_updated * C_Pp_updated * SR_updated * C_10_updated * C_10p_updated;
    } else {
        H_Pupdated = 0;
        H_Pcache(0) = Mb;
        H_Pcache(1) = MW;
        H_Pcache(2) = Mlep;
        H_Pcache(3) = Ms;
        
    }
    
    I0_updated = F_updated * H_V0updated * H_A0updated * H_Pupdated * beta_updated * H_Supdated;
    I1_updated = F_updated * beta_updated * H_V1updated * H_V2updated * H_A1updated * H_A2updated;
    I2_updated = F_updated * beta_updated * H_V0updated * H_A0updated;
    I3_updated = F_updated * H_V1updated * H_V2updated * H_A1updated * H_A2updated * beta_updated;
    I4_updated = F_updated * H_V1updated * H_V2updated * H_A1updated * H_A2updated;
    I5_updated = F_updated * H_V0updated * H_V1updated * H_V2updated * H_A0updated * H_A1updated * H_A2updated * beta_updated;
    I6_updated = F_updated * H_V1updated * H_V2updated * H_A0updated * H_A1updated * H_A2updated * H_V0updated * beta_updated * H_Supdated;
    I7_updated = I4_updated * beta_updated;
    I8_updated = F_updated * beta_updated * H_Supdated * H_V0updated;
    I9_updated = I6_updated;
    I10_updated = I5_updated;
    I11_updated = I7_updated;
    
    gtilde_1updated = lambda_updated * V_updated * h1_updated * h2_updated;
    gtilde_2updated = lambda_updated * A1_updated * h1_updated * h2_updated;
    gtilde_3updated = lambda_updated * A2_updated * h1_updated * h2_updated * h0_updated;
    
    h_0updated = h0_updated * k2_updated;
    h_pupdated = h1_updated * k2_updated;
    h_mupdated = h2_updated * k2_updated;
    
//    DC7_1updated = lambda_updated * T1_updated * h1_updated * h2_updated * Mb_Ms_updated;
//    DC7_2updated = lambda_updated * T2_updated * h1_updated * h2_updated * Mb_Ms_updated;
//    DC7_3updated = lambda_updated * T2_updated * T3_updated * h1_updated * h2_updated * h0_updated * Mb_Ms_updated;
    
}

/*******************************************************************************
 * Transverse Form Factors                                                     *
 * ****************************************************************************/
double MVll::LCSR_fit1(double q2, double r_1, double r_2, double m_R2, double m_fit2){
    return r_1/( 1. - q2/m_R2 ) + r_2/( 1. - q2/m_fit2 ) ;
}



double MVll::LCSR_fit2(double q2, double r_1, double r_2, double m_fit2){
    return r_1/( 1. - q2/m_fit2 ) + r_2/pow( ( 1. - q2/m_fit2 ) , 2.) ;

}



double MVll::LCSR_fit3(double q2, double r_2, double m_fit2){
    return r_2/( 1. - q2/m_fit2 ) ; 
}



double MVll::z(double q2){
    double t_0 = 12.;
    double t_p=pow(MM + MV,2.);
    return ( sqrt(t_p - q2) - sqrt(t_p - t_0) ) / ( sqrt(t_p - q2) + sqrt(t_p - t_0) );
}



double MVll::lat_fit(double q2, double a_0, double a_1, double dm){
    return 1 / (1 - q2/pow(MM + dm,2.)) * ( a_0 + a_1*z(q2) );
}



double MVll::V(double q2){
    if (q2<CUTOFF)
        return LCSR_fit1(q2, r_1V, r_2V, pow(m_RV, 2.), m_fit2V);
    else
        return lat_fit(q2, a_0V, a_1V, dmV);
}



double MVll::A_0(double q2){
    if (q2<CUTOFF)
        return LCSR_fit1(q2, r_1A0, r_2A0, pow(m_RA0, 2.), m_fit2A0);
    else
        return lat_fit(q2, a_0A0, a_1A0, dmA0);
}



double MVll::A_1(double q2){
    if (q2<CUTOFF)
        return LCSR_fit3(q2, r_2A1, m_fit2A1);
    else
        return lat_fit(q2, a_0A1, a_1A1, dmA1);
}



double MVll::A_2(double q2){
    return LCSR_fit2(q2, r_1A2, r_2A2, m_fit2A2);
}



double MVll::T_1(double q2){
    if (q2<CUTOFF)
        return LCSR_fit1(q2, r_1T1, r_2T1, pow(m_RT1, 2.), m_fit2T1);
    else
        return lat_fit(q2, a_0T1, a_1T1, dmT1);
}



double MVll::T_2(double q2){
    if (q2<CUTOFF)
        return LCSR_fit3(q2, r_2T2, m_fit2T2);
    else
        return lat_fit(q2, a_0T2, a_1T2, dmT2);
}



double MVll::T_3tilde(double q2){
    return LCSR_fit2(q2, r_1T3t, r_2T3t, m_fit2T3t);
}



double MVll::T_3(double q2){
    return (MM*MM - MV*MV)/q2*(T_3tilde(q2) - T_2(q2));
}



double MVll::V_L(int i, double q2){
    switch (i){
        case 0:
            if (q2 < CUTOFF)
                return 1. / ( 4.*MV*MM*(MM + MV)*sqrt(q2) ) * ( pow((MM + MV),2.)*(MM*MM - q2 - MV*MV)*A_1(q2) - lambda(q2)*A_2(q2) );
            else
                return 4*MV/sqrt(q2)*lat_fit(q2, a_0A12, a_1A12, dmA12);
        case 1:
            return 1./2. * ( ( 1. + MV/MM)*A_1(q2) - sqrt(lambda(q2))/ ( MM* (MM + MV) ) * V(q2) );
        case 2:
            return 1./2. * ( ( 1. + MV/MM)*A_1(q2) + sqrt(lambda(q2))/ ( MM* (MM + MV) ) * V(q2) );
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("I: index " + out.str() + " not implemented");
    }
}



double MVll::V_R(int i, double q2){
    if (i != 0) i=3-i;
    return -V_L(i,q2);
}



double MVll::T_L(int i, double q2){
    switch (i){
        case 0:
            if (q2 < CUTOFF)
                return sqrt(q2)/(4.*MM*MM*MV) * ( ( MM*MM+ 3.*MV*MV - q2 ) * T_2(q2) - lambda(q2) / (MM*MM - MV*MV) * T_3(q2) );
            else
                return 2*sqrt(q2)*MV/MM/(MM + MV)*lat_fit(q2, a_0T23, a_1T23, dmT23);
        case 1:
            return (MM*MM - MV*MV) / ( 2.*MM*MM ) * T_2(q2) - sqrt(lambda(q2)) / ( 2.*MM*MM ) * T_1(q2);
        case 2:
            return (MM*MM - MV*MV) / ( 2.*MM*MM ) * T_2(q2) + sqrt(lambda(q2)) / ( 2.*MM*MM ) * T_1(q2);
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("I: index " + out.str() + " not implemented");
    }
}



double MVll::T_R(int i, double q2){
    if (i != 0) i=3-i;
    return -T_L(i,q2);
}



double MVll::S_L(double q2){
    return -sqrt(lambda(q2))/ ( 2.*MM*(Mb + Ms) ) *A_0(q2);
}



double MVll::S_R(double q2){
    return -S_L(q2);
}



/*******************************************************************************
 * Helicity amplitudes                                                         *
 * ****************************************************************************/
gslpp::complex MVll::N(){
    return -(4.*GF*MM*ale*lambda_t)/(sqrt(2.)*4.*M_PI);
}



gslpp::complex MVll::H(double q2, double m){
    double x = 4.*m*m/q2;
    gslpp::complex par;
    
    if (x>1.) par = sqrt(x - 1.) * atan( 1. / sqrt(x - 1.) );
    else par = sqrt(1. - x) * ( log( ( 1. + sqrt(1. - x) ) / sqrt(x) ) - gslpp::complex::i()*M_PI/2.);
    
    if (x == 0.) return (8./ 27. + 4./9. * gslpp::complex::i() * M_PI - 4./9. * log(q2/mu_b/mu_b));
    else return - 4./9. * ( log( m*m/mu_b/mu_b ) - 2./3. - x ) - 4./9. * (2. + x) * par;
}



gslpp::complex MVll::Y(double q2){
    return  - 1./2. * H(q2,0.) * ( C_3 + 4./3.*C_4 + 16. * C_5 + 64./3.*C_6 )
            + H(q2, Mc) * ( 4./3.*C_1 + C_2 + 6.*C_3 + 60.*C_5 ) - 1./2. * H(q2, Mb) * ( 7.*C_3 + 4./3.*C_4 + 76.*C_5 + 64./3.*C_6 );
}



gslpp::complex MVll::H_V(int i, double q2, int bar) {
    gslpp::complex n;
    switch(bar){
        case 0:
            n = N();
            break;
        case 1:
            n = N().conjugate();
            break;
        default:
            std::stringstream out;
            out << bar;
            throw std::runtime_error("H_V: index " + out.str() + " not allowed for an Angular Coefficient");
    }

    return -gslpp::complex::i()*n*( (C_9 + Y(q2))*V_L(i,q2)
            + C_9p*V_R(i,q2)
            + MM*MM/q2*( 2*Mb/MM*( C_7*T_L(i,q2)
            + C_7p*T_R(i,q2) ) - 16*M_PI*M_PI*(h_0[i] + h_1[i] * q2 + h_2[i] * q2*q2)) );
}



gslpp::complex MVll::H_A(int i, double q2, int bar) {
    gslpp::complex n;
    switch(bar){
        case 0:
            n = N();
            break;
        case 1:
            n = N().conjugate();
            break;
        default:
            std::stringstream out;
            out << bar;
            throw std::runtime_error("H_A: index " + out.str() + " not allowed for an Angular Coefficient");
    }
     
    return -gslpp::complex::i()*n*( C_10*V_L(i,q2) 
            + C_10p*V_R(i,q2) );
}



gslpp::complex MVll::H_S(double q2, int bar) {
    gslpp::complex n;
    switch(bar){
        case 0:
            n = N();
            break;
        case 1:
            n = N().conjugate();
            break;
        default:
            std::stringstream out;
            out << bar;
            throw std::runtime_error("H_S: index " + out.str() + " not allowed for an Angular Coefficient");
    }
     
    return gslpp::complex::i()*n*Mb/MW*( C_S*S_L(q2) + 
            C_Sp*S_R(q2) );
}



gslpp::complex MVll::H_P(double q2, int bar) {
    gslpp::complex n;
    switch(bar){
        case 0:
            n = N();
            break;
        case 1:
            n = N().conjugate();
            break;
        default:
            std::stringstream out;
            out << bar;
            throw std::runtime_error("H_S: index " + out.str() + " not allowed for an Angular Coefficient");
    }
     
    return gslpp::complex::i()*n*( Mb/MW*( C_P*S_L(q2) 
            + C_Pp*S_R(q2) ) 
            + 2.*Mlep*Mb/q2*( C_10*( S_L(q2) - Ms/Mb*S_R(q2) ) 
            + C_10p*( S_R(q2) - Ms/Mb*S_L(q2) ) ) );
}



/*******************************************************************************
 * Angular coefficients                                                         *
 * ****************************************************************************/
double MVll::k2(double q2) {
    return (pow(MM,4.) + q2*q2 + pow(MV,4.) -2.*MV*MV*q2 -2.*MM*MM*(q2 + MV*MV))/(4.*MM*MM);
}



double MVll::beta(double q2) {
    return sqrt(1.-4.*Mlep*Mlep/q2);
}



double MVll::lambda(double q2) {
    return 4.*MM*MM*k2(q2);
}



double MVll::F(double q2, double b_i) {
    return sqrt(lambda(q2))*beta(q2)*q2*b_i/(96.*M_PI*M_PI*M_PI*MM*MM*MM);
}



double MVll::I(int i, double q2, int bar) {

    double Mlep2 = Mlep*Mlep;
    double beta2 = beta(q2)*beta(q2);
    

    switch (i){
        case 0: // I1c
            return F(q2,b)*( ( H_V(0,q2,bar).abs2() + H_A(0,q2,bar).abs2() )/2.  +  H_P(q2,bar).abs2()  +  2.*Mlep2/q2*( H_V(0,q2,bar).abs2() 
                    - H_A(0,q2,bar).abs2() )  + beta2*H_S(q2,bar).abs2() );
        case 1: // I1s
            return F(q2,b)*( (beta2 + 2.)/8.*( H_V(1,q2,bar).abs2() + H_V(2,q2,bar).abs2() + H_A(1,q2,bar).abs2() + H_A(2,q2,bar).abs2() )  +
                            Mlep2/q2*( H_V(1,q2,bar).abs2() + H_V(2,q2,bar).abs2() - H_A(1,q2,bar).abs2() - H_A(2,q2,bar).abs2() ) );
        case 2: // I2c
            return -F(q2,b)*beta2/2.*( H_V(0,q2,bar).abs2() + H_A(0,q2,bar).abs2() );
        case 3: // I2s
            return F(q2,b)*beta2/8.*( H_V(1,q2,bar).abs2() + H_V(2,q2,bar).abs2()  +  H_A(1,q2,bar).abs2() + H_A(2,q2,bar).abs2() );
        case 4: // I3
            return -F(q2,b)/2.*( ( H_V(1,q2,bar)*H_V(2,q2,bar).conjugate() ).real()  +  ( H_A(1,q2,bar)*H_A(2,q2,bar).conjugate() ).real() );
        case 5: // I4
            return F(q2,b)*beta2/4.*( ( (H_V(2,q2,bar) + H_V(1,q2,bar))*H_V(0,q2,bar).conjugate() ).real()  +  ( (H_A(2,q2,bar) + H_A(1,q2,bar))*H_A(0,q2,bar).conjugate() ).real() );
        case 6: // I5
            return F(q2,b)*( beta(q2)/2.*( ( (H_V(2,q2,bar) - H_V(1,q2,bar))*H_A(0,q2,bar).conjugate() ).real()  +  ( (H_A(2,q2,bar) - H_A(1,q2,bar))*H_V(0,q2,bar).conjugate() ).real() )  -
                            beta(q2)*Mlep/sqrt(q2)*( H_S(q2,bar).conjugate()*(H_V(1,q2,bar) + H_V(2,q2,bar)) ).real() );
        case 7: // I6s
            return F(q2,b)*beta(q2)*( H_V(2,q2,bar)*(H_A(2,q2,bar).conjugate()) - H_V(1,q2,bar)*(H_A(1,q2,bar).conjugate()) ).real();
        case 8: // I6c
            return 2.*F(q2,b)*beta(q2)*Mlep/sqrt(q2)*( H_S(q2,bar).conjugate()*H_V(0,q2,bar) ).real();
        case 9: // I7
            return F(q2,b)*( beta(q2)/2.*( ( (H_V(2,q2,bar) + H_V(1,q2,bar))*H_A(0,q2,bar).conjugate() ).imag()  +  ( (H_A(2,q2,bar) + H_A(1,q2,bar))*H_V(0,q2,bar).conjugate() ).imag() )  -
                            beta(q2)*Mlep/sqrt(q2)*( H_S(q2,bar).conjugate()*(H_V(2,q2,bar) - H_V(1,q2,bar)) ).imag() );
        case 10: // I8
            return F(q2,b)*beta2/4.*( ( (H_V(2,q2,bar) - H_V(1,q2,bar))*H_V(0,q2,bar).conjugate() ).imag()  +  ( (H_A(2,q2,bar) - H_A(1,q2,bar))*H_A(0,q2,bar).conjugate() ).imag() );
        case 11: // I9
            return F(q2,b)*beta2/2.*( ( H_V(1,q2,bar)*H_V(2,q2,bar).conjugate() ).imag()  +  ( H_A(1,q2,bar)*H_A(2,q2,bar).conjugate() ).imag() );
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("I: index " + out.str() + " not implemented");
    }
}

double MVll::Sigma(int i, double q2) {
    return (I(i, q2,0) + I(i, q2,1))/2;
}

double MVll::Delta(int i, double q2) {
    return (I(i, q2,0) - I(i, q2,1))/2;
}

double MVll::integrateFF(int i, double q_min, double q_max){
    
    if (mySM.getMyFlavour()->getUpdateFlag(meson, vectorM, lep)){
        updateParameters();
        mySM.getMyFlavour()->setUpdateFlag(meson, vectorM, lep, false);
    }
    
    std::pair<double, double > qbin = std::make_pair(q_min, q_max);
   
    switch(i){
        case 0:
            if (V0Cached[qbin] == 0) {
                FV0 = convertToGslFunction( boost::bind( &MVll::getV0, &(*this), _1 ) );
                gsl_integration_qags (&FV0, q_min, q_max, 1.e-5, 1.e-3, 200, w_V0, &avaV0, &errV0);
                cacheV0[qbin] = avaV0;
                V0Cached[qbin] = 1;
            }
            return cacheV0[qbin];
            break;
        case 1:
            if (VpCached[qbin] == 0) {
                FVp = convertToGslFunction( boost::bind( &MVll::getVp, &(*this), _1 ) );
                gsl_integration_qags (&FVp, q_min, q_max, 1.e-5, 1.e-3, 200, w_Vp, &avaVp, &errVp);
                cacheVp[qbin] = avaVp;
                VpCached[qbin] = 1;
            }
            return cacheVp[qbin];
            break;
        case 2:
            if (VmCached[qbin] == 0) {
                FVm = convertToGslFunction( boost::bind( &MVll::getVm, &(*this), _1 ) );
                gsl_integration_qags (&FVm, q_min, q_max, 1.e-5, 1.e-3, 200, w_Vm, &avaVm, &errVm);
                cacheVm[qbin] = avaVm;
                VmCached[qbin] = 1;
            }
            return cacheVm[qbin];
            break;
        case 3:
            if (T0Cached[qbin] == 0) {
                FT0 = convertToGslFunction( boost::bind( &MVll::getT0, &(*this), _1 ) );
                gsl_integration_qags (&FT0, q_min, q_max, 1.e-5, 1.e-3, 200, w_T0, &avaT0, &errT0);
                cacheT0[qbin] = avaT0;
                T0Cached[qbin] = 1;
            }
            return cacheT0[qbin];
            break;
        case 4:
            if (TpCached[qbin] == 0) {
                FTp = convertToGslFunction( boost::bind( &MVll::getTp, &(*this), _1 ) );
                gsl_integration_qags (&FTp, q_min, q_max, 1.e-5, 1.e-3, 200, w_Tp, &avaTp, &errTp);
                cacheTp[qbin] = avaTp;
                TpCached[qbin] = 1;
            }
            return cacheTp[qbin];
            break;
        case 5:
            if (TmCached[qbin] == 0) {
                FTm = convertToGslFunction( boost::bind( &MVll::getTm, &(*this), _1 ) );
                gsl_integration_qags (&FTm, q_min, q_max, 1.e-5, 1.e-3, 200, w_Tm, &avaTm, &errTm);
                cacheTm[qbin] = avaTm;
                TmCached[qbin] = 1;
            }
            return cacheTm[qbin];
            break;
        case 6:
            if (SCached[qbin] == 0) {
                FS = convertToGslFunction( boost::bind( &MVll::getS, &(*this), _1 ) );
                gsl_integration_qags (&FS, q_min, q_max, 1.e-5, 1.e-3, 200, w_S, &avaS, &errS);
                cacheS[qbin] = avaS;
                SCached[qbin] = 1;
            }
            return cacheS[qbin];
            break;
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("MVll::integrateFF: index " + out.str() + " not implemented");
    }
}

double MVll::integrateSigma(int i, double q_min, double q_max){

    if (mySM.getMyFlavour()->getUpdateFlag(meson, vectorM, lep)){
        updateParameters();
        mySM.getMyFlavour()->setUpdateFlag(meson, vectorM, lep, false);
    }
    
    std::pair<double, double > qbin = std::make_pair(q_min, q_max);
    
    switch(i){
        case 0:
            if (sigma0Cached[qbin] == 0) {
                FS0 = convertToGslFunction( boost::bind( &MVll::getSigma0, &(*this), _1 ) );
                gsl_integration_qags (&FS0, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma0, &avaSigma0, &errSigma0);
                cacheSigma0[qbin] = avaSigma0;
                sigma0Cached[qbin] = 1;
            }
            return cacheSigma0[qbin];
            break;
        case 1:
            if (sigma1Cached[qbin] == 0) {
                FS1 = convertToGslFunction( boost::bind( &MVll::getSigma1, &(*this), _1 ) );
                gsl_integration_qags (&FS1, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma1, &avaSigma1, &errSigma1);
                cacheSigma1[qbin] = avaSigma1;
                sigma1Cached[qbin] = 1;
            }
            return cacheSigma1[qbin];
            break;
        case 2:
            if (sigma2Cached[qbin] == 0) {
                FS2 = convertToGslFunction( boost::bind( &MVll::getSigma2, &(*this), _1 ) );
                gsl_integration_qags (&FS2, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma2, &avaSigma2, &errSigma2);
                cacheSigma2[qbin] = avaSigma2;
                sigma2Cached[qbin] = 1;
            }
            return cacheSigma2[qbin];
            break;
        case 3:
            if (sigma3Cached[qbin] == 0) {
                FS3 = convertToGslFunction( boost::bind( &MVll::getSigma3, &(*this), _1 ) );
                gsl_integration_qags (&FS3, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma3, &avaSigma3, &errSigma3);
                cacheSigma3[qbin] = avaSigma3;
                sigma3Cached[qbin] = 1;
            }
            return cacheSigma3[qbin];
            break;
        case 4:
            if (sigma4Cached[qbin] == 0) {
                FS4 = convertToGslFunction( boost::bind( &MVll::getSigma4, &(*this), _1 ) );
                gsl_integration_qags (&FS4, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma4, &avaSigma4, &errSigma4);
                cacheSigma4[qbin] = avaSigma4;
                sigma4Cached[qbin] = 1;
            }
            return cacheSigma4[qbin];
            break;
        case 5:
            if (sigma5Cached[qbin] == 0) {
                FS5 = convertToGslFunction( boost::bind( &MVll::getSigma5, &(*this), _1 ) );
                gsl_integration_qags (&FS5, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma5, &avaSigma5, &errSigma5);
                cacheSigma5[qbin] = avaSigma5;
                sigma5Cached[qbin] = 1;
            }
            return cacheSigma5[qbin];
            break;
        case 6:
            if (sigma6Cached[qbin] == 0) {
                FS6 = convertToGslFunction( boost::bind( &MVll::getSigma6, &(*this), _1 ) );
                gsl_integration_qags (&FS6, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma6, &avaSigma6, &errSigma6);
                cacheSigma6[qbin] = avaSigma6;
                sigma6Cached[qbin] = 1;
            }
            return cacheSigma6[qbin];
            break;
        case 7:
            if (sigma7Cached[qbin] == 0) {
                FS7 = convertToGslFunction( boost::bind( &MVll::getSigma7, &(*this), _1 ) );
                gsl_integration_qags (&FS7, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma7, &avaSigma7, &errSigma7);
                cacheSigma7[qbin] = avaSigma7;
                sigma7Cached[qbin] = 1;
            }
            return cacheSigma7[qbin];
            break;
        case 9:
            if (sigma9Cached[qbin] == 0) {
                FS9 = convertToGslFunction( boost::bind( &MVll::getSigma9, &(*this), _1 ) );
                gsl_integration_qags (&FS9, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma9, &avaSigma9, &errSigma9);
                cacheSigma9[qbin] = avaSigma9;
                sigma9Cached[qbin] = 1;
            }
            return cacheSigma9[qbin];
            break;
        case 10:
            if (sigma10Cached[qbin] == 0) {
                FS10 = convertToGslFunction( boost::bind( &MVll::getSigma10, &(*this), _1 ) );
                gsl_integration_qags (&FS10, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma10, &avaSigma10, &errSigma10);
                cacheSigma10[qbin] = avaSigma10;
                sigma10Cached[qbin] = 1;
            }
            return cacheSigma10[qbin];
            break;
        case 11:
            if (sigma11Cached[qbin] == 0) {
                FS11 = convertToGslFunction( boost::bind( &MVll::getSigma11, &(*this), _1 ) );
                gsl_integration_qags (&FS11, q_min, q_max, 1.e-5, 1.e-3, 200, w_sigma11, &avaSigma11, &errSigma11);
                cacheSigma11[qbin] = avaSigma11;
                sigma11Cached[qbin] = 1;
            }
            return cacheSigma11[qbin];
            break;
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("MVll::integrateSigma: index " + out.str() + " not implemented");
    }
    
}

double MVll::integrateDelta(int i, double q_min, double q_max){
    
    if (mySM.getMyFlavour()->getUpdateFlag(meson, vectorM, lep)){
        updateParameters();
        mySM.getMyFlavour()->setUpdateFlag(meson, vectorM, lep, false);
    }
        
    std::pair<double, double > qbin = std::make_pair(q_min, q_max);
    switch(i){
        case 0:
            if (delta0Cached[qbin] == 0) {
                FD0 = convertToGslFunction( boost::bind( &MVll::getDelta0, &(*this), _1 ) );
                gsl_integration_qags (&FD0, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta0, &avaDelta0, &errDelta0);
                cacheDelta0[qbin] = avaDelta0;
                delta0Cached[qbin] = 1;
            }
            return cacheDelta0[qbin];
            break;
        case 1:
            if (delta1Cached[qbin] == 0) {
                FD1 = convertToGslFunction( boost::bind( &MVll::getDelta1, &(*this), _1 ) );
                gsl_integration_qags (&FD1, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta1, &avaDelta1, &errDelta1);
                cacheDelta1[qbin] = avaDelta1;
                delta1Cached[qbin] = 1;
            }
            return cacheDelta1[qbin];
            break;
        case 2:
            if (delta2Cached[qbin] == 0) {
                FD2 = convertToGslFunction( boost::bind( &MVll::getDelta2, &(*this), _1 ) );
                gsl_integration_qags (&FD2, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta2, &avaDelta2, &errDelta2);
                cacheDelta2[qbin] = avaDelta2;
                delta2Cached[qbin] = 1;
            }
            return cacheDelta2[qbin];
            break;
        case 3:
            if (delta3Cached[qbin] == 0) {
                FD3 = convertToGslFunction( boost::bind( &MVll::getDelta3, &(*this), _1 ) );
                gsl_integration_qags (&FD3, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta3, &avaDelta3, &errDelta3);
                cacheDelta3[qbin] = avaDelta3;
                delta3Cached[qbin] = 1;
            }
            return cacheDelta3[qbin];
            break;
        case 7:
            if (delta7Cached[qbin] == 0) {
                FD7 = convertToGslFunction( boost::bind( &MVll::getDelta7, &(*this), _1 ) );
                gsl_integration_qags (&FD7, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta7, &avaDelta7, &errDelta7);
                cacheDelta7[qbin] = avaDelta7;
                delta7Cached[qbin] = 1;
            }
            return cacheDelta7[qbin];
            break;
        case 11:
            if (delta11Cached[qbin] == 0) {
                FD11 = convertToGslFunction( boost::bind( &MVll::getDelta11, &(*this), _1 ) );
                gsl_integration_qags (&FD11, q_min, q_max, 1.e-5, 1.e-3, 200, w_delta11, &avaDelta11, &errDelta11);
                cacheDelta11[qbin] = avaDelta11;
                delta11Cached[qbin] = 1;
            }
            return cacheDelta11[qbin];
            break;
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("integrateDelta: index " + out.str() + " not implemented"); 
    }
}

gslpp::complex MVll::integrategtilde(int i, double q_min, double q_max){
    
    if (mySM.getMyFlavour()->getUpdateFlag(meson, vectorM, lep)){
        updateParameters();
        mySM.getMyFlavour()->setUpdateFlag(meson, vectorM, lep, false);
    }
        
    std::pair<double, double > qbin = std::make_pair(q_min, q_max);
    switch(i){
        case 0:
            if (gtilde_1Cached[qbin] == 0) {
                Fgtilde_1_re = convertToGslFunction( boost::bind( &MVll::getgtilde_1_re, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_1_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_1_re, &avagtilde_1_re, &errgtilde_1_re);
                Fgtilde_1_im = convertToGslFunction( boost::bind( &MVll::getgtilde_1_im, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_1_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_1_im, &avagtilde_1_im, &errgtilde_1_im);
                cachegtilde_1[qbin] = avagtilde_1_re + gslpp::complex::i() * avagtilde_1_im;
                gtilde_1Cached[qbin] = 1;
            }
            return cachegtilde_1[qbin];
            break;
        case 1:
            if (gtilde_2Cached[qbin] == 0) {
                Fgtilde_2_re = convertToGslFunction( boost::bind( &MVll::getgtilde_2_re, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_2_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_2_re, &avagtilde_2_re, &errgtilde_2_re);
                Fgtilde_2_im = convertToGslFunction( boost::bind( &MVll::getgtilde_2_im, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_2_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_2_im, &avagtilde_2_im, &errgtilde_2_im);
                cachegtilde_2[qbin] = avagtilde_2_re + gslpp::complex::i() * avagtilde_2_im;
                gtilde_2Cached[qbin] = 1;
            }
            return cachegtilde_2[qbin];
            break;
        case 2:
            if (gtilde_3Cached[qbin] == 0) {
                Fgtilde_3_re = convertToGslFunction( boost::bind( &MVll::getgtilde_3_re, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_3_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_3_re, &avagtilde_3_re, &errgtilde_3_re);
                Fgtilde_3_im = convertToGslFunction( boost::bind( &MVll::getgtilde_3_im, &(*this), _1 ) );
                gsl_integration_qags (&Fgtilde_3_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_gtilde_3_im, &avagtilde_3_im, &errgtilde_3_im);
                cachegtilde_3[qbin] = avagtilde_3_re + gslpp::complex::i() * avagtilde_3_im;
                gtilde_3Cached[qbin] = 1;
            }
            return cachegtilde_3[qbin];
            break;
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("integrateDC9: index " + out.str() + " not implemented"); 
    }
}

gslpp::complex MVll::integrateh(int i, double q_min, double q_max){
    
    if (mySM.getMyFlavour()->getUpdateFlag(meson, vectorM, lep)){
        updateParameters();
        mySM.getMyFlavour()->setUpdateFlag(meson, vectorM, lep, false);
    }
        
    std::pair<double, double > qbin = std::make_pair(q_min, q_max);
    switch(i){
        case 0:
            if (h_0Cached[qbin] == 0) {
                Fh_0_re = convertToGslFunction( boost::bind( &MVll::geth_0_re, &(*this), _1 ) );
                gsl_integration_qags (&Fh_0_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_0_re, &avah_0_re, &errh_0_re);
                Fh_0_im = convertToGslFunction( boost::bind( &MVll::geth_0_im, &(*this), _1 ) );
                gsl_integration_qags (&Fh_0_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_0_im, &avah_0_im, &errh_0_im);
                cacheh_0[qbin] = avah_0_re + gslpp::complex::i() * avah_0_im;
                h_0Cached[qbin] = 1;
            }
            return cacheh_0[qbin];
            break;
        case 1:
            if (h_pCached[qbin] == 0) {
                Fh_p_re = convertToGslFunction( boost::bind( &MVll::geth_p_re, &(*this), _1 ) );
                gsl_integration_qags (&Fh_p_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_p_re, &avah_p_re, &errh_p_re);
                Fh_p_im = convertToGslFunction( boost::bind( &MVll::geth_p_im, &(*this), _1 ) );
                gsl_integration_qags (&Fh_p_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_p_im, &avah_p_im, &errh_p_im);
                cacheh_p[qbin] = avah_p_re + gslpp::complex::i() * avah_p_im;
                h_pCached[qbin] = 1;
            }
            return cacheh_p[qbin];
            break;
        case 2:
            if (h_mCached[qbin] == 0) {
                Fh_m_re = convertToGslFunction( boost::bind( &MVll::geth_m_re, &(*this), _1 ) );
                gsl_integration_qags (&Fh_m_re, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_m_re, &avah_m_re, &errh_m_re);
                Fh_m_im = convertToGslFunction( boost::bind( &MVll::geth_m_im, &(*this), _1 ) );
                gsl_integration_qags (&Fh_m_im, q_min, q_max, 1.e-5, 1.e-3, 1000, w_h_m_im, &avah_m_im, &errh_m_im);
                cacheh_m[qbin] = avah_m_re + gslpp::complex::i() * avah_m_im;
                h_mCached[qbin] = 1;
            }
            return cacheh_m[qbin];
            break;
        default:
            std::stringstream out;
            out << i;
            throw std::runtime_error("integrateDC7: index " + out.str() + " not implemented"); 
    }
}
