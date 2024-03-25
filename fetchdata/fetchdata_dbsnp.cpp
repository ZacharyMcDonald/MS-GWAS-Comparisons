#include "fetchdata_dbsnp.h"

using namespace std;

#define DEBUG false

void create_rsid_url(string& rsid, string& rsidUrl)
{
    string urlA = "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi?db=snp&id=";
    string urlB = rsid;
    string urlC = "&rettype=json&retmode=text";
    
    rsidUrl = urlA + urlB + urlC;
    
    if (DEBUG) cout << rsidUrl << endl;
}

void get_data_from_json(string& rsid, matrix3d& m3d, vector<string>& merged_rsids, Json::Value& obj)
{
    merged_rsids.push_back(rsid);
    
    // vector that only contains original rsid
    vector<string> rsid_vec;
    rsid_vec.push_back(rsid);

    // new 2d vector. represents a new row with a third z direction 
    vector<vector<string>> nvv;
    nvv.push_back(rsid_vec);

    if (obj.empty())
    {
        nvv.push_back(string_to_vec("FALSE"));
        //m3d.push_back(nvv);
        return;
    }

    // vectors that will contain all merged data for that rsid
    vector<string> merged_rsid_vec;
    vector<string> merge_date_vec;
    vector<string> revision_vec;

    // iterate over merges add data to their respective vectors
    for (size_t i = 0; i < obj["dbsnp1_merges"].size(); i++)
    {
        // to be returned on its own for other uses
        merged_rsids.push_back(obj["dbsnp1_merges"][int(i)]["merged_rsid"].asString());
        
        // for results matrix
        merged_rsid_vec.push_back(obj["dbsnp1_merges"][int(i)]["merged_rsid"].asString());
        merge_date_vec.push_back (obj["dbsnp1_merges"][int(i)]["merge_date"].asString());
        revision_vec.push_back   (obj["dbsnp1_merges"][int(i)]["revision"].asString());
    }

    // add data to row vector nvv
    nvv.push_back(merged_rsid_vec);
    nvv.push_back(merge_date_vec);
    nvv.push_back(revision_vec);

    // add data that does not have multiple data points
    size_t gene_size = obj["primary_snapshot_data"]["allele_annotations"][0]["assembly_annotation"][0]["genes"].size();
    vector<string> locus_v, name_v, orientation_v, ontology_v;
    
    for (size_t i = 0; i < gene_size; i++)
    {
        locus_v.push_back(       obj["primary_snapshot_data"]["allele_annotations"][0]["assembly_annotation"][0]["genes"][int(i)]["locus"].asString()      );
        name_v.push_back(        obj["primary_snapshot_data"]["allele_annotations"][0]["assembly_annotation"][0]["genes"][int(i)]["name"].asString()       );
        orientation_v.push_back( obj["primary_snapshot_data"]["allele_annotations"][0]["assembly_annotation"][0]["genes"][int(i)]["orientation"].asString());
        ontology_v.push_back(    obj["primary_snapshot_data"]["allele_annotations"][0]["assembly_annotation"][0]["genes"][int(i)]["rnas"][0]["sequence_ontology"][0]["name"].asString());
    }
    
    nvv.push_back(locus_v);
    nvv.push_back(name_v);
    nvv.push_back(orientation_v);
    nvv.push_back(ontology_v);
    
    nvv.push_back(string_to_vec(obj["present_obs_movements"][0]["allele_in_cur_release"]["position"].asString()));
    nvv.push_back(string_to_vec(obj["primary_snapshot_data"]["allele_annotations"][0]["clinical"][0].asString()));


    // add row vector to 3d matrix
    m3d.push_back(nvv);
}

void get_vec_of_rsid(vector<string>& all_rsids, string& ifn)
{
    // create a temporary matrix to store csv containing all rsids
    matrix m;
    read_file(ifn, m);

    if (DEBUG) test_print_data(m);

    // iterate over all rows and add them to new vector
    for (size_t i = 0; i < m.size(); i++)
    {
        if (m[i].size() != 0)
        {
            all_rsids.push_back(m[i][0]);
        }
    }

    if (DEBUG)
    {
        ofstream output;
        output.open("debug/DEBUG_rsid_vec.txt");
    
        output << "All RSIDs: " << endl;
        for (size_t i = 0; i < all_rsids.size(); i++)
        {
            output << all_rsids[i] << endl;
        }

        output.close();
    }
}

void fetch_all_rsids(vector<string>& all_rsids, matrix3d& results, matrix& all_merged_rsids)
{
    Json::Value obj;
    string url;

    vector<string> merged_rsids;

    // iterate over all rsids, create url, fetch data, and add data to results 
    // matrix
    for (size_t i = 0; i < all_rsids.size(); i++)
    {
        create_rsid_url(all_rsids[i], url);
        get_json_from_url(url, obj);
    
        get_data_from_json(all_rsids[i], results, merged_rsids, obj);
        all_merged_rsids.push_back(merged_rsids);
        merged_rsids.clear();

        progress_bar(float(i) / float(all_rsids.size()));
        
        url.clear();
    }
}

void add_header(matrix3d& m)
{
    vector<vector<string>> header;

    header.push_back(string_to_vec("Original RSID"));
    header.push_back(string_to_vec("All Merged RSIDs"));
    header.push_back(string_to_vec("Merged Dates"));
    header.push_back(string_to_vec("Revisions"));
    header.push_back(string_to_vec("Locus"));
    header.push_back(string_to_vec("Name"));
    header.push_back(string_to_vec("Orientation"));
    header.push_back(string_to_vec("Sequence Ontology"));
    header.push_back(string_to_vec("hg38 Position"));
    header.push_back(string_to_vec("Clinical"));

    m.push_back(header);
}

#undef DEBUG

// End of file