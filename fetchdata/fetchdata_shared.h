#include <iostream>
#include <fstream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "../myCSV.h"

typedef std::vector<std::vector<std::string>> matrix;
typedef std::vector<std::vector<std::vector<std::string>>> matrix3d;

/*
 * Takes url as std::string and returns a JSON object
*/ void get_json_from_url(std::string& url, Json::Value& obj);

/*
 * Helper for get_json_from_url
*/ size_t WriteCallback(void* contents, size_t size, size_t nmemb, void *userp);

/*
 * Helper funtion: takes std::string and returns a single value std::vector containing that
 * std::string. 
*/ std::vector<std::string> string_to_vec(std::string s);

/*
 * Prints a progress bar to cout. Takes a float of the ratio of progress; i.e. 
 * i / total. Use with a long loop.  
*/ void progress_bar(float progress);