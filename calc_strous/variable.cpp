#include "variable.h"
#include "token.h"


vector<Variable> var_table;

double get_value(string s)              /// Возвращает значение переменной с именем s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: Неопределенная переменная ", s);
}


void set_value(string s, double d)
// Присваивает объекту s типа Variable значение d
{
    for (Variable& v : var_table)
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    error("set: неопределенная переменная", s);
}


bool is_declared(string var)                /// Есть ли переменная var в векторе var_table?
{
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}


double define_name(string s, double val)           /// Добавляем пару (var, val) в вектор var_table
{
    if (is_declared(s)) error(s, " повторное объявление");
    var_table.push_back(Variable(s, val));
    return val;
}

