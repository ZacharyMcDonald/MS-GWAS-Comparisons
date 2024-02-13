#include <iostream>
#include <vector>
#include <set>

#include "matrix_typedef.h"

/*
 * Used to store the overlap between the two matrices (studies). 
*/
typedef struct comparisons
{
    // name of comparison; usually AvsB
    std::string name;
    
    // results
    matrix overlap;
    
    // how many matches were found
    int count; 

} comparison;

// creates a new comparison object
comparison* init(std::string& name);

// creates a std::vector of new comparison objects 
std::vector<comparison*> init(std::vector<std::string>& names);

// deletes a comparison object 
void del(comparison* c);

// deletes a std::vector of comparison objects 
void del(std::vector<comparison*> vc);

// Final function: compares two matrices and return which rows have matching values.
void matrix_cmpr(comparison* c, matrix& m1, matrix& m2);

// End of file