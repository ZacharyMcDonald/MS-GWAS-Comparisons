#include "fetchdata.h"
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
    string study_name;

    // rsid list input file name
    string rsid_input_fn;

    // list of all rsids from that study
    vector<string> all_rsids;
    
    // data from each rsid gets stored here
    matrix3d all_results;
    
    // each row contains the original rsid and its merged rsids
    matrix all_merged_rsids;

    //matrix overlap;

    //int count;

} study;

// creates a new study object
study* init(string& study_name, string& rsid_input_fn);

// creates a vector of study objects
vector<study*> init(vector<string>& study_names, vector<string>& rsid_input_fns);

// deletes the study object
void del(study* d);

// deletes the vector of study objects
void del(vector<study*>& vs);

// takes a study object and fetches the data from dbSNP. Fills all_results and all_merged_rsids
void fetch_data_driver(study* d);

// runs the fetch_data_driver function for each study in the vector
void fetch_data_driver(vector<study*>& vs);

// takes a vector of study objects. Compares all_merged_rsids from each study to themselves
vector<comparison*> compare_double_vector_driver(vector<study*>& vs);

// takes a comparison object and outputs it as a csv file
void output_comparisons_csv(comparison* c);

// takes a vector of comparison objects and outputs them to many csv files.
void output_comparisons_csv(vector<comparison*> vc);