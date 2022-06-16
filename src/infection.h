#pragma once
#include "engine.h"



class Infection : public Engine{
    int choice = 5;
    void Infect(){
        if(end) return;
        end = true;
        for(int y = 0; y < height;++y){
            for(int x = 0; x < width;++x){
                if(field[y][x] == 3){
                    if(y>0 and field[y-1][x]>3)field[y-1][x] = 2;
                    if(y<height-1 and field[y+1][x]>3)field[y+1][x] = 2;
                    if(x>0 and field[y][x-1]>3)field[y][x-1] = 2;
                    if(x<width-1 and field[y][x+1]>3)field[y][x+1] = 2;
                }else if(field[y][x] == 4 or field[y][x] == 2) end = false;
                
            }
        }
        drawField();
        ConsolePointer->wait();
        for(int y = 0; y < height;++y){
            for(int x = 0; x < width;++x){
                if(field[y][x] == 2)field[y][x]=3;
                
            }
        }
        drawField();
       
        
    }
protected:
    
void petrify()
{
    Engine::petrify();
    Infect();
    if(end){ 
        end = false;
        for(int x = 0; x < width;++x){
            if(field[height-1][x])end = true;
           
        } 
    }
    
}


    void spawn()
    {
        Engine::spawn();
        activePiece->move(width/2-1, -2);
        if(choice==0)nextPiece->setShape(l);
        else if(choice < 3)nextPiece->setShape(s);
        else nextPiece->setShape(z);
        choice = rand()%10;
        
        ghostDrop();
    }
public:
    Infection ( Console &c, std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h = 20, int lvl=1 ) : Engine ( c, blockSet, w, h, lvl )
    {
        c.print ( "GameMode: Infection" );
        std::queue<std::shared_ptr<Block>> empty;
        std::swap ( blockQ, empty );
        shuffle();
        spawn();
        spawn();
        activePiece->setShape(z);
    };
};
