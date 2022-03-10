#include "tetris.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>



int main(int argc, char* argv[]){
    console con;
    engine game;
    blockType blocks[7] = {s,z,t,i,o,l,j};
    bool gameloop = true;
    srand( time( NULL ) );
    con.in.setTimeout(200);
    game.drawField(con.out);
    game.spawn(blocks[rand()%7]);
    while(gameloop){
        int ch = con.in.getInput();
        if(ch ==27){
            gameloop = 0;
        }else if(ch=='1'){
            game.spawn(l);
        }else if(ch=='r'){
            game.spawn(blocks[rand()%7]);
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
        }else if(ch==' '){
            game.harddrop();
        }else if(ch=='s'){
            game.softdrop();
        }else if(ch=='d'){
            game.right();
        }else if(ch=='q'){
            game.rotateL();
        }else if(ch=='e'){
            game.rotateR();
        }else if(ch == -1){
            game.gravity();
        }
        game.drawField(con.out);
        game.drawPiece(con.out);
        if(game.fallen()){
            game.spawn(blocks[rand()%7]);
            con.out.move((con.out.getWidth()/2)+fieldWidth+2, 2);
            con.out.print("Score:"+std::to_string(game.getScore()));
        }
        
    }
    
    con.close();
    return 0;
}
