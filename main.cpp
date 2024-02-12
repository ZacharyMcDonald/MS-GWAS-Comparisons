#include "gwas_obj.h"

using namespace std;

#define DEBUG true

bool cmd_args(int argc, char** argv, vector<string>& study_names, 
vector<string>& file_names);

/******************************************************************************
 * ****************************** MAIN ************************************** *
*******************************************************************************/

int main(int argc, char** argv)
{
    cout << "Starting Program..." << endl;
    
    //vector<string> study_names{"s2007", "s2013", "s2019"};
    //vector<string> file_names{"input/rsid_2007.csv", "input/rsid_2013.csv", "input/rsid_2019.csv"};

    //vector<string> study_names{"s2007", "s2013", "s2019", "s2007_2"};
    //vector<string> file_names{"input/final_input/rsid_2007.csv", "input/final_input/rsid_2013.csv", "input/final_input/rsid_2019.csv", "input/final_input/2007_screened_replication.csv"};
    vector<string> study_names;
    vector<string> file_names;
    
    if (!cmd_args(argc, argv, study_names, file_names))
    {
        return 0;
    }

    vector<study*> studies = init(study_names, file_names);
    
    fetch_data_driver(studies);

    vector<comparison*> comparisons = compare_double_vector_driver(studies);

    output_csv(comparisons);
    output_csv(studies);
    
    del(studies);
    del(comparisons);

    cout << "...Program Ended" << endl;
    return 0;
}

bool cmd_args(int argc, char** argv, vector<string>& study_names, 
vector<string>& file_names)
{
    if (argc != 2)
    {
        cout << "Must specify a csv file name that contains the study names and "
             << "there relative file paths and file names" 
             << endl;
        return false;
    }

    cout << "argv[1]: " << argv[1] << endl;

    matrix in;
    string fn(argv[1]);
    read_file(fn, in);

    if (in[0].size() > 3)
    {
        cout << "Incorrect file format: Too many columns" << endl; 
        return false;
    }
    if (in[0].size() != in[1].size())
    {
        cout << "Incorrect file format: number of study names must be equal "
             << "to the number of file names" 
             << endl;
        return false;
    }

    for (int i = 0; i < in.size(); i++)
    {
        study_names.push_back(in[i][0]);
        file_names.push_back(in[i][1]);

        if (DEBUG)
        {
            cout << study_names[i] << ": " 
                 << file_names[i] 
                 << endl;
        }
    }
    
    return true;
}

#undef DEBUG

// End of file