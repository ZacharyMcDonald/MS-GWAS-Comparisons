#define DEBUG false

#include <iostream>
#include <fstream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "myCSV.h"

using namespace std;

/*
 * Functions for fetching json from dbSNP. Takes a url created in the 
 * create_rsid_url() function and uses it to get json for that rsid.
*/ void get_json_from_url(string& url, Json::Value& obj);
   static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
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
 * Helper funtion: takes string and returns a single value vector containing that
 * string. 
*/ vector<string> string_to_vec(string s);

/*
 * Takes empty matrix and adds the header with a the data points that will be 
 * collected.  
*/ void add_header(matrix3d& m);

void progress_bar(float progress);