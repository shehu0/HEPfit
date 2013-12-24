/*
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef __MONTECARLOENGINE__H
#define __MONTECARLOENGINE__H

#include <BAT/BCModel.h>
#include <BAT/BCH1D.h>
#include <BAT/BCH2D.h>
#include <BAT/BCModelOutput.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TRandom3.h>
#include <Observable.h>
#include <Observable2D.h>
#include <CorrelatedGaussianObservables.h>
#include <ModelParaVsObs.h>
#include <ModelParameter.h>
#include <Model.h>
#include <map>
#include <string>
#include <sstream>

#define NBINSMODELPARS 100
#define NBINS1D 100
#define NBINS2D 100

/**
 * @class MonteCarloEngine
 * @ingroup MonteCarlo
 * @brief An engine class for Monte Carlo.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details
 */
class MonteCarloEngine : public BCModel {
public:
    
    /**
     * @brief The default constructor.
     * @param[in] ModPars_i the vector of model parameters as defined in SomeModel.conf
     * @param[in] Obs_i the vector of observables as defined in SomeModel.conf
     * @param[in] Obs2D_i the vector of observables2D as defined in SomeModel.conf
     * @param[in] CGO_i the vector of correlated Gaussian observables as defined in SomeModel.conf
     * @param[in] ParaObs_i the vector of parameter vs. observables as defined in SomeModel.conf
     * @param[in] checkHistRange_i
     */
    MonteCarloEngine(const std::vector<ModelParameter>& ModPars_i,
                     std::vector<Observable>& Obs_i,
                     std::vector<Observable2D>& Obs2D_i,
                     std::vector<CorrelatedGaussianObservables>& CGO_i,
                     std::vector<ModelParaVsObs>& ParaObs_i,
                     const bool checkHistRange_i=false);
    
    /**
     * @brief The default destructor. Some pointers defined in this class are explicitly freed.
     */
    ~MonteCarloEngine();
    
    /**
     * @brief Initialization of the Monte Carlo Engine
     * @details The initialization of the Monte Carlo Engine performs the following tasks
     * \li The observables and observables2D lists are checked and sorted into the ones which are included
     * in the MCMC and the ones which are not.
     * \li The experimental likelihood for observables and observalbes2D are read if provided through a .root
     * file and the corresponding output histograms are initiated.
     * \li The correlated Gaussian observables are sorted for inclusion in the MCMC and the corresponding output 
     * histograms are initiated.
     * \li The histograms for the model paramaters vs. observables are initiated.\n
     * The output specifications are passed from the SomeModel.conf file parsed by the InputParser(). The number of 
     * bins for the 1D and 2D histograms are defined through the NBINS1D and NBINS2D parameters fixed in 
     * MonteCarloEngine.h.
     * @param[in] Mod_i the pointer to the model defined in SomeModel.conf
     */
    void Initialize(Model* Mod_i);
    
    /**
     * @brief A member to classify the prior of the model parameters varied in the Monte Carlo
     * @details The model parameters being varied are first sorted out checking for the existence of 
     * of Gaussian error (\f$\delta_{g}\f$) or flat error (\f$\delta_{f}\f$). The SetPriorGaus method 
     * and SetPriorConstant method in BCEngineMCMC 
     * (<a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>) is used to set a Gaussian
     * or flat prior for the model parameters respectively. In case a model parameter has both a Gaussian
     * and a flat error then the combined function is built using <a href="http://root.cern.ch/root/html/TF1.html"
     * target=blank>TF1</a>. The definition of the combined error is
     * \f[
     * \delta_{combined}(x) = \frac{1}{4\delta_f}\left(\frac{Erf(x - x_{ave}+\delta_f)}{\sqrt{2}\delta_g}
       - \frac{Erf(x - x_{ave}-\delta_f)}{\sqrt{2}\delta_g}\right),
     * \f]
     * with
     * \f[
     * Erf(x)=\frac{1}{\sqrt{2}\pi}\int_0^x \exp^{-\frac{t^2}{2}}dt.
     * \f]
     */
    void DefineParameters();
    
