#ifndef TETRIS_H
#define TETRIS_H
#define fieldWidth 10
#define fieldHeight 16
#include <utility>
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
};
class engine {
    int level;
    int score;
    int field[fieldHeight][fieldWidth];
    block activePiece;
    int scanLine(int y);
    bool collisionCheck();
public:
    void clearField();
    void setField(const int x, const int y, const int val);
    void drawField(display disp);
    void clearLine(int y);
    void scanLines();
    void spawn(const blockType s);
    void left();
    void right();
    void down();
    void rotateL();
    void rotateR();
    void drawPiece(display o);
    void reset();
    bool fallen();
    engine();
    
};

#endif // TETRIS_H
