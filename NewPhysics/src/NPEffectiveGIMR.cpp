/*
 * Copyright (C) 2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "NPEffectiveGIMR.h"

const std::string NPEffectiveGIMR::NPEffectiveGIMRVars[NNPEffectiveGIMRVars]
        = {"CW", "CHG", "CHW", "CHB", "CHWB", "CHD", "CHbox", "CH",
    "CHL1_11", "CHL1_12r", "CHL1_13r", "CHL1_22", "CHL1_23r", "CHL1_33",
    "CHL1_12i", "CHL1_13i", "CHL1_23i",
    "CHL3_11", "CHL3_12r", "CHL3_13r", "CHL3_22", "CHL3_23r", "CHL3_33",
    "CHL3_12i", "CHL3_13i", "CHL3_23i",
    "CHe_11", "CHe_12r", "CHe_13r", "CHe_22", "CHe_23r", "CHe_33",
    "CHe_12i", "CHe_13i", "CHe_23i",
    "CHQ1_11", "CHQ1_12r", "CHQ1_13r", "CHQ1_22", "CHQ1_23r", "CHQ1_33",
    "CHQ1_12i", "CHQ1_13i", "CHQ1_23i",
    "CHQ3_11", "CHQ3_12r", "CHQ3_13r", "CHQ3_22", "CHQ3_23r", "CHQ3_33",
    "CHQ3_12i", "CHQ3_13i", "CHQ3_23i",
    "CHu_11", "CHu_12r", "CHu_13r", "CHu_22", "CHu_23r", "CHu_33",
    "CHu_12i", "CHu_13i", "CHu_23i",
    "CHd_11", "CHd_12r", "CHd_13r", "CHd_22", "CHd_23r", "CHd_33",
    "CHd_12i", "CHd_13i", "CHd_23i",
    "CHud_11r", "CHud_12r", "CHud_13r", "CHud_22r", "CHud_23r", "CHud_33r",
    "CHud_11i", "CHud_12i", "CHud_13i", "CHud_22i", "CHud_23i", "CHud_33i",
    "CeH_11r", "CeH_12r", "CeH_13r", "CeH_22r", "CeH_23r", "CeH_33r",
    "CeH_11i", "CeH_12i", "CeH_13i", "CeH_22i", "CeH_23i", "CeH_33i",
    "CuH_11r", "CuH_12r", "CuH_13r", "CuH_22r", "CuH_23r", "CuH_33r",
    "CuH_11i", "CuH_12i", "CuH_13i", "CuH_22i", "CuH_23i", "CuH_33i",
    "CdH_11r", "CdH_12r", "CdH_13r", "CdH_22r", "CdH_23r", "CdH_33r",
    "CdH_11i", "CdH_12i", "CdH_13i", "CdH_22i", "CdH_23i", "CdH_33i",
    "CLL_1221", "Lambda_NP"};

const std::string NPEffectiveGIMR::NPEffectiveGIMRVars_LFU_QFU[NNPEffectiveGIMRVars_LFU_QFU]
        = {"CW", "CHG", "CHW", "CHB", "CHWB", "CHD", "CHbox", "CH",
    "CHL1", "CHL3", "CHe", "CHQ1", "CHQ3", "CHu", "CHd", "CHud_r", "CHud_i",
    "CeH_r", "CeH_i", "CuH_r", "CuH_i", "CdH_r", "CdH_i", "CLL",
    "Lambda_NP"};

NPEffectiveGIMR::NPEffectiveGIMR(const bool FlagLeptonUniversal_in, const bool FlagQuarkUniversal_in)
: NPbase(), FlagLeptonUniversal(FlagLeptonUniversal_in), FlagQuarkUniversal(FlagQuarkUniversal_in)
{
    if ((!FlagLeptonUniversal && !FlagQuarkUniversal)
            || (!FlagLeptonUniversal && FlagQuarkUniversal)
            || (FlagLeptonUniversal && !FlagQuarkUniversal))
        throw std::runtime_error("Invalid arguments for NPEffectiveGIMR::NPEffectiveGIMR()");

    FlagMwInput = false;

    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CW", boost::cref(CW)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHG", boost::cref(CHG)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHW", boost::cref(CHW)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHB", boost::cref(CHB)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHWB", boost::cref(CHWB)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHD", boost::cref(CHD)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHbox", boost::cref(CHbox)));
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CH", boost::cref(CH)));
    if (FlagLeptonUniversal) {
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1", boost::cref(CHL1_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3", boost::cref(CHL3_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe", boost::cref(CHe_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_r", boost::cref(CeH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_i", boost::cref(CeH_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CLL", boost::cref(CLL_1221)));
    } else {
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_11", boost::cref(CHL1_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_12r", boost::cref(CHL1_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_13r", boost::cref(CHL1_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_22", boost::cref(CHL1_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_23r", boost::cref(CHL1_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_33", boost::cref(CHL1_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_12i", boost::cref(CHL1_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_13i", boost::cref(CHL1_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL1_23i", boost::cref(CHL1_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_11", boost::cref(CHL3_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_12r", boost::cref(CHL3_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_13r", boost::cref(CHL3_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_22", boost::cref(CHL3_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_23r", boost::cref(CHL3_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_33", boost::cref(CHL3_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_12i", boost::cref(CHL3_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_13i", boost::cref(CHL3_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHL3_23i", boost::cref(CHL3_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_11", boost::cref(CHe_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_12r", boost::cref(CHe_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_13r", boost::cref(CHe_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_22", boost::cref(CHe_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_23r", boost::cref(CHe_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_33", boost::cref(CHe_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_12i", boost::cref(CHe_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_13i", boost::cref(CHe_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHe_23i", boost::cref(CHe_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_11r", boost::cref(CeH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_12r", boost::cref(CeH_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_13r", boost::cref(CeH_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_22r", boost::cref(CeH_22r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_23r", boost::cref(CeH_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_33r", boost::cref(CeH_33r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_11i", boost::cref(CeH_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_12i", boost::cref(CeH_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_13i", boost::cref(CeH_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_22i", boost::cref(CeH_22i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_23i", boost::cref(CeH_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CeH_33i", boost::cref(CeH_33i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CLL_1221", boost::cref(CLL_1221)));
    }
    if (FlagQuarkUniversal) {
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1", boost::cref(CHQ1_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3", boost::cref(CHQ3_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu", boost::cref(CHu_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd", boost::cref(CHd_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_r", boost::cref(CHud_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_i", boost::cref(CHud_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_r", boost::cref(CuH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_i", boost::cref(CuH_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_r", boost::cref(CdH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_i", boost::cref(CdH_11i)));
    } else {
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_11", boost::cref(CHQ1_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_12r", boost::cref(CHQ1_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_13r", boost::cref(CHQ1_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_22", boost::cref(CHQ1_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_23r", boost::cref(CHQ1_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_33", boost::cref(CHQ1_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_12i", boost::cref(CHQ1_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_13i", boost::cref(CHQ1_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ1_23i", boost::cref(CHQ1_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_11", boost::cref(CHQ3_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_12r", boost::cref(CHQ3_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_13r", boost::cref(CHQ3_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_22", boost::cref(CHQ3_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_23r", boost::cref(CHQ3_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_33", boost::cref(CHQ3_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_12i", boost::cref(CHQ3_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_13i", boost::cref(CHQ3_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHQ3_23i", boost::cref(CHQ3_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_11", boost::cref(CHu_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_12r", boost::cref(CHu_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_13r", boost::cref(CHu_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_22", boost::cref(CHu_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_23r", boost::cref(CHu_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_33", boost::cref(CHu_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_12i", boost::cref(CHu_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_13i", boost::cref(CHu_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHu_23i", boost::cref(CHu_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_11", boost::cref(CHd_11)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_12r", boost::cref(CHd_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_13r", boost::cref(CHd_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_22", boost::cref(CHd_22)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_23r", boost::cref(CHd_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_33", boost::cref(CHd_33)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_12i", boost::cref(CHd_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_13i", boost::cref(CHd_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHd_23i", boost::cref(CHd_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_11r", boost::cref(CHud_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_12r", boost::cref(CHud_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_13r", boost::cref(CHud_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_22r", boost::cref(CHud_22r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_23r", boost::cref(CHud_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_33r", boost::cref(CHud_33r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_11i", boost::cref(CHud_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_12i", boost::cref(CHud_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_13i", boost::cref(CHud_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_22i", boost::cref(CHud_22i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_23i", boost::cref(CHud_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CHud_33i", boost::cref(CHud_33i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_11r", boost::cref(CuH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_12r", boost::cref(CuH_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_13r", boost::cref(CuH_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_22r", boost::cref(CuH_22r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_23r", boost::cref(CuH_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_33r", boost::cref(CuH_33r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_11i", boost::cref(CuH_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_12i", boost::cref(CuH_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_13i", boost::cref(CuH_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_22i", boost::cref(CuH_22i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_23i", boost::cref(CuH_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CuH_33i", boost::cref(CuH_33i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_11r", boost::cref(CdH_11r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_12r", boost::cref(CdH_12r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_13r", boost::cref(CdH_13r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_22r", boost::cref(CdH_22r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_23r", boost::cref(CdH_23r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_33r", boost::cref(CdH_33r)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_11i", boost::cref(CdH_11i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_12i", boost::cref(CdH_12i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_13i", boost::cref(CdH_13i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_22i", boost::cref(CdH_22i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_23i", boost::cref(CdH_23i)));
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("CdH_33i", boost::cref(CdH_33i)));
    }
    ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("Lambda_NP", boost::cref(Lambda_NP)));
    if (FlagMwInput)
        ModelParamMap.insert(std::pair<std::string, boost::reference_wrapper<const double> >("MwInput", boost::cref(MwInput)));
}

bool NPEffectiveGIMR::PostUpdate()
{
    if (!NPbase::PostUpdate()) return (false);

    LambdaNP2 = Lambda_NP * Lambda_NP;
    v2_over_LambdaNP2 = v() * v() / LambdaNP2;
    if (FlagMwInput)
        cW_tree = MwInput / Mz;
    else
        cW_tree = Mw_tree() / Mz;
    cW2_tree = cW_tree * cW_tree;
    sW2_tree = 1.0 - cW2_tree;
    sW_tree = sqrt(sW2_tree);

    delta_ZZ = (cW2_tree * CHW + sW2_tree * CHB + sW_tree * cW_tree * CHWB) * v2_over_LambdaNP2;
    delta_AA = (sW2_tree * CHW + cW2_tree * CHB - sW_tree * cW_tree * CHWB) * v2_over_LambdaNP2;
    delta_AZ = 2.0 * sW_tree * cW_tree * (CHW - CHB) * v2_over_LambdaNP2
            - (cW2_tree - sW2_tree) * CHWB * v2_over_LambdaNP2;
    delta_h = (-CHD / 4.0 + CHbox) * v2_over_LambdaNP2;

    return (true);
}

void NPEffectiveGIMR::setParameter(const std::string name, const double& value)
{
    if (name.compare("CW") == 0)
        CW = value;
    else if (name.compare("CHG") == 0)
        CHG = value;
    else if (name.compare("CHW") == 0)
        CHW = value;
    else if (name.compare("CHB") == 0)
        CHB = value;
    else if (name.compare("CHWB") == 0)
        CHWB = value;
    else if (name.compare("CHD") == 0)
        CHD = value;
    else if (name.compare("CHbox") == 0)
        CHbox = value;
    else if (name.compare("CH") == 0)
        CH = value;
    else if (name.compare("CHL1_11") == 0)
        CHL1_11 = value;
    else if (name.compare("CHL1_12r") == 0)
        CHL1_12r = value;
    else if (name.compare("CHL1_13r") == 0)
        CHL1_13r = value;
    else if (name.compare("CHL1_22") == 0)
        CHL1_22 = value;
    else if (name.compare("CHL1_23r") == 0)
        CHL1_23r = value;
    else if (name.compare("CHL1_33") == 0)
        CHL1_33 = value;
    else if (name.compare("CHL1_12i") == 0)
        CHL1_12i = value;
    else if (name.compare("CHL1_13i") == 0)
        CHL1_13i = value;
    else if (name.compare("CHL1_23i") == 0)
        CHL1_23i = value;
    else if (name.compare("CHL1") == 0) {
        CHL1_11 = value;
        CHL1_12r = 0.0;
        CHL1_13r = 0.0;
        CHL1_22 = value;
        CHL1_23r = 0.0;
        CHL1_33 = value;
        CHL1_12i = 0.0;
        CHL1_13i = 0.0;
        CHL1_23i = 0.0;
    } else if (name.compare("CHL3_11") == 0)
        CHL3_11 = value;
    else if (name.compare("CHL3_12r") == 0)
        CHL3_12r = value;
    else if (name.compare("CHL3_13r") == 0)
        CHL3_13r = value;
    else if (name.compare("CHL3_22") == 0)
        CHL3_22 = value;
    else if (name.compare("CHL3_23r") == 0)
        CHL3_23r = value;
    else if (name.compare("CHL3_33") == 0)
        CHL3_33 = value;
    else if (name.compare("CHL3_12i") == 0)
        CHL3_12i = value;
    else if (name.compare("CHL3_13i") == 0)
        CHL3_13i = value;
    else if (name.compare("CHL3_23i") == 0)
        CHL3_23i = value;
    else if (name.compare("CHL3") == 0) {
        CHL3_11 = value;
        CHL3_12r = 0.0;
        CHL3_13r = 0.0;
        CHL3_22 = value;
        CHL3_23r = 0.0;
        CHL3_33 = value;
        CHL3_12i = 0.0;
        CHL3_13i = 0.0;
        CHL3_23i = 0.0;
    } else if (name.compare("CHe_11") == 0)
        CHe_11 = value;
    else if (name.compare("CHe_12r") == 0)
        CHe_12r = value;
    else if (name.compare("CHe_13r") == 0)
        CHe_13r = value;
    else if (name.compare("CHe_22") == 0)
        CHe_22 = value;
    else if (name.compare("CHe_23r") == 0)
        CHe_23r = value;
    else if (name.compare("CHe_33") == 0)
        CHe_33 = value;
    else if (name.compare("CHe_12i") == 0)
        CHe_12i = value;
    else if (name.compare("CHe_13i") == 0)
        CHe_13i = value;
    else if (name.compare("CHe_23i") == 0)
        CHe_23i = value;
    else if (name.compare("CHe") == 0) {
        CHe_11 = value;
        CHe_12r = 0.0;
        CHe_13r = 0.0;
        CHe_22 = value;
        CHe_23r = 0.0;
        CHe_33 = value;
        CHe_12i = 0.0;
        CHe_13i = 0.0;
        CHe_23i = 0.0;
    } else if (name.compare("CHQ1_11") == 0)
        CHQ1_11 = value;
    else if (name.compare("CHQ1_12r") == 0)
        CHQ1_12r = value;
    else if (name.compare("CHQ1_13r") == 0)
        CHQ1_13r = value;
    else if (name.compare("CHQ1_22") == 0)
        CHQ1_22 = value;
    else if (name.compare("CHQ1_23r") == 0)
        CHQ1_23r = value;
    else if (name.compare("CHQ1_33") == 0)
        CHQ1_33 = value;
    else if (name.compare("CHQ1_12i") == 0)
        CHQ1_12i = value;
    else if (name.compare("CHQ1_13i") == 0)
        CHQ1_13i = value;
    else if (name.compare("CHQ1_23i") == 0)
        CHQ1_23i = value;
    else if (name.compare("CHQ1") == 0) {
        CHQ1_11 = value;
        CHQ1_12r = 0.0;
        CHQ1_13r = 0.0;
        CHQ1_22 = value;
        CHQ1_23r = 0.0;
        CHQ1_33 = value;
        CHQ1_12i = 0.0;
        CHQ1_13i = 0.0;
        CHQ1_23i = 0.0;
    } else if (name.compare("CHQ3_11") == 0)
        CHQ3_11 = value;
    else if (name.compare("CHQ3_12r") == 0)
        CHQ3_12r = value;
    else if (name.compare("CHQ3_13r") == 0)
        CHQ3_13r = value;
    else if (name.compare("CHQ3_22") == 0)
        CHQ3_22 = value;
    else if (name.compare("CHQ3_23r") == 0)
        CHQ3_23r = value;
    else if (name.compare("CHQ3_33") == 0)
        CHQ3_33 = value;
    else if (name.compare("CHQ3_12i") == 0)
        CHQ3_12i = value;
    else if (name.compare("CHQ3_13i") == 0)
        CHQ3_13i = value;
    else if (name.compare("CHQ3_23i") == 0)
        CHQ3_23i = value;
    else if (name.compare("CHQ3") == 0) {
        CHQ3_11 = value;
        CHQ3_12r = 0.0;
        CHQ3_13r = 0.0;
        CHQ3_22 = value;
        CHQ3_23r = 0.0;
        CHQ3_33 = value;
        CHQ3_12i = 0.0;
        CHQ3_13i = 0.0;
        CHQ3_23i = 0.0;
    } else if (name.compare("CHu_11") == 0)
        CHu_11 = value;
    else if (name.compare("CHu_12r") == 0)
        CHu_12r = value;
    else if (name.compare("CHu_13r") == 0)
        CHu_13r = value;
    else if (name.compare("CHu_22") == 0)
        CHu_22 = value;
    else if (name.compare("CHu_23r") == 0)
        CHu_23r = value;
    else if (name.compare("CHu_33") == 0)
        CHu_33 = value;
    else if (name.compare("CHu_12i") == 0)
        CHu_12i = value;
    else if (name.compare("CHu_13i") == 0)
        CHu_13i = value;
    else if (name.compare("CHu_23i") == 0)
        CHu_23i = value;
    else if (name.compare("CHu") == 0) {
        CHu_11 = value;
        CHu_12r = 0.0;
        CHu_13r = 0.0;
        CHu_22 = value;
        CHu_23r = 0.0;
        CHu_33 = value;
        CHu_12i = 0.0;
        CHu_13i = 0.0;
        CHu_23i = 0.0;
    } else if (name.compare("CHd_11") == 0)
        CHd_11 = value;
    else if (name.compare("CHd_12r") == 0)
        CHd_12r = value;
    else if (name.compare("CHd_13r") == 0)
        CHd_13r = value;
    else if (name.compare("CHd_22") == 0)
        CHd_22 = value;
    else if (name.compare("CHd_23r") == 0)
        CHd_23r = value;
    else if (name.compare("CHd_33") == 0)
        CHd_33 = value;
    else if (name.compare("CHd_12i") == 0)
        CHd_12i = value;
    else if (name.compare("CHd_13i") == 0)
        CHd_13i = value;
    else if (name.compare("CHd_23i") == 0)
        CHd_23i = value;
    else if (name.compare("CHd") == 0) {
        CHd_11 = value;
        CHd_12r = 0.0;
        CHd_13r = 0.0;
        CHd_22 = value;
        CHd_23r = 0.0;
        CHd_33 = value;
        CHd_12i = 0.0;
        CHd_13i = 0.0;
        CHd_23i = 0.0;
    } else if (name.compare("CHud_11r") == 0)
        CHud_11r = value;
    else if (name.compare("CHud_12r") == 0)
        CHud_12r = value;
    else if (name.compare("CHud_13r") == 0)
        CHud_13r = value;
    else if (name.compare("CHud_22r") == 0)
        CHud_22r = value;
    else if (name.compare("CHud_23r") == 0)
        CHud_23r = value;
    else if (name.compare("CHud_33r") == 0)
        CHud_33r = value;
    else if (name.compare("CHud_r") == 0) {
        CHud_11r = value;
        CHud_12r = 0.0;
        CHud_13r = 0.0;
        CHud_22r = value;
        CHud_23r = 0.0;
        CHud_33r = value;
    } else if (name.compare("CHud_11i") == 0)
        CHud_11i = value;
    else if (name.compare("CHud_12i") == 0)
        CHud_12i = value;
    else if (name.compare("CHud_13i") == 0)
        CHud_13i = value;
    else if (name.compare("CHud_22i") == 0)
        CHud_22i = value;
    else if (name.compare("CHud_23i") == 0)
        CHud_23i = value;
    else if (name.compare("CHud_33i") == 0)
        CHud_33i = value;
    else if (name.compare("CHud_i") == 0) {
        CHud_11i = value;
        CHud_12i = 0.0;
        CHud_13i = 0.0;
        CHud_22i = value;
        CHud_23i = 0.0;
        CHud_33i = value;
    } else if (name.compare("CeH_11r") == 0)
        CeH_11r = value;
    else if (name.compare("CeH_12r") == 0)
        CeH_12r = value;
    else if (name.compare("CeH_13r") == 0)
        CeH_13r = value;
    else if (name.compare("CeH_22r") == 0)
        CeH_22r = value;
    else if (name.compare("CeH_23r") == 0)
        CeH_23r = value;
    else if (name.compare("CeH_33r") == 0)
        CeH_33r = value;
    else if (name.compare("CeH_r") == 0) {
        CeH_11r = value;
        CeH_12r = 0.0;
        CeH_13r = 0.0;
        CeH_22r = value;
        CeH_23r = 0.0;
        CeH_33r = value;
    } else if (name.compare("CeH_11i") == 0)
        CeH_11i = value;
    else if (name.compare("CeH_12i") == 0)
        CeH_12i = value;
    else if (name.compare("CeH_13i") == 0)
        CeH_13i = value;
    else if (name.compare("CeH_22i") == 0)
        CeH_22i = value;
    else if (name.compare("CeH_23i") == 0)
        CeH_23i = value;
    else if (name.compare("CeH_33i") == 0)
        CeH_33i = value;
    else if (name.compare("CeH_i") == 0) {
        CeH_11i = value;
        CeH_12i = 0.0;
        CeH_13i = 0.0;
        CeH_22i = value;
        CeH_23i = 0.0;
        CeH_33i = value;
    } else if (name.compare("CuH_11r") == 0)
        CuH_11r = value;
    else if (name.compare("CuH_12r") == 0)
        CuH_12r = value;
    else if (name.compare("CuH_13r") == 0)
        CuH_13r = value;
    else if (name.compare("CuH_22r") == 0)
        CuH_22r = value;
    else if (name.compare("CuH_23r") == 0)
        CuH_23r = value;
    else if (name.compare("CuH_33r") == 0)
        CuH_33r = value;
    else if (name.compare("CuH_r") == 0) {
        CuH_11r = value;
        CuH_12r = 0.0;
        CuH_13r = 0.0;
        CuH_22r = value;
        CuH_23r = 0.0;
        CuH_33r = value;
    } else if (name.compare("CuH_11i") == 0)
        CuH_11i = value;
    else if (name.compare("CuH_12i") == 0)
        CuH_12i = value;
    else if (name.compare("CuH_13i") == 0)
        CuH_13i = value;
    else if (name.compare("CuH_22i") == 0)
        CuH_22i = value;
    else if (name.compare("CuH_23i") == 0)
        CuH_23i = value;
    else if (name.compare("CuH_33i") == 0)
        CuH_33i = value;
    else if (name.compare("CuH_i") == 0) {
        CuH_11i = value;
        CuH_12i = 0.0;
        CuH_13i = 0.0;
        CuH_22i = value;
        CuH_23i = 0.0;
        CuH_33i = value;
    } else if (name.compare("CdH_11r") == 0)
        CdH_11r = value;
    else if (name.compare("CdH_12r") == 0)
        CdH_12r = value;
    else if (name.compare("CdH_13r") == 0)
        CdH_13r = value;
    else if (name.compare("CdH_22r") == 0)
        CdH_22r = value;
    else if (name.compare("CdH_23r") == 0)
        CdH_23r = value;
    else if (name.compare("CdH_33r") == 0)
        CdH_33r = value;
    else if (name.compare("CdH_r") == 0) {
        CdH_11r = value;
        CdH_12r = 0.0;
        CdH_13r = 0.0;
        CdH_22r = value;
        CdH_23r = 0.0;
        CdH_33r = value;
    } else if (name.compare("CdH_11i") == 0)
        CdH_11i = value;
    else if (name.compare("CdH_12i") == 0)
        CdH_12i = value;
    else if (name.compare("CdH_13i") == 0)
        CdH_13i = value;
    else if (name.compare("CdH_22i") == 0)
        CdH_22i = value;
    else if (name.compare("CdH_23i") == 0)
        CdH_23i = value;
    else if (name.compare("CdH_33i") == 0)
        CdH_33i = value;
    else if (name.compare("CdH_i") == 0) {
        CdH_11i = value;
        CdH_12i = 0.0;
        CdH_13i = 0.0;
        CdH_22i = value;
        CdH_23i = 0.0;
        CdH_33i = value;
    } else if (name.compare("CLL_1221") == 0) {
        CLL_1221 = value;
        CLL_2112 = value;
    } else if (name.compare("CLL") == 0) {
        CLL_1221 = value;
        CLL_2112 = value;
    } else if (name.compare("Lambda_NP") == 0)
        Lambda_NP = value;
    else if (name.compare("MwInput") == 0)
        MwInput = value;
    else
        NPbase::setParameter(name, value);
}

bool NPEffectiveGIMR::CheckParameters(const std::map<std::string, double>& DPars)
{
    if (FlagLeptonUniversal && FlagQuarkUniversal) {
        if (FlagMwInput) {
            if (DPars.find("MwInput") == DPars.end()) {
                std::cout << "ERROR: Missing mandatory NPEffectiveGIMR_LFU_QFU parameter MwInput" << std::endl;
                return false;
            }
        }
        for (int i = 0; i < NNPEffectiveGIMRVars_LFU_QFU; i++) {
            if (DPars.find(NPEffectiveGIMRVars_LFU_QFU[i]) == DPars.end()) {
                std::cout << "ERROR: Missing mandatory NPEffectiveGIMR_LFU_QFU parameter "
                        << NPEffectiveGIMRVars_LFU_QFU[i] << std::endl;
                return false;
            }
        }
        //} else if (FlagLeptonUniversal && !FlagQuarkUniversal) {
        //} else if (!FlagLeptonUniversal && FlagQuarkUniversal) {
    } else if (!FlagLeptonUniversal && !FlagQuarkUniversal) {
        if (FlagMwInput) {
            if (DPars.find("MwInput") == DPars.end()) {
                std::cout << "ERROR: Missing mandatory NPEffectiveGIMR parameter MwInput" << std::endl;
                return false;
            }
        }
        for (int i = 0; i < NNPEffectiveGIMRVars; i++) {
            if (DPars.find(NPEffectiveGIMRVars[i]) == DPars.end()) {
                std::cout << "ERROR: Missing mandatory NPEffectiveGIMR parameter"
                        << NPEffectiveGIMRVars[i] << std::endl;
                return false;
            }
        }
    } else
        throw std::runtime_error("Error in NPEffectiveGIMR::CheckParameters()");

    return (NPbase::CheckParameters(DPars));
}

bool NPEffectiveGIMR::setFlag(const std::string name, const bool value)
{
    bool res = false;
    if (name.compare("MwInput") == 0) {
        FlagMwInput = value;
        res = true;
    } else
        res = NPbase::setFlag(name, value);

    return (res);
}


////////////////////////////////////////////////////////////////////////

double NPEffectiveGIMR::CHF1_diag(const Particle F) const
{
    if (F.is("NEUTRINO_1") || F.is("ELECTRON"))
        return CHL1_11;
    else if (F.is("NEUTRINO_2") || F.is("MU"))
        return CHL1_22;
    else if (F.is("NEUTRINO_3") || F.is("TAU"))
        return CHL1_33;
    else if (F.is("UP") || F.is("DOWN"))
        return CHQ1_11;
    else if (F.is("CHARM") || F.is("STRANGE"))
        return CHQ1_22;
    else if (F.is("TOP") || F.is("BOTTOM"))
        return CHQ1_33;
    else
        throw std::runtime_error("NPEffectiveGIMR::CHF1_diag(): wrong argument");
}

double NPEffectiveGIMR::CHF3_diag(const Particle F) const
{
    if (F.is("NEUTRINO_1") || F.is("ELECTRON"))
        return CHL3_11;
    else if (F.is("NEUTRINO_2") || F.is("MU"))
        return CHL3_22;
    else if (F.is("NEUTRINO_3") || F.is("TAU"))
        return CHL3_33;
    else if (F.is("UP") || F.is("DOWN"))
        return CHQ3_11;
    else if (F.is("CHARM") || F.is("STRANGE"))
        return CHQ3_22;
    else if (F.is("TOP") || F.is("BOTTOM"))
        return CHQ3_33;
    else
        throw std::runtime_error("NPEffectiveGIMR::CHF3_diag(): wrong argument");
}

double NPEffectiveGIMR::CHf_diag(const Particle f) const
{
    if (f.is("NEUTRINO_1") || f.is("NEUTRINO_2") || f.is("NEUTRINO_3"))
        return 0.0;
    else if (f.is("ELECTRON"))
        return CHe_11;
    else if (f.is("MU"))
        return CHe_22;
    else if (f.is("TAU"))
        return CHe_33;
    else if (f.is("UP"))
        return CHu_11;
    else if (f.is("CHARM"))
        return CHu_22;
    else if (f.is("TOP"))
        return CHu_33;
    else if (f.is("DOWN"))
        return CHd_11;
    else if (f.is("STRANGE"))
        return CHd_22;
    else if (f.is("BOTTOM"))
        return CHd_33;
    else
        throw std::runtime_error("NPEffectiveGIMR::CHf_diag(): wrong argument");
}

complex NPEffectiveGIMR::CHud_diag(const Particle u) const
{
    if (!u.is("QUARK") || u.getIndex() % 2 != 0)
        throw std::runtime_error("NPEffectiveGIMR::CHud_diag(): wrong argument");

    if (u.is("UP"))
        return complex(CHud_11r, CHud_11i, false);
    else if (u.is("CHARM"))
        return complex(CHud_22r, CHud_22i, false);
    else if (u.is("TOP"))
        return complex(CHud_22r, CHud_33i, false);
    else
        throw std::runtime_error("NPEffectiveGIMR::CHud_diag(): wrong argument");
}

complex NPEffectiveGIMR::CfH_diag(const Particle f) const
{
    if (f.is("NEUTRINO_1") || f.is("NEUTRINO_2") || f.is("NEUTRINO_3"))
        return 0.0;
    else if (f.is("ELECTRON"))
        return complex(CeH_11r, CeH_11i, false);
    else if (f.is("MU"))
        return complex(CeH_22r, CeH_22i, false);
    else if (f.is("TAU"))
        return complex(CeH_33r, CeH_33i, false);
    else if (f.is("UP"))
        return complex(CuH_11r, CuH_11i, false);
    else if (f.is("CHARM"))
        return complex(CuH_22r, CuH_22i, false);
    else if (f.is("TOP"))
        return complex(CuH_33r, CuH_33i, false);
    else if (f.is("DOWN"))
        return complex(CdH_11r, CdH_11i, false);
    else if (f.is("STRANGE"))
        return complex(CdH_22r, CdH_22i, false);
    else if (f.is("BOTTOM"))
        return complex(CdH_33r, CdH_33i, false);
    else
        throw std::runtime_error("NPEffectiveGIMR::CfH_diag(): wrong argument");
}


////////////////////////////////////////////////////////////////////////

double NPEffectiveGIMR::DeltaGF() const
{
    return ((CHL3_11 + CHL3_22 - 0.5 * (CLL_1221 + CLL_2112)) * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::obliqueS() const
{
    return (4.0 * sW2_tree * cW_tree * CHWB / alphaMz() * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::obliqueT() const
{
    return (-CHD / 2.0 / alphaMz() * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::obliqueU() const
{
    return 0.0;
}

double NPEffectiveGIMR::Mw() const
{
    if (FlagMwInput)
        return MwInput;
    else
        return (trueSM.Mw() - Mw_tree() / 4.0 / (cW2_tree - sW2_tree)
            *(4.0 * sW_tree * cW_tree * CHWB * v2_over_LambdaNP2
            + cW2_tree * CHD * v2_over_LambdaNP2
            + 2.0 * sW2_tree * DeltaGF()));
}

double NPEffectiveGIMR::GammaW() const
{
    double G0 = GF * pow(Mw(), 3.0) / 6.0 / sqrt(2.0) / M_PI;
    double GammaW_tree = (3.0 + 2.0 * Nc) * G0;

    if (FlagMwInput)
        throw std::runtime_error("Write codes in NPEffectiveGIMR::GammaW()!");
    else
        return (trueSM.GammaW()
            - 3.0 * GammaW_tree / 4.0 / (cW2_tree - sW2_tree)
            *(4.0 * sW_tree * cW_tree * CHWB * v2_over_LambdaNP2
            + cW2_tree * CHD * v2_over_LambdaNP2
            + 2.0 * (1.0 + cW2_tree) / 3.0 * DeltaGF())
            + 2.0 * GammaW_tree / 3.0 * (CHL3_11 + CHQ3_11 + CHQ3_22) * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::deltaGV_f(const Particle p) const
{
    return (deltaGL_f(p) + deltaGR_f(p));
}

double NPEffectiveGIMR::deltaGA_f(const Particle p) const
{
    return (deltaGL_f(p) - deltaGR_f(p));
}

double NPEffectiveGIMR::deltaGL_f(const Particle p) const
{
    double I3p = p.getIsospin(), Qp = p.getCharge();
    double CHF1 = CHF1_diag(p);
    double CHF3 = CHF3_diag(p);
    double NPindirect;
    if (FlagMwInput) {
        NPindirect = -I3p / 4.0 * (CHD * v2_over_LambdaNP2 + 2.0 * DeltaGF())
                + Qp * sW2_tree
                * ((cW_tree / sW_tree * CHWB + (1.0 + cW2_tree) / 4.0 / sW2_tree * CHD) * v2_over_LambdaNP2 + 0.5 * DeltaGF());
    } else {
        NPindirect = -I3p / 4.0 * (CHD * v2_over_LambdaNP2 + 2.0 * DeltaGF())
                - Qp * sW2_tree / 4.0 / (cW2_tree - sW2_tree)
                *((4.0 * cW_tree / sW_tree * CHWB + CHD) * v2_over_LambdaNP2 + 2.0 * DeltaGF());
    }
    double NPdirect = -0.5 * (CHF1 - 2.0 * I3p * CHF3) * v2_over_LambdaNP2;
    return (NPindirect + NPdirect);
}

double NPEffectiveGIMR::deltaGR_f(const Particle p) const
{
    double Qp = p.getCharge();
    double CHf = CHf_diag(p);
    double NPindirect;
    if (FlagMwInput) {
        NPindirect = Qp * sW2_tree
                * ((cW_tree / sW_tree * CHWB + (1.0 + cW2_tree) / 4.0 / sW2_tree * CHD) * v2_over_LambdaNP2 + 0.5 * DeltaGF());
    } else {
        NPindirect = -Qp * sW2_tree / 4.0 / (cW2_tree - sW2_tree)
                *((4.0 * cW_tree / sW_tree * CHWB + CHD) * v2_over_LambdaNP2 + 2.0 * DeltaGF());
    }
    double NPdirect = -0.5 * CHf*v2_over_LambdaNP2;
    return (NPindirect + NPdirect);
}


////////////////////////////////////////////////////////////////////////

complex NPEffectiveGIMR::deltaGL_Wff(const Particle pbar, const Particle p) const
{
    if (pbar.getIndex() + 1 != p.getIndex() || pbar.getIndex() % 2 != 0)
        throw std::runtime_error("NPEffectiveGIMR::deltaGL_Wff(): Not implemented");

    double CHF3 = CHF3_diag(pbar);
    double NPindirect;
    if (FlagMwInput) {
        NPindirect = -0.5 * DeltaGF();
    } else {
        NPindirect = -cW2_tree / 4.0 / (cW2_tree - sW2_tree)
                * ((4.0 * sW_tree / cW_tree * CHWB + CHD) * v2_over_LambdaNP2 + 2.0 * DeltaGF());
    }
    double NPdirect = CHF3 * v2_over_LambdaNP2;
    return (NPindirect + NPdirect);
}

complex NPEffectiveGIMR::deltaGR_Wff(const Particle pbar, const Particle p) const
{
    if (pbar.getIndex() + 1 != p.getIndex() || pbar.getIndex() % 2 != 0)
        throw std::runtime_error("NPEffectiveGIMR::deltaGR_Wff(): Not implemented");

    complex CHud = CHud_diag(pbar);
    return (0.5 * CHud * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::deltaG_hgg() const
{
    return (CHG * v2_over_LambdaNP2 / v());
}

double NPEffectiveGIMR::deltaG1_hWW() const
{
    return (2.0 * CHW * v2_over_LambdaNP2 / v());
}

double NPEffectiveGIMR::deltaG2_hWW() const
{
    return 0.0;
}

double NPEffectiveGIMR::deltaG3_hWW() const
{
    double NPindirect;
    if (FlagMwInput) {
        NPindirect = 2.0 * MwInput * MwInput / v() * (delta_h - 0.5 * DeltaGF());
    } else {
        NPindirect = 2.0 * cW2_tree * Mz * Mz / v()
                * (delta_h - 1.0 / 2.0 / (cW2_tree - sW2_tree)
                * ((4.0 * sW_tree * cW_tree * CHWB + cW2_tree * CHD) * v2_over_LambdaNP2 + DeltaGF()));
    }
    return NPindirect;
}

double NPEffectiveGIMR::deltaG1_hZZ() const
{
    return (delta_ZZ / v());
}

double NPEffectiveGIMR::deltaG2_hZZ() const
{
    return 0.0;
}

double NPEffectiveGIMR::deltaG3_hZZ() const
{
    double NPindirect = Mz * Mz / v() * (-0.5 * CHD * v2_over_LambdaNP2 + delta_h - 0.5 * DeltaGF());
    double NPdirect = Mz * Mz / v() * CHD * v2_over_LambdaNP2;
    return (NPindirect + NPdirect);
}

double NPEffectiveGIMR::deltaG1_hZA() const
{
    return (delta_AZ / v());
}

double NPEffectiveGIMR::deltaG2_hZA() const
{
    return 0.0;
}

double NPEffectiveGIMR::deltaG_hAA() const
{
    return (delta_AA / v());
}

complex NPEffectiveGIMR::deltaG_hff(const Particle p) const
{
    /* The effects of the RG running are neglected. */
    double mf;
    if (p.is("TOP"))
        //mf = p.getMass(); // m_t(m_t)
        mf = mtpole; // pole mass
    else
        mf = p.getMass();
    complex CfH = CfH_diag(p);
    return (-mf / v() * (delta_h - 0.5 * DeltaGF())
            + CfH * v2_over_LambdaNP2 / sqrt(2.0));
}

