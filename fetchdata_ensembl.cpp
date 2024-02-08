#include "fetchdata_ensembl.h"
#include "fetchdata_dbsnp.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}

void create_ensembl_url(string& gene_name, string& url)
{
    string urlA = "https://rest.ensembl.org/lookup/symbol/homo_sapiens/";
    string urlB = gene_name;
    string urlC = "?content-type=application/json";

    url = urlA + urlB + urlC;
}

string get_gene_length(string& gene_name)
{
    string url;
    create_ensembl_url(gene_name, url);

    Json::Value obj;
    get_json_from_url(url, obj);

    return obj["Transcript"][0]["Length"].asString();
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