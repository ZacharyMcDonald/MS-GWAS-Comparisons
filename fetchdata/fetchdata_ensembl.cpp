#include "fetchdata_ensembl.h"

using namespace std;

#define DEBUG true

void create_ensembl_url(string& gene_name, string& url)
{
    // https://rest.ensembl.org/lookup/symbol/homo_sapiens/BRCA2?expand=1;content-type=application/json
    string urlA = "https://rest.ensembl.org/lookup/symbol/homo_sapiens/";
    string urlB = gene_name;
    string urlC = "?expand=1;content-type=application/json";

    url = urlA + urlB + urlC;

    if (DEBUG) cout << url << endl;
}

string get_gene_length(string& gene_name)
{
    string url;
    create_ensembl_url(gene_name, url);

    int length = 0, trys = 0;
    while (true)
    {
        Json::Value obj;
        get_json_from_url(url, obj);

        length = obj["end"].asInt() - obj["start"].asInt();
        trys++;
        
        if (length != 0 || trys >= 10)
        {
            break;
        }
        
        if (DEBUG)
        {
            string ERR = "gene name: " + gene_name
                       + " gene length: " + to_string(length) + "\n";

            cerr << ERR << endl;

            string fn = "output/gene_length_errors.txt";
            save_errors(ERR, fn);
        }
    }

    return to_string(length);
}

vector<string> get_gene_length(vector<string>& gene)
{
    vector<string> all_gene_lengths;

    for (size_t i = 0; i < gene.size(); i++)
    {
        all_gene_lengths.push_back( get_gene_length(gene[i]) );
    }

    return all_gene_lengths;
}

void add_gene_length_to_results(matrix3d& r)
{
    r[0].push_back(string_to_vec("Gene Length"));

    int name_loc = 4;

    for (size_t i = 1; i < r.size(); i++)
    {
        r[i].push_back( get_gene_length(r[i][name_loc]) );
        
        progress_bar(float(i) / float(r.size()));
    }
}

#undef DEBUG