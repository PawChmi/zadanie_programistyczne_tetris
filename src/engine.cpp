#include "engine.h"
#include <algorithm>
#include <iterator>

Engine::Engine ( Console & c,  std::vector<std::shared_ptr<Block>> &block_set, int w, int h, int lvl )
{

    blockSet = block_set;
    ConsolePointer = &c;
    ConsolePointer->setGameField ( w, h );
    ConsolePointer->setTimeout ( 100 );
    std::queue<std::shared_ptr<Block>> empty;
    std::swap ( blockQ, empty );
    field = new int* [h];
    width = w;
    height = h;
    for ( int i = 0; i < h; ++i ) {
        field[i] = new int[w];
    }
    clearField();
    ConsolePointer->clear();
    ConsolePointer->resize();
    level = lvl;
    goal = std::min ( 100, ( level+1 ) *4 );
    fallenUpdate = true;
    held = false;
}

Engine::~Engine()
{
    for ( int i = 0; i < Engine::height; ++i ) {
        delete[] field[i] ;
    }
    activePiece = nullptr;
    ghostPiece = nullptr;
    holdPiece = nullptr;
    nextPiece = nullptr;
    ConsolePointer->setTimeout ( 250 );
    delete [] field;
}





void Engine::incrementClock ( int ammount )
{
    clock += ammount;
    if ( clock >= ( 20-level ) *25 ) {
        gravity();
        clock = 0;
    }
}



/**
 * Funkcja przesuwa aktywny blok w lewo o 1 jednostkę
 */
void Engine::Left()
{

    activePiece->move ( -1, 0 );
    if ( collisionCheck ( *activePiece ) ) activePiece->move ( 1, 0 );
    ghostDrop();
    incrementClock();
}
/**
 * Funkcja przesuwa aktywny blok w prawo o 1 jednostkę
 */
void Engine::Right()
{

    activePiece->move ( 1, 0 );
    if ( collisionCheck ( *activePiece ) ) activePiece->move ( -1, 0 );
    ghostDrop();
    incrementClock();

}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę.
 * Jeżeli natrafi na przeszkodę - petryfikuje blok
 */
