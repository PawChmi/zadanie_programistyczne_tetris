#include "tetris.h"
#include "consoles/console.h"
#include <cstdlib>
#include <iostream>
#include <ctime>



int main(int argc, char* argv[]){

    console con;
    
    
    //blockType blocks[7] = {s,z,t,i,o,l,j};
    
    con.in.setTimeout(100);
    engine game(con, 10, 20, 2);
    //game.spawn();
    game.drawSide(con.out);
    while(!game.ended()){
        game.drawField(con.out);
        game.drawPiece(con.out);
        int ch = con.in.getInput();
        if(ch ==27){
            game.giveUp();
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
            con.out.move(con.out.getWidth()/2-3, 10);
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

        if(game.fallen()){
            game.spawn();
            game.drawSide(con.out);
        }
        
    }
    std::cout << game.getScore();
    
    return 0;
}
