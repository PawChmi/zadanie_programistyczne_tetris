#pragma once
#include "block.h"

//Classic blocks
class block_L : public block
{
public:
    block_L ( int x =0, int y = 0, blockType sh=l ) :block ( x,y,sh )
    {
        tiles= { {0, 0}, {-1, 1}, {-1,0},{1,0}};
    };
};
class block_J : public block
{
public:
    block_J ( int x =0, int y = 0, blockType sh=j ) :block ( x,y,sh )
    {
        tiles= {{0, 0},{1,0},{-1,0},{1,1}};
    };
};
class block_O : public block
{
public:
    block_O ( int x =0, int y = 0, blockType sh=o ) : block ( x, y, sh )
    {
        tiles = {{-0.5,-0.5},{0.5, -0.5},{-0.5,0.5},{0.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};
class block_S : public block
{

public:
    block_S ( int x =0, int y = 0, blockType sh=s )   : block ( x,y,sh )
    {

        tiles= { {1,0}, {0,1},{-1,1},{0,0}};
    };
};
class block_Z : public block
{

public:
    block_Z ( int x =0, int y = 0, blockType sh=z ) :block ( x,y,sh )
    {
        tiles = {{0,0},{-1,0}, {0, 1},{1,1}};
    };
};

class block_I : public block
{
public:
    block_I ( int x =0, int y = 0, blockType sh=i ) :block ( x,y,sh )
    {

        tiles = { {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};

class block_T : public block
{
public:
    block_T ( int x =0, int y = 0, blockType sh=t ) :block ( x,y,sh )
    {
        tiles = { {0,0}, {1,0}, {-1,0},{0,1}};
    };
};

//single cell
class block__ : public block
{

public:
    block__ ( int x =0, int y = 0, blockType sh=j ) :block ( x,y,sh )
    {
        tiles = {{1,0}};
    };
};

class block_slash : public block
{
public:
    block_slash ( int x =0, int y = 0, blockType sh=t ) :block ( x,y,sh )
    {

        tiles = { {0.5,0.5}, {-0.5,-0.5}, {-1.5,-1.5},{1.5,1.5}};
        center = {x+0.5, y+0.5};
    };
};
class block_II : public block
{
public:
    block_II ( int x =0, int y = 0, blockType sh=s ) :block ( x,y,sh )
    {

        tiles = { {0.5,0.5}, {-0.5,0.5}, {-1.5,0.5},{1.5,0.5}, {2.5,0.5}, {-2.5,0.5}, {-3.5,0.5},{3.5,0.5}};
        center = {x+0.5, y+0.5};
    };
};

class block_Y : public block
{
public:
    block_Y ( int x =0, int y = 0, blockType sh=o ) :block ( x,y,sh )
    {
        tiles = { {0,0}, {1,-1}, {-1,-1},{0,1}};
    };
};
class block_Tri : public block
{
public:
    block_Tri ( int x =0, int y = 0, blockType sh=z ) :block ( x,y,sh )
    {
        tiles = { {0.5,0.5}, {-0.5,-0.5}, {-1.5,-1.5},{1.5,1.5}, {0.5,1.5}, {-0.5,1.5}, {-1.5,-0.5},{-1.5,0.5},{-1.5,1.5}};
        center = {x+0.5, y+0.5};
    };

};
class block_E : public block
{
public:
    block_E ( int x =0, int y = 0, blockType sh=l ) :block ( x,y,sh )
    {
        tiles = {{0,0}, {1,0},{-1,0},{-1,-1}, {-1, 1}, {-1,-2}, {-1, 2}, {0,2}, {0,-2},{1,2}, {1,-2}};

    };

};
class block_F : public block
{
public:
    block_F ( int x =0, int y = 0, blockType sh=j ) :block ( x,y,sh )
    {
        tiles = {{0,0}, {1,0},{-1,0},{-1,-1}, {-1, 1}, {-1, 2},{-1,-2}, {0,-2}, {1,-2}};

    };

};
class block_O_offcenter : public block
{
public:
    block_O_offcenter ( int x =0, int y = 0, blockType sh=o ) : block ( x, y, sh )
    {
        tiles = {{3,3},{3,4},{4,4},{4,3}};
    };
};
