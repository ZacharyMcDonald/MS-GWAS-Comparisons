#include "fetchdata_ensembl.h"
#include "fetchdata_dbsnp.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}

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

    Json::Value obj;
    get_json_from_url(url, obj);

    //cout << "gene length" << obj["Transcript"][0]["length"].asString() << endl;

    return obj["Transcript"][0]["length"].asString();
}

void add_gene_length_to_results(matrix3d& r)
{
    r[0].push_back(string_to_vec("Gene Length"));

    int name_loc = 4;

    for (int i = 1; i < r.size(); i++)
    {
        r[i].push_back( string_to_vec( get_gene_length(r[i][name_loc][0]) ) );
    }
}