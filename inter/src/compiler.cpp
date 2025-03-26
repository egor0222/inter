#ifndef COMPILER_CPP
#define COMPILER_CPP

#include "../include/function.h"
#include "../include/compiler.h"
#include "../include/all.h"
//#include "compiler.h"
//#include "all.h"
//#include <numeric>

static constexpr long double epsilon = 1e9;

//typedef exit_status(Compiler::* func_pointer)(line*);

Compiler::Compiler(data* dt) {
    this->places = dt;
    this->currentline = 0;
}


exit_status Compiler::run(ull start) {
    this->currentline = start;
    ////////////////////////////////
}

Compiler::~Compiler() {
    for (int i = 0; i < variables.size(); i++) {
        delete variables[i];
    }
}

ull Compiler::next_line(ull line_number){

    line* cur_ln = this->places->lines[line_number];

    int code = function_name_data(cur_ln->words[0]);

    exit_status st;

    switch (code)
    {
    case codes::pl_code:
        st = pl(cur_ln);
        break;
    case codes::mn_code:
        st = mn(cur_ln);
        break;
    case codes::ml_code:
        st = ml(cur_ln);
        break;
    case codes::dv_code:
        st = dv(cur_ln);
        break;
    case codes::var_code:
        st = var(cur_ln);
        break;
    case codes::input_code:
        st = input(cur_ln);
        break;
    case codes::print_code:
        st = print(cur_ln);
        break;
    case codes::eq_code:
        st = eq(cur_ln);
        break;
    case codes::if_code:
        st = iff(cur_ln);
        break;
    case codes::end_code:
        st = end(cur_ln);
        break;
    case codes::per_code:
        st = per(cur_ln);
        break;
    default:
        st = exit_status(SYNTAX_ERROR);
        break;
    }

    if (st.error_code) {
        std::cerr << "ERROR: line " << line_number << ", error code: " << st.error_code << std::endl;
        return false;
    }
    return true;
}

exit_status Compiler::eq(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() != 3) return exit_status(SYNTAX_ERROR);

    variable* first = find_var(ln->words[1]);
    variable* second = find_var(ln->words[2]);
    if (first == nullptr) return exit_status(UNDEFINED_VARIABLE);
    if (second != nullptr) {
        if (first->type != second->type) return exit_status(VAR_TYPES_NOT_CONNECT);
        switch (first->type) {
        case Variable_types::INT:
            *static_cast<long long*>(first->data) = *static_cast<long long*>(second->data);
            break;
        case Variable_types::STR:
            *static_cast<std::string*>(first->data) = *static_cast<std::string*>(second->data);
            break;
        case Variable_types::FLOAT:
            *static_cast<long double*>(first->data) = *static_cast<long double*>(second->data);
            break;
        default:
            return exit_status(SYNTAX_ERROR);
        }
        return exit_status(OK);
    }
    switch (first->type)
    {
    case Variable_types::INT:
        {
            long long* ptrll = static_cast<long long*>(first->data);
            *ptrll = std::stoll(ln->words[2]);
        }
        break;
    case Variable_types::STR:
        {
            std::string* ptrs = static_cast<std::string*>(first->data);
            *ptrs = ln->words[2];
        }
        break;
    case Variable_types::FLOAT:
        {
            long double* ptrs = static_cast<long double*>(first->data);
            *ptrs = std::stold(ln->words[2]);
        }
    break;
    default:
        return exit_status(SYNTAX_ERROR);
        break;
    }
    return exit_status(OK);
}

exit_status Compiler::var(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR); 
    static const std::unordered_map<std::string, Variable_types>var_data{
        {"int", Variable_types::INT},
        {"str", Variable_types::STR},
        {"char", Variable_types::CHAR},
        {"float", Variable_types::FLOAT}
    };

    if (ln->words.size() != 3) return exit_status(SYNTAX_ERROR);

    // func - 0, name - 1, type - 2

    if (find_var(ln->words[1]) != nullptr) return exit_status(REDEFINE_VARIABLE);

    auto vr = var_data.find(ln->words[2]);

    variable* var;

    switch (vr->second)
    {
    case Variable_types::INT:
        var = new variable(ln->words[1], vr->second, (long long)(0));
        break;
    case Variable_types::STR:
        var = new variable(ln->words[1], vr->second, "");
        break;
    case Variable_types::FLOAT:
        var = new variable(ln->words[1], vr->second, static_cast<long double>(0));
        break;
    default:
        return exit_status(UNDEFINED_VARIABLE_TYPE);
    }

    /*variables.emplace(get_hash(var->name), var);*/

    variables.push_back(var);

    return exit_status(OK);
}

