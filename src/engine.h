#pragma once
#define DEFAULT_TIME_ADDED 100
#include <utility>
#include <string>
#include <queue>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include "console.h"
#include "tile.h"
#include "block.h"
#include "block_shapes.h"





class Engine
{
protected:
    int height;
    int width;
    bool end = false;
    int level=1;
    int score=0;
    int clock=0;
    int goal = 0;
    std::queue<std::shared_ptr<block>> blockQ;
    bool fallenUpdate=false;
    bool held=false;
    int ** field;
    std::shared_ptr<block> activePiece;
    std::shared_ptr<block>  nextPiece=nullptr;
    std::shared_ptr<block> ghostPiece;
    std::shared_ptr<block>  holdPiece=nullptr;
    console * conptr;
    int scanLine ( int y );
    bool collisionCheck ( block &b );
    void petrify();
    void clearLine ( int y );
    void scanLines();
    virtual void shuffle();
    void scoreIncrease ( int n );
    void clearField();
    void setField ( const int x, const int y, const int val );
    void gravity();
    void ghostDrop();
    void drawField();
    void spawn();
    void Left();
    void Right();
    void incrementClock ( int ammount=DEFAULT_TIME_ADDED );
    void SoftDrop();
    void HardDrop();
    void RotateL();
    void RotateR();
    void Hold();
    void drawPiece();
    void drawSide();
    bool fallen();
    void GiveUp()
    {
        end = true;
    }
public:
    bool work();
    int getScore() const noexcept
    {
        return score;
    }
    Engine ( console & c, int w=10, int h=20, int lvl = 1 );
    virtual ~Engine();

};



