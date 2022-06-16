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
#include "block_shapes.h"
#include "alphabet.h"





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
    std::vector<std::shared_ptr<Block>> blockSet;
    std::queue<std::shared_ptr<Block>> blockQ;
    bool fallenUpdate=false;
    bool held=false;
    int ** field;
    std::shared_ptr<Block> activePiece;
    std::shared_ptr<Block>  nextPiece=nullptr;
    std::shared_ptr<Block> ghostPiece;
    std::shared_ptr<Block>  holdPiece=nullptr;
    Console * ConsolePointer;
    int scanLine ( int y );
    virtual bool collisionCheck ( Block &b );
    virtual void petrify();
    virtual void clearLine ( int y );
    void scanLines();
    void shuffle();
    void scoreIncrease ( int n );
    void clearField();
    void setField ( const int x, const int y, const int val );
    virtual void gravity();
    virtual void ghostDrop();
    void drawField();
    virtual void spawn();
    void Left();
    void Right();
    void incrementClock ( int ammount=DEFAULT_TIME_ADDED );
    virtual void SoftDrop();
    virtual void HardDrop();
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
    virtual std::string getMode();
    int getScore() const noexcept
    {
        return score;
    }
    Engine ( Console & c,  std::vector<std::shared_ptr<Block>> &blockSet, int w=10, int h=20, int lvl = 1 );
    virtual ~Engine();

};