exit_status Compiler::print(line* ln) {
    for (int it = 1; it < ln->words.size(); it++) {
        variable* ptr = find_var(ln->words[it]);
        if (ptr != nullptr) {
            switch (ptr->type)
            {
            case Variable_types::INT:
                std::cout << *static_cast<long long*>(ptr->data);
                break;
            case Variable_types::STR:
                std::cout << *static_cast<std::string*>(ptr->data);
                break;
            case Variable_types::FLOAT:
                std::cout << *static_cast<long double*>(ptr->data);
                break;
            default:
                return exit_status(SYNTAX_ERROR);
                break;
            }
        }
        else {
            std::cout << ln->words[it];
        }
        if (it + 1 == ln->words.size()) std::cout << std::endl;
        else std::cout << ' ';
    }
    return exit_status(OK);
}

exit_status Compiler::input(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() < 2) 
        return exit_status(SYNTAX_ERROR);
    
    for (int it = 1; it < ln->words.size(); it++) {
        std::string str;
        std::cin >> str;
        
        variable* vr = find_var(ln->words[it]);

        if (vr == nullptr) return exit_status(UNDEFINED_VARIABLE);

        switch (vr->type)
        {
        case Variable_types::INT:
            *static_cast<long long*>(vr->data) = std::stoll(str);
            break;
        case Variable_types::STR:
            *static_cast<std::string*>(vr->data) = str;
            break;
        default:
            break;
        }
    }
    return exit_status(OK);
}

exit_status Compiler::end(line* ln) {
    if (ln->words.size() != 1) return exit_status(SYNTAX_ERROR);
    current_priority--;
    if (current_priority < 0) return exit_status(ERROR_END);
    return exit_status(OK);
}

namespace operator_codes {
    constexpr int eq_op = 1;
    constexpr int neq_op = 2;
    constexpr int b_op = 3;
    constexpr int s_op = 4;
    constexpr int be_op = 5;
    constexpr int se_op = 6;
    constexpr int tp_op = 7;
}

static const std::unordered_map<std::string, int>op_data{
    {"==",      operator_codes::eq_op},
    {"!=",      operator_codes::neq_op},
    {">",       operator_codes::b_op},
    {"<",       operator_codes::s_op},
    {">=",      operator_codes::be_op},
    {"<=",      operator_codes::se_op},
    {"<=>",     operator_codes::tp_op},
    {"eq",      operator_codes::eq_op},
    {"neq",     operator_codes::neq_op},
    {"more",    operator_codes::b_op},
    {"less",    operator_codes::s_op},
    {"type",    operator_codes::tp_op},
    {"mreq",    operator_codes::be_op},
    {"lseq",    operator_codes::se_op}
};

bool Compiler::check_expression(std::string& var1, std::string& op, std::string& var2) {
    using namespace operator_codes;

    variable* v1 = this->find_var(var1);
    variable* v2 = this->find_var(var2);
    bool v1_created = false; 
    bool v2_created = false;

    bool exit = false;

    if (v1 == nullptr) {
        v1 = new variable("", var2);
        v1_created = true;
    }

    if (v2 == nullptr) {
        v2 = new variable("", var2);
        v2_created = true;
    }
    
    if (v1->type != v2->type) return false;
    switch (v1->type)
    {
    case Variable_types::INT: 
    {
        long long v1c = *static_cast<long long*>(v1->data);
        long long v2c = *static_cast<long long*>(v2->data);

        switch (op_data.find(op)->second)
        {
        case eq_op:
            exit = (v1c == v2c);
            break;
        case neq_op:
            exit = (v1c != v2c);
            break;
        case b_op:
            exit = (v1c > v2c);
            break;
        case s_op:
            exit = (v1c < v2c);
            break;
        case be_op:
            exit = (v1c >= v2c);
            break;
        case se_op:
            exit = (v1c <= v2c);
            break;
        default:
            exit = false;
            break;
        }
        break;
    }
    case Variable_types::CHAR:
    case Variable_types::STR:
    {
        std::string v1c = *static_cast<std::string*>(v1->data);
        std::string v2c = *static_cast<std::string*>(v2->data);

        switch (op_data.find(op)->second)
        {
        case eq_op:
            exit = (v1c == v2c);
            break;
        case neq_op:
            exit = (v1c != v2c);
            break;
        case b_op:
            exit = (v1c > v2c);
            break;
        case s_op:
            exit = (v1c < v2c);
            break;
        case be_op:
            exit = (v1c >= v2c);
            break;
        case se_op:
            exit = (v1c >= v2c);
            break;
        default:
            exit = false;
            break;
        }
        break;
    }  
    case Variable_types::FLOAT:
    {
        long double v1c = *static_cast<long double*>(v1->data);
        long double v2c = *static_cast<long double*>(v2->data);

        switch (op_data.find(op)->second)
        {
        case eq_op:
            exit = (std::abs(v1c - v2c) < epsilon);
            break;
        case neq_op:
            exit = (std::abs(v1c - v2c) > epsilon);
            break;
        case b_op:
        case be_op:
            exit = (v1c > v2c);
            break;
        case s_op:
        case se_op:
            exit = (v1c < v2c);
            break;
        default:
            exit = false;
            break;
        }
        break;
    }
    default:
        exit = false;
        break;
    }

    if (v1_created) delete v1;
    if (v2_created) delete v2;
    return exit;
}

