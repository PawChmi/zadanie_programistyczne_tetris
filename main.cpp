#include "tetris.h"
#include <ncurses.h>




int main(int argc, char* argv[]){
    console con;
    engine game;
    bool gameloop = true;
    
    con.in.setTimeout(200);
    game.drawField(con.out);
    while(gameloop){
        int ch = con.in.getInput();
        if(ch =='q'){
            gameloop = 0;
        }else if(ch=='1'){
            game.spawn(l);
        }else if(ch=='2'){
            game.spawn(j);
        }else if(ch=='3'){
            game.spawn(t);
        }else if(ch=='4'){
            game.spawn(s);
        }else if(ch=='5'){
            game.spawn(z);
        }else if(ch=='6'){
            game.spawn(o);
        }else if(ch=='7'){
            game.spawn(i);
        }else if(ch=='a'){
            game.left();
        }else if(ch=='s'){
            game.down();
        }else if(ch=='d'){
            game.right();
        }else if(ch==','){
            game.rotateL();
        }else if(ch=='.'){
            game.rotateR();
        }else if(ch == -1){
            game.down();
        }
        game.drawField(con.out);
        game.drawPiece(con.out);
        
    }
    
    con.close();
    return 0;
}
