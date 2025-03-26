#ifndef ALL_CPP
#define ALL_CPP
#include "../include/all.h"
#include "../include/function.h"

exit_status::exit_status(int erc){
    this->error_code = erc;
}

bool line::empty() {
    return !bool(words.size());
}

line::line(std::string& str) {

    int cnt = 0;
    int pos = 0;
    while ((str[pos] == ' ' || str[pos] == '\t') && pos < str.size()) {
        if (str[pos] == ' ') cnt++;
        if (str[pos] == '\t') cnt += 4;
        pos++;
    }

    priority = cnt / 4;

    str.push_back(' ');
    std::string cur;
    for (int i = pos; i < str.length(); i++) {
        if (str[i] == ' ') {
            if (!cur.empty()) {
                words.push_back(cur);
                cur.clear();
            }
        }
        else {
            cur.push_back(str[i]);
        }
    }
}

func::func(std::string& name, ull line) {
    this->name = name;
    this->namehash = get_hash(name);
    this->place = line;
}

ull data::cur_line() {
    return this->lines.size();
}

data::data(){

    #ifdef DEBUG
    std::cout << "Data construct\n";
    #endif

    this->lines = std::vector<line*>(0);
    this->places = std::vector<struct func>(0);
    this->variables = std::vector<glvar>(0);
}

#endif