/** 
 * @file tetris
 * @authors Paweł Chmielewski
 */
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
    std::cout << " -t <0-4>\t set theme" << std::endl;
    
}

bool parse_arguments(int argc, char* argv[], std::string& kb_file_name, int &t){
    for (int i = 1; i < argc; i++) {
        if (not strcmp(argv[i], "-k")) { //key binds file
            kb_file_name = argv[i + 1];
        }
        else if (not strcmp(argv[i], "-h")) { //help message
            helpMessage();
            return true;
        }
        else if (not strcmp(argv[i], "-t")) { //unicode mode
            t = argv[++i][0]-'0';
        }

        
    }
    return false;
}


int main(int argc, char* argv[]) {
    std::string kb_file_name="";
    int theme;
    if(parse_arguments(argc, argv, kb_file_name, theme)) return 1; //exit due to help helpMessage
    Console con(kb_file_name);

    std::shared_ptr<Engine> game;
        Menu menu(con, theme);
    
        while(true){
            game = menu.result();
            if(game == nullptr){
                return 0;
            }

            while(game->work()) {
                //absolutely nothing has to happen here, it's just a loop.
            }
            menu.record(game->getScore(), con.prompt(" What is your name?  ", 10),game->getMode());
        
            con.clear();
            
            game = nullptr;
            
        }
    
    
    return 0;
}
