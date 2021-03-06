#pragma once
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string>
#include <cstdlib>

using Number = void (*)(int token);
using String = void (*)(const std::string& token);
using BeginOrEnd = void (*)();

void register_on_number_callback(Number callback);
void register_on_string_callback(String callback);
void register_on_start(BeginOrEnd callback);
void register_on_stop(BeginOrEnd callback);
void parser(const std::string& text);