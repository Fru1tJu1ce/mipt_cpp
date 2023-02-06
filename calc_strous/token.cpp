#include <set>

#include "func.h"
#include "token.h"


TokenStream ts;


TokenStream::TokenStream()
    : full(false), buffer(0)    // нет токена в буфере
{
}


void TokenStream::ignore(char c)
// Символ с представляет разновидность лексем
{
    // Проверка буфера
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // Проверка входных данных
    char ch = 0;
    while (cin >> ch)
        if (ch == c) return;
}


void::TokenStream::putback(Token t)
{
    if (full) error("putback(): буфер заполнен");
    buffer = t;
    full = true;
}


Token TokenStream::get()            /// Чтение символов из cin и составление Token
{
    if (full)                                              // Проверка наличия Token в буфере
    {
        full = false;
        return buffer;
    }
    char ch;                                               // Оператор >> пропускает пробельные символы
    cin >> ch;

    switch (ch)
    {
    case quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case print:
    case '*':
    case '/':
    case '%':
    case '{':
    case '=':
    case '}':
    case help:
    case '!':                                               // Обработка знаковых лексем + лексемы для инструкции
        return Token{ch};                                   // Каждый символ представляет сам себя
    case '.':                                               // Число с плавающей точкой может начинаться с точки

    // Числовой литерал:
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);                             // Вернуть цифру во входной поток
        double val;
        cin >> val;                                     // Считать число с плавающей точкой
        return Token{number, val};
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
            cin.putback(ch);
            if (s == declkey) return Token{let};
            if (has_function(s)) return Token{func, s};
            return Token{name, s};
        }
        error("Неправильная лексема");
    }
}
