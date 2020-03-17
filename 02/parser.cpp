#include "parser.h"

Number callback_on_number;
String callback_on_string;
BeginOrEnd callback_begin;
BeginOrEnd callback_end;


void register_on_number_callback(Number callback){
    callback_on_number = callback;
}

void register_on_string_callback(String callback){
    callback_on_string = callback;
}

void register_on_start(BeginOrEnd  callback){
    callback_begin = callback;
}

void register_on_stop(BeginOrEnd  callback){
    callback_end = callback;
}

void parser(const string& text){
    char current;
    string token = "";
    if(!callback_begin || !callback_end || !callback_on_string || !callback_on_number) return;
    callback_begin();
    for (int i =0; i < text.length(); ++i){
        while (text[i]=='\n'|| text[i] == '\t' || text[i] == ' ' ){
        ++i;
        }
        while (!(text[i]=='\n'|| text[i] == '\t' || text[i] == ' ' ) && text[i]){
            token += text[i];
            ++i;
        }
        current = text[i- 1];
        if (isdigit(current)) callback_on_number(std::stoull(token.c_str()));
        else if(!(current=='\n'|| current == '\t' || current == ' ' )) callback_on_string(token.c_str());
        token.erase();
    }
    callback_end();
}


