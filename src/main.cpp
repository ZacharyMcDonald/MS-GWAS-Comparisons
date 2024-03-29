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
    
    vector<string> study_names;
    vector<string> file_names;
    
    // takes command line arguments and adds them to study_names and file_names
    // returns false if something went wrong with the input filename or file
    if (!cmd_args(argc, argv, study_names, file_names))
    {
        return 0;
    }

    // initialize the study objects with the given filesnames and study_names
    vector<study*> studies = init(study_names, file_names);
    
    // fetches all the data from the dbSNP and ensembl databases and saves them
    // to the study objects
    fetch_data_driver(studies);

    // saves the study objects
    output_csv(studies);

    // finds the intersection of the rsid matrixes. No comparisons are made if
    // only one file is given. 
    if (file_names.size() > 1)
    {
        vector<comparison*> comparisons = compare_double_vector_driver(studies);
        output_csv(comparisons);
        del(comparisons);
    }
    else
    {
        cout << "Only one input given. No comparisons to be made." << endl;
    }
    
    // clean up
    del(studies);

    cout << "...Program Ended" << endl;
    
    // make c happy
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

    cout << "Your input file: " << argv[1] << endl;

    // read in the file names and the study names to a matrix
    matrix in;
    string fn(argv[1]);
    read_file(fn, in);

    // check if the file is formatted correctly
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

    // iterate over a correctly formatted file and add the the results to 
    // output vectors. These vectors will be used to initialize the study object
    for (size_t i = 0; i < in.size(); i++)
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
    
    // everything happened correctly
    return true;
}

#undef DEBUG

// End of file