    /**
     * @brief This member calculates the loglikelihood for the observables included in the MCMC run.
     * @details The model is updated with the new set of parameters through the Model::Update() method.
     * If this is successful this even is counted as a used event. Otherwise it is counted as a 
     * discarded event. The log probability is calculated using Weight(const Observable&, const double& )
     * function for the observables, Weight(const Observable2D&, const double&, const double& ) for 
     * the observable2D and Weight(const CorrelatedGaussianObservables& ) for the correlated Gaussian
     * observables. Overloaded from BCEngineMCMC in <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>.
     * @param[in] parameters the vector of the parameters that are being varied in the Monte Carlo
     * @return the loglikelihood
     */
    double LogLikelihood(const std::vector <double>& parameters);
    
    /**
     * @brief This member checks if there is overflow of the 1D histogram
     * @param[in] hist a reference to a object of type <a href="http://root.cern.ch/root/html/TH1D.html"
     * target=blank>TH1D</a> as defined in the ROOT libraries
     * @param[in] name the name for the histogram
     */
    void CheckHistogram(const TH1D& hist, const std::string name);
    
    /**
     * @brief This member checks if there is overflow of the 2D histogram
     * @param[in] hist a reference to a object of type <a href="http://root.cern.ch/root/html/TH2D.html"
     * target=blank>TH2D</a> as defined in the ROOT libraries
     * @param[in] name the name for the histogram
     */
    void CheckHistogram(const TH2D& hist, const std::string name);
    
    /**
     * @brief Overloaded from PrintHistogram(BCModelOutput&, const std::string ) to print
     * histogram for observables.
     * @param[in] out a reference to an object of type BCModelOutput as defined in the
     * <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT libraries</a>
     * @param[in] it a iterator of the vector of objects of type Observable()
     * @param[in] OutputDir the name of the output directory
     */
    void PrintHistogram(BCModelOutput & out,
                        std::vector<Observable>::iterator it,
                        const std::string OutputDir);
    
    /**
     * @brief Member used for printing histograms for observables, observable2D, correlated Gaussian observables
     * and model parameters vs. observables.
     * @param[in] out a reference to an object of type BCModelOutput as defined in the
     * <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT libraries</a>
     * @param[in] OutputDir the name of the output directory
     */
    void PrintHistogram(BCModelOutput& out, const std::string OutputDir);
    
    /**
     * @brief Overloaded from BCEngineMCMC in <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>
     * @details The interface is used to update the model parameters using the Model::Update() method. Then the
     * values of the observables are computed and the respective histograms are filled. If the checkTheoryRange
     * flag is true then the minimum and maximum of the theory value is checked and reset to include the current
     * theory values.
     */
    void MCMCIterationInterface();
    
    /**
     * @brief A set method to fix the number of chains.
     * @details The number of chains are set using the MCMCSetNChains() from
     * BCEngineMCMC class in <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>.
     * This also creates pointers to the vector of observable values and weights for all the chains.
     * @param[in] i the number of chains
     */
    void setNChains(unsigned int i);
    
    /**
     * @brief A method to add the observable values and weights to the chain information.
     * @details If the WriteChain flag is set to true in the MonteCarlo.conf file then chain information
     * is written. This method adds the observable values and weights (for the observables included in the MCMC)
     * to the chain information.
     */
    void AddChains();
    
    /**
     * @brief This is used to calculate the weight associated with the value of the observable
     * @param[in] obs a reference to an object of type Observable
     * @param[in] th a reference to a object containing the value of the first theory observable
     * @return the value of the weight
     */
    double Weight(const Observable& obs, const double& th);
    
    /**
     * @brief This is used to calculate the weight associated with the value of the pair of observables
     * @param[in] obs a reference to an object of type Observable2D
     * @param[in] th1 a reference to a object containing the value of the first theory observable
     * @param[in] th2 a reference to a object containing the value of the second theory observable
     * @return the value of the weight
     */
    double Weight(const Observable2D& obs, const double& th1, const double& th2);
    
