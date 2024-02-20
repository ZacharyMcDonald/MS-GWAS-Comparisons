#include "fetchdata_ensembl.h"

using namespace std;

#define DEBUG false

void create_hg37_url(string& rsid, string& url)
{
    string urlA = "https://grch37.rest.ensembl.org/variation/human/";
    string urlB = rsid;
    string urlC = "?expand=1;content-type=application/json";

    url = urlA + urlB + urlC;

    if (DEBUG) cout << url << endl;
}

void create_hg38_url(string& rsid, string& url)
{
    string urlA = "https://rest.ensembl.org/variation/human/";
    string urlB = rsid;
    string urlC = "?expand=1;content-type=application/json";

    url = urlA + urlB + urlC;

    if (DEBUG) cout << url << endl;
}

string get_rsid_positions_hg38(string& rsid)
{
    string url;
    create_hg38_url(rsid, url);

    Json::Value obj;
    get_json_from_url(url, obj);

    if (DEBUG) cout << "gene length: " << obj["mappings"][0]["location"].asString() << endl;

    return obj["mappings"][0]["location"].asString();
}

string get_rsid_positions_hg37(string& rsid)
{
    string url;
    create_hg37_url(rsid, url);

    Json::Value obj;
    get_json_from_url(url, obj);

    if (DEBUG) cout << "gene length: " << obj["mappings"][0]["location"].asString() << endl;

    return obj["mappings"][0]["location"].asString();
}

void add_rsid_positions_to_results(matrix3d& r)
{
    r[0].push_back(string_to_vec("GRCh38"));
    r[0].push_back(string_to_vec("GRCh37"));

    int rsid_loc = 0;

    for (size_t i = 1; i < r.size(); i++)
    {
        r[i].push_back( string_to_vec( get_rsid_positions_hg38(r[i][rsid_loc][0]) ) );
        r[i].push_back( string_to_vec( get_rsid_positions_hg37(r[i][rsid_loc][0]) ) );

        progress_bar(float(i) / float(r.size()));
    }
}

#undef DEBUG