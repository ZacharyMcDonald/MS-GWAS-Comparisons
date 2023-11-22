#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<vector<string>> matrix;
typedef vector<vector<vector<string>>> matrix3d;

/*
* Functions for reading the csv to matrix. Results is a Matrix 
* M[a][b] where 'a' is the row and 'b' is the column. i.e. M[y][x]
*/ void   read_file          (string& fn,   matrix& m);
   void   parse_line         (string& line, int& lineNumber, matrix& m);
   
   void   test_print_data    (matrix&   m);
   void   test_print_data    (matrix3d& m);
   
   void   save_matrix_as_csv (matrix& m,   string& ofn);
   void   save_matrix_as_csv (matrix3d& m, string& ofn);
   
   string vector_to_string   (vector<string>& v);
   void   remove_commas      (string& s);

   // do not use untested!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   void   restructure_matrix (matrix& m, matrix& im);