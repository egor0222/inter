#ifndef COMP_MATH_H
#define COMP_MATH_H
#include "../include/function.h"
#include "../include/compiler.h"
#include "../include/all.h"

exit_status Compiler::pl(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);

        bool sec_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (first->type != second->type ||
            first->type != Variable_types::INT ||
            first->type != Variable_types::STR ||
            first->type != Variable_types::FLOAT){
            if (sec_cr) delete second;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }

        if (first->type == Variable_types::INT) {
            *static_cast<long long*>(first->data) += *static_cast<long long*>(second->data);
        }
        else if (first->type == Variable_types::STR) {
            *static_cast<std::string*>(first->data) += *static_cast<std::string*>(second->data);
        }
        else if (first->type == Variable_types::FLOAT) {
            *static_cast<long double*>(first->data) += *static_cast<long double*>(second->data);
        }
        
        if (sec_cr) delete second;
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);

        bool sec_cr = false;
        bool th_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (third == nullptr) {
            third = new variable("", ln->words[3]);
            th_cr = true;
        }
        if (first->type != second->type || second->type != third->type ||
            first->type != Variable_types::INT || 
            first->type != Variable_types::STR || 
            first->type != Variable_types::FLOAT) {
            if (sec_cr) delete second;
            if (th_cr) delete third;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        if (first->type == Variable_types::INT) {
            *static_cast<long long*>(first->data) = *static_cast<long long*>(second->data) + *static_cast<long long*>(third->data);
        }
        else if (first->type == Variable_types::STR) {
            *static_cast<std::string*>(first->data) = *static_cast<std::string*>(second->data) + *static_cast<std::string*>(third->data);
        }

        if (sec_cr) delete second;
        if (th_cr) delete third;
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::mn(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);

        bool sec_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (first->type != second->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) -= *static_cast<long long*>(second->data);

        if (sec_cr) delete second;
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);

        bool sec_cr = false;
        bool th_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (third == nullptr) {
            third = new variable("", ln->words[3]);
            th_cr = true;
        }
        if (first->type != second->type || second->type != third->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            if (th_cr) delete third;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) = *static_cast<long long*>(second->data) - *static_cast<long long*>(third->data);

        if (sec_cr) delete second;
        if (th_cr) delete third;
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::ml(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);

        bool sec_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (first->type != second->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) *= *static_cast<long long*>(second->data);

        if (sec_cr) delete second;
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);

        bool sec_cr = false;
        bool th_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (third == nullptr) {
            third = new variable("", ln->words[3]);
            th_cr = true;
        }
        if (first->type != second->type || second->type != third->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            if (th_cr) delete third;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) = *static_cast<long long*>(second->data) * *static_cast<long long*>(third->data);

        if (sec_cr) delete second;
        if (th_cr) delete third;
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);

}

exit_status Compiler::dv(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);

        bool sec_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (first->type != second->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) -= *static_cast<long long*>(second->data);

        if (sec_cr) delete second;
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);

        bool sec_cr = false;
        bool th_cr = false;

        if (first == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (second == nullptr) {
            second = new variable("", ln->words[2]);
            sec_cr = true;
        }
        if (third == nullptr) {
            third = new variable("", ln->words[3]);
            th_cr = true;
        }
        if (first->type != second->type || second->type != third->type ||
            first->type != Variable_types::INT) {
            if (sec_cr) delete second;
            if (th_cr) delete third;
            return exit_status(VAR_TYPES_NOT_CONNECT);
        }
        *static_cast<long long*>(first->data) = *static_cast<long long*>(second->data) / *static_cast<long long*>(third->data);

        if (sec_cr) delete second;
        if (th_cr) delete third;
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);

}

exit_status Compiler::per(line* ln) {
    if (ln->priority != current_priority) return exit_status(SYNTAX_ERROR);
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        if (first == nullptr || second == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr %= *(long long*)(second->data);
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);
        if (first == nullptr || second == nullptr || third == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr = *(long long*)(second->data) % *(long long*)(third->data);
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}


#endif