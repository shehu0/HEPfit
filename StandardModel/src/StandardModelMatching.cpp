/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "StandardModelMatching.h"
#include "StandardModel.h"
#include "QCD.h"
#include <gsl/gsl_sf_dilog.h>
#include <gsl/gsl_sf_zeta.h>
#include <gsl/gsl_sf_clausen.h>
#include <stdexcept>


StandardModelMatching::StandardModelMatching(const StandardModel & SM_i) 
: ModelMatching(), SM(SM_i),
        mcdbd2(5, NDR, NLO),
        mcdbs2(5, NDR, NLO),
        mcdd2(5, NDR, NLO),
        mcdk2(5, NDR, NLO),
        mck(10, NDR, NLO),
        mckcc(10, NDR, NLO),
        mcbsg(8, NDR, NLO),
        mcBMll(13, NDR, NLO),
        mcprimeBMll(13, NDR, NLO),
        mcbnlep(10, NDR, NLO, NLO_ew),
        mcbnlepCC(10, NDR, NLO),
        mcd1(10, NDR, NLO),
        mcd1Buras(10, NDR, NLO),
        mckpnn(1, NDR, NLO, NLO_ew),
        mckmm(1, NDR, NLO),
        mcbsnn(1, NDR, NLO),
        mcbdnn(1, NDR, NLO),
        mcbsmm(6, NDR, NLO),
        mcbdmm(6, NDR, NLO),
        mcDL1(2, NDR, LO),
        Vckm(3, 3, 0)
{
    swa = 0.;
    swb = 0.;
    swc = 0.;
    xcachea = 0.;
    xcacheb = 0.;
    xcachec = 0.;
    

    for (int j=0; j<10; j++) {
        CWD1ArrayLO[j] = 0.; 
        CWD1ArrayNLO[j] = 0.;
        CWbnlepArrayLOqcd[j] = 0.;
        CWbnlepArrayNLOqcd[j] = 0.;
        CWbnlepArrayLOew[j] = 0.;
        CWbnlepArrayNLOew[j] = 0.;
    };
    
    
    for(int j=0; j<19; j++){
        CWBMllArrayLO[j] = 0.;
        CWBMllArrayNLO[j] = 0.;
    }
    
    for(int j=0; j<8; j++){
        CWbsgArrayLO[j] = 0.;
        CWbsgArrayNLO[j] = 0.;
    }
    
    Nc = SM.getNc();
    CF = SM.getCF();
    gamma0 = 6. * (Nc - 1.) / Nc;
    J5 = SM.Beta1(5) * gamma0 / 2. / SM.Beta0(5) / SM.Beta0(5) - ((Nc - 1.)/(2. * Nc) * (-21. + 57./Nc - 19./3. * Nc + 20./3.)) / 2. / SM.Beta0(5);
    BtNDR = 5. * (Nc - 1.) / 2. / Nc + 3. * CF;
}

void StandardModelMatching::updateSMParameters()
{
    Mut = SM.getMut();
    Muw = SM.getMuw();
    Ale = SM.getAle();
    GF = SM.getGF();
    Mw_tree = SM.Mw_tree();
    /* NP models should be added here after writing codes for Mw. */
    if (SM.ModelName()=="StandardModel") {
        Mw = SM.Mw(); /* on-shell Mw */
        sW2 = SM.sW2(); /* on-shell sW2 */
    } else {
        Mw = Mw_tree;
        sW2 = 1.0 - Mw*Mw/SM.getMz()/SM.getMz();
    }
    Vckm = SM.getVCKM();
    lam_t = SM.computelamt();
    L=2*log(Muw/Mw);
    mu_b = SM.getMub();
    
}

double StandardModelMatching::x_c(const double mu, const orders order) const 
{
    double mc = SM.Mrun(mu, SM.getQuarks(QCD::CHARM).getMass_scale(), 
                        SM.getQuarks(QCD::CHARM).getMass(), order);
    return mc*mc/Mw/Mw; 
}

double StandardModelMatching::x_t(const double mu, const orders order) const 
{
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), order);
#if SUSYFIT_DEBUG & 1
    std::cout << "mt(" << mu << "," << order << ")=" << mt << std::endl;
#endif
    return mt*mt/Mw/Mw; 
}

double StandardModelMatching::mt2omh2(const double mu, const orders order) const 
{
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), order);
    return (mt / SM.getMHl())*(mt / SM.getMHl());
}

double StandardModelMatching::S0(double x) const 
{
    return S0(x, x);
}

double StandardModelMatching::S0(double x, double y) const 
{ // Buras 2000 Appendix
    if (fabs(1. - y / x) < LEPS){
        return ((x * (-4. + 15. * x - 12. * x * x + x * x * x +
            6. * x * x * log(x))) / (4. * pow(-1. + x, 3.)));
    }
    else
        return (x * y * ((1./4. + 3./2. / (1. - x) - 3./4. / pow(1. - x, 2.)) *
            log(x) / (x - y) +
            (1./4. + 3./2. / (1. - y) - 3./4. / pow(1. - y, 2.)) *
            log(y) / (y - x) -
            3./4. / (1. - x) / (1. - y)));
}

double StandardModelMatching::S0p( double x) const
{
    double x2 = x * x;
    return (x * (4. - 22. * x + 15. * x2 + 2. * x2 * x + x2 * x2 - 18. * x2 * log(x)) / 4. / pow(x - 1., 4.));
}

double StandardModelMatching::S11(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double xm3 = (x - 1.) * (x - 1.) * (x - 1.);
    double xm4 = xm3 * (x - 1);
    
    return (x * (4. - 39. * x + 168. * x2 + 11. * x3) / 4. / xm3
            + 3. * x3 * gsl_sf_dilog(1. - x) * (5. + x) / xm3
            + 3. * x * log(x)*(-4. + 24. * x - 36. * x2 - 7. * x3 - x4) / 2.
            / xm4 + 3. * x3 * pow(log(x), 2.) * (13. + 4. * x + x2) / 2.
            / xm4);
}

double StandardModelMatching::S18(double x) const 
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double xm2 = (x - 1.) * (x - 1.);
    double xm3 = xm2 * (x - 1.);
    return ((-64. + 68. * x + 17. * x2 - 11. * x3) / 4. / xm2
            + pow(M_PI, 2.) * 8./3. / x + 2. * gsl_sf_dilog(1. - x) * (8. - 24. * x
            + 20. * x2 - x3 + 7. * x4 - x4 * x) / (x * xm3)
            + log(x)*(-32. + 68. * x - 32. * x2 + 28. * x3 - 3. * x4)
            / (2. * xm3) + x2 * pow(log(x), 2.) * (4. - 7. * x + 7. * x2
            - 2. * x3) / (2. * xm2 * xm2));
}

double StandardModelMatching::S1(double x) const 
{
    return (CF * S11(x) + (Nc - 1.) / 2. / Nc * S18(x));
}

/*******************************************************************************
 * loop functions misiak base for b -> s gamma                                 * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - magnetic and chromomagnetic penguins                      *         
 *                 - semileptonic                                              * 
 * ****************************************************************************/

double StandardModelMatching::A0t(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    
    return ((-3. * x3 + 2. * x2)/(2. * pow(1. - x, 4.)) * log(x) + 
            (22. * x3 - 153. * x2 + 159. * x - 46.)/(36. * pow(1. - x, 3.)));
}

double StandardModelMatching::B0t(double x) const
{
    return( x / (4.* (1. - x) * (1. - x)) * log(x) + 1. / (4. * (1. - x)) );
}

double StandardModelMatching::C0t(double x) const
{
    return( (3. * x * x + 2. * x) / (8. * (1. - x) * (1. - x)) * log(x) + (-x * x + 6. * x) / (8. * (1. - x)) );
}

double StandardModelMatching::D0t(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    
    return( (-3. * x4 + 30. * x3 - 54. * x2 + 32.* x - 8.) / (18.* pow(1. - x, 4)) * log(x)
            + (-47. * x3 + 237. * x2 - 312. * x + 104.) / (108. * pow(1.- x, 3.)) );
}

