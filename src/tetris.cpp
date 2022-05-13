#include "tetris.h"
#include <algorithm>
#include <iterator>

/** 
 * Funckcja zwraca znak podanej liczby.
 *  @param x liczba której znak należy wyznaczyć
 *  @return -1 gdy x\<0, w przeciwnym wypadku 1
 */
int sgn(double x){
    if(x==0)return 1;
    return x/x;
}

/**
 * Funckcja zamienia miejscami wspołrzędne kafelka
 */
void tile::swap()
{
    double t = x;
    x = y;
    y = t;
}
/**
 * Funkcja neguje współrzędną x kafelka
 */
void tile::negateX(){
    x = -x;
}
/**
 * Konstruktor obiektu konsoli. Inicjalizuje bibliotekę ncurses
 */
engine::engine(console & c, int w, int h, int lvl)
{

    conptr = &c;
    conptr->setGameField(w, h);
    conptr->setTimeout(100);
    std::queue<std::shared_ptr<block>> empty;
    std::swap(blockQ, empty);
    field = new int* [h];
    width = w;
    height = h;
    for(int i = 0; i < h; ++i){
        field[i] = new int[w];
    }
    clearField();
    conptr->clear();
    conptr->resize();
//     shuffle();
//     spawn();
//    spawn();
    level = lvl;
    goal = std::min(100, (level+1)*4);
   fallenUpdate = true;
    held = false;
}

engine::~engine()
{
    for(int i = 0; i < engine::height; ++i){
        delete[] field[i] ;
    }
    activePiece = nullptr;
    ghostPiece = nullptr;
    holdPiece = nullptr;
    nextPiece = nullptr;
    conptr->setTimeout(250);
    delete [] field;
}



/**
 * Funckja zwraca wynik który gracz osiągnął w obecnej grze
 */
int engine::getScore()
{
    return score;
}

void engine::GiveUp()
{
    end = true;
}

void engine::incrementClock(int ammount)
{
    clock += ammount;
    if(clock >= (20-level)*25){
        gravity();
        clock = 0;
    }
}



/** 
 * Funkcja przesuwa aktywny blok w lewo o 1 jednostkę
 */
void engine::Left()
{

    activePiece->move(-1, 0);
    if(collisionCheck(*activePiece))activePiece->move(1, 0);
    ghostDrop();
    incrementClock();
}
/**
 * Funkcja przesuwa aktywny blok w prawo o 1 jednostkę
 */
