#include <cmath>
#include <limits>

#include "func.h"
#include "std_lib_facilities.h"


double factorial(double value)  /// Вычисляет факториал
{
    int limit = static_cast<int>(value);
    if (limit == 0)
        return 1;

    for (int i = 1; i < limit; ++i)
        value *= i;

    return value;
}


double checked_sqrt(double d)       /// Вычисляет корень
{
    if (d < 0.)
        error ("отрицательное подкорневое выражение со значением= ", d);

    return sqrt(d);
}


double checked_acos(double d)       /// Вычисляет арккосинус
{
    if (d < -1. || 1. < d)
        error ("арккосинус лежит в пределах от -1 до 1 включительно");

    return acos(d);
}


double checked_asin(double d)       /// Вычисляет арккосинус
{
    if (d < -1. || 1. < d)
        error ("арксинус лежит в пределах от -1 до 1 включительно");

    return asin(d);
}


constexpr double tol = std::numeric_limits<double>::epsilon();


double checked_sin(double d)       /// Вычисляет арккосинус
{
    d = sin(d);
    if (std::abs(d) < tol)
        d = 0.;

    return d;
}


double checked_cos(double d)       /// Вычисляет арккосинус
{
    d = cos(d);
    if (std::abs(d) < tol)
        d = 0.;

    return d;
}


using FuncMap = std::map<std::string, std::function<double(double)>>;

FuncMap func_set
{
    {"sqrt", checked_sqrt},
    {"asin", checked_asin},
    {"acos", checked_acos},
    {"sin", checked_sin},
    {"cos", checked_cos},
};


bool has_function(const std::string& name)
{
    return func_set.find(name) != func_set.end();
}


double call_function(const std::string& name, double x)
{
    auto it = func_set.find(name);
    if (it != func_set.end())
        return it->second(x);

    error("unknown function '"+ name + "'");
}
