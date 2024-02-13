#include <iostream>
#include <fstream>
#include <vector>

#include "../myCSV.h"
#include "fetchdata_shared.h"

/*
 * Takes filename containing all rsids and creates a std::vector containing rsids.
*/ void get_vec_of_rsid(std::vector<std::string>& all_rsids, std::string& ifn);

/*
 *  Runs get_data_from_json for all rsids. 
*/ void fetch_all_rsids(std::vector<std::string>& all_rsids, matrix3d& results, matrix& all_merged_rsids);

/*
 * Takes empty matrix and adds the header with a the data points that will be 
 * collected.  
*/ void add_header(matrix3d& m);

// End of file