#pragma once
#include "consoles/console.h"
#include "tetris.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>


/** 
 * Ta klasa to jakby gałka do wybierania wartości, z górnym i dolnym ograniczeniem 
 */
class dial {
    int value;
    int max;
    int min;
public:
    dial(int val=0, int max=0, int min = 0): value(val),max(max),  min(min){};
    void turnUp();
    void turnDown();
    void operator++(int){
        turnUp();
    }
    void operator--(int){
        turnDown();
    }
    int val();
    operator int(){
        return value;
    }
    
};

class menu{
    dial choice, gamemode, lvl, width, height;
    console * conptr;
    int animation_frame;
    const int colors[6] = {4, 2, 3, 6,  1, 5};
    std::map<int, std::string> scores;
    const std::vector<std::vector<int>>logo = {
        {-12,1,0},//T
        {-11,1,0},
        {-10,1,0},
        {-11,2,0},
        {-11,3,0},
        {-11,4,0},
        {-11,5,0},
        {-8,1,1},//E
        {-7,1,1},
        {-6,1,1},
        {-8,2,1},
        {-8,3,1},
        {-7,3,1},
        {-8,4,1},
        {-8,5,1},
        {-7,5,1},
        {-6,5,1},
        {-4,1,2},//T
        {-3,1,2},
        {-2,1,2},
        {-3,2,2},
        {-3,3,2},
        {-3,4,2},
        {-3,5,2},
        {0,1,3}, //R
        {1,1,3}, 
        {0,2,3}, 
        {2,2,3}, 
        {0,3,3}, 
        {1,3,3}, 
        {0,4,3}, 
        {2,4,3}, 
        {0,5,3}, 
        {2,5,3}, 
        {5,1,4},//I 
        {5,3,4}, 
        {5,4,4}, 
        {5,5,4}, 
        {8,1,5},//S 
        {9,1,5}, 
        {10,1,5}, 
        {8,2,5}, 
        {8,3,5}, 
        {9,3,5}, 
        {10,3,5}, 
        {10,4,5}, 
        {8,5,5}, 
        {9,5,5}, 
        {10,5,5}     
        
    };
    void draw();
    void configureKeyBinds();
public:
    std::shared_ptr<engine> result();
    menu(console & c);
    ~menu();
    void record(int score, std::string name);
};


