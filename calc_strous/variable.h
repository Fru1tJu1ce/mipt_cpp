#ifndef VARIABLE_H
#define VARIABLE_H

#include "std_lib_facilities.h"


class Variable
{
public:
    string name;
    double value;

    Variable(string n, double v) : name(n), value(v) { }
};

extern vector<Variable> var_table;

double get_value(string s);
void set_value(string s, double d);
bool is_declared(string var);
double define_name(string s, double val);

#endif // VARIABLE_H
