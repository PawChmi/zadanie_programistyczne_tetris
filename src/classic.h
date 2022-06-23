#pragma once
#include "engine.h"

/**
 * Klasyczny wariant gry
 */
class Classic : public Engine
{
protected:
    virtual void spawn() noexcept
    {
        Engine::spawn();
        activePiece->move(width/2-1, -2);
        ghostDrop();
    }
public:
    Classic (  Console &c, std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h = 20, int lvl=1 ) noexcept : Engine ( c, blockSet, w, h, lvl )
    {
        c.print ( "GameMode: Classic" );
        mode = "[c]";
        std::queue<std::shared_ptr<Block>> empty;
        std::swap ( blockQueue, empty );
        shuffle();
        spawn();
        spawn();
    };

};
