#ifndef console_H
#define console_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>


enum key {
    NONE = -1,
    UNKNOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    DROP = 3,
    HARDDROP = 4,
    ROT_L = 5,
    ROT_R = 6,
    HOLD = 7,
    PAUSE = 8,
    QUIT = 9,
    REFRESH = 10
    
};

class console {
    bool pressed;
    std::map<int, key> bindings;
    int lastInput=0;
    int height;
    int width;
    int offsetX=0;
    char ** field;
    int offsetY=-1;
    int gameFieldWidth=0;
    int gameFieldHeight=0;
    void clear_abs(int x, int y, int w=1, int h=1);
public:
    
    
    console();
    console(std::string keybind_filename);
    ~console();
    key getInput();
    void wait();
    void setTimeout(int delay);
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
    std::string prompt(std::string question);
    void printCenter(std::string s, int y, bool h=false);

    void print_highlight(std::string s);
};


#endif // console_ASCII_H
