#include "parser.h"
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <assert.h>
#include <string.h>

using namespace std;
using String = void (*)(const string& token);

static string numbers = "";
static string strings = "";
void register_on_string_callback(String callback);
void parser(const string& text);

void reset()
{
    numbers = "";
    strings = "";
}

void Callback_on_number(int str)
{
    numbers += std::to_string(str);
    numbers += ' ';
}

void Callback_on_string(const string& str)
{
    strings += str;
    strings += ' ';
}

void Callback_on_beginning()
{

    printf("Parsing started\n");
}

void Callback_on_end()
{
    printf("Parsing finished successfully\n");
}

int main()
{
    register_on_string_callback(Callback_on_string);
    register_on_number_callback(Callback_on_number);
    register_on_start(Callback_on_beginning);
    register_on_stop(Callback_on_end);

    parser("\n \n\n 2662  asd  \nf\t255621\nrty");
    assert(numbers == "2662 255621 " && strings == "asd f rty ");
    reset();

    parser("\n \n\n   \n\t\n");
    assert(numbers == "" && strings == "");
    reset();

    parser("\n \n456\n123 ?%№ lkf\n\t\n");
    assert(numbers == "456 123 " && strings == "?%№ lkf ");
    reset();

    parser("123 asd 456 dfg 789 asd");
    assert(numbers == "123 456 789 " && strings == "asd dfg asd ");
    reset();

    parser("");
    assert(numbers == "" && strings == "");
    reset();

    return 0;
}