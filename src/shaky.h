#pragma once
#include "engine.h"
#include <time.h>
class Shaky : public Engine {
private: 
    int shake(int x){
        int t = (x-3)/3;
        return t*t*t;
    }
protected:
    virtual void gravity()
    {
        int sh = shake(rand()%7);
        activePiece->move ( 0, 1 );
        if ( collisionCheck ( *activePiece ) ) {
            activePiece->move ( 0, -1 );
            petrify();
        }
        activePiece->move ( sh, 0 );
        if ( collisionCheck ( *activePiece ) ) {
            activePiece->move ( -sh , 0 );
        }
        ghostDrop();
    }
    void SoftDrop()
    {
        int sh = shake(rand()%7);
        activePiece->move ( sh, 1 );
        if ( collisionCheck ( *activePiece ) ) activePiece->move ( -sh, -1 );
        incrementClock ( DEFAULT_TIME_ADDED/4 );
        ghostDrop();

    }
    
     virtual void spawn()
    {
        Engine::spawn();
        activePiece->move(width/2-1, -2);
        ghostDrop();
    }
public:
        Shaky (  Console &c, std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h = 20, int lvl=1 ) : Engine ( c, blockSet, w, h, lvl )
        {
            
            c.print ( "GameMode: Shaky" );
            std::queue<std::shared_ptr<Block>> empty;
            std::swap ( blockQ, empty );
            shuffle();
            spawn();
            spawn();
            srand((unsigned)time(NULL));
        };


    };