    /**
     * @brief This is used to calculate the weight associated with the value of correlated Gaussian observables
     * @param[in] obs a reference to an object of type CorrelatedGaussianObservables
     * @return the value of the weight
     */
    double Weight(const CorrelatedGaussianObservables& obs);
    
    /**
     * @brief A get method to access the stream that stores the log messages coming from histogram printing and checking.
     * @return a string containing the log messages
     */
    std::string getHistoLog() const
    {
        return HistoLog.str().c_str();
    }
    
    /**
     * @brief This member generates the correlation matrix using BCH2D from the
     * <a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT libraries</a>.
     * @param[in] filename the name of the file where the correlation matrix is printed
     */
    void PrintCorrelationMatrix(const std::string filename);
    
    /**
     * @brief A get method to access the number of events discarded due to failure to update model.
     * These events are not used for the MCMC run.
     * @return the number of discarded events
     */
    int getNumOfDiscardedEvents() const
    {
        return NumOfDiscardedEvents;
    }
    
    /**
     * @brief A get method to access the number of events used in the MCMC run.
     * @return the number of events used in the MCMC run
     */
    int getNumOfUsedEvents() const
    {
        return NumOfUsedEvents;
    }
    
private:
    const std::vector<ModelParameter>& ModPars; /**< A vector of model parameters. */
    std::vector<Observable> Obs_MCMC; /**< A vector of observables to be used in the MCMC. */
    std::vector<Observable>& Obs_ALL;  /**< A vector of all observables. */
    std::vector<Observable2D> Obs2D_MCMC; /**< A vector of pairs of observables for Observable2D() that are used in the MCMC.*/
    std::vector<Observable2D>& Obs2D_ALL; /**< A vector of all pairs of observable for Observable2D().*/
    std::vector<CorrelatedGaussianObservables>& CGO; /**< A vector of correlated Gaussian observables.*/
    std::vector<ModelParaVsObs>& ParaObs; /**< A vector of pairs of model parameters and observables.*/
    Model* Mod; /**< A pointer to an abject of type Model(). */
    std::map<std::string, double> DPars; /**< A map between parameter names and their values.*/
    std::map<std::string, BCH1D * > Histo1D; /**< A map between pointers to objects of type BCH1D (<a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>) and their given names. */
    std::map<std::string, TH1D * > InHisto1D; /**< A map between pointers to objects of type TH1D (<a href="http://root.cern.ch/root/html/TH1D.html" target=blank>TH1D</a>) and their given names.*/
    std::map<std::string, BCH2D * > Histo2D; /**< A map between pointers to objects of type BCH2D (<a href="https://www.mppmu.mpg.de/bat/?page=home" target=blank>BAT</a>) and their given names. */
    std::map<std::string, TH2D * > InHisto2D; /**< A map between pointers to objects of type TH2D (<a href="http://root.cern.ch/root/html/TH2D.html" target=blank>TH1D</a>) and their given names*/
    std::map<std::string, double> thMin; /**< A map between the name of a theory observable and its minimum value.*/
    std::map<std::string, double> thMax; /**< A map between the name of a theory observable and its maximum value.*/
    double *obval; /**< A pointer to the vector of observable values.*/
    double *obweight; /**< A pointer to the vector of observable weights.*/
    unsigned int kwmax; /**< The number of observables whose weights are used for the MCMC. */
    unsigned int kmax; /**< The number of observables.*/
    std::ostringstream HistoLog; /**< A stream to store the output messages from printing and checking histograms.*/
    int NumOfUsedEvents; /**< The number of events for which the model is successfully updated and hence used for the MCMC run*/
    int NumOfDiscardedEvents; /**< The number of events for which the update of the model fails and these events are not used for the MCMC run.*/
    bool checkTheoryRange; /**< The flag that specifies if the theory range should be checked.*/
    
};

#endif

