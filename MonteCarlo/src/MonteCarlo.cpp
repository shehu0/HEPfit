/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "MonteCarlo.h"
#include <BAT/BCParameter.h>
#include <TSystem.h>
#include <BAT/BCAux.h>
#include <BAT/BCLog.h>
#include <BAT/BCSummaryTool.h>
#include <ModelFactory.h>
#include <ThObsFactory.h>
#ifdef _MPI
#include <mpi.h>
#endif
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <RVersion.h>

MonteCarlo::MonteCarlo(
        ModelFactory& ModelF, ThObsFactory& ThObsF,
        const std::string& ModelConf_i,
        const std::string& MonteCarloConf_i,
        const std::string& OutFile_i,
        const std::string& JobTag_i)
: myInputParser(ModelF, ThObsF), MCEngine(ModPars, Obs, Obs2D, CGO)
{
    ModelConf = ModelConf_i;
    MCMCConf = MonteCarloConf_i;
    JobTag = JobTag_i;
    if (OutFile_i.compare("") == 0) OutFile = "MCout" + JobTag + ".root";
    else OutFile = OutFile_i + JobTag + ".root";
    ObsDirName = "Observables" + JobTag;
    FindModeWithMinuit = false;
    CalculateEvidence = false;
    PrintAllMarginalized = false;
    PrintCorrelationMatrix = false;
    PrintKnowledgeUpdatePlots = false;
    PrintParameterPlot = false;
    checkrun = false;
    evidence_min_iterations = 0;
}

//MonteCarlo::~MonteCarlo() {}

