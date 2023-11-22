#include "compare_double_vector.h"


comparison* init(string& name)
{
    comparison* c;
    c = new comparison;

    c->name  = name;
    c->count = 0;

    return c;
}

vector<comparison*> init(vector<string>& names)
{
    vector<comparison*> vc;

    for (size_t i = 0; i < names.size(); i++)
    {
        vc.push_back( init(names[i]) );    
    }

    return vc;
}

void del(comparison* c)
{
    delete c;
}

void del(vector<comparison*> vc)
{
    for (size_t i = 0; i < vc.size(); i++) 
    {
        del(vc[i]);
    }
}

void vector_to_set(vector<string>& v, set<string>& s)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        s.insert(v[i]);
    }
}

bool vec_cmpr(vector<string>& v1, vector<string>& v2)
{
    // working with pointers to avoid copying
    set<string> large_set;
    vector<string>* small_vec;
    
    // use the larger vector to make set
    if (v1.size() > v2.size())
    {
        vector_to_set(v1, large_set);
        small_vec = &v2;
    }
    else
    {
        vector_to_set(v2, large_set);
        small_vec = &v1;
    }

    // iterate over the smaller vector and search in larger set. 
    for (size_t i = 0; i < small_vec->size(); i++)
    {
        if (large_set.find(small_vec->at(i)) != large_set.end())
        {
            return true;
        }
    }
    return false;
}


void matrix_cmpr(matrix& m1, matrix& m2, matrix& overlap, int& count)
{
    for (size_t i = 0; i < m1.size(); i++)
    {
        for (size_t j = 0; i < m2.size(); j++)
        {
            if ( vec_cmpr(m1[i], m2[j]) )
            {
                overlap.push_back(m1[i]);
                overlap.push_back(m2[j]);
                count++;
            }
        }
    }
}

