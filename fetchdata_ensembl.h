// takes a 3d vector of all results and add the gene 
// length for each gene to the matrix

#include <iostream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

using namespace std;

#define DEBUG true

void get_gene_sequence(string& gene_name);