double StandardModelMatching::E0t(double x) const
{
//***// CHECK THIS FUNCTION    double x2 = x * x;
    
    return (-9. * x * x + 16. * x - 4.) / (6. * pow((1.- x),4) ) * log(x) + (-7. * x * x * x - 21. * x * x + 42. * x + 4.)/(36 * pow((1. - x), 3));
    //return (x * (18. - 11. * x - x * x) / (12. * pow(1. - x, 3.) + x * x * (15. - 16. * x + 4. * x * x) /(6. * pow(1. - x, 4.)) * log(x) - 2./3. * log(x)));
}

double StandardModelMatching::F0t(double x) const
{
    double x2 = x * x;
    double xm3 = (1. - x)*(1. - x)*(1. - x);
    
    return ((3. * x2) / (2. * xm3 * (1. - x)) * log(x) + ( 5. * x2 * x - 9. * x2 + 30. * x - 8.)/
            (12. * xm3));
}

double StandardModelMatching::A1t(double x, double mu) const
{
    double x2 = x * x;
    double x3 = x * x * x;
    double x4 = x * x * x * x;
    double xm2 = pow(1. - x, 2);
    double xm3 = xm2 * (1. - x);
    double xm4 = xm3 * (1. - x);
    double xm5 = xm4 * (1. - x);
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), FULLNNLO);
    
    return ((32. * x4 + 244. * x3 - 160. * x2 + 16. * x)/9./xm4 * gsl_sf_dilog(1.- 1./x) +
            (-774. * x4 - 2826. * x3 + 1994. *x2 - 130. * x + 8.)/81./xm5 * log(x) + 
            (-94. * x4 - 18665. * x3 + 20682. * x2 - 9113. * x + 2006.)/243./xm4 +
            ((-12. * x4 - 92. * x3 + 56. * x2)/3./(1.-x)/xm4 * log(x) + 
            (-68. * x4 - 202. * x3 - 804. * x2 + 794. * x - 152.)/27./xm4) * 2. * log(mu/mt));
}

double StandardModelMatching::B1t(double x, double mu) const
{
    double x2 = x * x;
    double xm2 = pow(1. - x, 2);
    double xm3 = pow(1. - x, 3);
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), FULLNNLO);
    
    return (-2. * x)/xm2 * gsl_sf_dilog(1.- 1./x) + (-x2 + 17. * x)/(3. * xm3)*log(x) + (13. * x + 3.)/(3. * xm2) + 
            ( (2. * x2 + 2. * x)/xm3*log(x) + (4. * x)/xm2 ) * 2. * log(mu / mt);
    /*(2. * x)/xm2 * gsl_sf_dilog(1.-x) + (3. * x2 + x)/xm3 * log(x) * log(x) + (-11. * x2 - 5. * x)/(3. * xm3) * log(x) +
            (-3. * x2 + 19. * x)/(3. * xm2) + 16. * x * (2. * (x - 1.) - (1. + x) * log(x))/(4. * xm3) * log(mu / Mw);*/
}

double StandardModelMatching::C1t(double x, double mu) const
{
    double x2 = x * x;
    double x3 = x * x2;
    double xm2 = pow(1. - x, 2);
    double xm3 = pow(1. - x, 3);
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), FULLNNLO);
    
    return (-x3 - 4. * x)/xm2 * gsl_sf_dilog(1.- 1./x) + (3. * x3 + 14. * x2 + 23 * x)/(3. * xm3)*log(x) + 
            (4. * x3 + 7. * x2 + 29. * x)/(3. * xm2) + ( (8. * x2 + 2. * x)/xm3*log(x) + (x3 + x2 + 8. * x)/xm2) * 2. * log(mu / mt);
    /*(x3 + 4. * x)/xm2 * gsl_sf_dilog(1.-x) + (x4 - x3  + 20. * x2)/(2. * xm3) * log(x) * log(x) +
            (-3. * x4 - 3. * x3 - 35. * x2 + x)/(3. * xm3) * log(x) + (4. * x3 + 7. * x2 + 29. * x)/(3. * xm2) +
            16. * x * (-8. + 7. * x + x3 - 2. * (1. + 4. * x) * log(x))/(8. * xm3) * log(mu / Mw);*/
}

double StandardModelMatching::D1t(double x, double mu) const
{
    double x2 = x * x;
    double x3 = x * x2;
    double x4 = x * x3;
    double xm4 = pow(1. - x, 4);
    double xm5 = pow(1. - x, 5);
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), FULLNNLO);
    
    return (380. * x4 - 1352. * x3 + 1656. * x2 - 784. * x + 256.)/(81. * xm4) * gsl_sf_dilog(1.- 1./x) +
            (304. * x4 + 1716. * x3 - 4644. * x2 + 2768. * x - 720.)/(81. * xm5)*log(x) +
            (-6175. * x4 + 41608. * x3 - 66723. * x2 + 33106. * x - 7000.)/(729. * xm4) +
            ( (648. * x4 - 720. * x3 - 232. * x2 - 160. * x + 32.)/(81. * xm5)*log(x) + 
            (-352. * x4 + 4912. * x3 - 8280. * x2 + 3304. * x - 880.)/(243. * xm4) ) * 2. * log(mu / mt);
}

double StandardModelMatching::F1t(double x, double mu) const
{
    double x2 = x * x;
    double x3 = x * x2;
    double x4 = x * x3;
    double xm4 = pow(1. - x, 4);
    double xm5 = pow(1. - x, 5);
    double mt = SM.Mrun(mu, SM.getQuarks(QCD::TOP).getMass_scale(), 
                        SM.getQuarks(QCD::TOP).getMass(), FULLNNLO);
    
    return ((4. * x4 - 40. * x3 - 41. * x2 - x)/3./xm4 * gsl_sf_dilog(1.- 1./x) +
            (-144. * x4 + 3177. * x3 + 3661. * x2 + 250. * x - 32.)/108./xm5 * log(x)
            + (-247. * x4 + 11890. * x3 + 31779. * x2 - 2966. * x + 1016.)/648./xm4
            + ((17. * x3 + 31. * x2)/xm5 * log(x) + (- 35. * x4 + 170. * x3 + 447. * x2  
            + 338. * x - 56.)/18./xm4)* 2. * log(mu/mt));
}

double StandardModelMatching::Y0(double x) const
{
    return( x/8. * ((4 - 5 * x + x * x + 3 * x * log(x))/pow(x - 1., 2.)) );
}

double StandardModelMatching::Y1(double x, double mu) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double logx = log(x);
    double xm = 1. - x;
    double xm2 = xm * xm;
    double xm3 = xm2 * xm;
    
    return ((10. * x + 10. * x2 + 4. * x3)/(3 * xm2) - (2. * x - 8. * x2 - x3 - x4)/xm3 * logx + (2. * x - 14. * x2 + x3 - x4)/(2. * xm3) * pow(logx, 2.) + (2. * x + x3)/xm2 * gsl_sf_dilog(1. - x) + 16. * x * (-4. + 3. * x + x3 - 6. * x * logx)/(8. * -xm3) * log(mu / Mw));
}

double StandardModelMatching::C7LOeff(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    
    return( (3. * x3 - 2. * x2) / (4. * pow(x - 1., 4.)) * log(x) + (-8. * x3 - 5. * x2 +
              7. * x) / (24. * pow(x-1.,3.)));
}

double StandardModelMatching::C8LOeff(double x) const
{
    return( -3. * x * x / (4. * pow( x - 1., 4.)) * log(x) + (-x * x * x + 5. * x * x + 2. * x) / (8. * pow(x - 1., 3)) );
}

double StandardModelMatching::C7NLOeff(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double xm4 = pow(x-1.,4.);
    double xm5 = xm4 * (x - 1);
    double logx = log(x);
    
    double Li2 = gsl_sf_dilog(1.-1./x);
    return( Li2 * ( -16. * x4 - 122. * x3 + 80. * x2 - 8. * x) / (9. * xm4) +
            (6. * x4 + 46. * x3 -28. * x2) / (3. * xm5) * logx * logx +
            (-102. * x4 * x - 588. * x4 - 2262. * x3 + 3244. * x2 - 1364. * x + 208.) / (81. * xm5) * logx +
            (1646. * x4 + 12205. * x3 - 10740. * x2 + 2509. * x - 436.) / (486. * xm4));
}

