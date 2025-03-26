#ifndef ALL_H
#define ALL_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>
#include <unordered_set>
#include <set>
#include <fstream>

//____________________
//#define DEBUG
//____________________


using ull = unsigned long long;

struct exit_status{
    int error_code;
    int line;
    //std::vector<unsigned short>warnings;

    explicit exit_status(int erc);

    exit_status() = default;

    exit_status(const exit_status& st) = default;
};

struct line {
    std::vector<std::string>words;
    unsigned int priority;

    bool empty();

    line(std::string& str);
};

struct func {
    std::string name;
    ull namehash;
    ull place;

    func(std::string& name, ull line);

    func() = default;
};

using glvar = func;

struct data {
    std::vector<line*>lines;
    std::vector<struct func>places;
    std::vector<glvar>variables;

    data();

    ull cur_line();
};


#define OK 0
#define SYNTAX_ERROR 1
#define VAR_TYPES_NOT_CONNECT 2
#define UNDEFINED_VARIABLE 3
#define REDEFINE_VARIABLE 5
#define UNDEFINED_VARIABLE_TYPE 6
#define ERROR_END 7
#define DEVIDE_BY_ZERO 8
#define BUILD_IMPORTATION_ERROR 9

#endif