#ifndef SOFTSUSYCALL_H
#define	SOFTSUSYCALL_H

#include "gslpp.h"
#include "SUSY.h"
#include <lowe.h>
#include <softsusy.h>

using namespace softsusy;

/**
 * @class SoftSusyCall
 * @ingroup SUSY
 * @brief A class for calling SOFTSUSY.
 * @author HEPfit Collaboration
 * @copyright GNU General Public License
 * @details
 */
class SoftSusyCall {
 public:
  
  /**
   * @brief A SoftSusyCall constructor.
   * @param[in] SUSY_in An object of SUSY class.
   */
  SoftSusyCall(SUSY& SUSY_in);

  // set boundary conditions on the parameters at high/Q_SUSY scale
  void (*boundaryCondition)(MssmSoftsusy &, const DoubleVector &) = EwsbMSSMbcs; 

  // generate higgs and sparticle spectrum
  bool GenerateSpectrum();

 private:
  SUSY& mySUSY;
  QedQcd oneset;
  DoubleVector pars(3); // not really needed
  MssmSoftsusy mssm;
  MssmSoftsusy * r = & mssm;
};

#endif	/* SOFTSUSYCALL_H */

