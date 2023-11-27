#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef vector<vector<string>> matrix;

typedef struct comparisons
{
    string name;
    
    matrix overlap;
    
    int count; 

} comparison;

comparison* init(string& name);

vector<comparison*> init (vector<string>& names);

void del(comparison* c);

void del(vector<comparison*> vc);

void vector_to_set(vector<string>& v, set<string>& s);

bool vec_cmpr(vector<string>& v1, vector<string>& v2);

void matrix_cmpr(matrix& m1, matrix& m2, matrix& overlap, int& count);