double StandardModelMatching::C8NLOeff(double x) const
{
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double xm4 = pow(x-1.,4.);
    double xm5 = xm4 * (x - 1);
    double logx = log(x);
    
    double Li2 = gsl_sf_dilog(1.-1./x);
    return(Li2 * ( -4. * x4 + 40. * x3 + 41. * x2 + x) / (6. * xm4) +
            (-17. * x3 - 31. * x2) / (2. * xm5) * logx * logx +
            (-210. * x * x4 + 1086. * x4 + 4893. * x3 + 2857. * x2 - 1994. * x + 280.)/(216. * xm5) * logx +
            (737. * x4 - 14102. * x3 - 28209. * x2 + 610. * x - 508.) / (1296. * xm4));
}


/******************************************************************************/


/*******************************************************************************
 * loop functions Buras base for nonlep. b decays                              * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - ew penguins                                               *
 * ****************************************************************************/

double StandardModelMatching::B0b(double x) const
{
    return ( 0.25 * ( x / (1. - x) + x / (x * x - 2. * x + 1.) * log(x) ) );
}

double StandardModelMatching::C0b(double x) const
{
    return ( x / 8. * ( (x - 6.) / (x - 1.) + (3. * x + 2.) / ( x * x - 2. * x + 1.) * log(x) ) );
}

double StandardModelMatching::D0b(double x) const
{
    double x2 = x * x;
    return ( -4. / 9. * log(x) + (-19. * x2 * x + 25. * x2) / (36. * (x2 * x - 3. * x2 + 3. * x - 1.))
            + (x2 * (5. * x2 - 2. * x - 6.) ) / (18. * pow(x - 1.,4.)) * log(x) );
}

double StandardModelMatching::E0b(double x) const
{
    double x2 = x * x;
    
    return ( -2./3. * log(x) + (18. * x - 11. * x2 - x2 * x) / (12.* (- x2 * x +3. * x2 -3. * x +1.)) +
            (x2 * (15. - 16. * x +4. * x2))/(6.*pow(1.-x,4.)) *log(x) );
}

/******************************************************************************/
/* loop functions for rare K and B decays, K-> pi nu nu & B-> Xs nu nu        */
/******************************************************************************/

double StandardModelMatching::X0t(double x) const{
    return((x/8.)*((x+2.)/(x-1.)+(3.*x -6)/(x-1.)/(x-1.)*log(x)));
}

double StandardModelMatching::X1t(double x) const{
    
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double xm3 = pow(1.-x,3.);
    double logx = log(x);
    
    return (-(29. * x - x2 -4. * x3) / (3. * (1. - x) * (1. - x))
            - logx * (x + 9. * x2 - x3 - x4) / xm3
            + logx * logx * (8. * x + 4. * x2 + x3 - x4) / (2. * xm3)
            - gsl_sf_dilog(1.-x) * (4. * x - x3) / ((1. - x) * (1. - x))
            - 8. * x * log(Mut*Mut/Muw/Muw) * (8. - 9. * x + x3 + 6. * logx)/8./xm3 );
  }

double StandardModelMatching::Xewt(double x, double a, double mu) const{
    double b = 0.;
    // WARNING: check consistency of EW scheme choice (see Gorbahn's NNLO papers)
    double swsq = (M_PI * Ale )/( sqrt(2) * GF * Mw * Mw);
    
    double A[17], C[17];
    
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x3 * x;
    double x5 = x4 * x;
    double x6 = x5 * x;
    double x7 = x6 * x;
    double x8 = x7 * x;
    double M_PI2 = M_PI * M_PI;
    double a2 = a * a;
    double a3 = a2 * a;
    double a4 = a3 * a;
    double a5 = a4 * a;
    double a6 = a5 * a;
    double xm2 = (x - 1.) * (x - 1.);
    double xm3 = xm2 * (x - 1.);
    double axm = a * x - 1.;
    double logx = log(x);
    double loga = log(a);
    
    A[0] = (16. - 48. * a) * M_PI2 + (288. * a - (32. - 88. * a) * M_PI2 ) * x
        + (2003. * a + 4. * (4. - 6. * a - a2 ) * M_PI2 )* x2
        + (9. * a * (93. + 28. * a) - 4. * a * (3. - 2. * a + 8. * a2) * M_PI2 ) * x3
        + (3. * a * (172. - 49. * a - 32. * a2) + 4. * a * (20. - a + 16. * a2 ) * M_PI2 ) * x4
        - (3. * a * (168. + 11. * a - 24. * a2 ) + 4. * a * (45. + 8. *a2) * M_PI2) * x5
        + 96. * a * M_PI2 * x6;
    
    A[1] = -768. * x - (525. - 867. * a)  * x2 + (303. + 318. * a) * x3 - 195. * a * x4;
    
    A[2] = -8.*(95. - 67. *  a + 11. * a2 ) * x2 + 2. * (662. - 78. *  a - 177. * a2 + 40. * a3 ) * x3
        - (608. + 476. *  a - 595. * a2 + 114. * a3 ) * x4 
        + (44. + 188. *  a - 321. * a2 + 103. * a3 - 8. * a4 ) * x5
        - a*(28. - 72. *  a + 33. * a2 - 4. * a3 ) * x6;
    
    A[3] = +48. - 10.*(57. + 4. * a) * x+ 51.*(29. + 10. * a) * x2 -
        (841. + 1265. * a) * x3 + (308. + 347. * a) * x4
        - (28. - 40. * a) * x5 + 12. * a * x6 ;
    
    A[4] = + 768. + (816. - 768. * a) * x+ (1240. - 1232. * a) * x2
        - 4.*(415. + 2.  * a) * x3 + (311. + 722.  * a) * x4
        + (145. - 267. * a) * x5 - (36. + 51. * a) * x6 + 20. * a * x7 ;
    
    A[5] = + 328. * x- (536. + 900. * a) * x2 + (208. + 1584. * a + 670. * a2 ) * x3
        - a * (668. + 1161. *  a + 225. * a2 ) * x4
        + a2 * (479. + 362. *  a + 28. * a2 ) * x5
        - a3 *(143. + 42. * a) * x6 + 16. * a4 * x7;
    
    A[6] = + 32. - 4.*(44. - 9. * a) * x + (384. - 322. *  a - 400. * a2 ) * x2
        - (400. - 869. *  a - 1126. * a2 - 696. * a3 ) * x3
        + 2.*(80. - 488. *  a - 517. * a2 - 631. * a3 - 264. * a4 ) * x4
        + (48. + 394. *  a + 269. * a2 + 190. * a3 + 882. * a4 + 196. * a5 ) * x5
        - (64. - 58. *  a - 89. * a2 - 95. * a3 + 34. * a4 + 296. * a5 + 32. * a6 ) * x6
        + (16. - 59. *  a - 79. * a2 + 256. * a3 - 239. * a4 
        + 57. * a5 + 48. * a6 ) * x7
        + (1. - a) * (1. - a) * (1. - a) * a2 * (29. + 16. * a) * x8 ;
    
    A[7] = + 28. * a2 * x2 - 32. * a3 * x3;
    
    A[8] = - 288. + 36.*(1. + 8. * a) * x + 6.*(647. + 87. * a) * x2 + 5.*(55. - 927. *  a - 132. * a2 ) * x3
        - (1233. + 98. *  a - 879. * a2 - 192. * a3 ) * x4 
        + (360. + 1371. *  a - 315. * a2 - 264. * a3 ) * x5
        - 24. * a * (17. - 4. * a2) * x6;
    
    A[9] = + 32. + 4.*(-44. + 29. * a) * x- 12.*(-32. + 77. *  a + 31. * a2 ) * x2
        + 2.*(-200. + 837. *  a + 767. * a2 + 182. * a3 ) * x3 
        - 2.*(-80. + 625. *  a + 905. * a2 + 520. * a3 + 82. * a4 ) * x4
        + (48. + 1079. *  a + 590. * a2 + 1002. * a3 + 462. * a4 + 32. * a5 ) * x5
        + (-64. - 1160. *  a - 501. * a2 - 364. * a3 - 486. * a4 - 72. * a5 ) * x6
        + (16. + 729. *  a + 1038. * a2 + 38. * a3 + 238. * a4 + 52. * a5 ) * x7
        - a*(192. + 743. *  a + 50. * a3 + 12. * a4 ) * x8 + 192. * a2 * x8 * x;
    
    A[10] = + 16. * x + 324. * x2 - 36. * x4;
    
    A[11] = + 216. * x - 672. * x2 + 152. * x3;
    
    A[12] = - 16. * x + (16. - 42. * a) * x2 + (16. + 21. *  a + 60. * a2 ) * x3
        - (16 - 21. *  a + 45. * a2 + 32. * a3 ) * x4 - a2 * (7. - 24. * a) * x5;
    
    A[13] = - 32. + (144. - 68. * a) * x + (-240. + 334. *  a + 332. * a2 ) * x2
        + (160. - 551. *  a - 660. * a2 - 364. * a3 ) * x3
        + a * (329. + 451. *  a + 650. * a2 + 164. * a3 ) * x4 
        + (-48. - a - 59. * a2 - 523. * a3 - 316. * a4 - 32. * a5 ) * x5
        + (16. - 43. *  a -93. * a2 + 255. * a3 + 287. * a4 + 32. * a5 ) * x6 
        - a2 * (-29. + 42. *  a + 103. * a2 + 8. * a3 ) * x7;

    A[14] = - 144.*(1. - a)*(1. - a) * x2 + 144. * (1. - a) * (1. - a) * x3 - 36. * (1. - a) * (1. - a) * x4;
    
    A[15] = - 32. + 96. *  a + (48. - 32. * a) * x - 176. * a * x2 - (16. - 74. * a) * x3 + 212. * a * x4;
    
    A[16] = - 32. + (64. - 100. * a) * x- 8.*(4. - 34. *  a -29. * a2 ) * x2
        - 4. * a * (34. + 170. *  a + 33. * a2 ) * x3
        + 8. * a2 * (47. + 51. *  a + 4. * a2) * x4 - 16. * a3 * (15. + 4. * a) * x5 
        + 32. * a4 * x6;
    
    C[0] = 1. / (3.* a * xm2 * x);
    
    C[1] = phi1(0.25) / (xm3 * axm);
    
    C[2] = phi1(0.25 * a) / (2. * xm3 * axm);
    
    C[3] = phi1(1. / 4. / x) / (2. * xm3 * axm);
    
    C[4] = phi1(0.25 * x) / (2. * xm3 * axm);
    
    C[5] = phi1(a * x * 0.25) / (xm3 * axm);
    
    C[6] = phi2(1. / a / x, 1. / a) / (2. * a2 * x2 * xm3 * axm);
    
    C[7] = loga * log(a) / axm;
    
    C[8] = logx / (xm3 * axm * 3.);
    
    C[9] = logx * logx / ((x-1.) * xm3 * axm * 2. * a * x);
    
    C[10] = 2. * log(mu/Mw) / xm2;
    
    C[11] = logx * 2. * log(mu/Mw) / xm3;
    
    C[12] = loga / (xm2 * axm);
    
    C[13] = logx * loga / (2. * a * xm3 * x * axm);
    
    C[14] = gsl_sf_dilog(1. - a) / xm2;
    
    C[15] = gsl_sf_dilog(1. - x) / a / x;
    
    C[16] = gsl_sf_dilog(1. - a * x) / (a * x * xm2); 
    
    for (int i=0; i<10; i++){
        b += C[i]*A[i];
    }
    
    return (b/128./swsq);
}