void engine::Right()
{
    
    activePiece->move(1, 0);
    if(collisionCheck(*activePiece))activePiece->move(-1, 0);
    ghostDrop();
    incrementClock();
    
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę.
 * Jeżeli natrafi na przeszkodę - petryfikuje blok
 */
void engine::gravity()
{
    activePiece->move(0, 1);
    if(collisionCheck(*activePiece)){
        activePiece->move(0, -1);
        petrify();
    }
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę
 */
void engine::SoftDrop()
{
    activePiece->move(0, 1);
    if(collisionCheck(*activePiece))activePiece->move(0, -1);
    incrementClock(DEFAULT_TIME_ADDED/4);
    
}
void engine::HardDrop()
{
    while(!collisionCheck(*activePiece)){
        activePiece->move(0, 1);
    }
    activePiece->move(0, -1);
    petrify();

        
}
/**
 * Funkcja obraca aktywny blok w kierunku przeciwnym do ruchu wskazówek zegara
 */
void engine::RotateL()
{
    activePiece->rotate(0);
    if(collisionCheck(*activePiece)){
        activePiece->rotate(1);
        Left();
        activePiece->rotate(0);
        if(collisionCheck(*activePiece)){
            activePiece->rotate(1);
            Right();
            activePiece->rotate(0);
            if(collisionCheck(*activePiece)){
                activePiece->rotate(1);
            }
        }
    }
    ghostDrop();
    incrementClock(DEFAULT_TIME_ADDED/4);
}
/**
 * Funkcja obraca aktywny blok w kierunku zgodnym z ruchem wskazówek zegara
 */
void engine::RotateR()
{
    activePiece->rotate(1);
    if(collisionCheck(*activePiece)){
        activePiece->rotate(0);
        Right();
        activePiece->rotate(1);
        if(collisionCheck(*activePiece)){
            activePiece->rotate(0);
            Left();
            activePiece->rotate(1);
            if(collisionCheck(*activePiece)){
                activePiece->rotate(0);
            }
        }
    }
    ghostDrop();
    incrementClock(DEFAULT_TIME_ADDED/4);
}
void engine::ghostDrop(){
    
    ghostPiece = std::make_shared<block>(*activePiece);
    ghostPiece->makeGhost();
    while(!collisionCheck(*ghostPiece)){
        ghostPiece->move(0, 1);
    }
    ghostPiece->move(0, -1);
}


void engine::petrify()
{
    std::vector<std::pair<int, int>> t;
    t = activePiece->getTileCoords();
    for(auto p : t){
        if(p.second<=0)end = true;
        else field[p.second][p.first] = activePiece->getShape();
    }
    scanLines();
    activePiece->move(0, -height);
    fallenUpdate = true;
    held = false;
}


bool engine::fallen()
{
    if(fallenUpdate){
        fallenUpdate=false;
        return true;
    }else
        return false;
   
}

/**
 * Funkcja rysuje aktywny blok
 * @param o obiekt wyświetlacza na którym ma być narysowany blok
 */
void engine::drawPiece(){
   ghostPiece->draw(conptr);
    activePiece->draw(conptr);
}


bool engine::work(){
        if(fallen()){
            spawn();
            drawSide();
        }
        drawField();
        drawPiece();
//         conptr->printData(score, level, goal);
        key ch = conptr->getInput();
        if(ch ==QUIT){
            GiveUp();
        }else if(ch==LEFT){
            Left();
        }else if(ch==PAUSE){
            bool pauseloop = true;
            conptr->move(conptr->getWidth()/2-3, 10);
            conptr->printCenter("        ", height/2-1, true);
            conptr->printCenter(" PAUSED ", height/2, true);
            conptr->printCenter("        ", height/2+1, true);
            while(pauseloop){
                
                ch = conptr->getInput();
                if(ch==PAUSE)pauseloop = false;
            }
        }else if(ch==HARDDROP){
            HardDrop();
        }else if(ch==DROP){
            SoftDrop();
        }else if(ch==RIGHT){
            Right();
        }else if(ch==REFRESH){
            conptr->clear();
            conptr->resize();
        }else if(ch==HOLD){
            Hold();
            drawSide();
        }else if(ch==ROT_L){
            RotateL();
        }else if(ch==ROT_R){
            RotateR();
        }else if(ch == NONE){
            incrementClock();
        }

        
    return !end;
}

void engine::drawSide()
{
    conptr->printData(score, level, goal);
    if(holdPiece!=nullptr)holdPiece->draw(conptr, width+3, 6); 
    
    nextPiece->draw(conptr, width+3, 12);
}

void engine::Hold()
{
    if(!held){
        held = true;
        std::shared_ptr<block> temp = holdPiece;
        holdPiece= std::make_shared<block>(*activePiece);
        if(temp!=nullptr)activePiece = std::make_shared<block>(*temp);
        else spawn();
    }
    ghostDrop();
}

void engine::scoreIncrease(int n)
{
    score += floor(n*(n/2.7+0.76))*50*(level+1);
    goal -= n;
    if(goal<=0){
        level++;
        goal = std::min(100, (level+1)*4);
    }
	
}

void block::set ( int x, int y )
{
    center = {x, y};
}


void engine::shuffle()
{
    std::vector<std::shared_ptr<block>> blocks={
        std::make_shared<block_I>((width/2)-1,-3),
        std::make_shared<block_slash>((width/2)-1,-3),
//         std::make_shared<block_II>((width/2)-1,-3),
//         std::make_shared<block__>((width/2)-1,-3),
//         std::make_shared<block_J>((width/2)-1,-3),
//         std::make_shared<block_L>((width/2)-1,-3),
//         std::make_shared<block_O>((width/2)-1,-3),
//         std::make_shared<block_S>((width/2)-1,-3),
//         std::make_shared<block_Z>((width/2)-1,-3),
//         std::make_shared<block_T>((width/2)-1,-3),
        std::make_shared<block_F>((width/2)-1,-3),
        std::make_shared<block_E>((width/2)-1,-3),
    };
    std::shuffle(std::begin(blocks), std::end(blocks), std::default_random_engine( time( NULL )));
    for(auto b : blocks){
        blockQ.push(b);
    }
}
void classic::shuffle()
{
    std::vector<std::shared_ptr<block>> blocks={
        std::make_shared<block_I>((width/2)-1,-3),
        std::make_shared<block_J>((width/2)-1,-3),
        std::make_shared<block_O>((width/2)-1,-3),
        std::make_shared<block_L>((width/2)-1,-3),
        std::make_shared<block_S>((width/2)-1,-3),
        std::make_shared<block_Z>((width/2)-1,-3),
        std::make_shared<block_T>((width/2)-1,-3),
    };
    std::shuffle(std::begin(blocks), std::end(blocks), std::default_random_engine( time( NULL )));
    for(auto b : blocks){
        blockQ.push(b);
    }
}
void justice::shuffle()
{
    std::vector<std::shared_ptr<block>> blocks={
        std::make_shared<block_T>((width/2)-1,-3),
    };
    std::shuffle(std::begin(blocks), std::end(blocks), std::default_random_engine( time( NULL )));
    for(auto b : blocks){
        blockQ.push(b);
    }
}
void ludicrous::shuffle()
{
    std::vector<std::shared_ptr<block>> blocks={
        std::make_shared<block_E>((width/2)-1,-3),
        std::make_shared<block_F>((width/2)-1,-3),
        std::make_shared<block_O_offcenter>((width/2)-1,-3),
    };
    std::shuffle(std::begin(blocks), std::end(blocks), std::default_random_engine( time( NULL )));
    for(auto b : blocks){
        blockQ.push(b);
    }
}

/**
 * Funkcja zeruje komórki tablicy zapisującej bloki
 */
void engine::clearField()
{
    for(int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            field[y][x] = 0;
        }
    }
}
/**
 * Funkcja ustawia aktywny blok na podany kształt w pozycji początkowej
 * @param s kształt jaki ma przyjąć nowy blok
 */

void engine::spawn()
{
  //  activePiece = nullptr;
    if(blockQ.size()<2)shuffle();
    if(nextPiece != nullptr){
        activePiece = std::make_shared<block>(*nextPiece);
    }else{
         activePiece = blockQ.front();
         blockQ.pop();
    }
    nextPiece = blockQ.front();
    
    blockQ.pop();
    ghostDrop();
    
}
/**
 * Funckcja ustawia komórkę tablicy na podaną wartość
 * @param x współrzędna x w tablicy
 * @param y współrzędna y w tablicy
 * @param val wartość która ma zostać ustawiona
 */
void engine::setField(const int x, const int y, const int val){
    field[y][x] = val;
}
/**
 * Funkcja wyświetla tablicę na podany wyświetlacz
 * @param disp obiekt wyświetlacza
 */
void engine::drawField()
{
    for(int y = 1; y<height; y++){
        for(int x = 0; x<width; x++){
            if(field[y][x]){
                conptr->drawTile(x,y,field[y][x]);
            }else{
                conptr->drawEmpty(x,y);
            }
        }
    }
    
}
/**
 * Funkcja sprawdza kompletność kolejnych linijek w tablicy, czyści kompletne i zwiększa wynik gracza
 */
void engine::scanLines(){
    int n = 0;
    for(int y = height-1; y>0; y--){
        while(scanLine(y)){//line is full
            clearLine(y);
            n++;
        }
    }
    scoreIncrease(n);
    
}
/** 
 * Funckcja zwraca iloczyn kolejnych komórek podanego wiersza tablicy
 * @param y wiersz tablicy
 * @return 0 jeśli przynajmniej jedena komórka pusta, więcej niż zero jeśli wszystkie zapełnione
 */
int engine::scanLine(int y)
{
    
    for(int x = 0; x<width; x++){
        if(!field[y][x])return 0;
    }
    return 1;
}
/** 
 * Funkcja kasuje wiersz w tablicy i przesuwa wszystkie wyższe wiersze o 1 w dół
 */
void engine::clearLine(int y)
{
    drawField();
    for(int x =0; x<width;x++){
     conptr->drawTile(x, y, field[y][x], true);   
    }
    conptr->wait();
    conptr->printData(score, level, goal);
    conptr->drawEmpty(0, y, width);
    conptr->wait();
    
    while(y>1){//kopiuj zawartość linijki nad y do y, powtarzaj aż dojdziesz do ostatniej linijki
        std::copy(field[y-1], field[y-1]+width, field[y]);
        y--;
    }
        
}
int block::countBlocks(){
    return tiles.size();
}
/**
 * Funkcja sprawdza czy blok wyszedł poza ramy pola gry lub nachodzi na zajęte już komórki
 * @return true jeśli nastąpiła kolizja, w przeciwnym razie false
 */
bool engine::collisionCheck(block &b)
{
    std::vector<std::pair<int, int>> t;
    t = b.getTileCoords();

    for(auto p : t){
        if(p.first<0||p.first>=width)return true;
        if(p.second >= 0){
            if(p.second>=height)return true;
            else if(field[p.second][p.first])return true;       
        }
    }
    return false;
}

/**
 * Funkcja oblicza absolutne współrzędne poszczególnych kafelków bloku
 * @return wskaźnik na tablicę par współrzędnych kafelków
 */
std::vector<std::pair<int, int>> block::getTileCoords()
{
    std::vector<std::pair<int, int>> a;
    for(auto t : tiles){
           a.push_back({center.first+t.x, center.second+t.y});
        }
//     a[0]= {center.first+tileA.x, center.second+tileA.y};//tileA
//     a[1]= {center.first+tileB.x, center.second+tileB.y};//tileB
//     a[2]= {center.first+tileC.x, center.second+tileC.y};//tileC
//     a[3]= {center.first+tileD.x, center.second+tileD.y};//tileD
    return a;
}

/**
 * Funckcja zwraca wspołrzędną Y środka bloku
 * @return y środka bloku
 */

int block::getY()
{
    return (int)center.second;
}
/**
 * Funckcja zwraca wspołrzędną X środka bloku
 * @return X środka bloku
 */

int block::getX()
{
    return (int)center.first;
}



/**
 * Funckja zwraca kształt bloku
 * @return typ bloku
 */
blockType block::getShape()
{
    return shape;
}


/**
 * Funkcja rysuje blok na podany wyświetlacz
 * @param disp obiekt wyświetlaczana którym ma być narysowany blok
 */
void block::draw(console* disp)
{
    for(auto t : tiles){    
        disp->drawTile(center.first+t.x, center.second+t.y, shape, ghost);//tileA
    }
}


void block::draw(console* disp, int x, int y)
{
    for(auto t : tiles){    
        disp->drawTile(x+t.x, y+t.y, shape, ghost);//tileA
    }
}


void block::makeGhost(){
    ghost = true;
}
/**
 * Funkcja zmienia współrzędne kafelków w taki sposób, żeby blok się obrócił
 * @param clockWise prawda jeśli zgodnie z ruchem wskazówek zegara, fałsz, jeśli przeciwnie
 */
void block::rotate(bool clockWise)
{
    if(clockWise){
        rotation++;
        if(rotation>3)rotation=0;
        for(auto &t : tiles){
            t.swap();
            t.negateX();
        }

    }else{
        rotation--;
        if(rotation<0)rotation=1;
        for(auto &t:tiles){
            t.negateX();
            t.swap();
        }

        
    }
    
}
/**
 * Funkcja zmienia współrzędne środka bloku o podane wartości
 * @param x przesunięcie w osi X
 * @param y przesunięcie w osi Y
 */
void block::move(int x, int y)
{
    center.first += x;
    center.second+=y;
}

block::~block()
{
    
}
block::block(int x, int y, blockType s)
{
    center = {x, y};
    
    shape = s;

}
