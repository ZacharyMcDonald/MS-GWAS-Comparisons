#include "fetchdata_shared.h"

using namespace std;

#define DEBUG false

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}

vector<string> string_to_vec(string s)
{
    vector<string> v;
    v.push_back(s);
    return v;
}

void progress_bar(float progress)
{
    if (progress < 1.0) 
    {
        int barWidth = 70;

        std::cout << "[";
        int pos = barWidth * progress;
        
        for (int i = 0; i < barWidth; ++i) 
        {
            if (i < pos)
            { 
                std::cout << "=";
                continue;
            }
            if (i == pos) 
            {    
                std::cout << ">";
                continue;
            }
            std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %" << std::endl;
        std::cout.flush();
        
        //if (!DEBUG) printf("\033c");
    }
    // cout << endl;
}

void get_json_from_url(string& url, Json::Value& obj)
{
    obj.clear();

    CURL* curl;
    //CURLcode res;

    string readBuffer;

    int attempts = 0;
    while (obj.empty())
    {
        curl = curl_easy_init();

        if(curl) 
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            //res = curl_easy_perform(curl);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        Json::Reader reader;
        
        if (readBuffer.size() > 0)
        {
            reader.parse(readBuffer, obj); 
        }
        else
        {
            cerr << "Read Buffer is empty" << endl;
        }

        if (attempts > 3)
        {
            cerr << "***ERROR*** Failed to retreive data from " << url << endl;
            break;
        }
        attempts++;
    }

    if (DEBUG)
    {
        ofstream output;
        output.open("debug/DEBUG_json_obj.txt");
        output << obj << endl;
        output.close();
    }
}

#undef DEBUG