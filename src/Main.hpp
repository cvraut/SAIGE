#ifndef MAIN_HPP
#define MAIN_HPP

// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>


void setAssocTest_GlobalVarsInCPP(std::string t_impute_method,
                double t_missing_cutoff,
                               double t_min_maf_marker,
                               double t_min_mac_marker,
                               double t_min_info_marker,
                               double t_dosage_zerod_cutoff,
                               double t_dosage_zerod_MAC_cutoff,
                               arma::vec & t_weights_beta);

void setMarker_GlobalVarsInCPP(
                               bool t_isOutputMoreDetails,
                               int t_marker_chunksize
                               );


void setRegion_GlobalVarsInCPP(
                               arma::vec t_max_maf_region,
                               unsigned int t_max_markers_region,
                               double t_MACCutoff_to_CollapseUltraRare);



Rcpp::DataFrame mainMarkerInCPP(
                           std::string & t_genoType,     // "PLINK", "BGEN"
                           std::string & t_traitType,
                           std::vector<std::string>  & t_genoIndex,
                           bool & t_isMoreOutput,
                           bool & t_isImputation);

bool Unified_getOneMarker(std::string & t_genoType,   // "PLINK", "BGEN"
                               uint64_t & t_gIndex,        // different meanings for different genoType
                               std::string& t_ref,       // REF allele
                               std::string& t_alt,       // ALT allele (should probably be minor allele, otherwise, computation time will increase)
                               std::string& t_marker,    // marker ID extracted from genotype file
                               uint32_t& t_pd,           // base position
                               std::string& t_chr,       // chromosome
                               double& t_altFreq,        // frequency of ALT allele
                               double& t_altCounts,      // counts of ALT allele
                               double& t_missingRate,    // missing rate
                               double& t_imputeInfo,     // imputation information score, i.e., R2 (all 1 for PLINK)
                               bool & t_isOutputIndexForMissing,               // if true, output index of missing genotype data
                               std::vector<uint>& t_indexForMissing,     // index of missing genotype data
                               bool & t_isOnlyOutputNonZero,                   // if true, only output a vector of non-zero genotype. (NOTE: if ALT allele is not minor allele, this might take much computation time)
                               std::vector<uint>& t_indexForNonZero,
			       arma::vec & t_GVec,
			       bool t_isImputation);

void Unified_getMarkerPval(
                           arma::vec & t_GVec,
                           bool t_isOnlyOutputNonZero,
                           arma::uvec & t_indexForNonZero_vec,
                           arma::uvec & t_indexForZero_vec,
                           double& t_Beta,
                           double& t_seBeta,
                           double& t_pval,
                           double& t_pval_noSPA,
                           double& t_Tstat,
			   double& t_gy,
                           double& t_varT,
                           double t_altFreq,
                           bool & t_isSPAConverge,
                           arma::vec & t_gtilde,
                           bool & is_gtilde,
			   bool  is_region,
			   arma::vec & t_P2Vec,
			   bool t_isCondition, 
			   double& t_Beta_c,
                           double& t_seBeta_c,
                           double& t_pval_c,
                           double& t_pval_noSPA_c,
                           double& t_Tstat_c,
                           double& t_varT_c,
			   arma::rowvec & t_G1tilde_P_G2tilde_Vec);


Rcpp::List mainRegionInCPP(
                           std::string t_genoType,     // "PLINK", "BGEN"
                           std::vector<std::string> & t_genoIndex,
                           arma::mat & annoIndicatorMat,
                           arma::vec & maxMAFVec,
                           std::string t_outputFile,
                           std::string t_traitType,
                           unsigned int t_n,           // sample size
                           arma::mat P1Mat,            // edited on 2021-08-19: to avoid repeated memory allocation of P1Mat and P2Mat
                           arma::mat P2Mat,
                           std::string t_regionTestType,
			   bool t_isImputation,
			   arma::vec & t_weight,
			   arma::vec & t_weight_cond,
			   bool t_isSingleinGroupTest,
			   bool t_isOutputMarkerList);



void setPLINKobjInCPP(std::string t_bimFile,
                      std::string t_famFile,
                      std::string t_bedFile,
                      std::vector<std::string> & t_SampleInModel,
                      std::string t_AlleleOrder);



void setBGENobjInCPP(std::string t_bgenFileName,
                     std::string t_bgenFileIndex,
                     std::vector<std::string> & t_SampleInBgen,
                     std::vector<std::string> & t_SampleInModel,
                     std::string t_AlleleOrder);

void setVCFobjInCPP(std::string t_vcfFileName,
            std::string t_vcfFileIndex,
            std::string t_vcfField,
            std::vector<std::string> & t_SampleInModel);



void setSAIGEobjInCPP(arma::mat & t_XVX,
        arma::mat & t_XXVX_inv,
        arma::mat & t_XV,
        arma::mat & t_XVX_inv_XV,
        arma::mat & t_X,
        arma::vec &  t_S_a,
        arma::vec & t_res,
        arma::vec & t_mu2,
        arma::vec & t_mu,
        arma::vec & t_varRatio,
        arma::vec & t_cateVarRatioMinMACVecExclude,
        arma::vec & t_cateVarRatioMaxMACVecInclude,
        double t_SPA_Cutoff,
        arma::vec & t_tauvec,
        std::string t_traitType,
        arma::vec & t_y,
        std::string t_impute_method,
        bool t_flagSparseGRM,
        arma::umat & t_locationMat,
        arma::vec & t_valueVec,
        int t_dimNum,
        bool t_isCondition,
        std::vector<uint32_t> & t_condition_genoIndex,
	bool t_is_Firth_beta,
        double t_pCutoffforFirth, 
	arma::vec & t_offset);


void assign_conditionMarkers_factors(
                           std::string t_genoType,     // "PLINK", "BGEN"
                           std::vector<std::string> & t_genoIndex,
                           unsigned int t_n,
			    arma::vec & t_weight_cond);

void assign_conditionMarkers_factors_binary_region(
                           arma::vec & scalefactor_G2_cond);

void set_iterator_inVcf(std::string & variantList);

bool check_Vcf_end();

arma::vec fast_logistf_fit(arma::mat & x,
                arma::vec & y,
                arma::vec & weight,
                arma::vec & offset,
                bool firth,
                arma::uvec & col_fit,
        arma::vec init,
        int maxit,
        int maxstep,
        int maxhs,
        double lconv,
        double gconv,
        double xconv);

Rcpp::List RegionSetUpConditional_binary_InCPP(arma::vec & t_weight_cond);


#endif
