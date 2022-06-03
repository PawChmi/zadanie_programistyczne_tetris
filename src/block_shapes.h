#pragma once
#include "block.h"

//Classic blocks
class block_L : public Block
{
public:
    block_L ( int x =0, int y = 0, blockType sh=l ) :Block ( x,y,sh )
    {
        name = "L";
        tiles= { {0, 0}, {-1, 1}, {-1,0},{1,0}};
    };
};
class block_J : public Block
{
public:
    block_J ( int x =0, int y = 0, blockType sh=j ) :Block ( x,y,sh )
    {
        name = "J";
        tiles= {{0, 0},{1,0},{-1,0},{1,1}};
    };
};
class block_O : public Block
{
public:
    block_O ( int x =0, int y = 0, blockType sh=o ) : Block ( x, y, sh )
    {
        name = "O";
        tiles = {{-0.5,-0.5},{0.5, -0.5},{-0.5,0.5},{0.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};
class block_S : public Block
{

public:
    block_S ( int x =0, int y = 0, blockType sh=s )   : Block ( x,y,sh )
    {
        name = "S";
        tiles= { {1,0}, {0,1},{-1,1},{0,0}};
    };
};
class block_Z : public Block
{

public:
    block_Z ( int x =0, int y = 0, blockType sh=z ) :Block ( x,y,sh )
    {
        name = "Z";
        tiles = {{0,0},{-1,0}, {0, 1},{1,1}};
    };
};

class block_I : public Block
{
public:
    block_I ( int x =0, int y = 0, blockType sh=i ) :Block ( x,y,sh )
    {

        name = "I";
        tiles = { {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};

class block_T : public Block
{
public:
    block_T ( int x =0, int y = 0, blockType sh=t ) :Block ( x,y,sh )
    {
        name = "T";
        tiles = { {0,0}, {1,0}, {-1,0},{0,1}};
    };
};

//single cell
class block_dot : public Block
{

public:
    block_dot ( int x =0, int y = 0, blockType sh=j ) :Block ( x,y,sh )
    {
        name = ".";
        tiles = {{1,0}};
    };
};

class block_slash : public Block
{
public:
    block_slash ( int x =0, int y = 0, blockType sh=t ) :Block ( x,y,sh )
    {
        name = "/";
        tiles = { {0.5,0.5}, {-0.5,-0.5}, {-1.5,-1.5},{1.5,1.5}};
        center = {x+0.5, y+0.5};
    };
};