void Engine::gravity()
{
    activePiece->move ( 0, 1 );
    if ( collisionCheck ( *activePiece ) ) {
        activePiece->move ( 0, -1 );
        petrify();
    }
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę
 */
void Engine::SoftDrop()
{
    activePiece->move ( 0, 1 );
    if ( collisionCheck ( *activePiece ) ) activePiece->move ( 0, -1 );
    incrementClock ( DEFAULT_TIME_ADDED/4 );

}
void Engine::HardDrop()
{
    while ( !collisionCheck ( *activePiece ) ) {
        activePiece->move ( 0, 1 );
    }
    activePiece->move ( 0, -1 );
    petrify();


}
/**
 * Funkcja obraca aktywny blok w kierunku przeciwnym do ruchu wskazówek zegara
 */
void Engine::RotateL()
{
    activePiece->rotateLeft();
    if ( collisionCheck ( *activePiece ) ) {
        activePiece->rotateRight();
        Left();
        activePiece->rotateLeft();
        if ( collisionCheck ( *activePiece ) ) {
            activePiece->rotateRight();
            Right();
            activePiece->rotateLeft();
            if ( collisionCheck ( *activePiece ) ) {
                activePiece->rotateRight();
            }
        }
    }
    ghostDrop();
    incrementClock ( DEFAULT_TIME_ADDED/4 );
}
/**
 * Funkcja obraca aktywny blok w kierunku zgodnym z ruchem wskazówek zegara
 */
void Engine::RotateR()
{
    activePiece->rotateRight();
    if ( collisionCheck ( *activePiece ) ) {
        activePiece->rotateLeft();
        Right();
        activePiece->rotateRight();
        if ( collisionCheck ( *activePiece ) ) {
            activePiece->rotateLeft();
            Left();
            activePiece->rotateRight();
            if ( collisionCheck ( *activePiece ) ) {
                activePiece->rotateLeft();
            }
        }
    }
    ghostDrop();
    incrementClock ( DEFAULT_TIME_ADDED/4 );
}
void Engine::ghostDrop()
{

    ghostPiece = std::make_shared<Block> ( *activePiece );
    ghostPiece->makeGhost();
    while ( !collisionCheck ( *ghostPiece ) ) {
        ghostPiece->move ( 0, 1 );
    }
    ghostPiece->move ( 0, -1 );
}


void Engine::petrify()
{
    std::vector<std::pair<int, int>> t;
    t = activePiece->getTileCoords();
    for ( auto p : t ) {
        if ( p.second<=0 ) end = true;
        else field[p.second][p.first] = activePiece->getShape();
    }
    scanLines();
    activePiece->move ( 0, -height );
    fallenUpdate = true;
    held = false;
}


bool Engine::fallen()
{
    if ( fallenUpdate ) {
        fallenUpdate=false;
        return true;
    } else
        return false;

}

/**
 * Funkcja rysuje aktywny blok
 * @param o obiekt wyświetlacza na którym ma być narysowany blok
 */
void Engine::drawPiece()
{
    ghostPiece->draw ( ConsolePointer );
    activePiece->draw ( ConsolePointer );
}


bool Engine::work()
{
    if ( fallen() ) {
        spawn();
        drawSide();
    }
    drawField();
    drawPiece();
    key ch = ConsolePointer->getInput();
    if ( ch ==QUIT ) {
        GiveUp();
    } else if ( ch==LEFT ) {
        Left();
    } else if ( ch==PAUSE ) {
        bool pauseloop = true;
        ConsolePointer->move ( ConsolePointer->getWidth() /2-3, 10 );
        ConsolePointer->printCenter ( "        ", height/2-1, true );
        ConsolePointer->printCenter ( " PAUSED ", height/2, true );
        ConsolePointer->printCenter ( "        ", height/2+1, true );
        while ( pauseloop ) {

            ch = ConsolePointer->getInput();
            if ( ch==PAUSE ) pauseloop = false;
        }
    } else if ( ch==HARDDROP ) {
        HardDrop();
    } else if ( ch==DROP ) {
        SoftDrop();
    } else if ( ch==RIGHT ) {
        Right();
    } else if ( ch==REFRESH ) {
        ConsolePointer->clear();
        ConsolePointer->resize();
    } else if ( ch==HOLD ) {
        Hold();
        drawSide();
    } else if ( ch==ROT_L ) {
        RotateL();
    } else if ( ch==ROT_R ) {
        RotateR();
    } else if ( ch == NONE ) {
        incrementClock();
    }


    return !end;
}

void Engine::drawSide()
{
    ConsolePointer->printData ( score, level, goal );
    if ( holdPiece!=nullptr ) holdPiece->draw ( ConsolePointer, width+3, 6 );

    nextPiece->draw ( ConsolePointer, width+3, 12 );
}

void Engine::Hold()
{
    if ( !held ) {
        held = true;
        std::shared_ptr<Block> temp = holdPiece;
        holdPiece= std::make_shared<Block> ( *activePiece );
        if ( temp!=nullptr ) activePiece = std::make_shared<Block> ( *temp );
        else spawn();
    }
    ghostDrop();
}

void Engine::scoreIncrease ( int n )
{
    score += floor ( n* ( n/2.7+0.76 ) ) *50* ( level+1 );
    goal -= n;
    if ( goal<=0 ) {
        level++;
        goal = std::min ( 100, ( level+1 ) *4 );
    }

}

void Engine::shuffle()
{
        std::shuffle ( std::begin ( blockSet ), std::end ( blockSet ), std::default_random_engine ( time ( NULL ) ) );
        for ( auto b : blockSet ) {
            blockQ.push ( b );
        }
    
}



/**
 * Funkcja zeruje komórki tablicy zapisującej bloki
 */
void Engine::clearField()
{
    for ( int y = 0; y<height; y++ ) {
        for ( int x = 0; x<width; x++ ) {
            field[y][x] = 0;
        }
    }
}
/**
 * Funkcja ustawia aktywny blok na podany kształt w pozycji początkowej
 * @param s kształt jaki ma przyjąć nowy blok
 */

void Engine::spawn()
{
    //  activePiece = nullptr;
    if ( blockQ.size() <2 ) shuffle();
    if ( nextPiece == nullptr ) {
        nextPiece = blockQ.front();
        blockQ.pop();
    }
    activePiece = std::make_shared<Block> ( *nextPiece );
    nextPiece = blockQ.front();

    blockQ.pop();
}
/**
 * Funckcja ustawia komórkę tablicy na podaną wartość
 * @param x współrzędna x w tablicy
 * @param y współrzędna y w tablicy
 * @param val wartość która ma zostać ustawiona
 */
void Engine::setField ( const int x, const int y, const int val )
{
    field[y][x] = val;
}
/**
 * Funkcja wyświetla tablicę na podany wyświetlacz
 * @param disp obiekt wyświetlacza
 */
void Engine::drawField()
{
    for ( int y = 1; y<height; y++ ) {
        for ( int x = 0; x<width; x++ ) {
            if ( field[y][x] ) {
                ConsolePointer->drawTile ( x,y,field[y][x] );
            } else {
                ConsolePointer->drawEmpty ( x,y );
            }
        }
    }

}
/**
 * Funkcja sprawdza kompletność kolejnych linijek w tablicy, czyści kompletne i zwiększa wynik gracza
 */
void Engine::scanLines()
{
    int n = 0;
    for ( int y = height-1; y>0; y-- ) {
        while ( scanLine ( y ) ) { //line is full
            clearLine ( y );
            n++;
        }
    }
    scoreIncrease ( n );

}
/**
 * Funckcja zwraca iloczyn kolejnych komórek podanego wiersza tablicy
 * @param y wiersz tablicy
 * @return 0 jeśli przynajmniej jedena komórka pusta, więcej niż zero jeśli wszystkie zapełnione
 */
int Engine::scanLine ( int y )
{

    for ( int x = 0; x<width; x++ ) {
        if ( !field[y][x] ) return 0;
    }
    return 1;
}
/**
 * Funkcja kasuje wiersz w tablicy i przesuwa wszystkie wyższe wiersze o 1 w dół
 */
void Engine::clearLine ( int y )
{
    drawField();
    for ( int x =0; x<width; x++ ) {
        ConsolePointer->drawTile ( x, y, field[y][x], true );
    }
    ConsolePointer->wait();
    ConsolePointer->printData ( score, level, goal );
    ConsolePointer->drawEmpty ( 0, y, width );
    ConsolePointer->wait();

    while ( y>1 ) { //kopiuj zawartość linijki nad y do y, powtarzaj aż dojdziesz do ostatniej linijki
        std::copy ( field[y-1], field[y-1]+width, field[y] );
        y--;
    }

}
/**
 * Funkcja sprawdza czy blok wyszedł poza ramy pola gry lub nachodzi na zajęte już komórki
 * @return true jeśli nastąpiła kolizja, w przeciwnym razie false
 */
bool Engine::collisionCheck ( Block &b )
{
    std::vector<std::pair<int, int>> t;
    t = b.getTileCoords();

    for ( auto p : t ) {
        if ( p.first<0||p.first>=width ) return true;
        if ( p.second >= 0 ) {
            if ( p.second>=height ) return true;
            else if ( field[p.second][p.first] ) return true;
        }
    }
    return false;
}



