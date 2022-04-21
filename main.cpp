#include "tetris.h"
#include "consoles/console.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <memory>




int main(int argc, char* argv[]) {

    console con("kb.txt");


    bool ext = 1;
    con.setTimeout(100);
    while(ext){
        std::unique_ptr<engine> game(new engine(con, 10, 20));
        while(game->work()) {
            //absolutely nothing has to happen here, it's just a loop.
        }
        std::cout << game->getScore()<<"\n";
        }
        if(con.getInput() == QUIT)ext = 0;
    return 0;
}
