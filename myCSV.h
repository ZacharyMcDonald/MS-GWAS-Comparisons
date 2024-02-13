#include <iostream>
#include <fstream>
#include <vector>

#include "matrix_typedef.h"

/*
* Functions for reading the csv to matrix. Results is a Matrix 
* M[a][b] where 'a' is the row and 'b' is the column. i.e. M[y][x]
*/ void   read_file          (std::string& fn,   matrix& m);
   
   void   test_print_data    (matrix&   m);
   void   test_print_data    (matrix3d& m);
   
   void   save_matrix_as_csv (matrix& m,   std::string& ofn);
   void   save_matrix_as_csv (matrix3d& m, std::string& ofn);
   
   std::string vector_to_string   (std::vector<std::string>& v);
   void   remove_commas      (std::string& s);

   // do not use untested!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   void   restructure_matrix (matrix& m, matrix& im);