
#pragma once
#include "tile.h"
#include "console.h"

enum blockType { //this one is just used for colors
    n = 0,
    l = 1,
    j = 2,
    s = 3,
    z = 4,
    t = 5,
    i = 6,
    o = 7
};

class Block
{
    blockType shape = n;
    bool ghost = false;
protected:
    std::string name;
    coords center= {0,0};
    std::vector<Tile> tiles;
public:
    Block ( int x=0, int y=0, blockType s=n ) : shape ( s ), center ( x, y ) {};
    ~Block()
    {

    }
    int countBlocks() const noexcept
    {
        return tiles.size();
    }
    void move ( int x, int y )
    {
        center.first += x;
        center.second+=y;
    }
    void rotateLeft()
    {
        for ( auto &t : tiles ) {
            t.rotL();
        }
    }
    void rotateRight()
    {
        for ( auto &t : tiles ) {
            t.rotR();
        }
    }
    void draw ( Console* disp ) const noexcept
    {
        for ( auto t : tiles ) {
            disp->drawTile ( center.first+t.x(), center.second+t.y(), shape, ghost );
        }
    }
    void draw ( Console* disp, const int x, const int y ) const noexcept
    {
        for ( auto t : tiles ) {
            disp->drawTile ( x+t.x(), y+t.y(), shape, ghost );
        }
    }
    void makeGhost()
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
    blockType getShape() const noexcept
    {
        return shape;
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

