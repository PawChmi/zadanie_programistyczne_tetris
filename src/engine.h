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




/**
 * Interfejs silnika gry. Odpowiada za kontrolowanie przebiegu rozgrywki, interpretuje wejście konsoli i 
 */
class Engine
{
protected:
    std::string mode = "default";
    int height;
    int width;
    bool end = false;
    int level=1;
    int score=0;
    int clock=0;
    int goal = 0;
    std::vector<std::shared_ptr<Block>> blockSet;
    std::queue<std::shared_ptr<Block>> blockQueue;
    bool fallenUpdate=false;
    bool held=false;
    int ** field;
    std::shared_ptr<Block> activePiece=nullptr;
    std::shared_ptr<Block>  nextPiece=nullptr;
    std::shared_ptr<Block> ghostPiece=nullptr;
    std::shared_ptr<Block>  holdPiece=nullptr;
    Console * ConsolePointer;
    int scanLine ( int y ) noexcept;
    virtual bool collisionCheck ( Block &b ) noexcept;
    virtual void petrify() noexcept;
    virtual void clearLine ( int y ) noexcept;
    void scanLines() noexcept;
    void shuffle() noexcept;
    void scoreIncrease ( const int n ) noexcept;
    void clearField() noexcept;
    virtual void gravity() noexcept;
    virtual void ghostDrop() noexcept;
    void drawField() noexcept;
    virtual void spawn() noexcept;
    void Left() noexcept;
    void Right() noexcept;
    void incrementClock ( int ammount=DEFAULT_TIME_ADDED ) noexcept;
    virtual void SoftDrop() noexcept;
    virtual void HardDrop() noexcept;
    void RotateL() noexcept;
    void RotateR() noexcept;
    void Hold() noexcept;
    void drawPiece() noexcept;
    void drawSide() noexcept;
    bool fallen() noexcept;
    void GiveUp() noexcept
    {
        end = true;
    }
public:
    bool step() noexcept;
    std::string getMode() const noexcept{
        return mode;
    }
    int getScore() const noexcept
    {
        return score;
    }
    Engine ( Console & c,  std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h=20, int lvl = 1 ) noexcept;
    virtual ~Engine() noexcept; 

};