double StandardModelMatching::phi1(double z) const{
    if (z >= 0.) {
        if (z < 1){
                return(4. * sqrt(z / (1. - z)) * gsl_sf_clausen(2. * asin(sqrt(z))));
        }
        else{
            return((1. / sqrt(1. - 1. / z)) * (2. * log(0.5 * sqrt(1. - 1. / z)) * log(0.5 * sqrt(1. -1. / z))- 4. * gsl_sf_dilog(0.5 * (1. - sqrt(z / (1. - z)))) - log(4. * z) * log(4. * z)
                    + M_PI * M_PI / 3.));
        }
    }
    else{
        std::stringstream out;
        out << z;
        throw std::runtime_error("StandardModelMatching::phi1(double z)" + out.str() + " <0");
    }
    return(0.);
}

double StandardModelMatching::phi2(double x, double y) const{
    double l = sqrt((1. - x - y) * (1. - x - y) - 4. * x * y);
    
    if ((l * l) >= 0. || (sqrt(x) + sqrt(y)) <= 1.){
        return( 1. / l * (M_PI * M_PI/3. + 2. * log(0.5 * (1. + x - y - l)) * log(0.5 * (1. - x + y - l)) - log(x) * log(y) - 2. * gsl_sf_dilog(0.5 * (1. + x - y - l)) - 2. * gsl_sf_dilog(0.5 * (1. -x + y - l))));
    }
    else if((l * l) < 0. || (sqrt(x) + sqrt(y)) > 1.){
        return(2./( -l * l) * (gsl_sf_clausen(2. * acos((-1. + x + y)/(2. * sqrt(x * y))))
                +gsl_sf_clausen(2. * acos((1. + x - y) / (2. * sqrt(x))))
                +gsl_sf_clausen(2. * acos((1. - x + y) / (2. * sqrt(y))))));
    }
    else{
        std::stringstream out;
        out << x;
        throw std::runtime_error("StandardModelMatching::phi2(double x, double y) wrong" + out.str());
    }
    return(0.);
}

