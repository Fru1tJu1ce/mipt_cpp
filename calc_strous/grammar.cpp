#include "func.h"
#include "grammar.h"
#include "token.h"
#include "variable.h"


double statement()
{
    Token t = ts.get();
    switch(t.kind)
    {
        case let:
            return declaration();
        default:
            ts.putback(t);
            return expression();
    }
}


double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
        error("в объявлении ожидается имя переменной");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        error("пропущен  символ = в объявлении ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}


double primary()                // Работает с числами и скобками
{
    Token t = ts.get();
    switch(t.kind)
    {
        case '(':                       // Обработка '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
            {
                error("требуется ')'");
            }
            return d;
        }
        case '{':                       // Обработка '{' expression '}'
        {
            t.kind = '(';               // Замена '{' на '{'
            double d = expression();
            t = ts.get();
            if (t.kind != '}')
            {
                error("требуется '}'");
            }
            return d;
        }
        case '}':                       // Замена '}' на ')'
            t.kind = ')';
            [[fallthrough]];
        case number:                       // Возвращает значение
        {
            return t.value;
        }
        case name:                          // Обработка имени переменной
        {
            Token next = ts.get();
            if (next.kind == '=')
            {
                double d = expression();
                set_value(t.name, d);
                return d;
            }
            else
            {
                ts.putback(next);
                return get_value(t.name);
            }
        }
        case func:
        {
            Token br = ts.get();
            if (br.kind != '(')
                error("пропущена открывающая скобка");

            double d = expression();
            d = call_function(t.name, d);

            br = ts.get();
            if (br.kind != ')')
                error("требуется ')' для вычисления корня");

            return d;
        }
        case '-':
            return - primary();
        case '+':
            return primary();
        default:
            error("требуется первичное выражение");
    }
}


double expression()             // Работает с операциями + и -
{
    double left = term();       // Считываем и вычисляем терм
    Token t = ts.get();      // Получаем следующую лексему
    while (true)
    {
        switch(t.kind)          // Определяем вид лексемы
        {
            case '+':
                left += term();       // Вычисляем терм и суммируем
                t = ts.get();
                break;
            case '-':
                left -= term();       // Вычисляем терм и вычитаем
                t = ts.get();
                break;
            default:
                ts.putback(t);      // Возврат t в потом лексем
                return left;        // Символов + и - нет -> возвращаем ответ
        }
    }
}


double term()                   // Работает с операциями *, / и %
{
    double left = primary();
    Token t = ts.get();
    while (true)
    {
        switch(t.kind)
        {
            case '*':               // Обработка умножения
                left *= primary();
                t = ts.get();
                break;
            case '/':               // Обработка деления
            {
                double d = primary();
                if (d == 0)
                {
                    error("Деление на нуль");
                }
                left /= d;
                t = ts.get();
                break;
            }
            case '%':               // Обработка целочисленного деления
            {
                double d = primary();
                if (d == 0) error("%: деление на нуль");
                left = fmod(left, d);
                t = ts.get();
                break;
            }
            case '!':
                left = factorial(left);
                return left;
            default:
                ts.putback(t);      // Возвращаем t в поток лексем
                return left;        // Символов * и / нет
        }
    }
}
