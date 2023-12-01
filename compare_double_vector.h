#include <iostream>
#include <vector>
//#include <map>
#include <set>

using namespace std;

typedef vector<vector<string>> matrix;

/*
 * Used to store the overlap between the two matrices. 
*/
typedef struct comparisons
{
    // name of comparison; usually AvsB
    string name;
    
    // results
    matrix overlap;
    
    // how many matches were found
    int count; 

} comparison;

// creates a new comparison object
comparison* init(string& name);

// creates a vector of new comparison objects 
vector<comparison*> init (vector<string>& names);

// deletes a comparison object 
void del(comparison* c);

// deletes a vector of comparison objects 
void del(vector<comparison*> vc);

// Helper: takes vector and empty set and adds the values to the set.
void vector_to_set(vector<string>& v, set<string>& s);

// Helper: takes two vectors and and compares to see if they have any matching values
bool vec_cmpr(vector<string>& v1, vector<string>& v2);

// Final function: compares two matrices and return which rows have matching values.
void matrix_cmpr(matrix& m1, matrix& m2, matrix& overlap, int& count);