#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "all.h"
#include "compiler.h"

std::vector<std::string> convert_args(int argc, char** argv);

int function_name_data(std::string str);

void conv_line(std::string& str, line* result);

Variable_types check_type(std::string& str);

ull get_hash(std::string& str);

ull find_main(data* dt);

void printfile(std::string path);

void printdata(data* dt);
#endif