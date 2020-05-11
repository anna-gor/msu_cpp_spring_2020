#pragma once

#include <string>

#include <iostream>

#include <ctype.h>

#include <vector>


template < class T >
  std::string to_string(T && arg) {
    std::stringstream stream;
    stream << arg;

    return stream.str();
  }

template < class...ArgsT >
  std::string format(const std::string & str, ArgsT && ...args) 
{
  std::vector < std::string > parameters {
    to_string(std::forward < ArgsT > (args))...
  };
  std::string result = "";
  for (auto j = 0; j < str.length(); j++) {
    if (str[j] == '{') {
      if (j == str.length() - 1) throw std::runtime_error("error");
      j += 1;
      std::string tmp = "";
      while (str[j] != '}') {
        if (j > str.length() - 2 || !isdigit(str[j])) throw std::runtime_error("error");
        tmp += str[j];
        j += 1;
      }
      int n = std::stoi(tmp);
      if (tmp.empty() || n > parameters.size() - 1) throw std::runtime_error("error");
      result += parameters[n];
    } 
    else if (str[j] == '}') throw std::runtime_error("error");
    else result += str[j];
  }
  return result;

}