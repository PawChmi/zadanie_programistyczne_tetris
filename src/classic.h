#pragma once
#include "engine.h"


class Classic : public Engine
{
protected:
    virtual void spawn()
    {
        Engine::spawn();
        activePiece->move(width/2-1, -2);
        ghostDrop();
    }
public:
    Classic (  Console &c, std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h = 20, int lvl=1 ) : Engine ( c, blockSet, w, h, lvl )
    {
        c.print ( "GameMode: Classic" );
        std::queue<std::shared_ptr<Block>> empty;
        std::swap ( blockQ, empty );
        shuffle();
        spawn();
        spawn();
    };
    virtual std::string getMode(){
        return "[C]";
    }
};
