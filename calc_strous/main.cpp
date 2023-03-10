/*
Эта программа реализует основные выражения калькулятора.
Ввод о существляется из потока cin; вывод - в поток cout.

Грамматика для ввода:

Инструкция:
    Выражение
    Вывод
    Выход

Вывод:
    ;

Выход:
    q

Выражение:
    Терм
    Выражение + Терм
    Выражение - Терм

Терм:
    Первичное_выражение
    Терм * Первичное_выражение
    Терм / Первичное_выражение
    Терм % Первичное_выражение

Первичное_выражение:
    Число
    ( Выражение )
    - Первичное_выражение
    + Первичное_выражение

Число:
    Литерал_с_плавающей_точкой

Переменная:
    let Наименование_переменной = Выражение
    let Наименование_переменной = ( Выражение )

Ввод из потока cin через TokenStream с именем ts.
*/

#include <iostream>
#include "std_lib_facilities.h"
#include "variable.h"
#include "token.h"
#include "grammar.h"


void greet_user()               /// Приветствует пользователя калькулятора
{
    cout << "!----------КАЛЬКУЛЯТОР----------!\n\n"
         << "Добро пожаловать в программу-калькулятор!\n"
         << "Вводите выражения с числами с плавающей точкой.\n"
         << "Для помощи введите 'h'\n"
         << "Введите выражение:\n";
}


void give_instructions()        /// Выводит инструкцию к калькулятору
{
    cout << "Вводите выражение в виде: Операнд оператор Операнд...\n"
         << "Список доступных операторов: {+, -, *, /, !, sin, asin, cos, acos, sqrt}\n"
         << "Для объявления переменной напишите конструкцию в виде: let Имя_переменной = Выражение\n"
         << "Для расчёта sin, asin, cos, acos пишите выражение в скобках: sqrt(Выражение)\n"
         << "Для завершения записи выражения или объявления переменной введите ';'\n"
         << "Для выхода из программы введите 'q'\n\n"
         << "Введите выражение:\n";
}


void clean_up_mess()
{
    ts.ignore(print);
}


void calculate()                /// Вычисляет выражение
{
    while (cin)
    try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)  t = ts.get();                             // Удаление вывода
        if (t.kind == quit) return;                                        // Для выхода из калькулятора
        if (t.kind == help)                                                // Вывод инструкции
        {
            give_instructions();
            continue;
        }
        ts.putback(t);
        cout << result << statement() << '\n';
    }
    catch (exception& e)
    {
        cerr << e.what() << '\n';               // Вывод сообщения об ошибке
        clean_up_mess();
    }
}


int main()
{
    if (setlocale(LC_ALL, "ru-RU") == NULL)
    {
        cout << "Error set locale ru-RU." << endl;
    }
    greet_user();
    try
    {
        define_name("pi", acos(-1));
        define_name("e", exp(1));

        calculate();
        keep_window_open();                     // Удерживает консольное окно открытым
        return 0;
    }
    catch (runtime_error& e)
    {
        cerr << e.what() << '\n';
        cout << "Чтобы закрыть окно, введите символ ~\n";
        for(char ch; cin >> ch;)
            if (ch == '~') return 1;
        return 1;
    }
    catch (...)
    {
        cerr << "исключение\n";
        keep_window_open("~~");
        return 2;
    }
}
