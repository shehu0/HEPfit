/*
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef NPZBBBAR_H
#define	NPZBBBAR_H

#include "NPbase.h"

/**
 * @class NPZbbbar
 * @brief A model class for new physics in the form of contributions to the
 * @f$Zb\bar{b}@f$ couplings.
 * @ingroup NewPhysics
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is a Model class containing the necessary functions to
 * work with new physics contributions to electroweak precision observables,
 * in the form of contributions to the neutral current couplings of the bottom
 * quark:
 * @f[
 * \mathcal{L}
 * =
 * \frac{e}{2 s_W c_W}\,
 * Z_\mu\, \bar{b}
 * \left[
 *   \big(g_{V,\mathrm{SM}}^b + \delta g_V^b\big) \gamma_\mu
 *    - \big(g_{A,\mathrm{SM}}^b + \delta g_A^b\big) \gamma_\mu\gamma_5
 * \right] b\,.
 * @f]
 * Equivalently, the shifts in the left-handed and right-handed couplings are
 * defined as
 * @f[
 * \mathcal{L} =
 * \frac{e}{2s_W c_W}\,
 * Z_\mu\, \bar{b}
 * \left[ \big(g_{R,\mathrm{SM}}^b+\delta g_R^b\big) \gamma_\mu (1 + \gamma_5)
 * + \big(g_{L,\mathrm{SM}}^b+\delta g_L^b\big) \gamma_\mu (1 - \gamma_5)
 * \right] b
 * @f]
 * with
 * @f[
 *  \delta g_R^b = \frac{\delta g_V^b - \delta g_A^b}{2}\,,\qquad
 *  \delta g_L^b = \frac{\delta g_V^b + \delta g_A^b}{2}\,.
 * @f]
 *
 *
 * @anchor NPZbbbarInitialization
 * <h3>Initialization</h3>
 *
 * The constructor NPZbbbar() initializes the model flags explained below to their
 * default values. After creating an instance of the current class,
 * it is required to call the initialization method InitializeModel(), which
 * allocates memory to the pointer #myEWSM, inherited from StndardModel, with
 * type EWNPZbbbar.
 * This pointer is then used in computing the fermionic neutral-current
 * couplings in the presence of new physics contribution to @f$Zb\bar{b}@f$.
 * In the Monte Carlo run, the constructor as well as the initialization
 * method are called in InputParser::ReadParameters().
 *
 *
 * @anchor NPZbbbarParameters
 * <h3>%Model parameters</h3>
 *
 * The model parameters of %NPZbbbar are summarized below:
 *
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%deltaGVb</td>
 *   <td class="mod_symb">\f$\delta g_{V}^b\f$</td>
 *   <td class="mod_desc">New physics contribution to \f$g_{V}^b\f$.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%deltaGAb</td>
 *   <td class="mod_symb">\f$\delta g_{A}^b\f$</td>
 *   <td class="mod_desc">New physics contribution to \f$g_{A}^b\f$.</td>
 * </tr>
 * </table>
 *
 * which are applicable when the instance of the current class is created with
 * the constructor NPZbbbar() or NPZbbbar(false). 
 * Alternatively, when using NPZbbbar(true), which corresponds to the use of the 
 * model name "NPZbbbarLR" instead of "NPZbbbar" in InputParser::ModelFactory(),
 * the following parameters have to be used as inputs:
 *
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%deltaGLb</td>
 *   <td class="mod_symb">\f$\delta g_{L}^b\f$</td>
 *   <td class="mod_desc">New physics contribution to \f$g_{L}^b\f$.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%deltaGRb</td>
 *   <td class="mod_symb">\f$\delta g_{R}^b\f$</td>
 *   <td class="mod_desc">New physics contribution to \f$g_{R}^b\f$.</td>
 * </tr>
 * </table>
 *
 * @anchor NPZbbbarFlags
 * <h3>%Model Flags</h3>
 *
 * The flag of %NPZbbbar is summarized below:
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>Value</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%NotLinearizedNP</td>
 *   <td class="mod_valu">TRUE&nbsp;/&nbsp;<b>FALSE</b></td>
 *   <td class="mod_desc">This flag is set to TRUE if new physics contributions
 *   to electroweak observables are not linearized in \f$\delta g^b\f$.
 *   The default value is FALSE; new physics contributions are linearized.</td>
 * </tr>
 * </table>
 *
 *
 * @anchor NPZbbbarFunctions
 * <h3>Important member functions</h3>
 *
 * Compared to the base class NPbase, the functions for the following quantities
 * are reimplemented in the current class:
 *
 * @li @f$\delta g_V^f@f$&nbsp;&nbsp;(with deltaGVl() and deltaGVq()),
 * @li @f$\delta g_A^f@f$&nbsp;&nbsp;(with deltaGAl() and deltaGAq()).
 *
 */
class NPZbbbar : public NPbase  {
public:

    /**
     * @brief The number of the model parameters in %NPZbbbar.
     */
    static const int NZbbbarVars = 2;

