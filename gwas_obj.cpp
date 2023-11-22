#include "gwas_obj.h"

study* init(string& study_name, string& rsid_input_fn)
{
    study* d;
    d = new study;

    d->study_name    = study_name;
    d->rsid_input_fn = rsid_input_fn;
    d->count         = 0; 

    return d;
}

vector<study*> init(vector<string>& study_names, vector<string>& rsid_input_fns)
{
    vector<study*> vs;

    for (size_t i = 0; i < study_names.size(); i++)
    {
        vs.push_back( init(study_names[i], rsid_input_fns[i]) );
    }

    return vs;
}

void del(study* d)
{
    delete d;
}

void del(vector<study*>& vs)
{
    for (size_t i = 0; i < vs.size(); i++)
    {
        del(vs[i]);
    }
}

void fetch_data_driver(study* d)
{
    get_vec_of_rsid(d->all_rsids, d->rsid_input_fn);
    fetch_all_rsids(d->all_rsids, d->all_results, d->all_merged_rsids);
}

void fetch_data_driver(vector<study*>& vs)
{
    for (size_t i = 0; i < vs.size(); i++)
    {
        fetch_data_driver(vs[i]);
    }
}

vector<comparison*> compare_double_vector_driver(vector<study*>& vs)
{
    vector<comparison*> vc;

    // temp place to create comparison name 
    string comp_name;

    // loop over vector and make comparison of every value to every other value
    for (size_t i = 0; i < vs.size(); i++)
    {
        for (size_t j = 0; i + 1 < vs.size(); j++)
        {
            // create name
            comp_name.clear();
            comp_name = vs[i]->study_name + vs[j]->study_name;

            // initialize a new comparison
            comparison* c = init(comp_name);
            
            // make comparison
            matrix_cmpr(vs[i]->all_merged_rsids, vs[j]->all_merged_rsids, c->overlap, c->count);

            // add results to vector of all comparisons
            vc.push_back(c);
        }
    }
    return vc;
}