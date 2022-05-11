#include "tetris.h"

#include "menu.h"
#include "consoles/console.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <memory>


void helpMessage(){
    std::cout << "This is a console based tetris game" << std::endl;
    std::cout << "use -k <filename> to use custom key binds" << std::endl;
    
}

bool parse_arguments(int argc, char* argv[], std::string& kb_file_name){
    for (int i = 1; i < argc; i++) {
        if (not strcmp(argv[i], "-k")) { //key binds file
            kb_file_name = argv[i + 1];
        }
        else if (not strcmp(argv[i], "-h")) { //help message
            helpMessage();
            return true;
        }
    }
    return false;
}


int main(int argc, char* argv[]) {
    std::string kb_file_name="";
    if(parse_arguments(argc, argv, kb_file_name)) return 1; //exit due to help helpMessage
    console con(kb_file_name);

    menu m(con);
    std::shared_ptr<engine> game;
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
