#include "fetchdata/fetchdata_dbsnp.h"
#include "fetchdata/fetchdata_ensembl.h"
#include "fetchdata/fetchdata_positions.h"
#include "compare_double_vector.h"
#include "myCSV.h"


/*
 * Each study has its own gwas object. Rsids are read from a csv, they are then
 * used to fetch data from dbSNP. The results are the stored in two matrixes, one
 * only contains the original rsid and its merged rsids and the other are the 
 * overview results that get saved as a csv. 
*/
typedef struct gwas_study
{
    // name of the list of rsids
    std::string study_name;

    // rsid list input file name
    std::string rsid_input_fn;

    // list of all rsids from that study
    std::vector<std::string> all_rsids;
    
    // data from each rsid gets stored here
    matrix3d all_results;
    
    // each row contains the original rsid and its merged rsids
    matrix all_merged_rsids;

} study;

// creates a new study object
study* init(std::string& study_name, std::string& rsid_input_fn);

// creates a vector of study objects
std::vector<study*> init(std::vector<std::string>& study_names, std::vector<std::string>& rsid_input_fns);

// deletes the study object
void del(study* d);

// deletes the vector of study objects
void del(std::vector<study*>& vs);

// takes a study object and fetches the data from dbSNP. Fills all_results and all_merged_rsids
void fetch_data_driver(study* d);

// runs the fetch_data_driver function for each study in the vector
void fetch_data_driver(std::vector<study*>& vs);

// takes a vector of study objects. Compares all_merged_rsids from each study to themselves
std::vector<comparison*> compare_double_vector_driver(std::vector<study*>& vs);

// takes a comparison object and outputs it as a csv file
void output_csv(comparison* c);

// takes a vector of comparison objects and outputs them to many csv files.
void output_csv(std::vector<comparison*> vc);

// takes the study object and outputs the results matrix to a csv file
void output_csv(study* s);

// takses a vector of study objects and outputs each as a csv file
void output_csv(std::vector<study*> ss);