/*******************************************************************************
 * Wilson coefficients Buras base for Delta B = 2 observables                  *                                           
 * ****************************************************************************/

 std::vector<WilsonCoefficient>& StandardModelMatching::CMdbd2() 
{
    double gammam = 6. * CF;
    double Bt;  
    
    
    double xt = x_t(Mut);
    complex co = GF / 4. / M_PI * Mw * SM.computelamt_d();
    
    vmcdb.clear();

    switch (mcdbd2.getScheme()) {
        case NDR:
            Bt = BtNDR;
            break;
        case HV:
        case LRI:
        default:
            std::stringstream out;
            out << mcdbd2.getScheme();
            throw std::runtime_error("StandardModel::CMdb2(): scheme " + out.str() + "not implemented"); 
    }

    mcdbd2.setMu(Mut);
    
    switch (mcdbd2.getOrder()) {
        case NNLO:
        case NLO:
            mcdbd2.setCoeff(0, co * co * 4. * (SM.Als(Mut, FULLNLO) / 4. / M_PI * (S1(xt) + //* CHECK ORDER *//
                    (Bt + gamma0 * log(Mut / Mw)) * S0(xt, xt) + 2. * gammam * S0p(xt) * log(Mut / Mw))), NLO);
#if SUSYFIT_DEBUG & 1
    std::cout << "Mw = " << Mw << " xt(muw=" << Muw << ")= " << xt << "matching of DB=2: S0(xt) = " << S0(xt) << 
                ", S1(xt) = " << S1(xt) +
                    (Bt + gamma0 * log(Muw / Mw)) * S0(xt, xt) + 2. * gammam * S0p(xt) * log(Muw / Mw) 
            << ", lambdat_d^2 = " << SM.getlamt_d()*SM.getlamt_d() << std::endl;
#endif
        case LO:
            mcdbd2.setCoeff(0, co * co * 4. * (S0(xt, xt)), LO);
            break;
        default:
            std::stringstream out;
            out << mcdbd2.getOrder();
            throw std::runtime_error("StandardModelMatching::CMdbd2(): order " + out.str() + "not implemented"); 
    }
    

    vmcdb.push_back(mcdbd2);
    return(vmcdb);
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMdbs2() 
{
    double gammam = 6. * CF;
    double Bt;
    double xt = x_t(Mut);
    complex co = GF / 4. / M_PI * Mw * SM.computelamt_s();

    vmcds.clear();

    switch (mcdbs2.getScheme()) {
        case NDR:
            Bt = BtNDR;
            break;
        case HV:
        case LRI:
        default:
            std::stringstream out;
            out << mcdbs2.getScheme();
            throw std::runtime_error("StandardModel::CMdbs2(): scheme " + out.str() + "not implemented"); 
    }

    mcdbs2.setMu(Mut);
 
    switch (mcdbs2.getOrder()) {
        case NNLO:
        case NLO:          
            mcdbs2.setCoeff(0, co * co * 4. * (SM.Als(Mut, FULLNLO) / 4. / M_PI * (S1(xt) + //* CHECK ORDER *//
                    (Bt + gamma0 * log(Mut / Mw)) * S0(xt, xt) + 2. * gammam * S0p(xt) * log(Mut / Mw))), NLO);
         case LO:
            mcdbs2.setCoeff(0, co * co * 4. * (S0(xt, xt)), LO);
            break;
        default:
            std::stringstream out;
            out << mcdbs2.getOrder();
            throw std::runtime_error("StandardModelMatching::CMdbs2(): order " + out.str() + "not implemented"); 
    }    

    vmcds.push_back(mcdbs2);
    return(vmcds);
}

/*******************************************************************************
 * Wilson coefficients Buras base for Delta S = 2 observables                  *
 * Comment: they look empty because they are computed in Flavour/EvolDF2.cpp   *
 *          due to historical reasons.                                         *
 * ****************************************************************************/

 std::vector<WilsonCoefficient>& StandardModelMatching::CMdk2() 
{
    vmck2.clear();
    
    mcdk2.setMu(Mut);
 
    switch (mcdk2.getOrder()) {
        case NNLO:
        case NLO:
            mcdk2.setCoeff(0, 0., NLO);
        case LO:
            mcdk2.setCoeff(0, 0., LO);
            break;
        default:
            std::stringstream out;
            out << mcdk2.getOrder();
            throw std::runtime_error("StandardModelMatching::CMdk2(): order " + out.str() + "not implemented"); 
    }

    vmck2.push_back(mcdk2);
    return(vmck2);
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMd1Buras()
{    
    vmcd1Buras.clear();
    
    switch (mcd1Buras.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcd1Buras.getScheme();
            throw std::runtime_error("StandardModel::CMd1Buras(): scheme " + out.str() + "not implemented"); 
    }

    mcd1Buras.setMu(Muw);
    
    switch (mcd1Buras.getOrder()) {
        case NNLO:
        case NLO:
            mcd1Buras.setCoeff(0, SM.Als(Muw, FULLNLO) / 4. / M_PI  * 11./2. , NLO); //* CHECK ORDER *//
            mcd1Buras.setCoeff(1, SM.Als(Muw, FULLNLO) / 4. / M_PI * (-11./6.) , NLO);
            for (int j=2; j<10; j++){
            mcd1Buras.setCoeff(j, 0., NLO);    
            }
            case LO:
            mcd1Buras.setCoeff(0, 0., LO);
            mcd1Buras.setCoeff(1, 1., LO);
            for (int j=2; j<10; j++){
            mcd1Buras.setCoeff(j, 0., LO);
            }
            break;
        default:
            std::stringstream out;
            out << mcd1Buras.getOrder();
            throw std::runtime_error("StandardModelMatching::CMd1Buras(): order " + out.str() + "not implemented"); 
    }
        
    vmcd1Buras.push_back(mcd1Buras);
    
    return(vmcd1Buras);

}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMd1()
{ 
    vmcd1.clear();
    
    switch (mcd1.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcd1.getScheme();
            throw std::runtime_error("StandardModel::CMd1(): scheme " + out.str() + "not implemented"); 
    }

    mcd1.setMu(Muw);
    
    switch (mcd1.getOrder()) {
        case NNLO:
        case NLO:
            mcd1.setCoeff(0, SM.Als(Muw, FULLNLO) / 4. / M_PI  * 15. , NLO); //* CHECK ORDER *//
            for (int j=1; j<10; j++){
            mcd1.setCoeff(j, 0., NLO);
            }
        case LO:
            mcd1.setCoeff(0,  0. , LO);
            mcd1.setCoeff(1,  1. , LO);
            for (int j=2; j<10; j++){
            mcd1.setCoeff(j, 0., LO);
            }
            break;
        default:
            std::stringstream out;
            out << mcd1.getOrder();
            throw std::runtime_error("StandardModelMatching::CMd1(): order " + out.str() + "not implemented"); 
    }
      
    vmcd1.push_back(mcd1);
    
    return(vmcd1);
    
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMdd2() 
{
    vmcd2.clear();

    switch (mcdd2.getScheme()) {
        case NDR:
        case HV:
        case LRI:
          break; 
        default:
            std::stringstream out;
            out << mcdd2.getScheme();
            throw std::runtime_error("StandardModel::CMdd2(): scheme " + out.str() + "not implemented"); 
    }

    mcdd2.setMu(Muw);
 
    switch (mcdd2.getOrder()) {
        case NNLO:
        case NLO:
            for(int i=0; i<5; i++)
                mcdd2.setCoeff(i, 0., NLO);
        case LO:
            for(int j=0; j<5; j++)
                mcdd2.setCoeff(j, 0., LO);
            break;
        default:
            std::stringstream out;
            out << mcdd2.getOrder();
            throw std::runtime_error("StandardModelMatching::CMdd2(): order " + out.str() + "not implemented"); 
    }

    vmcd2.push_back(mcdd2);
    return(vmcd2);
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMK(){
    
    double xt = x_t(Muw);
    
    vmck.clear();
    
    switch (mck.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mck.getScheme();
            throw "StandardModel::CMK(): scheme " + out.str() + "not implemented";
    }

    mck.setMu(Muw);
    
    switch (mck.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<10; j++){
                mck.setCoeff(j, lam_t * SM.Als(Muw, FULLNLO) / 4. / M_PI * //* CHECK ORDER *//
                                setWCbnlep(j, xt,  NLO), NLO);
                mck.setCoeff(j, lam_t * Ale / 4. / M_PI *
                                setWCbnlepEW(j, xt), NLO_ew);
                }
        case LO:
            for (int j=0; j<10; j++){
                mck.setCoeff(j, lam_t *  setWCbnlep(j, xt,  LO), LO);
                mck.setCoeff(j, 0., LO_ew); 
                }                   
            break;
        default:
            std::stringstream out;
            out << mck.getOrder();
            throw "StandardModelMatching::CMK(): order " + out.str() + "not implemented";
    }

    vmck.push_back(mck);
    return(vmck);
}

/*******************************************************************************
 * Wilson coefficients Buras base for K -> pi pi decays                        * 
 * operator basis: - current current                                           *
 * ****************************************************************************/
 std::vector<WilsonCoefficient>& StandardModelMatching::CMKCC(){
    
    double xt = x_t(Muw);
    
    vmckcc.clear();
    
    switch (mckcc.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mckcc.getScheme();
            throw "StandardModel::CMKCC(): scheme " + out.str() + "not implemented";
    }

    mckcc.setMu(Muw);
    
    switch (mckcc.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<2; j++){
                mckcc.setCoeff(j, lam_t * setWCbnlep(j, xt, NLO), NLO); 
            }
            for (int j=2; j<10; j++){
                mckcc.setCoeff(j, 0. , NLO); 
            }
        case LO:
            for (int j=0; j<2; j++){
                mckcc.setCoeff(j, lam_t * setWCbnlep(j, xt, LO), LO); 
            }
            for (int j=2; j<10; j++){
                mckcc.setCoeff(j, 0. , LO); 
            }
            break;
        default:
            std::stringstream out;
            out << mckcc.getOrder();
            throw "StandardModelMatching::CMKCC(): order " + out.str() + "not implemented";
    }

    vmckcc.push_back(mckcc);
    return(vmckcc);
}

    
/*******************************************************************************
 * Wilson coefficients misiak base for b -> s gamma                            * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - magnetic and chromomagnetic penguins                      *         
 *                 - semileptonic                                              * 
 * ****************************************************************************/
 std::vector<WilsonCoefficient>& StandardModelMatching::CMbsg() 
{    
    double xt = x_t(Muw);
    complex co = 1.; // (- 4. * GF / sqrt(2)) * SM.computelamt_s(); THIS SHOULD ALREADY BE IMPLEMENTED IN THE OBSERVABLE 
    
    vmcbsg.clear();
    
    switch (mcbsg.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcbsg.getScheme();
            throw std::runtime_error("StandardModel::CMbsg(): scheme " + out.str() + "not implemented"); 
    }

    mcbsg.setMu(Muw);
    
    switch (mcbsg.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<8; j++){
            mcbsg.setCoeff(j, co * SM.Als(Muw, FULLNLO) / 4. / M_PI * setWCbsg(j, xt,  NLO) , NLO);//* CHECK ORDER *//
            }
        case LO:
            for (int j=0; j<8; j++){
            mcbsg.setCoeff(j, co * setWCbsg(j, xt,  LO), LO);
            }
            break;
        default:
            std::stringstream out;
            out << mcbsg.getOrder();
            throw std::runtime_error("StandardModelMatching::CMbsg(): order " + out.str() + "not implemented"); 
    }
    
    vmcbsg.push_back(mcbsg);
    return(vmcbsg);
}


/*******************************************************************************
 * Wilson coefficients calcoulus, misiak base for b -> s gamma                  *  
 * ****************************************************************************/

double StandardModelMatching::setWCbsg(int i, double x, orders order)
{    
    sw =  sqrt( (M_PI * Ale )/( sqrt(2) * GF * Mw * Mw) ) ;

    if ( swa == sw && xcachea == x){
        switch (order){
        case NNLO:
        case NLO:
            return ( CWbsgArrayNLO[i] );
            break;
        case LO:
            return ( CWbsgArrayLO[i] );
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
        }
    }
    
    swa = sw; xcachea = x;
    // this function returns the effective Wilson coefficients if  CWbsgArrayNLO[7] = C8NLOeff(x);
    //                                                             CWbsgArrayNLO[6] = C7NLOeff(x);
    //                                                             CWbsgArrayLO[6] = C7LOeff(x);
    //                                                             CWbsgArrayLO[7] = C8LOeff(x);
    // or the standard one if CWbsgArrayNLO[7] = -0.5 * A0t(x)- 23./36.;
    //                        CWbsgArrayNLO[6] = -0.5 * F0t(x)- 1./3.;
    //                        CWbsgArrayLO[6] = 0.;
    //                        CWbsgArrayLO[7] = 0.;
    switch (order){
        case NNLO:
        case NLO:
            CWbsgArrayNLO[0] = 15.;
            CWbsgArrayNLO[3] = E0t(x)-(2./3.);
            CWbsgArrayNLO[6] = C7NLOeff(x);//-0.5 * A0t(x)- 23./36.;
            CWbsgArrayNLO[7] = C8NLOeff(x);//-0.5 * F0t(x)- 1./3.;
            CWbsgArrayNLO[8] = (1-4.*sw*sw) / sw *C0t(x) - 1./(sw*sw) *
                                B0t(x) - D0t(x) + 38./27. + 1./(4.*sw*sw);
            CWbsgArrayNLO[9] = 1./(sw*sw) * (B0t(x) - C0t(x)) -1./(4.*sw*sw);
        case LO:
            CWbsgArrayLO[1] = 1.;
            CWbsgArrayLO[6] = C7LOeff(x);//0.;
            CWbsgArrayLO[7] = C8LOeff(x);//0.;
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
            }
    
    switch (order){
        case NNLO:
        case NLO:
            return ( CWbsgArrayNLO[i] );
            break;
        case LO:
            return ( CWbsgArrayLO[i] );
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
        }
}




/*******************************************************************************
 * Wilson coefficients misiak base for B -> K^*ll                              * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - magnetic and chromomagnetic penguins                      *         
 *                 - semileptonic                                              * 
 * ****************************************************************************/
    std::vector<WilsonCoefficient>& StandardModelMatching::CMBMll() 
    {    
    double xt = x_t(Muw); //* ORDER FULLNNLO*//
    
    vmcBMll.clear();
    
    switch (mcBMll.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcBMll.getScheme();
            throw std::runtime_error("StandardModel::CMBKstrall(): scheme " + out.str() + "not implemented"); 
    }

    mcBMll.setMu(Muw);
    
    switch (mcBMll.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<13; j++){
            mcBMll.setCoeff(j, SM.Als(Muw, FULLNNLO) / 4. / M_PI * setWCBMll(j, xt,  NLO) , NLO);
            }
        case LO:
            for (int j=0; j<13; j++){
            mcBMll.setCoeff(j, setWCBMll(j, xt,  LO), LO);
            }
            break;
        default:
            std::stringstream out;
            out << mcBMll.getOrder();
            throw std::runtime_error("StandardModelMatching::CMBKstrall(): order " + out.str() + "not implemented"); 
    }
   
    vmcBMll.push_back(mcBMll);
    return(vmcBMll);
}
        


 /*******************************************************************************
 * Wilson coefficients calcoulus, misiak base for B -> K^*ll                    *  
 * *****************************************************************************/

