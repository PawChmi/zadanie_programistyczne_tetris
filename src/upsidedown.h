#pragma once
#include "engine.h"



class UpsideDown : public Engine{
    

protected:
    virtual void SoftDrop()
    {
    activePiece->move ( 0, -1 );
    if ( collisionCheck ( *activePiece ) ) activePiece->move ( 0, 1 );
    incrementClock ( DEFAULT_TIME_ADDED/4 );

    }
    void HardDrop()
    {
        while ( !collisionCheck ( *activePiece ) ) {
            activePiece->move ( 0, -1 );
        }
        activePiece->move ( 0, 1 );
        petrify();


    }
    void ghostDrop()
    {

        ghostPiece = std::make_shared<Block> ( *activePiece );
        ghostPiece->makeGhost();
        while ( !collisionCheck ( *ghostPiece ) ) {
            ghostPiece->move ( 0, -1 );
        }
        ghostPiece->move ( 0, 1 );
    }
    bool collisionCheck ( Block &b ){
            std::vector<std::pair<int, int>> t;
    t = b.getTileCoords();

    for ( auto p : t ) {
        if ( p.first<0||p.first>=width ) return true;
        if ( p.second <height ) {
            if ( p.second <= 0 ) return true;
            else if ( field[p.second][p.first] ) return true;
        }
    }
    return false;
    }
    void clearLine ( int y )
    {
    drawField();
    for ( int x =0; x<width; x++ ) {
        ConsolePointer->drawTile ( x, y, field[y][x], true );
    }
    ConsolePointer->wait();
    ConsolePointer->printData ( score, level, goal );
    ConsolePointer->drawEmpty ( 0, y, width );
    ConsolePointer->wait();

    while ( y<height-1 ) { //kopiuj zawartość linijki nad y do y, powtarzaj aż dojdziesz do ostatniej linijki
        std::copy ( field[y+1], field[y+1]+width, field[y] );
        y++;
    }

}

void petrify()
{
    std::vector<std::pair<int, int>> t;
    t = activePiece->getTileCoords();
    for ( auto p : t ) {
        if ( p.second>=height-1 ) end = true;
        else field[p.second][p.first] = activePiece->getShape();
    }
    scanLines();
    activePiece->move ( 0, height );
    fallenUpdate = true;
    held = false;
}

    void gravity()
    {
    activePiece->move ( 0, -1 );
    if ( collisionCheck ( *activePiece ) ) {
        activePiece->move ( 0, 1 );
        petrify();
    }
    }
    void spawn()
    {
        Engine::spawn();
        activePiece->move(width/2-1, height+1);
        ghostDrop();
    }
public:
    UpsideDown ( Console &c, std::vector<std::shared_ptr<Block>> blockSet, int w=10, int h = 20, int lvl=1 ) : Engine ( c, blockSet, w, h, lvl )
    {
        c.print ( "GameMode: UpsideDown" );
        std::queue<std::shared_ptr<Block>> empty;
        std::swap ( blockQ, empty );
        shuffle();
        spawn();
        spawn();
    };
    virtual std::string getMode(){
        return "[UD]";
    }
};
