#include <iostream>
#include <fstream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "../myCSV.h"


/*
 * Takes url as string and returns a JSON object
*/ void get_json_from_url(string& url, Json::Value& obj);

/*
 * Helper for get_json_from_url
*/ static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void *userp);

/*
 * Helper funtion: takes string and returns a single value vector containing that
 * string. 
*/ vector<string> string_to_vec(string s);

/*
 * Prints a progress bar to cout. Takes a float of the ratio of progress; i.e. 
 * i / total. Use with a long loop.  
*/ void progress_bar(float progress);