double StandardModelMatching::setWCBMll(int i, double x, orders order)
{    
    sw =  sqrt( sW2 ) ;

    if ( swa == sw && xcachea == x){
        switch (order){
        case NNLO:
        case NLO:
            return ( CWBMllArrayNLO[i] );
            break;
        case LO:
            return ( CWBMllArrayLO[i] );
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
        }
    }
    
    swa = sw; xcachea = x;

    switch (order){
        case NNLO:
        case NLO:
            CWBMllArrayNLO[0] = 15. + 6*L;
            CWBMllArrayNLO[3] = E0t(x) - (7./9.) + (2./3.* L);
            CWBMllArrayNLO[6] = -0.5*A1t(x,Muw) + 713./243. + 4./81.*L - 4./9.*CWBMllArrayNLO[3];
            CWBMllArrayNLO[7] = -0.5*F1t(x,Muw) + 91./324. - 4./27.*L - 1./6.*CWBMllArrayNLO[3];
            CWBMllArrayNLO[8] = (1-4.*sW2) / (sW2) *C1t(x,Muw) - 1./(sW2) * B1t(x,Muw) - D1t(x,Muw) + 1./sW2 + 524./729. - 
                    128.*M_PI*M_PI/243. - 16.*L/3. -128.*L*L/81.;
            CWBMllArrayNLO[9] = (B1t(x,Muw) - C1t(x,Muw)) / sW2 - 1./sW2;
        case LO:
            CWBMllArrayLO[1] = 1.;
            CWBMllArrayLO[6] = -0.5*A0t(x) - 23./36.;
            CWBMllArrayLO[7] = -0.5*F0t(x) - 1./3.;
            CWBMllArrayLO[8] = (1-4.*sW2) / (sW2) *C0t(x) - 1./(sW2) * B0t(x) - D0t(x) + 38./27. + 1./(4.*sW2) - (4./9.)*L + 8./9. * log(SM.getMuw()/mu_b); 
            CWBMllArrayLO[9] = 1./(sW2) * (B0t(x) - C0t(x)) -1./(4.*sW2);
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
            }
    
    switch (order){
        case NNLO:
        case NLO:
            return ( CWBMllArrayNLO[i] );
            break;
        case LO:
            return ( CWBMllArrayLO[i] );
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
        }
}
    


/*******************************************************************************
 * Wilson coefficients misiak primed base for B -> K^*ll                       * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - magnetic and chromomagnetic penguins                      *         
 *                 - semileptonic                                              * 
 * ****************************************************************************/
    std::vector<WilsonCoefficient>& StandardModelMatching::CMprimeBMll() 
    {
        vmcprimeBMll.clear();
        mcprimeBMll.setMu(Muw);
        switch (mcprimeBMll.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<13; j++){
            mcprimeBMll.setCoeff(j, 0., NLO);
            }
        case LO:
            for (int j=0; j<13; j++){
            mcprimeBMll.setCoeff(j, 0., LO);
            }
            break;
        default:
            std::stringstream out;
            out << mcprimeBMll.getOrder();
            throw std::runtime_error("StandardModelMatching::CMBKstrall(): order " + out.str() + "not implemented"); 
    }
        vmcprimeBMll.push_back(mcprimeBMll);
        return(vmcprimeBMll);
    }


/******************************************************************************/

