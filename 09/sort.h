#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/stat.h>

int sort(const std::string& file_to_sort);
void mymerge(std::vector<uint64_t>& vec, size_t start, size_t mid, size_t end);
void merge_sort(std::vector<uint64_t>& vec, size_t start, size_t end);
void mergeF(std::string& input1, const std::string& input2, const std::string& output);
int batch(const std::string& strF);
void usual_merge_sort(std::vector<uint64_t>& vec, size_t start, size_t end);