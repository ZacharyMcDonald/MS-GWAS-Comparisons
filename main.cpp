#include "gwas_obj.h"

/******************************************************************************
 * ****************************** MAIN ************************************** *
*******************************************************************************/

int main(int argc, char** argv)
{
    cout << "Starting Program..." << endl;
    
    vector<string> study_names{"s2007", "s2013", "s2019", "s2007_2"};
    //vector<string> file_names{"input/rsid_2007.csv", "input/rsid_2013.csv", "input/rsid_2019.csv"};

    vector<string> file_names{"input/final_input/rsid_2007.csv", "input/final_input/rsid_2013.csv", "input/final_input/rsid_2019.csv", "input/final_input/2007_screened_replication.csv"};
    
    vector<study*> studies = init(study_names, file_names);
    
    fetch_data_driver(studies);

    vector<comparison*> comparisons = compare_double_vector_driver(studies);

    output_comparisons_csv(comparisons);
    
    del(studies);
    del(comparisons);

    cout << "...Program Ended" << endl;
    return 0;
}

// End of file