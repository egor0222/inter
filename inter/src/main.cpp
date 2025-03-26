
#include <cstdio>
#include "../include/all.h"
#include "../include/function.h"
#include "../include/compiler.h"
#include "../include/build.h"

std::string mpath = "/home/egor/Документы/compdata/main.txt";

int main(int argc, char** argv) {
    setlocale(LC_ALL, "rus");

    std::vector<std::string>params = convert_args(argc, argv);
    #ifdef DEBUG
    std::cout << "DEBUG activated\n";
    int pos = 1;
    for (int i = 0; i < params.size(); i++){
        std::cout << params[i] << std::endl;
    }
    #endif

    if (params.size() < 2) {
        std::cout << "No args\n";
        return 0;
    }

    if (params[1] == "help"){
        std::cout << "help called\n";
        printfile("help.txt");
        return 0;
    }

    if (params[1] == "version"){
        std::cout << "comp version: 0.0.1\n";
        return 0;
    }
    
    std::cout << "________________\n";
    std::cout << mpath << std::endl;

    //data all;

    data* all = new data;

    #ifdef DEBUG
    std::cout << "Data created: " << (int*)(all) << '\n';
    #endif

    //main_build(mpath, &all);
    main_build(mpath, all);

    #ifdef DEBUG
    if (all->lines.size() == 0){
        std::cout << "Build failed\n";
        return 0;
    }
    else {
        std::cout << "Build ok\n";
    }
    #endif

    //printdata(&all);
    printdata(all);
/*
    ull start = find_main(&all);

    Compiler comp(&all);
*/
}


/*

int a = 1280000;
while(a--)

*/

// 120 

// 32 