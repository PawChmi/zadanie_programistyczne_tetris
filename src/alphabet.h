#pragma once
#include "block.h"

class block_A : public Block
{
public:
    block_A ( int x =0, int y = 0, blockColor c=green ) noexcept : Block ( x,y,c )
    {
        name = "A";
        tiles = {{1,0}, {-1,0}, {-1,-1}, {1,-1}, {-1, 1}, {1,1}, {0, -2}};
    };
};
class block_B : public Block
{
public:
    block_B ( int x =0, int y = 0, blockColor c=red ) noexcept : Block ( x,y,c )
    {
        name = "B";
        tiles = {{0,0}, {-1,0}, {-1,-1}, {1,-1}, {-1, 1}, {1,1}, {0, -2}, {0,2},{-1, -2}, {-1,2}};
    };
};
class block_C : public Block
{
public:
    block_C ( int x =0, int y = 0, blockColor c=blue ) noexcept : Block ( x,y,c )
    {
        name = "C";
        tiles = {{0,0}, {0,-1}, {0,1}, {1, -1}, {1,1}};
    };
};
class block_D : public Block
{
public:
    block_D ( int x =0, int y = 0, blockColor c=orange ) noexcept : Block ( x,y,c )
    {
        name = "D";
        tiles = {{0,0}, {0,-1}, {0,1}, {1, -1}, {1,1}, {2, 0}};
        center= {x+1, y};
    };
};
class block_E : public Block
{
public:
    block_E ( int x =0, int y = 0, blockColor c=blue ) noexcept : Block ( x,y,c )
    {
        name = "E";
        tiles = {{0,0}, {-1,0},{-1,-1}, {-1, 1}, {-1,-2}, {-1, 2}, {0,2}, {0,-2}};
    };
};
class block_F : public Block
{
public:
    block_F ( int x =0, int y = 0, blockColor c=orange ) noexcept : Block ( x,y,c )
    {
        name = "F";
        tiles = {{0,0},{-1,0},{-1,-1}, {-1, 1},{-1,-2}, {0,-2}};
    };
};
class block_G : public Block
{
public:
    block_G ( int x =0, int y = 0, blockColor c=yellow ) noexcept : Block ( x,y,c )
    {
        name = "G";
        tiles = {{0,0},{-1,0},{0,-1}, {0, 1}, {1, 0},{-1,-1}};
    };
};
class block_H : public Block
{
public:
    block_H ( int x =0, int y = 0, blockColor c=purple ) noexcept : Block ( x,y,c )
    {
        name = "H";
        tiles = {{0,0},{-1,0},{1,0}, {1, 1}, {1, -1},{-1,-1}, {-1,1}};
    };
};
class block_K : public Block
{
public:
    block_K ( int x =0, int y = 0, blockColor c=cyan ) noexcept : Block ( x,y,c )
    {
        name = "K";
        tiles = {{0,0},{-1,0}, {1, 1}, {1, -1},{-1,-1}, {-1,1}};
    };
};
class block_M : public Block
{
public:
    block_M ( int x =0, int y = 0, blockColor c=green ) noexcept : Block ( x,y,c )
    {
        name = "M";
        tiles = {{0,0},{1, -1}, {2, 0},{-1,-1}, {-2,0}};
    };
};
class block_N : public Block
{
public:
    block_N ( int x =0, int y = 0, blockColor c=red ) noexcept : Block ( x,y,c )
    {
        name = "N";
        tiles = {{-1,-1},{-1,0}, {1,0}, {0,-1}};
    };
};
class block_P : public Block
{
public:
    block_P ( int x =0, int y = 0, blockColor c=orange ) noexcept : Block ( x,y,c )
    {
        name = "P";
        center= {x+0.5, y+0.5};
        tiles = {{-0.5,-0.5},{0.5,-0.5}, {-0.5, 0.5}, {0.5,0.5}, {-0.5, 1.5}};
    };
};
class block_Q : public Block
{
public:
    block_Q ( int x =0, int y = 0, blockColor c=blue ) noexcept : Block ( x,y,c )
    {
        name = "Q";
        center= {x+0.5, y+0.5};
        tiles = {{-0.5,-0.5},{0.5,-0.5}, {-0.5, 0.5}, {0.5,0.5}, {0.5, 1.5}};
    };
};
class block_R : public Block
{
public:
    block_R ( int x =0, int y = 0, blockColor c=purple ) noexcept : Block ( x,y,c )
    {
        name = "R";
        center= {x+0.5, y+0.5};
        tiles = {{-0.5,-0.5},{0.5,-0.5}, {-0.5, 0.5}};
    };
};
class block_U : public Block
{
public:
    block_U ( int x =0, int y = 0, blockColor c=red ) noexcept : Block ( x,y,c )
    {
        name = "U";
        tiles = {{-1,1},{-1,0}, {1,0}, {0,1}};
    };
};
class block_V : public Block
{
public:
    block_V ( int x =0, int y = 0, blockColor c=yellow ) noexcept : Block ( x,y,c )
    {
        name = "V";
        tiles = {{-1,0}, {1,0}, {0,1}};
    };
};
class block_W : public Block
{
public:
    block_W ( int x =0, int y = 0, blockColor c=green ) noexcept : Block ( x,y,c )
    {
        name = "W";
        tiles = {{0,0}, {0,1}, {1,1}, {-1,1}, {-2,0}, {2,0}};
    };
};

class block_X : public Block
{
public:
    block_X ( int x =0, int y = 0, blockColor c=yellow ) noexcept : Block ( x,y,c )
    {
        name = "X";
        tiles = { {0,0}, {-1,-1}, {1,-1},{-1,1}, {1,1}};
    };
};
class block_Y : public Block
{
public:
    block_Y ( int x =0, int y = 0, blockColor c=yellow ) noexcept : Block ( x,y,c )
    {
        name = "Y";
        tiles = { {0,0}, {-1,0}, {1,0},{1,-1}, {-1,-1},{0,1}};
    };
};
