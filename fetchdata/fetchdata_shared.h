#include <iostream>
#include <fstream>
#include <vector>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "../myCSV.h"


void get_json_from_url(string& url, Json::Value& obj);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

/*
 * Helper funtion: takes string and returns a single value vector containing that
 * string. 
*/ vector<string> string_to_vec(string s);

void progress_bar(float progress);