#ifndef _DATA_SET_H
#define _DATA_SET_H

#include "vector_math.h"
#include <fstream>
#include <map>
using namespace std;

typedef map <euclid_vector *, int> label_space;
typedef vector <euclid_vector *> vector_space;

class data_set;

void load(data_set & st, ifstream & vtr_in);
void label(data_set & st, ifstream & label_in);

class data_set
{
private:
    data_set * _parent;
    label_space * _labels;
    vector_space * _vectors;
    vector <int> _domain;
    data_set(data_set & parent, vector <int> domain);
public:
    data_set();
    data_set(vector_space vectors);
    ~data_set();
    int size();
    void set_label(euclid_vector * vtr, int label);
    int get_label(euclid_vector * vtr);
    euclid_vector * operator[](int i);
    data_set subset(vector <int> domain);
    friend void load(data_set & st, ifstream & vtr_in);
    friend void label(data_set & st, ifstream & label_in);
};

#endif