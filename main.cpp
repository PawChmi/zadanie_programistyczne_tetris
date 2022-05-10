#include "tetris.h"

#include "menu.h"
#include "consoles/console.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <memory>




int main(int argc, char* argv[]) {

    console con("kb.txt");

    menu m(con);

    std::shared_ptr<engine> game;
    
    while(true){
        game = m.result();
        if(game == nullptr)return 0;

        while(game->work()) {
            //absolutely nothing has to happen here, it's just a loop.
        }
        con.clear();
        std::cout << game->getScore()<<"\n";
        game = nullptr;
        
    }
    return 0;
}