/*******************************************************************************
 * Wilson coefficients Buras base for b -> nonlep. decays                      * 
 * operator basis: - current current                                           *         
 *                 - qcd penguins                                              * 
 *                 - magnetic and chromomagnetic penguins                      *         
 *                 - semileptonic                                              *
 * i=0 deltaS=0 deltaC=0;  i=1 1,0 ;                                           *
 * ****************************************************************************/
 std::vector<WilsonCoefficient>& StandardModelMatching::CMbnlep(const int a)
{
    complex lambda;
    
    switch (a) {
        case 0: lambda = SM.computelamt_d();
        break;
        case 1: lambda = SM.computelamt_s();
        break;   
        default:
            std::stringstream out;
            out << a;
            throw std::runtime_error("case" + out.str() + "not implemented; implemented i=0,1,2,3"); 
    }
    
    double xt = x_t(Muw);
    double co = ( GF / sqrt(2));
    
    vmcbnlep.clear();
    
    switch (mcbnlep.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcbnlep.getScheme();
            throw std::runtime_error("StandardModel::CMbsg(): scheme " + out.str() + "not implemented"); 
    }

    mcbnlep.setMu(Muw);
    
    switch (mcbnlep.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<10; j++){
                mcbnlep.setCoeff(j,co * lambda * SM.Als(Muw, FULLNLO) / 4. / M_PI * //* CHECK ORDER *//
                                setWCbnlep(j, xt,  NLO), NLO);
                mcbnlep.setCoeff(j, co * lambda * Ale / 4. / M_PI *
                                setWCbnlepEW(j, xt), NLO_ew);
                }
        case LO:
            for (int j=0; j<10; j++){
                mcbnlep.setCoeff(j, co * lambda *  setWCbnlep(j, xt,  LO), LO);
                mcbnlep.setCoeff(j, 0., LO_ew); 
                }                   
            break;
        default:
            std::stringstream out;
            out << mcbnlep.getOrder();
            throw std::runtime_error("StandardModelMatching::CMbsg(): order " + out.str() + "not implemented"); 
    }

    vmcbnlep.push_back(mcbnlep);
    return(vmcbnlep);
}

