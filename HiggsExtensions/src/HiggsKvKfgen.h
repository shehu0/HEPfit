/*
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef HIGGSKVKFGEN_H
#define	HIGGSKVKFGEN_H
#include <NPbase.h>

/**
 * @class HiggsKvKfgen
 * @ingroup HiggsExtensions
 * @brief A model class extending the %StandardModel Higgs sector with four flavour-universal couplings.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This is a Model class containing parameters and functions associated
 * with an extension of the %StandardModel where Higgs couplings to all vector bosons
 * are rescaled by @f$K_v@f$ and Higgs couplings to all up, down and lepton fermions are rescaled by @f$K_u, K_d, K_l@f$ respectively.
 * This class inherits from the %HiggsExtensionModel class, which defines parameters related to generic
 * extensions of the %StandardModel Higgs sector.
 *
 *
 * @anchor HiggsKvKfgenInitialization
 * <h3>Initialization</h3>
 *
 * After creating an instance of the current class,
 * it is required to call the initialization method InitializeModel(), which
 * is needed by the base class. 
 *
 * The initializations and updates of the model parameters are explained
 * below. 
 *
 * 
 * @anchor HiggsKvKfgenParameters
 * <h3>%Model parameters</h3>
 *
 * The model parameters of %HiggsKvKfgen (in addition to the %StandardModel ones) are summarized below:
 * <table class="model">
 * <tr>
 *   <th>Label</th>
 *   <th>LaTeX symbol</th>
 *   <th>Description</th>
 * </tr>
 * <tr>
 *   <td class="mod_name">%Kv</td>
 *   <td class="mod_symb">@f$\kappa_V@f$</td>
 *   <td class="mod_desc">The factor rescaling all Higgs couplings to vector bosons with respect to the SM.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%Ku</td>
 *   <td class="mod_symb">@f$\kappa_u@f$</td>
 *   <td class="mod_desc">The factor rescaling all Higgs couplings to up-type fermions with respect to the SM.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%Kd</td>
 *   <td class="mod_symb">@f$\kappa_d@f$</td>
 *   <td class="mod_desc">The factor rescaling all Higgs couplings to down-type fermions with respect to the SM.</td>
 * </tr>
 * <tr>
 *   <td class="mod_name">%Kl</td>
 *   <td class="mod_symb">@f$\kappa_l@f$</td>
 *   <td class="mod_desc">The factor rescaling all Higgs couplings to leptons with respect to the SM.</td>
 * </tr>
 * </table>
 * 
 * Please read information about parameter initialization and update in the documentation of the %StandardModel class.
 */
class HiggsKvKfgen : public NPbase {
public:

    static const int NHKvKfgenvars = 5; ///< The number of the model parameters in %HiggsKvKf.

    /**
     * @brief A string array containing the labels of the model parameters in %HiggsKvKf.
     */
    static const std::string HKvKfgenvars[NHKvKfgenvars];

    HiggsKvKfgen();

    virtual ~HiggsKvKfgen()
    {
    };

    double getKv() const
    {
        return Kv;
    }

    void setKv(double Kv)
    {
        this->Kv = Kv;
    }

    double getKd() const
    {
        return Kd;
    }

    void setKd(double Kd)
    {
        this->Kd = Kd;
    }

    double getKl() const
    {
        return Kl;
    }

    void setKl(double Kl)
    {
        this->Kl = Kl;
    }

    double getKu() const
    {
        return Ku;
    }

    void setKu(double Ku)
    {
        this->Ku = Ku;
    }

    /**
     * @brief A method to check if all the mandatory parameters for %HiggsKvKfgen
     * have been provided in model initialization.
     * @param[in] DPars a map of the parameters that are being updated in the Monte Carlo run
     * (including parameters that are varied and those that are held constant)
     * @return a boolean that is true if the execution is successful
     */
    virtual bool CheckParameters(const std::map<std::string, double>& DPars);

    ////////////////////////////////////////////////////////////////////////

    /**
     * @brief The oblique parameter @f$S@f$.
     * @return @f$S@f$
     */
    virtual double obliqueS() const;

    /**
     * @brief The oblique parameter @f$T@f$.
     * @return @f$T@f$
     */
    virtual double obliqueT() const;

    /**
     * @brief The oblique parameter @f$U@f$.
     * @return @f$U=0@f$
     */
    virtual double obliqueU() const;

    virtual double muggH(const double sqrt_s) const;
    virtual double muVBF(const double sqrt_s) const;
    virtual double muWH(const double sqrt_s) const;
    virtual double muZH(const double sqrt_s) const;
    virtual double muVH(const double sqrt_s) const;
    virtual double muttH(const double sqrt_s) const;
    virtual double BrHggRatio() const;
    virtual double BrHWWRatio() const;
    virtual double BrHZZRatio() const;
    virtual double BrHZgaRatio() const;
    virtual double BrHgagaRatio() const;
    virtual double BrHtautauRatio() const;
    virtual double BrHccRatio() const;
    virtual double BrHbbRatio() const;
    virtual double computeGammaTotalRatio() const;

    ////////////////////////////////////////////////////////////////////////
protected:

    /**
     * @brief A method to set the value of a parameter of %HiggsKvKf.
     * @param[in] name name of a model parameter
     * @param[in] value the value to be assigned to the parameter specified by name
     */
    virtual void setParameter(const std::string name, const double& value);

    virtual double computeKg(const double sqrt_s) const;

    virtual double computeKW() const;

    virtual double computeKZ() const;

    /**
     * @brief A method to compute the ratio of the @f$HZ\gamma@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$HZ\gamma@f$ coupling in the current model and in the SM
     */
    virtual double computeKZga() const;

    /**
     * @brief A method to compute the ratio of the @f$H\gamma\gamma@f$ coupling in the current model and in the SM.
     * @return the ratio of the @f$H\gamma\gamma@f$ coupling in the current model and in the SM
     */
    virtual double computeKgaga() const;

    virtual double computeKtau() const;

    virtual double computeKc() const;

    virtual double computeKt() const;

    virtual double computeKb() const;

    ////////////////////////////////////////////////////////////////////////
private:
    double Kv, Ku, Kd, Kl, BrHinv;
};

#endif	/* HIGGSKVKFGEN_H */

