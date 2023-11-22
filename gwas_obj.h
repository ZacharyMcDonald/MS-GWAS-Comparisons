#include "fetchdata.h"
#include "compare_double_vector.h"
#include "myCSV.h"

typedef struct gwas_study
{
    string study_name;

    string rsid_input_fn;

    vector<string> all_rsids;
    
    matrix3d all_results;
    
    matrix all_merged_rsids;

    matrix overlap;

    int count;

} study;

study* init(string& study_name, string& rsid_input_fn);

vector<study*> init(vector<string>& study_names, vector<string>& rsid_input_fns);

void del(study* d);

void del(vector<study*>& vs);

void fetch_data_driver(study* d);

void fetch_data_driver(vector<study*>& vs);

vector<comparison*> compare_double_vector_driver(vector<study*>& vs);