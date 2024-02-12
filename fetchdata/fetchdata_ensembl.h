// takes a 3d std::vector of all results and add the gene 
// length for each gene to the matrix

#include <iostream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

#include "fetchdata_shared.h"

void add_gene_length_to_results(matrix3d& r);