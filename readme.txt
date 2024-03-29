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

TODO