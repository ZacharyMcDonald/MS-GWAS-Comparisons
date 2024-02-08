// takes a 3d vector of all results and add the gene 
// length for each gene to the matrix

#include <iostream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

using namespace std;

typedef vector<vector<string>> matrix;
typedef vector<vector<vector<string>>> matrix3d;

#define DEBUG true

void add_gene_length_to_results(matrix3d& r);