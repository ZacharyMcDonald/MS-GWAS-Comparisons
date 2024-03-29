How to use the program:

1) To this program folder, add CSV files (i.e. study1.csv) containing only the list 
of RSIDs in the first column; do not add a header to any files. Each file should 
contain the RSIDs for one GWAS.

Example RSID file:
study1.csv:
| rs000001 |
| rs000002 |
| rs000003 |
|  rs...   |

2) Create a new CSV (i.e. yourStudyNames.csv) in this folder that contains the GWAS 
names in column 1 and the corresponding RSID filnames in column 2; do not add a 
header. If only one study is specified, then the program will fetch data for that
study, but no intersection will occur. 


Example filename csv:
yourStudyNames.csv:
|study1 | study1.csv |
|study2 | study2.csv |
|...    | ...        |

3) Run program in linux terminal. Command: GwasDatabaseTool.exe yourStudyNames.csv

Expected output: study1_results.csv, study2_results.csv, study1study2_overlap.csv, ...

How the program works:

Data is read from the input csv file using a custom CSV API. All CSV data is stored 
as a vector<vector<string>> typedefined as "matrix". RSID vectors are stored in
the GWAS object (gwas_obj.cpp), each study is represented by a one GWAS object, then 
each object is added to a vector. All objects are C-style heap allocated structs.
The GWAS objects are passed into the fetch_data_driver function, this funtion
handles are database calls to dbSNP and the various Ensembl databases. The main
results are added to the 3-d vector because many data contain more than one value; 
the myCSV api handles printing multiple values per cell with semicolons. The main
results are exported to CSV, but the merged RSIDs are added to a 2-d matrix, where
the first value is the original rsid followed by the megered RSIDs. All data thus 
far has been stored in the GWAS objects, which are themselves stored in the a vector.
The GWAS vector is then passed into compare_double_vector_driver(), which returns
a vector of comparison objects that contain the overlap between all the of the 
GWAS objects. Theses overlaps are stored as matrices which then saved as CSVs.