std::pair<bool, exit_status> Compiler::check(line* ln) {
    bool res = true;
    
    int cnt = ln->words.size();

    if (cnt % 4 != 0 || cnt < 4) return { false, exit_status(SYNTAX_ERROR) };

    res = check_expression(ln->words[1], ln->words[2], ln->words[3]);

    for (int i = 4; i < cnt; i++) {
        if (ln->words[i] == "and")
            res &= check_expression(ln->words[i + 1], ln->words[i + 2], ln->words[i + 3]);
        else if (ln->words[i] == "or")
            res |= check_expression(ln->words[i + 1], ln->words[i + 2], ln->words[i + 3]);
        else if (ln->words[i] == "xor")
            res ^= check_expression(ln->words[i + 1], ln->words[i + 2], ln->words[i + 3]);
        else
            return { false, exit_status(SYNTAX_ERROR) };
    }

    return { res, exit_status(OK) };
}

exit_status Compiler::iff(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    std::pair<bool, exit_status> state = this->check(ln);
    if (state.first && !(state.second.error_code)) {
        current_priority++;
    }
    else return state.second;
    return exit_status(OK);
}

variable* Compiler::find_var(std::string name) {
    /*ull hash = get_hash(name);
    auto ptr = variables.find(hash);
    if (ptr != variables.end() && ptr->second->name == name) 
        return static_cast<variable*>(ptr->second);
    return nullptr;*/

    ull hash = get_hash(name);
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->namehash == hash && variables[i]->name == name) return variables[i];
    }
    return nullptr;
}

variable::variable(std::string name, Variable_types type, long long num){
    this->name = name;
    this->type = type;
    this->data = new long long(num);
    this->namehash = get_hash(name);
}

variable::variable(std::string name, Variable_types type, long double num) {
    this->name = name;
    this->type = type;
    this->data = new long double(num);
    this->namehash = get_hash(name);
}

variable::variable(std::string name, Variable_types type, std::string str){
    this->name = name;
    this->type = type;
    this->data = new std::string(str);
    this->namehash = get_hash(name);
}

variable::variable(std::string name, std::string data) {
    this->name = name;
    this->type = check_type(data);
    switch (type)
    {
    case Variable_types::INT:
        this->data = new long long(std::stoll(data));
        break;
    case Variable_types::STR:
        this->data = new std::string(data);
        break;
    case Variable_types::FLOAT:
        this->data = new long double(std::stold(data));
        break;
    case Variable_types::CHAR:
        this->data = new char(data[0]);
        break;
    }
    this->namehash = get_hash(name);
}

variable::~variable(){
    switch (type)
    {
    case Variable_types::INT:
        delete static_cast<long long*>(data);
        break;
    case Variable_types::STR:
        delete static_cast<std::string*>(data);
        break;
    case Variable_types::CHAR:
        delete static_cast<char*>(data);
        break;
    case Variable_types::FLOAT:
        delete static_cast<long double*>(data);
        break;
    }
}

bool var_comp(variable* one, variable* two) {
    return one->name > two->name;
}

#endif 