void MonteCarlo::TestRun(int rank)
{
    if (checkrun == true) {
        if (rank == 0) throw std::runtime_error("ERROR: MonteCarlo::TestRun() cannot be called after calling MonteCarlo::Run().\n");
    } else {
        checkrun = true;
    }

    if (rank == 0) {
        ModelName = myInputParser.ReadParameters(ModelConf, rank, ModPars, Obs, Obs2D, CGO);
        std::map<std::string, double> DP;
        if (Obs.size() == 0 && CGO.size() == 0) throw std::runtime_error("\nMonteCarlo::TestRun(): No observables or correlated Gaussian observables defined in SomeModel.conf file\n");

        for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
            DP[it->name] = it->ave;
        }

        if (!myInputParser.getModel()->Init(DP)) {
            if (rank == 0) throw std::runtime_error("ERROR: Parameter(s) missing in model initialization. \n");
        }

        if (Obs.size() > 0) std::cout << "\nOservables: \n" << std::endl;
        for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
            double th = it->computeTheoryValue();
            std::cout << it->getName() << " = " << th << std::endl;
        }

        if (CGO.size() > 0) std::cout << "\nCorrelated Gaussian Oservables: \n" << std::endl;
        for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin(); it1 < CGO.end(); it1++) {
            std::cout << it1->getName() << ":" << std::endl;
            std::vector<Observable> ObsInCGO = it1->getObs();
            for (std::vector<Observable>::iterator it2 = ObsInCGO.begin(); it2 < ObsInCGO.end(); it2++) {
                double th = it2->computeTheoryValue();
                std::cout << it2->getName() << " = " << th << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

void MonteCarlo::Run(const int rank)
{
    if (checkrun == true) {
        if (rank == 0) throw std::runtime_error("ERROR: MonteCarlo::Run() cannot be called after calling MonteCarlo::TestRun().\n");
    } else {
        checkrun = true;
    }

    try {

        /* set model parameters */
        ModelName = myInputParser.ReadParameters(ModelConf, rank, ModPars, Obs, Obs2D, CGO);
        int buffsize = 0;
        std::map<std::string, double> DP;
        for (std::vector<ModelParameter>::iterator it = ModPars.begin(); it < ModPars.end(); it++) {
            DP[it->name] = it->ave;
            if (it->errg > 0. || it->errf > 0.)
                buffsize++;
        }
        if (buffsize == 0)
            if (rank == 0) throw std::runtime_error("No parameters being varied. Aborting MCMC run.\n");
        buffsize++;
        if (!myInputParser.getModel()->Init(DP))
            if (rank == 0) throw std::runtime_error("ERROR: Parameter(s) missing in model initialization.\n");

        if (rank == 0) std::cout << std::endl << "Running in MonteCarlo mode...\n" << std::endl;

        /* create a directory for outputs */
        if (rank == 0) {
            FileStat_t info;
            if (gSystem->GetPathInfo(ObsDirName.c_str(), info) != 0) {
                if (gSystem->MakeDirectory(ObsDirName.c_str()) == 0)
                    std::cout << ObsDirName << " directory has been created." << std::endl;
                else
                    throw std::runtime_error("ERROR: " + ObsDirName + " directory cannot be created.\n");
            }
        }

        MCEngine.SetName(ModelName.c_str());
        MCEngine.Initialize(myInputParser.getModel());

#ifdef _MPI
        double *recvbuff = new double[buffsize];
#endif

        if (rank != 0) {
#ifdef _MPI
            double **sendbuff = new double*[1];
            sendbuff[0] = new double[1];

            std::vector<double> pars;
            int obsbuffsize = Obs.size() + 2 * Obs2D.size();
            for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin(); it1 < CGO.end(); it1++)
                obsbuffsize += it1->getObs().size();

            while (true) {
                MPI::COMM_WORLD.Scatter(sendbuff[0], buffsize, MPI::DOUBLE,
                        recvbuff, buffsize, MPI::DOUBLE, 0);

                if (recvbuff[0] == 0.) { // do nothing and return ll
                    double ll = log(0.);
                    MPI::COMM_WORLD.Gather(&ll, 1, MPI::DOUBLE, sendbuff[0], 1, MPI::DOUBLE, 0);
                } else if (recvbuff[0] == 1.) { //compute log likelihood
                    pars.assign(recvbuff + 1, recvbuff + buffsize);
                    double ll = MCEngine.LogEval(pars);
                    MPI::COMM_WORLD.Gather(&ll, 1, MPI::DOUBLE, sendbuff[0], 1, MPI::DOUBLE, 0);
                }
                else if (recvbuff[0] == 2.) { // compute observables
                    double sbuff[obsbuffsize];
                    std::map<std::string, double> DPars;
                    pars.assign(recvbuff + 1, recvbuff + buffsize);
                    for (unsigned int k = 0; k < pars.size(); k++) {
                        DPars[MCEngine.GetParameter(k)->GetName()] = pars[k];
                    }
                    myInputParser.getModel()->Update(DPars);

                    int k = 0;
                    for (boost::ptr_vector<Observable>::iterator it = Obs.begin(); it < Obs.end(); it++) {
                        sbuff[k++] = it->computeTheoryValue();
                    }
                    for (std::vector<Observable2D>::iterator it = Obs2D.begin(); it < Obs2D.end(); it++) {
                        sbuff[k++] = it->computeTheoryValue();
                        sbuff[k++] = it->computeTheoryValue2();
                    }

                    for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin(); it1 < CGO.end(); it1++) {
                        std::vector<Observable> pino(it1->getObs());
                        for (std::vector<Observable>::iterator it = pino.begin(); it != pino.end(); ++it)
                            sbuff[k++] = it->computeTheoryValue();
                    }
                    MPI::COMM_WORLD.Gather(sbuff, obsbuffsize, MPI::DOUBLE, sendbuff[0], obsbuffsize, MPI::DOUBLE, 0);
                } else if (recvbuff[0] == 3.) { // do not compute observables, but gather the buffer
                    double sbuff[obsbuffsize];
                    MPI::COMM_WORLD.Gather(sbuff, obsbuffsize, MPI::DOUBLE, sendbuff[0], obsbuffsize, MPI::DOUBLE, 0);
                } else if (recvbuff[0] == -1.)
                    break;
                else {
                    std::cout << "recvbuff = " << recvbuff[0] << " rank " << rank << std::endl;
                    throw "MonteCarlo::Run(): error in MPI message!\n";
                }
            }
            delete sendbuff[0];
            delete [] sendbuff;
#endif
        } else {

            bool writechains = false;
            std::cout << ModPars.size() << " parameters defined." << std::endl;
            std::cout << Obs.size() << " observables defined." << std::endl;
            std::cout << CGO.size() << " correlated gaussian observables defined";
            if (CGO.size() == 0)
                std::cout << "." << std::endl;
            else
                std::cout << ":" << std::endl;
            for (std::vector<CorrelatedGaussianObservables>::iterator it1 = CGO.begin();
                    it1 != CGO.end(); ++it1)
                std::cout << "  " << it1->getName() << " containing "
                << it1->getObs().size() << " observables." << std::endl;
            //MonteCarlo configuration parser
            std::ifstream ifile(MCMCConf.c_str());
            if (!ifile.is_open())
                throw std::runtime_error("\nERROR: " + MCMCConf + " does not exist. Make sure to specify a valid Monte Carlo configuration file.\n");
            std::string line;
            bool IsEOF = false;
            do {
                IsEOF = getline(ifile, line).eof();
                if (*line.rbegin() == '\r') line.erase(line.length() - 1); // for CR+LF
                if (line.empty() || line.at(0) == '#')
                    continue;
                boost::char_separator<char> sep(" ");
                boost::tokenizer<boost::char_separator<char> > tok(line, sep);
                boost::tokenizer<boost::char_separator<char> >::iterator beg = tok.begin();
                if (beg->compare("NChains") == 0) {
                    ++beg;
                    MCEngine.setNChains(atoi((*beg).c_str()));
                } else if (beg->compare("PrerunMaxIter") == 0) {
                    ++beg;
                    MCEngine.MCMCSetNIterationsMax(atoi((*beg).c_str()));
                } else if (beg->compare("Seed") == 0) {
                    ++beg;
                    int seed = atoi((*beg).c_str());
                    if (seed != 0)
                        MCEngine.MCMCSetRandomSeed(seed);
                } else if (beg->compare("Iterations") == 0) {
                    ++beg;
                    MCEngine.MCMCSetNIterationsRun(atoi((*beg).c_str()));
                } else if (beg->compare("WriteChain") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0)
                        writechains = true;
                } else if (beg->compare("FindModeWithMinuit") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        FindModeWithMinuit = true;
                    }
                } else if (beg->compare("CalculateEvidence") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        CalculateEvidence = true;
                    }
                } else if (beg->compare("EvidenceMinIter") == 0) {
                    ++beg;
                    evidence_min_iterations = atoi((*beg).c_str());
                } else if (beg->compare("PrintAllMarginalized") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        PrintAllMarginalized = true;
                    }
                } else if (beg->compare("PrintCorrelationMatrix") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        PrintCorrelationMatrix = true;
                    }
                } else if (beg->compare("PrintKnowledgeUpdatePlots") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        PrintKnowledgeUpdatePlots = true;
                    }
                } else if (beg->compare("PrintParameterPlot") == 0) {
                    ++beg;
                    if (beg->compare("true") == 0) {
                        PrintParameterPlot = true;
                    }
                } else if (beg->compare("OrderParameters") == 0) {
                    ++beg;
                    if (beg->compare("false") == 0) {
                        MCEngine.MCMCSetFlagOrderParameters(false);
                    }
                } else
                    throw std::runtime_error("\nERROR: Wrong keyword in MonteCarlo config file: " + *beg + "\n Make sure to specify a valid Monte Carlo configuration file.\n");
            } while (!IsEOF);

            BCModelOutput out(&MCEngine, OutFile.c_str());
            if (writechains) {
                out.WriteMarkovChain(true);
                MCEngine.AddChains();
            }

            // set nicer style for drawing than the ROOT default
            BCAux::SetStyle();

            // open log file
            BCLog::OpenLog(("log" + JobTag + ".txt").c_str());
            BCLog::SetLogLevel(BCLog::debug);

            // run the MCMC and marginalize w.r.t. to all parameters
            MCEngine.BCIntegrate::SetNbins(NBINSMODELPARS);
            MCEngine.SetMarginalizationMethod(BCIntegrate::kMargMetropolis);
            MCEngine.MarginalizeAll();

            // find mode using the best fit parameters as start values
            if (FindModeWithMinuit)
                MCEngine.FindMode(MCEngine.GetBestFitParameters());

            if (CalculateEvidence) {
                std::vector <double> pars;
                                    double logmode = 211.571;
                                    pars.push_back(0.118437);
                                    pars.push_back(0.0272741);
                                    pars.push_back(91.1885);
                                    pars.push_back(173.01);
                                    pars.push_back(0.09067);
                                    pars.push_back(1.31105);
                                    pars.push_back(4.21102);
                                    pars.push_back(164.163);
                                    pars.push_back(1.51782);
                                    pars.push_back(1.22492);
                                    pars.push_back(1.5141);
                                    pars.push_back(0.226106);
                                    pars.push_back(1.6362);
                                    pars.push_back(12380);
                                    pars.push_back(0.225224);
                                    pars.push_back(0.819906);
                                    pars.push_back(0.124584);
                                    pars.push_back(0.344956);
                                    pars.push_back(-0.00015551);
                                    pars.push_back(0.000166167);
                                    pars.push_back(-1.83188e-05);
                                    pars.push_back(-0.000175787);
                                    pars.push_back(-0.000152502);
                                    pars.push_back(0.000110332);
                                    pars.push_back(0.000115577);
                                    pars.push_back(-0.000146047);
                                    pars.push_back(-3.05786e-07);
                                    pars.push_back(-0.000159357);
                                    pars.push_back(0.000131088);
                                    pars.push_back(-0.000102858);
                                    pars.push_back(-1.44821e-05);
                                    pars.push_back(-2.31685e-06);
                                    pars.push_back(1.69625e-05);
                                    pars.push_back(9.47749e-07);
                                    pars.push_back(-1.53587e-05);
                                    pars.push_back(-6.48001e-06);
                                    pars.push_back(0.897944);
                                    pars.push_back(-0.551732);
                                    pars.push_back(1.49241);
                                    pars.push_back(0.259487);
                                    pars.push_back(-0.0760865);
                                    pars.push_back(0.336411);
                                    pars.push_back(0.878961);
                                    pars.push_back(-0.537981);
                                    pars.push_back(-0.0351767);
                                    pars.push_back(0.428882);

//                double logmode = 61.1956;
//                pars.push_back(0.118214);
//                pars.push_back(0.0275908);
//                pars.push_back(91.189);
//                pars.push_back(172.864);
//                pars.push_back(0.0932932);
//                pars.push_back(1.31496);
//                pars.push_back(4.17802);
//                pars.push_back(164.074);
//                pars.push_back(1.51904);
//                pars.push_back(1.20248);
//                pars.push_back(1.51032);
//                pars.push_back(0.225052);
//                pars.push_back(1.63723);
//                pars.push_back(12380.);
//                pars.push_back(0.225659);
//                pars.push_back(0.819004);
//                pars.push_back(0.121807);
//                pars.push_back(0.34584);
//                pars.push_back(0.766653);
//                pars.push_back(-0.5554);
//                pars.push_back(1.32346);
//                pars.push_back(0.292367);
//                pars.push_back(-0.0872784);
//                pars.push_back(0.384439);
//                pars.push_back(0.794937);
//                pars.push_back(-0.50489);
//                pars.push_back(-0.0365481);
//                pars.push_back(0.438477);

                std::cout << "Evidence: " << MCEngine.getEvidence(pars, logmode) << std::endl;
            }
            std::cout << "ROOT VERSION:" << ROOT_RELEASE << std::endl;
            return ;
            // calculate the evidence
            //            if (CalculateEvidence) {
            //                // BAT default: 
            //                //   kIntGrid for the number of free parameters <= 2;
            //                //   otherwise, kIntMonteCarlo (or kIntCuba if available)
            //                //   MCEngine.SetIntegrationMethod(BCIntegrate::kIntCuba);
            //                MCEngine.SetRelativePrecision(1.e-3);
            //                MCEngine.SetAbsolutePrecision(1.e-10);
            //                if (evidence_min_iterations == 0) MCEngine.SetNIterationsMin(10000);
            //                else {
            //                    MCEngine.SetNIterationsMin(evidence_min_iterations);
            //                    MCEngine.SetNIterationsMax(10*evidence_min_iterations);
            //                }
            //                MCEngine.Integrate();
            //                evidence = MCEngine.GetIntegral();
            //                BCLog::OutSummary(Form(" Evidence = %.6e", MCEngine.GetIntegral()));
            //            }

            // draw all marginalized distributions into a pdf file
            if (PrintAllMarginalized)
                MCEngine.PrintAllMarginalized(("MonteCarlo_plots" + JobTag + ".pdf").c_str());

            // print results of the analysis into a text file
            MCEngine.PrintResults(("MonteCarlo_results" + JobTag + ".txt").c_str());

            // print histograms
            MCEngine.PrintHistogram(out, ObsDirName);

            BCSummaryTool myBCSummaryTool(&MCEngine);

            // draw the correlation matrix into a pdf file
            if (PrintCorrelationMatrix)
                myBCSummaryTool.PrintCorrelationMatrix(("ParamCorrelations" + JobTag + ".pdf").c_str());

            // print the correlation matrix into a tex file
            if (PrintCorrelationMatrix)
                MCEngine.PrintCorrelationMatrix(("ParamCorrelations" + JobTag + ".tex").c_str());

            // print comparisons of the prior knowledge to the posterior knowledge 
            // for all parameters into a pdf file
            if (PrintKnowledgeUpdatePlots)
                myBCSummaryTool.PrintKnowledgeUpdatePlots(("ParamUpdate" + JobTag + ".pdf").c_str());

            // draw an overview plot of the parameters into a pdf file
            if (PrintParameterPlot)
                myBCSummaryTool.PrintParameterPlot(("ParamSummary" + JobTag + ".pdf").c_str());

            // print a LaTeX table of the parameters into a tex file
            //myBCSummaryTool.PrintParameterLatex(("ParamSummary" + JobTag + ".tex").c_str());

            out.WriteMarginalizedDistributions();
            out.FillAnalysisTree();
            out.Close();

            // print logs for the histograms of the observables into a text file
            std::ofstream outHistoLog;
            outHistoLog.open((ObsDirName + "/HistoLog" + JobTag + ".txt").c_str(), std::ios::out);
            outHistoLog << MCEngine.getHistoLog();
            outHistoLog.close();

            // print statistics for the theory values of the observables into a text file
            std::ofstream outStatLog;
            outStatLog.open((ObsDirName + "/Statistics" + JobTag + ".txt").c_str(), std::ios::out);
            if (CalculateEvidence) outStatLog << "Evidence for " << ModelName.c_str() << ": " << evidence << "\n" << std::endl;
            outStatLog << MCEngine.computeStatistics();
            outStatLog.close();

            /* Number of events */
            std::stringstream ss;
            ss << "Number of used events: " << MCEngine.getNumOfUsedEvents();
            BCLog::OutSummary(ss.str().c_str());
            ss.str("");
            ss << "Number of discarded events: " << MCEngine.getNumOfDiscardedEvents();
            BCLog::OutSummary(ss.str().c_str());

            // close log file
            BCLog::CloseLog();

#ifdef _MPI
            double ** sendbuff = new double *[MCEngine.procnum];
            sendbuff[0] = new double[MCEngine.procnum * buffsize];
            for (int il = 1; il < MCEngine.procnum; il++) {
                sendbuff[il] = sendbuff[il - 1] + buffsize;
                sendbuff[il][0] = -1.; //Exit command
            }
            MPI::COMM_WORLD.Scatter(sendbuff[0], buffsize, MPI::DOUBLE,
                    recvbuff, buffsize, MPI::DOUBLE, 0);
            delete sendbuff[0];
            delete [] sendbuff;
#endif
        }
#ifdef _MPI
        delete [] recvbuff;
#endif
    } catch (std::string message) {
        std::cerr << message << std::endl;
        exit(EXIT_FAILURE);
    }
}