/*******************************************************************************
 * Wilson coefficients Buras base for b -> nonlep. decays                      * 
 * operator basis: - current current opertors                                  *         
 * i=0 deltaS=0 deltaC=0;  i=1 1,0 ;  i=2 0,1 ; i=3 1,1                        *
 * ****************************************************************************/
 std::vector<WilsonCoefficient>& StandardModelMatching::CMbnlepCC(const int a) 
{    
    complex lambda1 = 0.;
    //complex lambda2 = 0.;
    //matrix<complex> ckm = SM.getVCKM();
    
    switch (a) {
        case 0: lambda1 = SM.computelamu_d();
                break;
        case 1: lambda1 = SM.computelamu_s();
                break;
        case 2: lambda1 = Vckm(0,2).conjugate()*Vckm(1,0);
                break;
        case 3: lambda1 = Vckm(1,2).conjugate()*Vckm(0,0); 
                break;
        case 4: lambda1 = Vckm(0,2).conjugate()*Vckm(1,1);
                break;
        case 5: lambda1 = Vckm(1,2).conjugate()*Vckm(2,1);
                break;
        default:
            std::stringstream out;
            out << a;
            throw std::runtime_error("case" + out.str() + " not existing; implemented i=0,1,2,3"); 
    }
    
    double xt = x_t(Muw);
    double co = ( GF / sqrt(2));
    
    vmcbnlepCC.clear();
    
    switch (mcbnlepCC.getScheme()) {
        case NDR:
        //case HV:
        //case LRI:
        break;
        default:
            std::stringstream out;
            out << mcbnlepCC.getScheme();
            throw std::runtime_error("StandardModel::CMbsg(): scheme " + out.str() + "not implemented"); 
    }

    mcbnlepCC.setMu(Muw);
    
    switch (mcbnlepCC.getOrder()) {
        case NNLO:
        case NLO:
            for (int j=0; j<2; j++){
                mcbnlepCC.setCoeff(j, co * lambda1 * setWCbnlep(j, xt,  NLO), NLO); 
            }
            for (int j=2; j<10; j++){
                mcbnlepCC.setCoeff(j, 0. , NLO); 
            }
        case LO:
            for (int j=0; j<2; j++){
                mcbnlepCC.setCoeff(j, co * lambda1 *  setWCbnlep(j, xt,  LO), LO); }
            for (int j=2; j<10; j++){
                mcbnlepCC.setCoeff(j, 0. , LO); }
            break;
        default:
            std::stringstream out;
            out << mcbnlepCC.getOrder();
            throw std::runtime_error("StandardModelMatching::CMbsg(): order " + out.str() + "not implemented"); 
    }

    vmcbnlepCC.push_back(mcbnlepCC);
    return(vmcbnlepCC);
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMkpnn() {
    
    //scales assigned to xt, a and Xewt to be checked!
    
    double xt = x_t(SM.getMut());
    double a = 1./mt2omh2(Muw);
    double lambda5 = SM.getLambda()*SM.getLambda()*SM.getLambda()*SM.getLambda()*SM.getLambda();
    
    vmckpnn.clear();
    
    mckpnn.setMu(Mut);
 
    switch (mckpnn.getOrder()) {
        case NNLO:
        case NLO:
            mckpnn.setCoeff(0, SM.Als(SM.getMut(), FULLNLO)/4./M_PI*lam_t.imag()*X1t(xt)/lambda5, NLO);//* CHECK ORDER *//
        case LO:
            mckpnn.setCoeff(0, lam_t.imag()*X0t(xt)/lambda5, LO);
            break;
        default:
            std::stringstream out;
            out << mckpnn.getOrder();
            throw std::runtime_error("StandardModelMatching::CMkpnn(): order " + out.str() + "not implemented"); 
    }
    
    switch (mckpnn.getOrder_ew()) {
        case NLO_ew:
            mckpnn.setCoeff(0, Ale/4./M_PI*lam_t.imag()*Xewt(xt, a, Muw)/lambda5, NLO_ew);
        case LO_ew:
            break; 
        default:
            std::stringstream out;
            out << mckpnn.getOrder();
            throw std::runtime_error("StandardModelMatching::CMkpnn(): order " + out.str() + "not implemented"); 
    }

    vmckpnn.push_back(mckpnn);
    return(vmckpnn);
    
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMkmm() {
    
    //PROBLEMI: mu e sin(theta_weak) e la scala di als
    
    double xt = x_t(Muw);
    
    vmckmm.clear();
    
    mckmm.setMu(Mut);
 
    switch (mckmm.getOrder()) {
        case NNLO:
        case NLO:
            mckmm.setCoeff(0, SM.Als(Muw, FULLNLO)/4./M_PI*lam_t.real()*Y1(xt, Muw)/SM.getLambda(), NLO);//* CHECK ORDER *//
        case LO:
            mckmm.setCoeff(0, lam_t.real()*Y0(xt)/SM.getLambda(), LO);
            break;
        default:
            std::stringstream out;
            out << mckmm.getOrder();
            throw std::runtime_error("StandardModelMatching::CMkmm(): order " + out.str() + "not implemented"); 
    }

    vmckmm.push_back(mckmm);
    return(vmckmm);
    
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMBXsnn() {
    
    double xt = x_t(Muw);
    
    vmcbsnn.clear();
    
    mcbsnn.setMu(Mut);
 
    switch (mcbsnn.getOrder()) {
        case NNLO:
        case NLO:
            mcbsnn.setCoeff(0, (Vckm(2,1).abs() / Vckm(1,2).abs())*
                                SM.Als(Muw, FULLNLO)/4./M_PI*X1t(xt), NLO);//* CHECK ORDER *//
        case LO:
            mcbsnn.setCoeff(0,  (Vckm(2,1).abs() / Vckm(1,2).abs())*
                                X0t(xt), LO);
            break;
        default:
            std::stringstream out;
            out << mcbsnn.getOrder();
            throw std::runtime_error("StandardModelMatching::CMXsnn(): order " + out.str() + "not implemented"); 
    }

    vmcbsnn.push_back(mcbsnn);
    return(vmcbsnn);
    
}

 std::vector<WilsonCoefficient>& StandardModelMatching::CMBXdnn() {
    
    double xt = x_t(Muw);
    
    vmcbdnn.clear();
    
    mcbdnn.setMu(Mut);
 
    switch (mcbdnn.getOrder()) {
        case NNLO:
        case NLO:
            mcbsnn.setCoeff(0, (Vckm(2,2).abs() / Vckm(1,2).abs()) *
                                SM.Als(Muw, FULLNLO)/4./M_PI*X1t(xt), NLO);//* CHECK ORDER *//
        case LO:
            mcbsnn.setCoeff(0,  (Vckm(2,2).abs() / Vckm(1,2).abs()) *
                                X0t(xt), LO);
            break;
        default:
            std::stringstream out;
            out << mcbdnn.getOrder();
            throw std::runtime_error("StandardModelMatching::CXdnn(): order " + out.str() + "not implemented"); 
    }
    
    vmcbdnn.push_back(mcbdnn);
    return(vmcbdnn);
    
}

/*******************************************************************************
 * Wilson coefficients calcoulus, misiak base for B -> mu mu                   *
 * ****************************************************************************/

 std::vector<WilsonCoefficient>& StandardModelMatching::CMbsmm() {
    
    double xt = x_t(Muw);
    
    vmcbsmm.clear();
    
    mcbsmm.setMu(Muw);
 
    switch (mcbsmm.getOrder()) {
        case NNLO:
        case NLO:
            mcbsmm.setCoeff(0, (Vckm(2,2).conjugate() * Vckm(2,1)) *
                                SM.Als(Muw, FULLNLO) / 4. / M_PI * Y1(xt, Muw) / sW2, NLO);//* CHECK ORDER *//
        case LO:
            mcbsmm.setCoeff(0, (Vckm(2,2).conjugate() * Vckm(2,1)) *
                                Y0(xt) / sW2, LO);
            break;
        default:
            std::stringstream out;
            out << mcbsmm.getOrder();
            throw std::runtime_error("StandardModelMatching::CMbsmm(): order " + out.str() + "not implemented");
    }
    
    vmcbsmm.push_back(mcbsmm);
    return(vmcbsmm);
    
}

std::vector<WilsonCoefficient>& StandardModelMatching::CMbdmm() {
    
    double xt = x_t(Muw);
    
    vmcbdmm.clear();
    
    mcbdmm.setMu(Muw);
    
    switch (mcbdmm.getOrder()) {
        case NNLO:
        case NLO:
            mcbdmm.setCoeff(0, (Vckm(2,2).conjugate() * Vckm(2,0)) *
                            SM.Als(Muw, FULLNLO) / 4. / M_PI * Y1(xt, Muw) / sW2, NLO);//* CHECK ORDER *//
        case LO:
            mcbdmm.setCoeff(0, (Vckm(2,2).conjugate() * Vckm(2,0)) *
                            Y0(xt) / sW2, LO);
            break;
        default:
            std::stringstream out;
            out << mcbdmm.getOrder();
            throw std::runtime_error("StandardModelMatching::CMbdmm(): order " + out.str() + "not implemented");
    }
    
    vmcbdmm.push_back(mcbdmm);
    return(vmcbdmm);
    
}


/*******************************************************************************
 * Wilson coefficients calculus, Buras base for nonlep. b decays               *  
 * ****************************************************************************/
double StandardModelMatching::setWCbnlep(int i, double x, orders order) 
{    
    sw =  sqrt( (M_PI * Ale ) / ( sqrt(2) * GF * Mw * Mw) );
    
    if ( swb == sw && xcacheb == x){
        switch (order){
        case NNLO:
        case NLO:
            return (CWbnlepArrayNLOqcd[i]);
            break;
        case LO:
            return (CWbnlepArrayLOqcd[i]);
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted");      
        }
    }
    
    swb = sw; xcacheb = x;
    
    switch (order){
        case NNLO:
        case NLO:
            CWbnlepArrayNLOqcd[0] = 11./2.;
            CWbnlepArrayNLOqcd[1] = -11./6.;
            CWbnlepArrayNLOqcd[2] = -1./6. * (E0b(x) - 2./3.);
            CWbnlepArrayNLOqcd[3] = 0.5 * (E0b(x) - 2./3.);
            CWbnlepArrayNLOqcd[4] = -1./6. * (E0b(x) - 2./3.);
            CWbnlepArrayNLOqcd[5] = 0.5 * (E0b(x) - 2./3.);
        case LO:
            CWbnlepArrayLOqcd[1] = 1.;
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted"); 
        }
    
    switch (order){
        case NNLO:
        case NLO:
            return (CWbnlepArrayNLOqcd[i]);
            break;
        case LO:
            return (CWbnlepArrayLOqcd[i]);
            break;
        default:
            std::stringstream out;
            out << order;
            throw std::runtime_error("order" + out.str() + "not implemeted");      
        }
}

double StandardModelMatching::setWCbnlepEW(int i, double x) 
{     
    sw =  sqrt( (M_PI * Ale ) / ( sqrt(2) * GF * Mw * Mw) ) ;
    
    if ( swb == sw && xcacheb == x){
        return (CWbnlepArrayNLOew[i]);
    }
    
    swc = sw; xcachec = x;
    
    CWbnlepArrayNLOew[1] = -35./18.;
    CWbnlepArrayNLOew[2] = 2. / (3. * sw * sw) * ( 2. * B0b(x) + C0b(x) );
    CWbnlepArrayNLOew[6] = 2./3. * (4. * C0b(x) + D0b(x) - 4./9.);
    CWbnlepArrayNLOew[8] = 2./3. * (4. * C0b(x) + D0b(x) - 4./9. + (1. / (sw * sw)) *
                           (10. * B0b(x) - 4. * C0b(x)) );
    
    return (CWbnlepArrayNLOew[i]);
}

complex StandardModelMatching::S0c() const 
{
    double xc = x_c(SM.getMuc());
    complex co = GF / 2. / M_PI * Mw_tree * SM.computelamc().conjugate(); /* Mw_tree...?? */
    
    return(co * co * S0(xc, xc));
}

complex StandardModelMatching::S0ct() const 
{
    double xc = SM.Mrun4(SM.getMuc(),SM.getQuarks(QCD::CHARM).getMass_scale(),SM.getQuarks(QCD::CHARM).getMass())/Mw;
    xc *= xc;
    double xt = SM.Mrun4(SM.getMuw(),SM.getQuarks(QCD::TOP).getMass_scale(),SM.getQuarks(QCD::TOP).getMass())/Mw;
    xt *= xt;
    double co = GF / 2. / M_PI * Mw;
#if SUSYFIT_DEBUG & 2
    std::cout << "S0(" << xc << "," << xt << ") = " << S0(xc,xt) << std::endl;
#endif
    
    return( co * co * 2. * SM.computelamc().conjugate() * lam_t.conjugate() * S0(xc, xt) );
}

complex StandardModelMatching::S0tt() const
{
    double xt = x_t(Mut);
    complex co = GF / 2. / M_PI * Mw * lam_t.conjugate();
#if SUSYFIT_DEBUG & 2
    std::cout << "S0(" << xt << ") = " << S0(xt,xt) << std::endl;
#endif

    return ( co * co * S0(xt, xt) );
}

double StandardModelMatching::ZDP(const double x, const double y) const
{
    double co = 2. * GF / M_PI / M_PI * Mw * Mw ;

    return co * co / sqrt(2.) * GF * C0t(x) * C0t(y);
}

complex StandardModelMatching::ZDPtt() const
{
    double xt = x_t(Mut);
    
    return (ZDP(xt,xt) * lam_t.conjugate() * lam_t.conjugate());
    
}

complex StandardModelMatching::ZDPct() const
{
    double xt = x_t(Mut);
    double xc = x_c(SM.getMuc());
    
    return (2. * ZDP(xc,xt) * lam_t.conjugate() * SM.computelamc().conjugate());
    
}


/*******************************************************************************
 * Wilson coefficients for Lepton Flavour Violation               *  
 * ****************************************************************************/

std::vector<WilsonCoefficient>& StandardModelMatching::CMDL1() {
    
    vmcDL1.clear();
    
    mcDL1.setMu(Muw);
    
    switch (mcDL1.getOrder()) {
        case LO:
            mcDL1.setCoeff(0, 0., LO);
            mcDL1.setCoeff(1, 0., LO);
            break;
        case NNLO:
        case NLO:
        default:
            std::stringstream out;
            out << mcDL1.getOrder();
            throw std::runtime_error("StandardModelMatching::CMDL1(): order " + out.str() + " not implemented.\nFor lepton flavour violating observables only Leading Order (LO) necessary.");
    }
    
    vmcDL1.push_back(mcDL1);
    return(vmcDL1);
    
}
