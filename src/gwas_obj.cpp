#include "gwas_obj.h"

using namespace std;

study* init(string& study_name, string& rsid_input_fn)
{
    study* d;
    d = new study;

    d->study_name    = study_name;
    d->rsid_input_fn = rsid_input_fn;
    //d->count         = 0; 

    add_header(d->all_results);

    return d;
}

vector<study*> init(vector<string>& study_names, vector<string>& rsid_input_fns)
{
    if (study_names.size() != rsid_input_fns.size()) 
    {
        cerr << "***ERROR*** study_names and rsid_input_fns must have the same size" << endl;
        return vector<study*>();
    }
        
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
    add_gene_length_to_results(d->all_results);
    add_rsid_positions_to_results(d->all_results);
}

void fetch_data_driver(vector<study*>& vs)
{
    for (size_t i = 0; i < vs.size(); i++)
    {
        fetch_data_driver(vs[i]);
        progress_bar(float(i) / float(vs.size()), '%');
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
        for (size_t j = i + 1; j < vs.size(); j++)
        {
            // create name
            comp_name.clear();
            comp_name = vs[i]->study_name + vs[j]->study_name;

            // initialize a new comparison
            comparison* c = init(comp_name);
            
            // make comparison
            matrix_cmpr(c, vs[i]->all_merged_rsids, vs[j]->all_merged_rsids);

            // add results to vector of all comparisons
            vc.push_back(c);
        }
        progress_bar(float(i) / float(vs.size()));
    }
    return vc;
}

void output_csv(comparison* c)
{
    string thisname = "output/" + c->name + "_overlap.csv";
    save_matrix_as_csv(c->overlap, thisname);
}

void output_csv(vector<comparison*> vc)
{
    // loop over comparisons
    cout << "Saving Comparisons..." << endl;
    for (size_t i = 0; i < vc.size(); i++)
    {
        output_csv(vc[i]);
        progress_bar(float(i) / float(vc.size()));
    }
}

void output_csv(study* s)
{
    string thisname = "output/" + s->study_name + "_results.csv";
    save_matrix_as_csv(s->all_results, thisname);
}

void output_csv(vector<study*> ss)
{
    cout << "Saving Results..." << endl;
    for (size_t i = 0; i < ss.size(); i++)
    {
        output_csv(ss[i]);
        progress_bar(float(i) / float(ss.size()));
    }
}

// End of file