#include "fetchdata_shared.h"

using namespace std;

#define DEBUG false

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}

vector<string> string_to_vec(string s)
{
    vector<string> v(1, s);
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
    }
}

bool save_errors (string& ERR)
{
    cerr << ERR << endl;
    
    ofstream output;
    output.open("output/errors.txt", ios::app);

    if (!output)
    {
        return false;
    }

    output << ERR << endl;
    output.close();

    return true;
}

bool save_errors (string& ERR, string& out_file)
{
    cerr << ERR << endl;
    
    ofstream output;
    output.open(out_file, ios::app);

    if (!output)
    {
        return false;
    }

    output << ERR << endl;
    output.close();

    return true;
}

void get_json_from_url(string& url, Json::Value& obj)
{
    // prevents the server from being pinged too quickly
    sleep(0.5);

    obj.clear();

    CURL* curl;

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
            string err = "Read Buffer is empty: " + url;
            if (!save_errors(err))
            {
                cerr << "Failed to open error file" << endl;
            }
        }

        if (attempts > 1)
        {
            sleep(10);
        }

        if (attempts > 2)
        {
            string err = "***ERROR*** Failed to retreive data from " + url;
            save_errors(err);
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