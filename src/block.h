
#pragma once
#include "tile.h"
#include "console.h"

enum blockColor { //this one is just used for colors
    none = 0,
    blue = 1,
    orange = 2,
    green = 3,
    red = 4,
    purple = 5,
    cyan = 6,
    yellow = 7
};

/**
 * Interfejs obiektu bloku
 */

class Block
{
    blockColor color = none;
    bool ghost = false;
protected:
    std::string name;
    coords center= {0,0};
    std::vector<Tile> tiles;
public:
    Block ( int x=0, int y=0, blockColor c=none ) noexcept: color ( c), center ( x, y ) {};
    ~Block() noexcept
    {
    }
    void move ( int x, int y ) noexcept
    {
        center.first += x;
        center.second+=y;
    }
    void rotateLeft() noexcept
    {
        for ( auto &t : tiles ) {
            t.rotL();
        }
    }
    void rotateRight() noexcept
    {
        for ( auto &t : tiles ) {
            t.rotR();
        }
    }
    void draw ( Console* disp ) const noexcept
    {
        for ( auto t : tiles ) {
            disp->drawTile ( center.first+t.x(), center.second+t.y(), color, ghost );
        }
    }
    void draw ( Console* disp, const int x, const int y ) const noexcept
    {
        for ( auto t : tiles ) {
            disp->drawTile ( x+t.x(), y+t.y(), color, ghost );
        }
    }
    void makeGhost() noexcept
    {
        ghost=true;
    }
    std::vector<std::pair<int, int>> getTileCoords() const noexcept
    {
        std::vector<std::pair<int, int>> output;
        for ( auto t : tiles ) {
            output.push_back ( {center.first+t.x(), center.second+t.y() } );
        }

        return output;
    }
    void setColor(const blockColor c) noexcept {
        this->color = c;
    }
    blockColor getColor() const noexcept
    {
        return color;
    }
    std::string getName() const noexcept {
        return name;
    }
    int getX() const noexcept
    {
        return ( int ) center.first;
    }
    int getY() const noexcept
    {
        return ( int ) center.second;
    }
};

