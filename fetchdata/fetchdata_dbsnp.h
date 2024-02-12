#include <iostream>
#include <fstream>
#include <vector>

#include "../myCSV.h"
#include "fetchdata_shared.h"


void create_rsid_url(std::string& rsid, std::string& rsidUrl);

/*
 * Takes filename containing all rsids and creates a std::vector containing rsids.
*/ void get_vec_of_rsid(std::vector<std::string>& all_rsids, std::string& ifn);

/*
 * Helper: Takes json object and adds all necessary data to results matrix. 
*/ void get_data_from_json(std::string& rsid, matrix3d& m3d, std::vector<std::string>& merged_rsids, Json::Value& obj);

/*
 *  Runs get_data_from_json for all rsids. 
*/ void fetch_all_rsids(std::vector<std::string>& all_rsids, matrix3d& results, matrix& all_merged_rsids);

/*
 * Takes empty matrix and adds the header with a the data points that will be 
 * collected.  
*/ void add_header(matrix3d& m);

// End of file