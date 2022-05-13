#ifndef console_H
#define console_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>


struct Font{
    bool reversed = 1;
    std::string empty = "[]";
    std::string ghost = "[]";
    std::string block = "  ";
    std::string hLine = "-";
    std::string vLine = "|";
    std::string corNW = "+";
    std::string corNE = "+";
    std::string corSW = "+";
    std::string corSE = "+";

};

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
    Font font;
    
    void clear_abs(int x, int y, int w=1, int h=1);
public:
    
    
    console();
    console(const std::string keybind_filename, const bool unicode = false, const bool reverse = false);
    ~console();
    key getInput();
    void wait();
    void setTimeout(int delay);
    void printData(int scr, int lvl, int goal);
    void drawTile(int x, int y, int color, bool ghost=false);
    void drawEmpty(int x, int y, int w=1, int h=1);
    void clear(const int x, const int y, const int w=1, const int h=1);
    void clear();
    void resize();
    void setGameField(const int w, const int h);
    int getWidth();
    int getHeight();
    void move(const int x, const int y);
    void print(const std::string& s);
    std::string prompt(std::string question, int limit = 0);
    int prompt_key(std::string question);
    void printCenter(std::string s, int y, bool h=false);

    void print_highlight(std::string s);
};

#endif // console_ASCII_H