complex NPEffectiveGIMR::deltaGL_Wffh(const Particle pbar, const Particle p) const
{
    if (pbar.getIndex() + 1 != p.getIndex() || pbar.getIndex() % 2 != 0)
        throw std::runtime_error("NPEffectiveGIMR::deltaGL_Wffh(): Not implemented");

    double CHF3 = CHF3_diag(pbar);
    return (2.0 * sqrt(2.0) * Mz * cW_tree / v() / v() * CHF3 * v2_over_LambdaNP2);
}

complex NPEffectiveGIMR::deltaGR_Wffh(const Particle pbar, const Particle p) const
{
    if (pbar.getIndex() + 1 != p.getIndex() || pbar.getIndex() % 2 != 0)
        throw std::runtime_error("NPEffectiveGIMR::deltaGR_Wffh(): Not implemented");

    complex CHud = CHud_diag(pbar);
    return (sqrt(2.0) * Mz * cW_tree / v() / v() * CHud * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::deltaGL_Zffh(const Particle p) const
{
    double I3p = p.getIsospin();
    double CHF1 = CHF1_diag(p);
    double CHF3 = CHF3_diag(p);
    return (-2.0 * Mz / v() / v() * (CHF1 - 2.0 * I3p * CHF3) * v2_over_LambdaNP2);
}

double NPEffectiveGIMR::deltaGR_Zffh(const Particle p) const
{
    double CHf = CHf_diag(p);
    return (-2.0 * Mz / v() / v() * CHf * v2_over_LambdaNP2);
}


////////////////////////////////////////////////////////////////////////

complex NPEffectiveGIMR::f_triangle(const double tau) const
{
    complex tmp;
    if (tau >= 1.0) {
        tmp = asin(1.0 / sqrt(tau));
        return (tmp * tmp);
    } else {
        tmp = log((1.0 + sqrt(1.0 - tau)) / (1.0 - sqrt(1.0 - tau))) - M_PI * complex::i();
        return (-0.25 * tmp * tmp);
    }
}

complex NPEffectiveGIMR::AH_f(const double tau) const
{
    return (2.0 * tau * (1.0 + (1.0 - tau) * f_triangle(tau)));
}

double NPEffectiveGIMR::muggH(const double sqrt_s) const
{
    double m_t = mtpole;
    //doulbe m_t = quarks[TOP].getMass();
    //double m_b = quarks[BOTTOM].getMass();

    complex dKappa_t = deltaG_hff(quarks[TOP]) / (-m_t / v());
    //complex dKappa_b = deltaG_hff(quarks[BOTTOM]) / (-m_b / v());

    /* L_eff = G_eff_t_SM*hGG */
    complex G_eff_t_SM = AlsMz / 16.0 / M_PI / v() * AH_f(4.0 * m_t * m_t / mHl / mHl);

    //double sigma_tt_SM = trueSM.computeSigmaggH_tt(sqrt_s);
    //double sigma_bb_SM = trueSM.computeSigmaggH_bb(sqrt_s);
    //double sigma_tb_SM = trueSM.computeSigmaggH_tb(sqrt_s);
    //complex tmp = (2.0 * dKappa_t * sigma_tt_SM
    //        + 2.0 * dKappa_b * sigma_bb_SM
    //        + (dKappa_t + dKappa_b) * sigma_tb_SM)
    //        / (sigma_tt_SM + sigma_bb_SM + sigma_tb_SM);
    complex tmp = 2.0 * dKappa_t;

    complex tmp2 = 2.0 * CHG / v() * v2_over_LambdaNP2 / G_eff_t_SM;
    return (1.0 + tmp.real() + tmp2.real());
}

double NPEffectiveGIMR::muVBF(const double sqrt_s) const
{
    double mu = 1.0;
    if (sqrt_s == 1.96) {
        mu +=  -0.046 * deltaGL_f(quarks[UP])
                +0.088 * deltaGR_f(quarks[UP])
                +11.594 * deltaGL_f(quarks[DOWN])
                -0.021 * deltaGR_f(quarks[DOWN])
	            +0.046 * deltaGL_Wff(quarks[UP],quarks[DOWN]).real()
                -0.012 * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real()
                -0.084 * deltaG_hgg()
                +0.391 * deltaG_hAA()
                +26.344 * deltaG1_hZA()
                +14.928 * deltaG2_hZA()
                -0.129 * deltaG1_hWW()
                +0.084 * deltaG2_hWW()
                +0.164 * deltaG3_hWW()
                -0.033 * deltaG1_hZZ()
                -1.408 * deltaG2_hZZ()
                -0.001 * deltaG3_hZZ()
                +1.123 * deltaGL_Zffh(quarks[UP])
                -0.531 * deltaGR_Zffh(quarks[UP])
                -0.705 * deltaGL_Zffh(quarks[DOWN])
                +0.136 * deltaGR_Zffh(quarks[DOWN]);
    } else if (sqrt_s == 7.0) {
        mu +=  -0.068 * deltaGL_f(quarks[UP])
                +0.169 * deltaGR_f(quarks[UP])
                +13.657 * deltaGL_f(quarks[DOWN])
                -0.042 * deltaGR_f(quarks[DOWN])
	            +0.089 * deltaGL_Wff(quarks[UP],quarks[DOWN]).real()
                -0.04 * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real()
                -0.108 * deltaG_hgg()
                +0.548 * deltaG_hAA()
                +25.688 * deltaG1_hZA()
                +14.266 * deltaG2_hZA()
                -0.466 * deltaG1_hWW()
                +0.211 * deltaG2_hWW()
                +0.375 * deltaG3_hWW()
                -0.07 * deltaG1_hZZ()
                -1.827 * deltaG2_hZZ()
                +0.001 * deltaG3_hZZ()
                +1.188 * deltaGL_Zffh(quarks[UP])
                -0.536 * deltaGR_Zffh(quarks[UP])
                -0.976 * deltaGL_Zffh(quarks[DOWN])
                +0.179 * deltaGR_Zffh(quarks[DOWN]);
    } else if (sqrt_s == 8.0) {
        mu +=  -0.068 * deltaGL_f(quarks[UP])
                +0.174 * deltaGR_f(quarks[UP])
                +13.649 * deltaGL_f(quarks[DOWN])
                -0.042 * deltaGR_f(quarks[DOWN])
	            +0.09 * deltaGL_Wff(quarks[UP],quarks[DOWN]).real()
                -0.04 * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real()
                -0.107 * deltaG_hgg()
                +0.563 * deltaG_hAA()
                +25.676 * deltaG1_hZA()
                +14.247 * deltaG2_hZA()
                -0.473 * deltaG1_hWW()
                +0.215 * deltaG2_hWW()
                +0.387 * deltaG3_hWW()
                -0.072 * deltaG1_hZZ()
                -1.858 * deltaG2_hZZ()
                +0.002 * deltaG3_hZZ()
                +1.179 * deltaGL_Zffh(quarks[UP])
                -0.532 * deltaGR_Zffh(quarks[UP])
                -0.984 * deltaGL_Zffh(quarks[DOWN])
                +0.181 * deltaGR_Zffh(quarks[DOWN]);
    } else
        throw std::runtime_error("Bad argument in NPEffectiveGIMR::muVBF()");

    return mu;
}

double NPEffectiveGIMR::muWH(const double sqrt_s) const
{
    double mu = 1.0;
    if (sqrt_s == 1.96) {
        mu += +2.032 * deltaGL_Wff(quarks[UP], quarks[DOWN]).real()
                +1.739  * deltaG1_hWW()
                -3.433  * deltaG2_hWW()
                +38.642  * deltaG3_hWW()
                +6.523  * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real();
    } else if (sqrt_s == 7.0) {
        mu += +1.979 * deltaGL_Wff(quarks[UP], quarks[DOWN]).real()
                +1.778  * deltaG1_hWW()
                -3.891  * deltaG2_hWW()
                +38.637  * deltaG3_hWW()
                +7.345  * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real();
    } else if (sqrt_s == 8.0) {
        mu += +1.978 * deltaGL_Wff(quarks[UP], quarks[DOWN]).real()
                +1.784  * deltaG1_hWW()
                -3.967  * deltaG2_hWW()
                +38.643  * deltaG3_hWW()
                +7.507  * deltaGL_Wffh(quarks[UP], quarks[DOWN]).real();
    } else
        throw std::runtime_error("Bad argument in NPEffectiveGIMR::muWH()");

    return mu;
}

double NPEffectiveGIMR::muZH(const double sqrt_s) const
{
    double mu = 1.0;
    if (sqrt_s == 1.96) {
        mu += +3.529 * deltaGL_f(quarks[UP])
                -1.598  * deltaGR_f(quarks[UP])
                -1.229  * deltaGL_f(quarks[DOWN])
                +0.227  * deltaGR_f(quarks[DOWN])
                +3.215  * deltaG1_hZZ()
                -2.922  * deltaG2_hZZ()
                +59.223  * deltaG3_hZZ()
                +0.495  * deltaG1_hZA()
                -0.839  * deltaG2_hZA()
                +5.932  * deltaGL_Zffh(quarks[UP])
                -2.684  * deltaGR_Zffh(quarks[UP])
                -1.878  * deltaGL_Zffh(quarks[DOWN])
                +0.347  * deltaGR_Zffh(quarks[DOWN]);
    } else if (sqrt_s == 7.0) {
        mu += +2.583 * deltaGL_f(quarks[UP])
                -1.17  * deltaGR_f(quarks[UP])
                -2.127  * deltaGL_f(quarks[DOWN])
                +0.392  * deltaGR_f(quarks[DOWN])
                +3.27  * deltaG1_hZZ()
                -3.202  * deltaG2_hZZ()
                +59.218  * deltaG3_hZZ()
                +0.473  * deltaG1_hZA()
                -0.873  * deltaG2_hZA()
                +4.763  * deltaGL_Zffh(quarks[UP])
                -2.157  * deltaGR_Zffh(quarks[UP])
                -3.853  * deltaGL_Zffh(quarks[DOWN])
                +0.712  * deltaGR_Zffh(quarks[DOWN]);
    } else if (sqrt_s == 8.0) {
        mu += +2.569 * deltaGL_f(quarks[UP])
                -1.163  * deltaGR_f(quarks[UP])
                -2.14  * deltaGL_f(quarks[DOWN])
                +0.395  * deltaGR_f(quarks[DOWN])
                +3.283  * deltaG1_hZZ()
                -3.262  * deltaG2_hZZ()
                +59.229  * deltaG3_hZZ()
                +0.475  * deltaG1_hZA()
                -0.892  * deltaG2_hZA()
                +4.848  * deltaGL_Zffh(quarks[UP])
                -2.194  * deltaGR_Zffh(quarks[UP])
                -3.96  * deltaGL_Zffh(quarks[DOWN])
                +0.731  * deltaGR_Zffh(quarks[DOWN]);
    } else
        throw std::runtime_error("Bad argument in NPEffectiveGIMR::muZH()");

    return mu;
}

double NPEffectiveGIMR::muVH(const double sqrt_s) const
{
    double sigmaWH_SM = computeSigmaWH(sqrt_s);
    double sigmaZH_SM = computeSigmaZH(sqrt_s);
    double sigmaWH = muWH(sqrt_s) * sigmaWH_SM;
    double sigmaZH = muZH(sqrt_s) * sigmaZH_SM;
    return ((sigmaWH + sigmaZH) / (sigmaWH_SM + sigmaZH_SM));
}

double NPEffectiveGIMR::muVBFVH(const double sqrt_s) const
{
    double sigmaWH_SM = computeSigmaWH(sqrt_s);
    double sigmaZH_SM = computeSigmaZH(sqrt_s);
    double sigmaVBF_SM = computeSigmaVBF(sqrt_s);
    double sigmaWH = muWH(sqrt_s) * sigmaWH_SM;
    double sigmaZH = muZH(sqrt_s) * sigmaZH_SM;
    double sigmaVBF = muVBF(sqrt_s) * sigmaVBF_SM;

    return ((sigmaWH + sigmaZH + sigmaVBF) / (sigmaWH_SM + sigmaZH_SM + sigmaVBF_SM));
}

double NPEffectiveGIMR::muttH(const double sqrt_s) const
{
    double mu = 1.0;
    if (sqrt_s == 1.96) {
        mu += -2.863 * deltaG_hff(quarks[TOP]).real()
      +1.737 * deltaG_hgg();
    } else if (sqrt_s == 7.0) {
        mu += -2.861 * deltaG_hff(quarks[TOP]).real()
      +2.583 * deltaG_hgg();
    } else if (sqrt_s == 8.0) {
        mu += -2.861 * deltaG_hff(quarks[TOP]).real()
      +2.637 * deltaG_hgg();
    } else
        throw std::runtime_error("Bad argument in NPEffectiveGIMR::muttH()");

    return mu;
}

double NPEffectiveGIMR::muggFttH(const double sqrt_s) const
{
    double sigmaggH_SM = computeSigmaggH(sqrt_s);
    double sigmattH_SM = computeSigmattH(sqrt_s);
    double sigmaggH = muggH(sqrt_s) * sigmaggH_SM;
    double sigmattH = muttH(sqrt_s) * sigmattH_SM;

    return ((sigmaggH + sigmattH) / (sigmaggH_SM + sigmattH_SM));
} 

double NPEffectiveGIMR::BrHggRatio() const
{
    return (GammaHggRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHWWRatio() const
{
    return (GammaHWWRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHZZRatio() const
{
    return (GammaHZZRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHZgaRatio() const
{
    return (GammaHZgaRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHgagaRatio() const
{
    return (GammaHgagaRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHtautauRatio() const
{
    return (GammaHtautauRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHccRatio() const
{
    return (GammaHccRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::BrHbbRatio() const
{
    return (GammaHbbRatio() / computeGammaTotalRatio());
}

double NPEffectiveGIMR::computeGammaTotalRatio() const
{
    return (trueSM.computeBrHtogg() * GammaHggRatio()
            + trueSM.computeBrHtoWW() * GammaHWWRatio()
            + trueSM.computeBrHtoZZ() * GammaHZZRatio()
            + trueSM.computeBrHtoZga() * GammaHZgaRatio()
            + trueSM.computeBrHtogaga() * GammaHgagaRatio()
            + trueSM.computeBrHtotautau() * GammaHtautauRatio()
            + trueSM.computeBrHtocc() * GammaHccRatio()
            + trueSM.computeBrHtobb() * GammaHbbRatio());
}

double NPEffectiveGIMR::GammaHggRatio() const
{
    return (1.0
            +151.669 * deltaG_hgg()
            -3.006 * deltaG_hff(quarks[TOP]).real()
            +5.853 * deltaG_hff(quarks[BOTTOM]).real()
            +4.71 * deltaG_hff(quarks[CHARM]).real());
}

double NPEffectiveGIMR::GammaHWWRatio() const
{
    return (1.0
            -0.183 * deltaG1_hWW()
            -0.275 * deltaG2_hWW()
            +38.683 * deltaG3_hWW());
}

double NPEffectiveGIMR::GammaHZZRatio() const
{
    return (1.0
            -0.247 * deltaG1_hZZ()
            -0.241 * deltaG2_hZZ()
            +59.249 * deltaG3_hZZ()
            +0.075 * deltaG3_hWW());
}

double NPEffectiveGIMR::GammaHZgaRatio() const
{
    return (1.0
            +0.033 * deltaG3_hZZ()
            -71.321 * deltaG1_hZA()
            +40.776 * deltaG3_hWW()
            +0.172 * deltaG_hff(quarks[TOP]).real()
            -0.301 * deltaG_hff(quarks[BOTTOM]).real()
            +0.196 * deltaG_hff(leptons[TAU]).real()
            +0.232 * deltaG_hff(quarks[CHARM]).real());
}

double NPEffectiveGIMR::GammaHgagaRatio() const
{
    return (1.0
            -0.033 * deltaG3_hZZ()
            -257.366 * deltaG_hAA()
            +48.696 * deltaG3_hWW()
            +0.761 * deltaG_hff(quarks[TOP]).real()
            -0.441 * deltaG_hff(quarks[BOTTOM]).real()
            -1.087 * deltaG_hff(leptons[TAU]).real()
            -0.646 * deltaG_hff(quarks[CHARM]).real());
}

double NPEffectiveGIMR::GammaHtautauRatio() const
{
    return (1.0
            -277.458 * deltaG_hff(leptons[TAU]).real());
}

double NPEffectiveGIMR::GammaHccRatio() const
{
    return (1.0
            -383.036 * deltaG_hff(quarks[CHARM]).real());
}

double NPEffectiveGIMR::GammaHbbRatio() const
{
    return (1.0
            -0.013 * deltaG_hff(quarks[TOP]).real()
            -117.431 * deltaG_hff(quarks[BOTTOM]).real());
}

