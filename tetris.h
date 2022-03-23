#ifndef TETRIS_H
#define TETRIS_H
#define DEFAULT_TIME_ADDED 100
#include <utility>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>
#include "consoles/console.h"
typedef std::pair<double, double> coords;
enum blockType {
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
    blockType shape;
    bool ghost = false;
    coords center;
    tile tileD;
    tile tileA;
    tile tileB;
    tile tileC;
    short int rotation;
    
public:
    void set(int x, int y, blockType s);
    void move(int x, int y);
    void rotate(bool clockWise);
    void draw(display disp);
    void makeGhost();
    std::pair<int, int>* getTileCoords();
    blockType getShape();
    int getX();
    int getY();
};
class engine {
    int level=1;
    int score=0;
    int clock=0;
    int height;
    int width; 
    int goal = 0;
    bool end = false;
    std::queue<blockType> blockQ;
    bool fallenUpdate=false;
    blockType holder=n;
    blockType next=n;
    bool held=false;
    int ** field;
  //  int field[fieldHeight][fieldWidth];
    
    block activePiece;
    block nextPiece;
    block ghostPiece;
    block holdPiece;
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
public:
    void drawField(display disp);
    void spawn(const blockType s);
    void spawn();
    int getScore();
    void left();
    void right();
    void incrementClock(int ammount=DEFAULT_TIME_ADDED);
    void softdrop();
    void harddrop();
    void rotateL();
    void rotateR();
    void hold();
    void drawPiece(display o);
    void drawSide(display o);
    void reset();
    bool fallen();
    bool ended();
    void giveUp();
    engine(console & c, int w=10, int h=20, int lvl = 1);
    ~engine();
    
};

#endif // TETRIS_H
