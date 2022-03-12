#ifndef console_ASCII_H
#define console_ASCII_H
#define fieldWidth 10
#define fieldHeight 20
#include <curses.h>
#include <string>

class display {
    int height;
    int width;
    int offsetX=0;
    int offsetY=-1;
public:
    void drawTile(int x, int y, int color);
    void drawEmpty(int x, int y, int w=1, int h=1);
    void clear(int x, int y, int w=1, int h=1);
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

#endif // console_ASCII_H
