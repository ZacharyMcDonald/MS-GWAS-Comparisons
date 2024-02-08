#include "fetchdata_ensembl.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    
    return size * nmemb;
}

void create_ensembl_url(string& gene_name, string& url)
{
    string urlA = "https://rest.ensembl.org/sequence/id/";
    string urlB = gene_name;
    string urlC = "?";

    url = urlA + urlB + urlC;
}

void get_gene_sequence(string& gene_name, string& gene_sequence)
{
    //curl 'https://rest.ensembl.org/sequence/id/ENSG00000157764?' -H 'Content-type:text/plain'

    string url; 
    create_ensembl_url(gene_name, url);

    CURL* curl;

    string readBuffer;

    int attempts = 0;
    while (readBuffer.size() < 1)
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

        cout << readBuffer << endl;
        
        if (attempts > 10)
        {
            cerr << "***ERROR*** Failed to retreive data from " << url << endl;
            break;
        }
        attempts++;
    }

    if (DEBUG)
    {
        ofstream output;
        output.open("debug/DEBUG_json_obj_ensembl.txt");
        output << readBuffer << endl;
        output.close();
    }
}

int get_gene_length(string& gene_name)
{
    string gene_sequence;
    get_gene_sequence(gene_name, gene_sequence);
    return gene_sequence.size();
}