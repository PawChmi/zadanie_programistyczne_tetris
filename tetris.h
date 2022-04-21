#ifndef TETRIS_H
#define TETRIS_H
#define DEFAULT_TIME_ADDED 100
#include <utility>
#include <string>
#include <queue>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include "consoles/console.h"
typedef std::pair<double, double> coords;
enum blockType { //this one is just used for colors
    n = 0,
    l = 1,
    j = 2,
    s = 3,
    z = 4,
    t = 5,
    i = 6,
    o = 7
};



class tile {
public:
    double x;
    double y;
    void swap();
    void negateX();
};

class block {
    blockType shape = n;
    bool ghost = false;
    short int rotation;

protected:
    
    coords center={0,0};
    std::vector<tile> tiles;
public:
    block(int x=0, int y=0, blockType s=n);
    virtual ~block();
    int countBlocks();
    void set(int x, int y);
    virtual void move(int x, int y);
    virtual void rotate(bool clockWise);
    void draw(console* disp);
    void draw(console* disp, int x, int y);
    virtual void makeGhost();
    std::vector<std::pair<int, int>> getTileCoords();
    virtual blockType getShape();
    int getX();
    int getY();
};

class block_L : public block{
public:
    block_L(int x =0, int y = 0):block(x,y,l){
        tiles={ {0, 0}, {-1, 1}, {-1,0},{1,0}};
    };
};
class block_J : public block{
public:
    block_J(int x =0, int y = 0):block(x,y,j){
            tiles= {{0, 0},{1,0},{-1,0},{1,1}};
    };
};
class block_O : public block{
public:
    block_O(int x =0, int y = 0) : block(x, y, o)  {
        tiles = {{-0.5,-0.5},{0.5, -0.5},{-0.5,0.5},{0.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};
class block_S : public block{

public:
    block_S(int x =0, int y = 0)   : block(x,y,s)
    {

    tiles={ {1,0}, {0,1},{-1,1},{0,0}};
    };
};
class block_Z : public block{

public:
    block_Z(int x =0, int y = 0):block(x,y,z){
         tiles = {{0,0},{-1,0}, {0, 1},{1,1}};
    };
};
class block__ : public block{

public:
    block__(int x =0, int y = 0):block(x,y,z){
         tiles = {{1,0}};
    };
};
class block_I : public block{
public:
    block_I(int x =0, int y = 0):block(x,y,i){
            
    tiles ={ {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}};
    center = {x+0.5, y+0.5};
    };
};
class block_II : public block{
public:
    block_II(int x =0, int y = 0):block(x,y,i){
            
    tiles ={ {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}, {2.5,0.5}, {-2.5,0.5}, {-3.5,0.5},{3.5,0.5}};
    center = {x+0.5, y+0.5};
    };
};
class block_T : public block{
public:
    block_T(int x =0, int y = 0):block(x,y,t){
        tiles ={ {0,0}, {1,0}, {-1,0},{0,1}};
    };
};


class engine {
    int level=1;
    int score=0;
    int clock=0;
    int height;
    int width; 
    int goal = 0;
    bool end = false;
    std::queue<std::shared_ptr<block>> blockQ;
    bool fallenUpdate=false;
    
    blockType next=n;
    bool held=false;
    int ** field;
  //  int field[fieldHeight][fieldWidth];
    
    std::shared_ptr<block> activePiece;
    std::shared_ptr<block>  nextPiece=nullptr;
    std::shared_ptr<block> ghostPiece;
    std::shared_ptr<block>  holdPiece=nullptr;
    console * conptr;
    int scanLine(int y);
    bool collisionCheck(block &b);
    void petrify();
    void clearLine(int y);
    void scanLines();
    void shuffle();
    void scoreIncrease(int n);
    void clearField();
    void setField(const int x, const int y, const int val);
    void gravity();
    void ghostDrop();
    void drawField();
    void spawn(const blockType s);
    void spawn();
    void Left();
    void Right();
    void incrementClock(int ammount=DEFAULT_TIME_ADDED);
    void SoftDrop();
    void HardDrop();
    void RotateL();
    void RotateR();
    void Hold();
    void drawPiece();
    void drawSide();
    void reset();
    bool fallen();
    void GiveUp();
public:
    bool work();
    int getScore();
    engine(console & c, int w=10, int h=20, int lvl = 1);
    ~engine();
    
};

#endif // TETRIS_H