    /**
     * @brief A string array containing the labels of the model parameters in %NPZbbbar,
     * used for NPZbbbarLR=FALSE.
     */
    static const std::string ZbbbarVAVars[NZbbbarVars];

    /**
     * @brief A string array containing the labels of the model parameters in %NPZbbbar,
     * used for NPZbbbarLR=TRUE.
     */
    static const std::string ZbbbarLRVars[NZbbbarVars];

    /**
     * @brief Constructor.
     * @param[in] FlagNPZbbbarLR_in a flag that is true if \f$\delta g_{L}^b\f$
     * and  \f$\delta g_{R}^b\f$ are used for the model parameters, instead of
     * \f$\delta g_{V}^b\f$ and \f$\delta g_{A}^b\f$. For the model parameters, 
     * the labels %deltaGVb and %deltaGAb are applicable for FlagNPZbbbarLR_in=fALSE,
     * while %deltaGLb and %deltaGRb are applicable for FlagNPZbbbarLR_in=TRUE.
     */
    NPZbbbar(const bool FlagNPZbbbarLR_in = false);

    /**
     * @brief @copybrief StandardModel::InitializeModel()
     * @details This method allocates memory to the pointer #myEWSM, inherited
     * from StndardModel, with type EWNPZbbbar.
     * @return a boolean that is true if model initialization is successful
     */
    virtual bool InitializeModel();

    /**
     * @brief @copybrief Model::Init()
     * @copydetails Model::Init()
     */
    virtual bool Init(const std::map<std::string, double>& DPars);

    /**
     * @brief @copybrief Model::Update()
     * @copydetails Model::Update()
     */
    virtual bool Update(const std::map<std::string, double>& DPars);

    /**
     * @brief @copybrief Model::CheckParameters()
     * @copydetails Model::CheckParameters()
     */
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);

    /**
     * @brief @copybrief Model::setFlag()
     * @copydetails Model::setFlag()
     */
    virtual bool setFlag(const std::string name, const bool value);

    /**
     * @brief @copybrief Model::CheckFlags()
     * @copydetails Model::CheckFlags()
     */
    virtual bool CheckFlags() const;


    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief A method to retrieve the model flag NotLinearizedNP.
     * @details See @ref NPZbbbarFlags for detail.
     * @return a boolean that is true if new physics contributions
     * to electroweak observables are not linearized in \f$\delta g^b\f$.
     */
    bool IsFlagNotLinearizedNP() const
    {
        return FlagNotLinearizedNP;
    }


    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief New physics contribution to @f$g_V^l@f$.
     * @param[in] l name of a lepton (see StandardModel::lepton)
     * @return @f$\delta g_V^l@f$ (zero in the current model)
     */
    virtual double deltaGVl(StandardModel::lepton l) const;

    /**
     * @brief New physics contribution to @f$g_V^q@f$.
     * @param[in] q name of a quark (see QCD::quark)
     * @return @f$\delta g_V^q@f$ (non-zero only for \f$q=b\f$)
     */
    virtual double deltaGVq(QCD::quark q) const;

    /**
     * @brief New physics contribution to @f$g_A^l@f$.
     * @param[in] l name of a lepton (see StandardModel::lepton)
     * @return @f$\delta g_A^l@f$ (zero in the current model)
     */
    virtual double deltaGAl(StandardModel::lepton l) const;

    /**
     * @brief New physics contribution to @f$g_A^q@f$.
     * @param[in] q name of a quark (see QCD::quark)
     * @return @f$\delta g_A^q@f$ (non-zero only for \f$q=b\f$)
     */
    virtual double deltaGAq(QCD::quark q) const;


    ////////////////////////////////////////////////////////////////////////
protected:

    /**
     * @brief @copybrief Model::setParameter()
     * @copydetails Model::setParameter()
     */
    virtual void setParameter(const std::string name, const double& value);


    ////////////////////////////////////////////////////////////////////////
private:

    /* These variables are used internally as the deviations in the left-handed
     * and right-handed couplings if FlagNPZbbbarLR is set to true.
     * Therefore, they should not be used directly. Instead, the functions
     * deltaGVq() and deltaGAq() have to be called. */
    double myDeltaGVb;///< New physics contribution to \f$g_{V}^b\f$.
    double myDeltaGAb;///< New physics contribution to \f$g_{A}^b\f$.

    /**
     * @brief An internal boolean flag that is true if \f$\delta g_{L,R}^b\f$ are
     * used instead of \f$\delta g_{V,A}^b\f$. This flag is initialized in the
     * constructor. 
     */
    const bool FlagNPZbbbarLR;

    /**
     * @brief A boolean flag that is true if new physics contributions
     * to electroweak observables are not linearized in \f$\delta g^b\f$.
     */
    bool FlagNotLinearizedNP;
    int rank; ///< Rank of the process for a MPI run. Value is 0 for a serial run.


};

#endif	/* NPZBBBAR_H */

