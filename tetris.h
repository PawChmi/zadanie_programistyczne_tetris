#ifndef TETRIS_H
#define TETRIS_H
#define fieldWidth 10
#define fieldHeight 16
#include <utility>
#include <string>
typedef std::pair<double, double> coords;
enum blockType {
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
class display {
    int height;
    int width;
public:
    void drawTile(int x, int y, int color);
    void drawEmpty(int x, int y, int w=1, int h=1);
    void clear();
    void resize();
    int getWidth();
    void move(int x, int y);
    void print(std::string s);
};
class keyboard {
    bool pressed;
    int lastInput=0;
public:
    int getInput();
    void setTimeout(int delay);
};

class console {



public:
    keyboard in;
    display out;
    console();

    void close();
};
class block {
    blockType shape;
    double offset = 1;
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
    std::pair<int, int>* getTileCoords();
    blockType getShape();
    int getY();
};
class engine {
    int level=1;
    int score;
    bool fallenUpdate=false;
    int field[fieldHeight][fieldWidth];
    block activePiece;
    int scanLine(int y);
    bool collisionCheck();
    void petrify();
    void clearLine(int y);
    void scanLines();
public:
    void clearField();
    void setField(const int x, const int y, const int val);
    void drawField(display disp);
    void spawn(const blockType s);
    int getScore();
    void left();
    void right();
    void gravity();
    void softdrop();
    void harddrop();
    void rotateL();
    void rotateR();
    void drawPiece(display o);
    void reset();
    bool fallen();
    engine();
    
};

#endif // TETRIS_H
