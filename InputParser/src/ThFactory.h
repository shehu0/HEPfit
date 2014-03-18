/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef THFACTORY_H
#define	THFACTORY_H

#include <ThObservable.h>
#include <ModelObservable.h>
#include <StandardModel.h>
#include <EW.h>

/**
 * @class ThFactory
 * @ingroup InputParser 
 * @brief A class for an interface to theoretical predictions for observables. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details 
 *
 * @anchor ListOfObservables
 * <h3>List of Observables</h3>
 *
 * Here all the available observables are listed:
 *
 * @li Electroweak Precision Observables:
 * 
 * <table class="observables">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="obs_name">Mw</td>
 *   <td class="obs_symb">@f$ M_W @f$</td>
 *   <td class="obs_desc">@copybrief Mw::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">GammaW</td>
 *   <td class="obs_symb">@f$ \Gamma_W @f$</td>
 *   <td class="obs_desc">@copybrief GammaW::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">GammaZ</td>
 *   <td class="obs_symb">@f$ \Gamma_Z @f$</td>
 *   <td class="obs_desc">@copybrief GammaZ::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">sigmaHadron</td>
 *   <td class="obs_symb"> @f$\sigma_h^0@f$</td>
 *   <td class="obs_desc">@copybrief sigmaHadron::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">sin2thetaEff</td>
 *   <td class="obs_symb">@f$\sin^2\theta_{\rm eff}^{\rm lept}@f$</td>
 *   <td class="obs_desc">@copybrief sin2thetaEff::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">PtauPol</td>
 *   <td class="obs_symb">@f$P_\tau^\mathrm{pol}@f$</td>
 *   <td class="obs_desc">@copybrief PtauPol::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Alepton</td>
 *   <td class="obs_symb">@f$\mathcal{A}_\ell@f$</td>
 *   <td class="obs_desc">@copybrief Alepton::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Acharm</td>
 *   <td class="obs_symb">@f$\mathcal{A}_c@f$</td>
 *   <td class="obs_desc">@copybrief Acharm::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Abottom</td>
 *   <td class="obs_symb">@f$\mathcal{A}_b@f$</td>
 *   <td class="obs_desc">@copybrief Abottom::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">AFBlepton</td>
 *   <td class="obs_symb">@f$A_{\mathrm{FB}}^{0,\ell}@f$</td>
 *   <td class="obs_desc">@copybrief AFBlepton::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">AFBcharm</td>
 *   <td class="obs_symb">@f$A_{\mathrm{FB}}^{0,c}@f$</td>
 *   <td class="obs_desc">@copybrief AFBcharm::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">AFBbottom</td>
 *   <td class="obs_symb">@f$A_{\mathrm{FB}}^{0,b}@f$</td>
 *   <td class="obs_desc">@copybrief AFBbottom::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Rlepton</td>
 *   <td class="obs_symb">@f$R_\ell^0@f$</td>
 *   <td class="obs_desc">@copybrief Rlepton::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Rcharm</td>
 *   <td class="obs_symb">@f$R_c^0@f$</td>
 *   <td class="obs_desc">@copybrief Rcharm::computeThValue()</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">Rbottom</td>
 *   <td class="obs_symb">@f$R_b^0@f$</td>
 *   <td class="obs_desc">@copybrief Rbottom::computeThValue()</td>
 * </tr>
 * </table>
 *
 * @li Epsilon %Parameters:
 * 
 * <table class="observables">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "epsilon1"</td>
 *   <td class="obs_symb">@f$\varepsilon_1@f$</td>
 *   <td class="obs_desc">The epsilon parameter @f$\varepsilon_1@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "epsilon2"</td>
 *   <td class="obs_symb">@f$\varepsilon_2@f$</td>
 *   <td class="obs_desc">The epsilon parameter @f$\varepsilon_2@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "epsilon3"</td>
 *   <td class="obs_symb">@f$\varepsilon_3@f$</td>
 *   <td class="obs_desc">The epsilon parameter @f$\varepsilon_3@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "epsilonb"</td>
 *   <td class="obs_symb">@f$\varepsilon_b@f$</td>
 *   <td class="obs_desc">The epsilon parameter @f$\varepsilon_b@f$.</td>
 * </tr>
 * </table>
 *
 *
 * @li %Model %Parameters of StandardModel class:
 * 
 * <table class="observables">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref StandardModelParams::StandardModelParams() "Mz"</td>
 *   <td class="obs_symb">@f$M_Z@f$</td>
 *   <td class="obs_desc">The mass of the @f$Z@f$ boson in GeV.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref StandardModelParams::StandardModelParams() "mHl"</td>
 *   <td class="obs_symb">@f$m_h@f$</td>
 *   <td class="obs_desc">The Higgs mass in GeV.</td>
 * </tr>
 * </table>
 *
 * @li %Model %Parameters, etc. of NPEffective1 and NPEffective2 classes:
 * 
 * <table class="observables">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "cHQ1pPLUScHQ2p_NP"</td>
 *   <td class="obs_symb">@f$C'_{HQ_1} + C'_{HQ_2}@f$</td>
 *   <td class="obs_desc">The sum of the coefficients of the operators
 *   @f${\cal O}'_{HQ_1}@f$ and @f${\cal O}'_{HQ_2}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "cHQ2pMINUScHQ2_NP"</td>
 *   <td class="obs_symb">@f$C'_{HQ_2} - C_{HQ_2}@f$</td>
 *   <td class="obs_desc">The difference of the coefficients of the operators
 *   @f${\cal O}'_{HQ_2}@f$ and @f${\cal O}_{HQ_2}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "cHQ3pPLUScHQ3_NP"</td>
 *   <td class="obs_symb">@f$C'_{HQ_3} + C_{HQ_3}@f$</td>
 *   <td class="obs_desc">The sum of the coefficients of the operators
 *   @f${\cal O}'_{HQ_3}@f$ and @f${\cal O}_{HQ_3}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "c_Ae_NP"</td>
 *   <td class="obs_symb">@f$C[\mathcal{A}_\ell]@f$</td>
 *   <td class="obs_desc">A combination of the coefficients of the dim. 6
 *   operators, associated with @f$\mathcal{A}_\ell@f$.
 *   See @cite Ciuchini:2013pca.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "c_GammaZ_uds_NP"</td>
 *   <td class="obs_symb">@f$C[\Gamma_{uds}]@f$</td>
 *   <td class="obs_desc">A combination of the coefficients of the dim. 6
 *   operators, associated with the light-quark contribution to @f$\Gamma_Z@f$. 
 *   See @cite Ciuchini:2013pca.</td>
 * </tr>
 * </table>
 *
 * @li %Model %Parameters, etc. of NPZbbbar class:
 * 
 * <table class="observables">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaGVb"</td>
 *   <td class="obs_symb">@f$\delta g_V^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the vector coupling @f$g_V^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaGAb"</td>
 *   <td class="obs_symb">@f$\delta g_A^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the axial-vector coupling @f$g_A^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaGLb"</td>
 *   <td class="obs_symb">@f$\delta g_L^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the left-handed coupling @f$g_L^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaGRb"</td>
 *   <td class="obs_symb">@f$\delta g_R^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the right-handed coupling @f$g_R^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaRhoZb"</td>
 *   <td class="obs_symb">@f$\delta \rho_Z^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the coupling @f$\rho_Z^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * <tr>
 *   <td class="obs_name">@ref NewPhysicsParams::NewPhysicsParams() "deltaKappaZb"</td>
 *   <td class="obs_symb">@f$\delta \kappa_Z^b@f$</td>
 *   <td class="obs_desc">New physics contribution to the coupling @f$\kappa_Z^b@f$ for @f$Zb\bar{b}@f$.</td>
 * </tr>
 * </table>
 *
 * 
 */
class ThFactory {
public:
    
    /**
     * @brief Constructor.
     * @details All the theory observables are built by the constructor. These
     * are implemented as a map between the names of the observables and a
     * pointer to an object of type ThObservable.
     * @param[in] myModel a reference to an object of the type StandardModel
     */
    ThFactory(const StandardModel& myModel);
    
    /**
     * @brief Destructor for deleting all the non-NULL pointers
     * in the thobs map.
     */
    virtual ~ThFactory();
    
    /**
     * @brief This method checks for the existence of an observable of a specific name in the map
     * thobs and returns a pointer to the particular ThObservable.
     * @param[in] name the name of the observable
     * @return a pointer to an object of the type ThObservable
     */
    ThObservable* getThMethod(const std::string& name);

private:
    std::map<std::string, ThObservable *> thobs; ///< A map between a pointer of type ThObservable and the name of the observable.
    EW myEW; ///< An object of type EW.
    ModelObservable myMO; ///< An object of type ModelObservable
};

#endif	/* THFACTORY_H */
