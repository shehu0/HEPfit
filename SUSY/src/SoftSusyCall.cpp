#include <iostream>
#include <sstream>
#include <stdexcept>
#include "SoftSusyCall.h"
#include <linalg.h>
#include<physpars.h>


using namespace softsusy;


SoftSusyCall::SoftSusyCall(SUSY& SUSY_in) : mySUSY(SUSY_in) { }


void SoftSusyCall::EwsbMSSMbcs(MssmSoftsusy & m, const DoubleVector & /* inputParameters */)
{
  oneset.setAlpha( ALPHA, mySUSY.alphaMz() ); 
  oneset.setAlpha( ALPHAS, mySUSY.getAlsMz() );
  GMU = mySUSY.getGF();
  oneset.setMu( mySUSY.getMz() );
  MZ = mySUSY.getMz();
  m.setData(oneset);
 
  //  oneset.setMass(mBottom, mySUSY.getQuarks(QCD::BOTTOM).getMass()); // scale?
  //  oneset.setPoleMt(mtop);
  //  oneset.setMbMb(mbmb);
  //  mySUSY.getLambda(), mySUSY.getA(), mySUSY.getRhob(), mySUSY.getEtab());
  // set Q_SUSY;
    
  m.setGauginoMass(1, mySUSY.m1.real());   
  m.setGauginoMass(2, mySUSY.m2.real());
  m.setGauginoMass(3, mySUSY.m3);

  m.setAltEwsb(mySUSY.mHptree, mySUSY.muH.real()); // taking mHptree to be MApole

  m.setSoftMassMatrix(mLl, mySUSY.msLhat2.real() );
  m.setSoftMassMatrix(mEr, mySUSY.msEhat2.real() );
  m.setSoftMassMatrix(mQl, mySUSY.msQhat2.real() );
  m.setSoftMassMatrix(mUr, mySUSY.msUhat2.real() );
  m.setSoftMassMatrix(mDr, mySUSY.msDhat2.real() );

  m.setTrilinearMatrix(UA, mySUSY.TUhat.real());
  m.setTrilinearMatrix(DA, mySUSY.TDhat.real());
  m.setTrilinearMatrix(EA, mySUSY.TEhat.real());
}


