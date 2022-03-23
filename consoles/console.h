#ifndef console_H
#define console_H


#include <string>

class display {
    int height;
    int width;
    int offsetX=0;
    int offsetY=-1;
    int gameFieldWidth=0;
    int gameFieldHeight=0;
public:
    void printData(int scr, int lvl, int goal);
    void drawTile(int x, int y, int color, bool ghost=false);
    void drawEmpty(int x, int y, int w=1, int h=1);
    void clear(int x, int y, int w=1, int h=1);
    void clear();
    void resize();
    void setGameField(int w, int h);
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
    ~console();
};

#endif // console_ASCII_H
