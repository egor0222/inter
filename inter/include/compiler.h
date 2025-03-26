#ifndef COMPILER_H
#define COMPILER_H
#include "all.h"

enum class Variable_types{
    INT, STR, FLOAT, CHAR, NONE, FUNC
};

//bool test(std::string line);

//using func = decltype(test);

struct variable {
    std::string name;
    Variable_types type;
    void* data;
    ull namehash;

    explicit variable(std::string name, Variable_types type, long long num);

    explicit variable(std::string name, Variable_types type, long double num);

    explicit variable(std::string name, Variable_types type, std::string str);

    explicit variable(std::string name, std::string data);

    ~variable();
};

bool var_comp(variable* one, variable* two);

namespace codes {
    constexpr int pl_code = 1;
    constexpr int mn_code = 2;
    constexpr int dv_code = 3;
    constexpr int ml_code = 4;
    constexpr int var_code = 5;
    constexpr int print_code = 6;
    constexpr int eq_code = 7;
    constexpr int input_code = 8;
    constexpr int if_code = 9;
    constexpr int per_code = 10;
    constexpr int end_code = 11;
    constexpr int import_code = 12;
}

//struct data {
//    static std::vector<line>* all;
//};

class Compiler{
public:

    Compiler(data* dt);

    exit_status run(ull start);

    ~Compiler();
private:
    data* places;

    std::vector<variable*>variables;
    std::vector<ull>last_return;
    std::vector<ull>calls;

    exit_status pl(line* ln);

    exit_status mn(line* ln);

    exit_status dv(line* ln);

    exit_status ml(line* ln);

    exit_status per(line* ln);

    exit_status var(line* ln);

    exit_status eq(line* ln);

    exit_status print(line* ln);

    exit_status input(line* ln);

    exit_status iff(line* ln);

    exit_status end(line* ln);

    ull next_line(ull line_number);

    std::pair<bool, exit_status> check(line* ln);

    bool check_expression(std::string& var1, std::string& op, std::string& var2);

    int priority_coef = 4;

    ull current_priority = 0;
    ull currentline;
    
    ull find_func(std::string name);

    variable* find_var(std::string name);

    bool print_warnings = true;
};
 
#endif