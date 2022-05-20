#include "engine.h"

#include "menu.h"
#include "console.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <memory>


void helpMessage(){
    std::cout << "This is a console based tetris game" << std::endl<< std::endl;
    
    std::cout << "OPTIONS:" << std::endl;
    std::cout << " -k <filename> \tto use custom key binds specified in a file" << std::endl;
    std::cout << " -h \t display this help message" << std::endl;
    std::cout << " -r \t reverse the color theme (only applies to block and ghost block)" << std::endl;
    std::cout << " -u \t use unicode characters" << std::endl;
    
}

bool parse_arguments(int argc, char* argv[], std::string& kb_file_name, bool &u, bool &r){
    for (int i = 1; i < argc; i++) {
        if (not strcmp(argv[i], "-k")) { //key binds file
            kb_file_name = argv[i + 1];
        }
        else if (not strcmp(argv[i], "-h")) { //help message
            helpMessage();
            return true;
        }
        else if (not strcmp(argv[i], "-u")) { //unicode mode
            u = 1;
        }
        else if (not strcmp(argv[i], "-r")) { //reversed colors
            r = 1;
        }
        
    }
    return false;
}


int main(int argc, char* argv[]) {
    std::string kb_file_name="";
    bool unicode=0, reversed=0;
    if(parse_arguments(argc, argv, kb_file_name, unicode, reversed)) return 1; //exit due to help helpMessage
    console con(kb_file_name, unicode, reversed);

    menu m(con, 2*unicode+reversed);
    std::shared_ptr<Engine> game;
    while(true){
        game = m.result();
        if(game == nullptr){
            return 0;
        }

        while(game->work()) {
            //absolutely nothing has to happen here, it's just a loop.
        }
        m.record(game->getScore(), con.prompt(" What is your name?  ", 10));
       
        con.clear();
        
        game = nullptr;
        
    }
    
    return 0;
}
