#include <iostream>
#include <fstream>
#include <vector>

#include "../myCSV.h"

#include "fetchdata_shared.h"

using namespace std;


void create_rsid_url(string& rsid, string& rsidUrl);

/*
 * Takes filename containing all rsids and creates a vector containing rsids.
*/ void get_vec_of_rsid(vector<string>& all_rsids, string& ifn);

/*
 * Helper: Takes json object and adds all necessary data to results matrix. 
*/ void get_data_from_json(string& rsid, matrix3d& m3d, vector<string>& merged_rsids, Json::Value& obj);

/*
 *  Runs get_data_from_json for all rsids. 
*/ void fetch_all_rsids(vector<string>& all_rsids, matrix3d& results, matrix& all_merged_rsids);

/*
 * Takes empty matrix and adds the header with a the data points that will be 
 * collected.  
*/ void add_header(matrix3d& m);

// End of file