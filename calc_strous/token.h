#ifndef TOKEN_H
#define TOKEN_H
#include "std_lib_facilities.h"

const double pi = acos(-1);

const char number = '8';                // Для работы с числами
const char quit = 'q';                  // Для символа выхода из программы
const string prompt = "> ";             // Для указания ввода
const string result = "= ";             // Для указания вывода
const char help = 'h';                  // Для вывода инструкции в консоль
const char print = ';';                 // Для немедленного вывода результата
const char name = 'a';                  // Лексема Имя
const char let = 'L';                   // Лексема let
const string declkey = "let";           // Ключевое слово let
const char func = 'f';
/*
const string sqtkey = "sqrt";           // Ключевое слово sqrt
const string acoskey = "acos";          // Ключевое слово arccos
const string asinkey = "asin";          // Ключевое слово arcsin
const string coskey = "cos";            // Ключевое слово cos
const string sinkey = "sin";            // Ключевое слово sin
*/

bool has_function();

class Token
{                                       // Пользовательский тип
public:
    char kind;
    double value;
    string name;

    Token(char ch)
        :kind{ch}, value{0} { }         // Инициализирует kind символом ch
    Token(char ch, double val)
        :kind{ch}, value{val} { }       // Инициализирует kind и value
    Token(char ch, string n)
        :kind{ch}, value{0}, name{n} { }          // Инициализирует kind и name
};


class TokenStream
{
public:
    TokenStream();           // Создает объект класса TokenStream, считывающий данные из cin
    Token get();               // Получает объект токен из потока
    void putback(Token t);     // Помещает токен обратно в поток
    void ignore (char c);      // Отбрасывает символы до символа с включительно
private:
    bool full {false};         // Есть ли токен в буфере?
    Token buffer = {'0'};  // Где мы храним putback токен
};

extern TokenStream ts;

#endif // TOKEN_H
