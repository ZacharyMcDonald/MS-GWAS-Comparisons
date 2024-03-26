#include <iostream>
#include <fstream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>

#include "../myCSV.h"

/*
 * Takes url as std::string and returns a JSON object
*/ void get_json_from_url(std::string& url, Json::Value& obj);

/*
 * Helper funtion: takes string and returns a single value vector containing that
 * string. 
*/ std::vector<std::string> string_to_vec(std::string s);

/*
 * Prints a progress bar to cout. Takes a float of the ratio of progress; i.e. 
 * i / total. Use with a long loop.  
*/ void progress_bar(float progress);

bool save_errors (std::string& ERR, std::string& out_file);