#include "tetris.h"

#include "menu.h"
#include "consoles/console.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <memory>




int main(int argc, char* argv[]) {

    console con("kb.txt");

    menu m(con);
    std::ofstream test;
    test.open("test.txt");
    std::shared_ptr<engine> game;
    
    while(true){
        game = m.result();
        if(game == nullptr){
            test.close();
            return 0;
        }

        while(game->work()) {
            //absolutely nothing has to happen here, it's just a loop.
        }
        m.record(game->getScore(), con.prompt(" What is your name?  "));
       
        con.clear();
        
        game = nullptr;
        
    }
    
    return 0;
}
