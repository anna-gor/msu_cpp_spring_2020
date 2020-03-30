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

Number callback_on_number;
String callback_on_string;
BeginOrEnd callback_begin;
BeginOrEnd callback_end;

void parser(const string& text);
void register_on_string_callback(String callback);

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

void register_on_number_callback(Number callback)
{
    callback_on_number = callback;
}

void register_on_string_callback(String callback)
{
    callback_on_string = callback;
}

void register_on_start(BeginOrEnd callback)
{
    callback_begin = callback;
}

void register_on_stop(BeginOrEnd callback)
{
    callback_end = callback;
}

void parser(const string& text)
{
    char current;
    string token = "";
    if (!callback_begin || !callback_end || !callback_on_string || !callback_on_number)
        return;
    callback_begin();
    for (size_t i = 0; i < text.length(); ++i) {
        while (text[i] == '\n' || text[i] == '\t' || text[i] == ' ') {
            ++i;
        }
        while (!(text[i] == '\n' || text[i] == '\t' || text[i] == ' ') && text[i]) {
            token += text[i];
            ++i;
        }
        current = text[i - 1];
        if (is_number(token))
            callback_on_number(stoi(token));
        else if (!(current == '\n' || current == '\t' || current == ' '))
            callback_on_string(token);
        token.erase();
    }
    callback_end();
}