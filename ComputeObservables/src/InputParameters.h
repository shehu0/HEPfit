/* 
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef INPUTPARAMETERS_H
#define	INPUTPARAMETERS_H

/**
 * @class InputParameters
 * @ingroup ComputeObservables
 * @brief A class for defining the default values of the mandatory parameters of
 * the model being used on the library mode.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 */

class InputParameters {
public:
    
    /**
     * @brief The default constructor.
     */
    InputParameters()
    {};
    
    /**
     * @brief The default destructor.
     */
    virtual ~InputParameters()
    {};
    
    /**
     * @brief A method that returns the map of the mandatory model parameters given the model name. 
     * @param[in] ModelName the name of the model being used
     * @return the map of the mandatory parameters 
     */
    std::map<std::string, double> getInputParameters(std::string& ModelName)
    {
        if (ModelName.compare("StandardModel") == 0) return(StandardModel());
        else if (ModelName.compare("NPEpsilons") == 0) return(NPEpsilons());
        else if (ModelName.compare("NPEpsilons_pureNP") == 0) return(NPEpsilons_pureNP());
        else if (ModelName.compare("NPSTU") == 0) return(NPSTU());
        else if (ModelName.compare("NPHiggs") == 0) return(NPHiggs());
        else if (ModelName.compare("NPZbbbar") == 0) return(NPZbbbar());
        else if (ModelName.compare("NPZbbbarLR") == 0) return(NPZbbbarLR());
        else if (ModelName.compare("NPEffective1") == 0) return(NPEffective1());
        else if (ModelName.compare("NPEffective2") == 0) return(NPEffective2());
        else throw std::runtime_error("\nERROR: Incorrect model name passed to InputParameters():  " + ModelName + "\n");
    };
    
private:
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for StandardModel.
     * @return the map of the mandatory parameters
     *
     * @attention The parameters are initialized to the central values of the 
     * experimental data used in @cite Ciuchini:2013pca. 
     */
    std::map<std::string, double> StandardModel()
    {
        DPars_IN["GF"] = 1.1663787e-5;
        DPars_IN["ale"] = 7.2973525698e-3;
        DPars_IN["AlsMz"] = 0.1184;
        DPars_IN["dAle5Mz"] = 0.02750;
        DPars_IN["Mz"] = 91.1875;
        DPars_IN["mtop"] = 173.2;
        DPars_IN["mHl"] = 125.6;
        DPars_IN["delMw"] = 0.;
        DPars_IN["delSin2th_l"] = 0.;
        DPars_IN["delGammaZ"] = 0.;
        DPars_IN["mup"] = 0.0023;
        DPars_IN["mdown"] = 0.0048;
        DPars_IN["mstrange"] = 0.095;
        DPars_IN["mcharm"] = 1.275;
        DPars_IN["mbottom"] = 4.18;
        DPars_IN["muc"] = 1.275;
        DPars_IN["mub"] = 4.18;
        DPars_IN["mut"] = 164.;
        DPars_IN["mneutrino_1"] = 0.;
        DPars_IN["mneutrino_2"] = 0.;
        DPars_IN["mneutrino_3"] = 0.;
        DPars_IN["melectron"] = 5.109989e-4;
        DPars_IN["mmu"] = 0.10565837;
        DPars_IN["mtau"] = 1.77682;

        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPEpsilons.
     * @return the map of the mandatory parameters
     *
     * @attention The values of the epsilon parameters are initialized to their 
     * SM values @cite Ciuchini:2013pca.
     */
    std::map<std::string, double> NPEpsilons()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["epsilon_1"] = 0.00521;
        DPars_IN["epsilon_2"] = -0.00737;
        DPars_IN["epsilon_3"] = 0.00528;
        DPars_IN["epsilon_b"] = -0.00694;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPEpsilons_pureNP.
     * @return the map of the mandatory parameters 
     */
    std::map<std::string, double> NPEpsilons_pureNP()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["delEps_1"] = 0.;
        DPars_IN["delEps_2"] = 0.;
        DPars_IN["delEps_3"] = 0.;
        DPars_IN["delEps_b"] = 0.;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPSTU.
     * @return the map of the mandatory parameters 
     */
    std::map<std::string, double> NPSTU()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["obliqueS"] = 0.;
        DPars_IN["obliqueT"] = 0.;
        DPars_IN["obliqueU"] = 0.;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPHiggs.
     * @return the map of the mandatory parameters 
     *
     * @attention The cutoff scale LambdaNP is initialize to 0, i.e., it is taken
     * to be @f$\Lambda = 4\pi v/\sqrt{|1-a^2|}@f$ as explained in the description
     * of @ref NPHiggsParameters "NPHiggs" class.
     */
    std::map<std::string, double> NPHiggs()
    {
        DPars_IN = StandardModel();
                
        DPars_IN["a"] = 1.;
        DPars_IN["b"] = 1.;
        DPars_IN["c_u"] = 1.;
        DPars_IN["c_d"] = 1.;
        DPars_IN["c_e"] = 1.;
        DPars_IN["d_3"] = 1.;
        DPars_IN["d_4"] = 1.;
        DPars_IN["LambdaNP"] = 0.;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPZbbbar.
     * @return the map of the mandatory parameters
     *
     * @attention This method is applicable for the model "NPZbbbar", but not for "NPZbbbarLR".
     */
    std::map<std::string, double> NPZbbbar()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["deltaGVb"] = 0.;
        DPars_IN["deltaGAb"] = 0.;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPZbbbar.
     * @return the map of the mandatory parameters
     * 
     * @attention This method is applicable for the model "NPZbbbarLR", but not for "NPZbbbar".
     */
    std::map<std::string, double> NPZbbbarLR()
    {
        DPars_IN = StandardModel();

        DPars_IN["deltaGLb"] = 0.;
        DPars_IN["deltaGRb"] = 0.;

        return (DPars_IN);
    };

    /**
     * @brief A method that generates the map of the mandatory model parameters for NPEffective1.
     * @return the map of the mandatory parameters 
     *
     * @attention The NP scale Lambda_NP is initialize to 1 TeV.
     */
    std::map<std::string, double> NPEffective1()
    {
        DPars_IN = StandardModel();
                        
        DPars_IN["cWB_NP"] = 0.;
        DPars_IN["cH_NP"] = 0.;
        DPars_IN["cLL_NP"] = 0.;
        DPars_IN["cHLp_NP"] = 0.;
        DPars_IN["cHQp_NP"] = 0.;
        DPars_IN["cHL_NP"] = 0.;
        DPars_IN["cHQ_NP"] = 0.;
        DPars_IN["cHE_NP"] = 0.;
        DPars_IN["cHU_NP"] = 0.;
        DPars_IN["cHD_NP"] = 0.;
        DPars_IN["Lambda_NP"] = 1000.;
        
        return (DPars_IN);
    };
    
    /**
     * @brief A method that generates the map of the mandatory model parameters for NPEffective2.
     * @return the map of the mandatory parameters
     *
     * @attention The NP scale Lambda_NP is initialize to 1 TeV.
     */
    std::map<std::string, double> NPEffective2()
    {
        DPars_IN = StandardModel();
        
        DPars_IN["cWB_NP"] = 0.;
        DPars_IN["cH_NP"] = 0.;
        DPars_IN["cLL_NP"] = 0.;
        DPars_IN["cHLp_NP"] = 0.;
        DPars_IN["cHQ1p_NP"] = 0.;
        DPars_IN["cHQ2p_NP"] = 0.;
        DPars_IN["cHQ3p_NP"] = 0.;
        DPars_IN["cHL_NP"] = 0.;
        DPars_IN["cHQ1_NP"] = 0.;
        DPars_IN["cHQ2_NP"] = 0.;
        DPars_IN["cHQ3_NP"] = 0.;
        DPars_IN["cHE_NP"] = 0.;
        DPars_IN["cHU1_NP"] = 0.;
        DPars_IN["cHU2_NP"] = 0.;
        DPars_IN["cHU3_NP"] = 0.;
        DPars_IN["cHD1_NP"] = 0.;
        DPars_IN["cHD2_NP"] = 0.;
        DPars_IN["cHD3_NP"] = 0.;
        DPars_IN["Lambda_NP"] = 1000.;
        
        return (DPars_IN);
    };
    
    std::map<std::string, double> DPars_IN;///< A map for the list of mandatory parameters in the model being used.
};

#endif	/* INPUTPARAMETERS_H */
    
