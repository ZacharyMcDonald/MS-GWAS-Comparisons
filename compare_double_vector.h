#include <iostream>
#include <vector>
#include <set>

typedef std::vector<std::vector<std::string>> matrix;

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
std::vector<comparison*> init (std::vector<std::string>& names);

// deletes a comparison object 
void del(comparison* c);

// deletes a std::vector of comparison objects 
void del(std::vector<comparison*> vc);

// Helper: takes std::vector and empty set and adds the values to the set.
void vector_to_set(std::vector<std::string>& v, std::set<std::string>& s);

// Helper: takes two std::vectors and and compares to see if they have any matching values
bool vec_cmpr(std::vector<std::string>& v1, std::vector<std::string>& v2);

// Final function: compares two matrices and return which rows have matching values.
void matrix_cmpr(matrix& m1, matrix& m2, matrix& overlap, int& count);

// End of file