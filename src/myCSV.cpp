#include "myCSV.h"

using namespace std;

void parse_line(string& line, int& lineNumber, matrix& m);
void read_file(string& fn, matrix& m)
{
    fstream fin;

    string line;
    int    lineNumber = 0;

    fin.open(fn);
    // get each row of the CSV
    while (getline(fin, line))
    {
        parse_line(line, lineNumber, m);
        lineNumber++;
    }
    fin.close();
}

void parse_line(string& line, int& lineNumber, matrix& m)
{
    string word;
    //word.push_back(line[0]);

    // create new column vector
    vector<string> nv;
    m.push_back(nv);

    // iterate over line, at each comma add to row vector
    for (size_t i = 0; i + 1 < line.size(); i++)
    {
        while (i + 1 < line.size() && line[i] != ',')
        {
            word.push_back(line[i]);
            i++;
        }
        m[lineNumber].push_back(word);
        
        word.clear();
    }
}

void test_print_data(matrix& m)
{
    for (size_t i = 0; i < m.size(); i++)
    {
        cout << i << ' ';
        for (size_t j = 0; j < m[i].size(); j++)
        {
            cout << m[i][j] << ',';
        }
        cout << endl;
    }
}

void test_print_data(matrix3d& m)
{
    for (size_t i = 0; i < m.size(); i++)
    {
        cout << i << ' ';
        for (size_t j = 0; j < m[i].size(); j++)
        {
            if (m[i][j].size() == 1)
            {
                cout << m[i][j][0] << ',';
                continue;
            }
            if (m[i][j].size() == 0)
            {
                continue;
            }
            
            cout << vector_to_string(m[i][j]) << ',';
        }
        cout << endl;
    }
}

void save_matrix_as_csv(matrix& m, string& ofn)
{
    ofstream output;
    output.open(ofn);

    for (size_t i = 0; i < m.size(); i++)
    {
        //output << i << ' ';
        for (size_t j = 0; j < m[i].size(); j++)
        {
            output << m[i][j] << ',';
        }
        output << endl;
    }

    output.close();
}

void save_matrix_as_csv(matrix3d& m, string& ofn)
{
    ofstream output;
    output.open(ofn);

    //string buffer;

    for (size_t i = 0; i < m.size(); i++)
    {
        //output << i << ' ';
        for (size_t j = 0; j < m[i].size(); j++)
        {
            if (m[i][j].size() == 1)
            {
                remove_commas(m[i][j][0]);
                output << m[i][j][0] << ',';
                continue;
            }
            if (m[i][j].size() == 0)
            {
                output << ',';
                continue;
            }
            
            output << vector_to_string(m[i][j]) << ',';
        }
        output << endl;
    }
    output.close();
}

string vector_to_string(vector<string>& v)
{
    string s;

    s += "{";
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v[i].size(); j++)
        {
            if (v[i][j] == ',')
            {
                s += '.';
                continue;
            }
            s += v[i][j];
        }
        
        if (v.size() != i+1)
        {
            s += "; ";
        }
    }
    s += "}";

    return s;
}

void remove_commas(string& s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == ',')
        {
            s[i] = '.';
        }
    }
}

// do not use untested!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void restructure_matrix (matrix& m, matrix& im)
{
    im.resize(m[0].size());
    
    for (size_t i = 0; i < m.size(); i++)
    {
        for (size_t j = 0; j < m.size(); j++)
        {
            // m[i][j]
            im[j].push_back(m[i][j]);
        }
    }
}