bool SoftSusyCall::GenerateSpectrum()
{
  // specialise for BC at the EWSB only:
  // gaugeUnification = false, ewsbBCscale = true, mgutGuess=1.0e3, sgnMu=0 since mu is a parameter
  r -> fixedPointIteration(ewsbMSSMbcs, 1.0e3, pars, 0.0, mySUSY.tanb, oneset.toMz(), false, true);
  if ( r->displayProblem().test() ) return false;
    
  sPhysical phys( r->displayPhys() );
   
  mySUSY.mh[0] =  phys.mh0(1); // Higgs masses and mixing 
  mySUSY.mh[1] =  phys.mh0(2);
  mySUSY.mh[2] =  phys.mA0(1);
  mySUSY.mh[3] =  phys.mHpm;
  mySUSY.saeff = phys.thetaH;   

  // the gauge couplings
  //	 MssmSoftsusy::gaugeSLHA
  //	 MssmSoftsusy::hmixSLHA(ostream & out)

  std::cout << "Mgluino = " << phys.mGluino << std::endl;
  
  // chargino masses    
  for (int i = 0; i < 2; i++) {
    mySUSY.mch(i) = fabs( phys.mch(i) );
  }

  // chargino mixings 
  DoubleMatrix u( rot2d(phys.thetaL) ), v( rot2d(phys.thetaR) );

  // implementing positive-only chargino masses 
  if (phys.mch(1) < 0.) { v(1, 1) = -v(1, 1); v(1, 2) = -v(1, 2);}
  if (phys.mch(2) < 0.) { v(2, 1) = -v(2, 1); v(2, 2) = -v(2, 2);}

  // chargino U and V mixing matrises 
  for (int i=0; i<2; i++)
    for (int j=0; j<2; j++) {
      mySUSY.U.assign( i, j, gslpp::complex(u(i+1, j+1), 0.0) );
      mySUSY.V.assign(i, j, gslpp::complex( v(i+1, j+1), 0.0));
    }
  
  // neutralino masses and mixings 
  for (int i = 0; i < 3; i++) {
    mySUSY.mneu(i) = phys.mneut(i);
    for (int j = 0; j < 3; j++) {
      mySUSY.N.assign( i, j, s.mixNeut(j, i) );
    }
  }

  // sfermion mass-squareds
  for (int i = 0; i < 3; i++) {
    if ( i == 2){

      mySUSY.m_sn2(i).push_back( phys.msnu(i+1) * phys.msnu(i+1) );
      
      mySUSY.m_se2(i).push_back(  minimum(phys.me(1, i+1), phys.me(2, i+1)) * minimum(phys.me(1, i+1), phys.me(2, i+1))  );
      mySUSY.m_se2(i+3).push_back(  maximum(phys.me(1, i+1), phys.me(2, i+1)) * maximum(phys.me(1, i+1), phys.me(2, i+1))  );

      mySUSY.m_su2(i).push_back(  minimum(phys.mu(1, i+1), phys.mu(2, i+1)) * minimum(phys.mu(1, i+1), phys.mu(2, i+1))  );
      mySUSY.m_su2(i+3).push_back(  maximum(phys.mu(1, i+1), phys.mu(2, i+1)) * maximum(phys.mu(1, i+1), phys.mu(2, i+1))  );

      mySUSY.m_sd2(i).push_back(  minimum(phys.md(1, i+1), phys.md(2, i+1)) * minimum(phys.md(1, i+1), phys.md(2, i+1))  );
      mySUSY.m_sd2(i+3).push_back(  maximum(phys.md(1, i+1), phys.md(2, i+1)) * maximum(phys.md(1, i+1), phys.md(2, i+1))  );

    } else {

      mySUSY.m_sn2(i).push_back( phys.msnu(i+1)*phys.msnu(i+1) );
      
      mySUSY.m_se2(i).push_back( phys.me(1, i+1)*phys.me(1, i+1) );
      mySUSY.m_se2(i+3).push_back( phys.me(1, i+1)*phys.me(1, i+1) );

      mySUSY.m_su2(i).push_back( phys.mu(1, i+1)*phys.mu(1, i+1) );
      mySUSY.m_su2(i+3).push_back( phys.mu(1, i+1)*phys.mu(1, i+1) );

      mySUSY.m_sd2(i).push_back( phys.md(1, i+1)*phys.md(1, i+1) );
      mySUSY.m_sd2(i+3).push_back( phys.md(1, i+1)*phys.md(1, i+1) );

    }
  }

  DoubleMatrix mat(2, 2);
  
  if (phys.mu(1, 3) < phys.mu(2, 3)) mat = rot2d(phys.thetat);
  else mat = rot2dTwist(phys.thetat);
  for (int i=0; i<2; i++)
    for (int j=0; j<2; j++) {
      mySUSY.Ru.assign(i, j, gslpp::complex( mat(i+1, j+1), 0.0) ); // stop mixing matrix
    }

  if (phys.md(1, 3) < phys.md(2, 3)) mat = rot2d(phys.thetab);
  else mat = rot2dTwist(phys.thetab);
  for (int i=0; i<2; i++)
    for (int j=0; j<2; j++) {
      mySUSY.Rd.assign(i, j, gslpp::complex( mat(i+1, j+1), 0.0) ); // sbottom mixing matrix
    }

  if (phys.me(1, 3) < phys.me(2, 3)) mat = rot2d(phys.thetatau);
  else mat = rot2dTwist(phys.thetatau);
  for (int i=0; i<2; i++)
    for (int j=0; j<2; j++) {
      mySUSY.Rl.assign(i, j, gslpp::complex( mat(i+1, j+1), 0.0) ); // stau mixing matrix
    }
  
  return true;
}



  //
  // boundaryCondition is the function which sets to SUSY BCs at the high scale
  // mGutGuess:  mxGuess is the GUT scale
  // pars: the susy breaking parameters themselves 
  // sgnMu: +1 or -1; if 0 then \mu is set initially as a list of BC parameters
  // tanb: DR bar \tan \beta (at MZ)
  // oneset: should be at MZ and contains the SM data to fit the model to
  // uni: gaugeUnification=true if the user requests true gauge unification, in
  //      which case case mxGuess is the first guess. Returns actual GUT scale.
  // ewsbBCscale: = false (or omitted) means that the boundary condition on
  //              SUSY breaking is set in the usual way. If it is true, the boundary
  //              condition is set to \f$\sqrt{m_{{\tilde t}_1} m_{{\tilde t}_2}} \f$, ie
  //              like in the "pheno MSSM"
  //r.lowOrg(sugraBcs, mGutGuess, pars, sgnMu, tanb, oneset, uni);
  




