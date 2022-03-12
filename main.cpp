#include "tetris.h"
#include "consoles/console_u8.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>



int main(int argc, char* argv[]){
    console con;
    engine game;
    //blockType blocks[7] = {s,z,t,i,o,l,j};
    bool gameloop = true;
    
    con.in.setTimeout(100);
    game.spawn();
    game.drawField(con.out);
    game.drawSide(con.out);
    while(gameloop){
        int ch = con.in.getInput();
        if(ch ==27){
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
        }else if(ch=='p'){
            bool pauseloop = true;
            con.out.move(con.out.getWidth()/2-3, fieldHeight/2);
            con.out.print("PAUSED");
            while(pauseloop){
                
                ch = con.in.getInput();
                if(ch=='p')pauseloop = false;
            }
        }else if(ch==' '){
            game.harddrop();
        }else if(ch=='s'){
            game.softdrop();
        }else if(ch=='d'){
            game.right();
        }else if(ch=='r'){
            con.out.clear();
            con.out.resize();
        }else if(ch=='f'){
            game.hold();
            game.drawSide(con.out);
        }else if(ch=='q'){
            game.rotateL();
        }else if(ch=='e'){
            game.rotateR();
        }else if(ch == -1){
            game.incrementClock();
        }
        game.drawField(con.out);
        game.drawPiece(con.out);
        if(game.fallen()){
            game.spawn();
            game.drawSide(con.out);
        }
        
    }
    
    con.close();
    return 0;
}
