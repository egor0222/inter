#ifndef FUNCTION_CPP
#define FUNCTION_CPP
#include "../include/function.h"
#include "../include/all.h"

std::string main_name = "main";

std::vector<std::string> convert_args(int argc, char** argv){
    std::vector<std::string> res(argc);
    for (int i = 0; i < argc; i++){
        res[i] = std::string(argv[i]);
    }
    return res;
}

int function_name_data(std::string str){
    static const std::unordered_map<std::string, int>func_data{
        {"pl",      codes::pl_code},
        {"mn",      codes::mn_code},  
        {"dv",      codes::dv_code},
        {"ml",      codes::ml_code},
        {"var",     codes::var_code},
        //{"for", 6},
        //{"while", 7},
        //{"return", 8},
        {"if",      codes::if_code},
        //{"else", 10},
        //{"def", 11},
        {"eq",      codes::eq_code},
        {"print",   codes::print_code},
        {"input",   codes::input_code},
        {"per",     codes::per_code},
        {"end",     codes::end_code}
    };
    auto ptr = func_data.find(str);
    if (ptr == func_data.end()) return 0;
    return ptr->second;
}

ull get_hash(std::string& str) {
    const int mn = 3;
    const unsigned long long mod = (ull(1) << 63) + 31;
    unsigned long long res = 0;
    for (int i = 0; i < str.size(); i++) {
        res += (mn * (int)str[i] * (i + 1)) % mod;
    }
    return res;
}

void conv_line(std::string& str, line* result){
    str.push_back(' ');
    std::string cur;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == ' ') {
            if (!cur.empty()) {
                result->words.push_back(cur);
                cur.clear();
            }
        }
        else {
            cur.push_back(str[i]);
        }
    }
}

Variable_types check_type(std::string& str) {
    if (str.front() == '"' && str.back() == '"') return Variable_types::STR;
    else if (str.front() == '\'' && str.back() == '\'' && str.size() == 3)
        return Variable_types::CHAR;
    else if (str.front() >= '0' && str.front() <= '9') {
        int is_dot = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '.') is_dot++;
            else if (str[i] < '0' || str[i] > '9') return Variable_types::NONE;
        }
        if (is_dot == 1) return Variable_types::FLOAT;
        else if (is_dot == 0) return Variable_types::INT;
    }
    return Variable_types::NONE;
}

ull find_main(data* dt) {
    ull pos = 0;
    ull main_hash = get_hash(main_name);
    for (auto& it : dt->places) {
        if (it.namehash == main_hash && it.name == main_name)
            return it.place;
        pos++;
    }
    return ull(-1);
}

void printfile(std::string path){
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        #ifdef DEBUG
        std::cout << "File " << path << " not opened!\n"; 
        #endif
        return;
    }
    #ifdef DEBUG
    else std::cout << "File " << path << " opended!\n";
    #endif
    std::string cur;
    while (!file.eof()){
        getline(file, cur);
        std::cout << cur << '\n';
    }
}

void printdata(data* dt){
    std::cout << "_____LINES_____\n";
    for (auto& it : dt->lines){
        for (int i = 0; i < it->words.size(); i++){
            std::cout << it->words[i] << '\n';
        }
        std::cout << '\n';
    }
    std::cout << "\n_____VARIABLES_____\n";
    for (auto& it : dt->variables){
        std::cout << it.name << ' ' << it.place << '\n';
    }
    std::cout << '\n';
}

#endif