#pragma once
#include "engine.h"


class classic : public Engine
{
protected:
    void shuffle()
    {
        std::vector<std::shared_ptr<block>> blocks= {
            std::make_shared<block_I> ( ( width/2 )-1,-3 ),
            std::make_shared<block_J> ( ( width/2 )-1,-3 ),
            std::make_shared<block_O> ( ( width/2 )-1,-3 ),
            std::make_shared<block_L> ( ( width/2 )-1,-3 ),
            std::make_shared<block_S> ( ( width/2 )-1,-3 ),
            std::make_shared<block_Z> ( ( width/2 )-1,-3 ),
            std::make_shared<block_T> ( ( width/2 )-1,-3 ),
        };
        std::shuffle ( std::begin ( blocks ), std::end ( blocks ), std::default_random_engine ( time ( NULL ) ) );
        for ( auto b : blocks ) {
            blockQ.push ( b );
        }
    }
public:
    classic ( console &c, int w=10, int h = 20, int lvl=1 ) : Engine ( c, w, h, lvl )
    {
        c.print ( "GameMode: Classic" );
        std::queue<std::shared_ptr<block>> empty;
        std::swap ( blockQ, empty );
        classic::shuffle();
        spawn();
        spawn();
    };

};
class justice : public Engine
{
protected:
    void shuffle()
    {
        std::vector<std::shared_ptr<block>> blocks= {
            std::make_shared<block_T> ( ( width/2 )-1,-3 ),
        };
        std::shuffle ( std::begin ( blocks ), std::end ( blocks ), std::default_random_engine ( time ( NULL ) ) );
        for ( auto b : blocks ) {
            blockQ.push ( b );
        }
    }
public:
    justice ( console &c, int w=10, int h = 20, int lvl=1 ) : Engine ( c, w, h, lvl )
    {
        c.print ( "GameMode: Justice" );
        std::queue<std::shared_ptr<block>> empty;
        std::swap ( blockQ, empty );
        justice::shuffle();
        spawn();
        spawn();
    };

};
class ludicrous : public Engine
{
protected:
    void shuffle()
    {
        std::vector<std::shared_ptr<block>> blocks= {
            std::make_shared<block_E> ( ( width/2 )-1,-3 ),
            std::make_shared<block_F> ( ( width/2 )-1,-3 ),
            std::make_shared<block_O_offcenter> ( ( width/2 )-1,-3 ),
        };
        std::shuffle ( std::begin ( blocks ), std::end ( blocks ), std::default_random_engine ( time ( NULL ) ) );
        for ( auto b : blocks ) {
            blockQ.push ( b );
        }
    }
public:
    ludicrous ( console &c, int w=10, int h = 20, int lvl=1 ) : Engine ( c, w, h, lvl )
    {
        c.print ( "GameMode: Ludicrous" );
        std::queue<std::shared_ptr<block>> empty;
        std::swap ( blockQ, empty );
        ludicrous::shuffle();
        spawn();
        spawn();
    };

};
