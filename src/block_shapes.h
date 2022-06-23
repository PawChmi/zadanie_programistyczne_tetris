#pragma once
#include "block.h"

//Classic blocks
class block_L : public Block
{
public:
    block_L ( int x =0, int y = 0, blockColor c=blue )noexcept : Block ( x,y,c )
    {
        name = "L";
        tiles= { {0, 0}, {-1, 1}, {-1,0},{1,0}};
    };
};
class block_J : public Block
{
public:
    block_J ( int x =0, int y = 0, blockColor c=orange ) noexcept : Block ( x,y,c )
    {
        name = "J";
        tiles= {{0, 0},{1,0},{-1,0},{1,1}};
    };
};
class block_O : public Block
{
public:
    block_O ( int x =0, int y = 0, blockColor c=yellow ) noexcept : Block ( x, y, c )
    {
        name = "O";
        tiles = {{-0.5,-0.5},{0.5, -0.5},{-0.5,0.5},{0.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};
class block_S : public Block
{

public:
    block_S ( int x =0, int y = 0, blockColor c=green )   : Block ( x,y,c )
    {
        name = "S";
        tiles= { {1,0}, {0,1},{-1,1},{0,0}};
    };
};
class block_Z : public Block
{

public:
    block_Z ( int x =0, int y = 0, blockColor c=red ) noexcept : Block ( x,y,c )
    {
        name = "Z";
        tiles = {{0,0},{-1,0}, {0, 1},{1,1}};
    };
};

class block_I : public Block
{
public:
    block_I ( int x =0, int y = 0, blockColor c=cyan ) noexcept : Block ( x,y,c )
    {

        name = "I";
        tiles = { {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};

class block_T : public Block
{
public:
    block_T ( int x =0, int y = 0, blockColor c=purple ) noexcept : Block ( x,y,c )
    {
        name = "T";
        tiles = { {0,0}, {1,0}, {-1,0},{0,1}};
    };
};

//single cell
class block_dot : public Block
{

public:
    block_dot ( int x =0, int y = 0, blockColor c=none ) noexcept : Block ( x,y,c )
    {
        name = ".";
        tiles = {{1,0}};
    };
};





