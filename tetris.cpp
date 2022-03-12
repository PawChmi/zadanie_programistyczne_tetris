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
engine::engine()
{
    reset();
}



int engine::getScore()
{
    return score;
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
void engine::left()
{

    activePiece.move(-1, 0);
    if(collisionCheck())activePiece.move(1, 0);

    incrementClock();
}
/**
 * Funkcja przesuwa aktywny blok w prawo o 1 jednostkę
 */
void engine::right()
{
    
    activePiece.move(1, 0);
    if(collisionCheck())activePiece.move(-1, 0);
    incrementClock();
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę.
 * Jeżeli natrafi na przeszkodę - petryfikuje blok
 */
void engine::gravity()
{
    activePiece.move(0, 1);
    if(collisionCheck()){
        activePiece.move(0, -1);
        petrify();
    }
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę
 */
void engine::softdrop()
{
    activePiece.move(0, 1);
    if(collisionCheck())activePiece.move(0, -1);
    incrementClock(DEFAULT_TIME_ADDED/4);
}
void engine::harddrop()
{
    while(!collisionCheck()){
        activePiece.move(0, 1);
    }
    activePiece.move(0, -1);
    petrify();
        
}
/**
 * Funkcja obraca aktywny blok w kierunku przeciwnym do ruchu wskazówek zegara
 */
void engine::rotateL()
{
    activePiece.rotate(0);
    if(collisionCheck()){
        activePiece.rotate(1);
        left();
        activePiece.rotate(0);
        if(collisionCheck()){
            activePiece.rotate(1);
            right();
            activePiece.rotate(0);
            if(collisionCheck()){
                activePiece.rotate(1);
            }
        }
    }
    incrementClock(DEFAULT_TIME_ADDED/4);
}
/**
 * Funkcja obraca aktywny blok w kierunku zgodnym z ruchem wskazówek zegara
 */
void engine::rotateR()
{
    activePiece.rotate(1);
    if(collisionCheck()){
        activePiece.rotate(0);
        right();
        activePiece.rotate(1);
        if(collisionCheck()){
            activePiece.rotate(0);
            left();
            activePiece.rotate(1);
            if(collisionCheck()){
                activePiece.rotate(0);
            }
        }
    }
    incrementClock(DEFAULT_TIME_ADDED/4);
}
void engine::reset()
{
    clearField();
    std::queue<blockType> empty;
    std::swap(blockQ, empty);
    shuffle();
    spawn();
    level = 0;
    goal = 10;
    holder = n;
    held = false;
    
}

void engine::petrify()
{
    std::pair<int, int> *t;
    t = activePiece.getTileCoords();
    for(int i = 0; i<4; i++){
        std::pair<int, int> p = *(t+i);
        if(p.second<=0)reset();
        else field[p.second][p.first] = activePiece.getShape();
    }
    scanLines();
    activePiece.move(0, -fieldHeight);
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
void engine::drawPiece(display o){
    activePiece.draw(o);
}

void engine::drawSide(display o)
{
    o.clear(fieldWidth+1, 1, 6, fieldHeight);
    o.move((o.getWidth()/2)+fieldWidth+2, 1);
    o.print("Level:"+std::to_string(level));
    o.move((o.getWidth()/2)+fieldWidth+2, 2);
    o.print("To LvlUp:"+std::to_string(goal));
    o.move((o.getWidth()/2)+fieldWidth+2, 3);
    o.print("Score:"+std::to_string(score));
    
    o.move((o.getWidth()/2)+fieldWidth+2, 4);
    o.print("Hold:");
    if(holder)holdPiece.draw(o); 
    o.move((o.getWidth()/2)+fieldWidth+2, 9);
    o.print("Next:");
    nextPiece.set(fieldWidth+2, 10, next);
    nextPiece.draw(o);
    
}

void engine::hold()
{
    if(!held){
        held = true;
        blockType temp = holder;
        holder = activePiece.getShape();
        holdPiece.set(fieldWidth+2, 5, holder);
        if(temp)spawn(temp);
        else spawn();
    }
}

void engine::scoreIncrease(int n)
{
    switch(n){
        case 1:
           score += (level+1)*100;
           break;
        case 2:
            score += (level+1)*100*3;
            break;
        case 3:
            score += (level+1)*100*5;
            break;
        case 4:
            score += (level+1)*100*8;
            break;
    }
    goal -= n;
    if(goal<=0){
        level++;
        goal = std::min(100, (level+1)*10);
    }
	
}


void engine::shuffle()
{
    std::vector<blockType> blocks={l,j,o,i,t,s,z};
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
    for(int y = 0; y<fieldHeight; y++){
        for(int x = 0; x<fieldWidth; x++){
            field[y][x] = 0;
        }
    }
}
/**
 * Funkcja ustawia aktywny blok na podany kształt w pozycji początkowej
 * @param s kształt jaki ma przyjąć nowy blok
 */
void engine::spawn(const blockType s)
{
    activePiece.set((fieldWidth/2)-1,-3, s);
}
void engine::spawn()
{
    activePiece.set((fieldWidth/2)-1,-3, next);
    
    if(!blockQ.size())shuffle();
    next = blockQ.front();
    blockQ.pop();
    
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
void engine::drawField(display disp)
{
    for(int y = 0; y<fieldHeight; y++){
        for(int x = 0; x<fieldWidth; x++){
            if(field[y][x]){
                disp.drawTile(x,y,field[y][x]);
            }else{
                disp.drawEmpty(x,y);
            }
        }
    }
    refresh();
}
/**
 * Funkcja sprawdza kompletność kolejnych linijek w tablicy, czyści kompletne i zwiększa wynik gracza
 */
void engine::scanLines(){
    int n = 0;
    for(int y = fieldHeight-1; y>0; y--){
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
    
    for(int x = 0; x<fieldWidth; x++){
        if(!field[y][x])return 0;
    }
    return 1;
}
/** 
 * Funkcja kasuje wiersz w tablicy i przesuwa wszystkie wyższe wiersze o 1 w dół
 */
void engine::clearLine(int y)
{
    while(y>1){//kopiuj zawartość linijki nad y do y, powtarzaj aż dojdziesz do ostatniej linijki
        std::copy(std::begin(field[y-1]), std::end(field[y-1]), std::begin(field[y]));
        y--;
    }
        
}
/**
 * Funkcja sprawdza czy blok wyszedł poza ramy pola gry lub nachodzi na zajęte już komórki
 * @return true jeśli nastąpiła kolizja, w przeciwnym razie false
 */
bool engine::collisionCheck()
{
    std::pair<int, int> *t;
    t = activePiece.getTileCoords();
    for(int i = 0; i<4; i++){
        std::pair<int, int> p = *(t+i);
        if(p.first<0||p.first>=fieldWidth)return true;
        if(p.second >= 0){
            if(p.second>=fieldHeight)return true;
            else if(field[p.second][p.first])return true;       
        }
    }
    return false;
}

/**
 * Funkcja oblicza absolutne współrzędne poszczególnych kafelków bloku
 * @return wskaźnik na tablicę par współrzędnych kafelków
 */
std::pair<int, int> * block::getTileCoords()
{
    static std::pair<int, int> a[4];
    a[0]= {center.first+tileA.x, center.second+tileA.y};//tileA
    a[1]= {center.first+tileB.x, center.second+tileB.y};//tileB
    a[2]= {center.first+tileC.x, center.second+tileC.y};//tileC
    a[3]= {center.first+tileD.x, center.second+tileD.y};//tileD
    return a;
}

int block::getY()
{
    return (int)center.second;
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
void block::draw(display disp)
{
    disp.drawTile(center.first+tileA.x, center.second+tileA.y, shape);//tileA
    disp.drawTile(center.first+tileB.x, center.second+tileB.y, shape);//tileB
    disp.drawTile(center.first+tileC.x, center.second+tileC.y, shape);//tileC
    disp.drawTile(center.first+tileD.x, center.second+tileD.y, shape);//tileD
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
        tileA.swap();
        tileB.swap();
        tileC.swap();
        tileD.swap();
        tileA.negateX();
        tileB.negateX();
        tileC.negateX();
        tileD.negateX();
    }else{
        rotation--;
        if(rotation<0)rotation=1;
        tileA.negateX();
        tileB.negateX();
        tileC.negateX();
        tileD.negateX();
        tileA.swap();
        tileB.swap();
        tileC.swap();
        tileD.swap();
        
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

/**
 * Funkcja ustawia wartości bloku. 
 * @param x nowa wpółrzędna x środka bloku
 * @param y nowa wpółrzędna y środka bloku
 * @param sh kształt który ma mieć blok
 */
void block::set(int x, int y, blockType sh)
{
    center = {x, y};
    rotation = 0;
    shape = sh;
    tileD = {0,0};
    switch(sh){
        case n:
            tileA= {0,0};
            tileB= {0,0};
            tileC= {0,0};
        case l:
            tileA = {1,0};
            tileB = {-1,0};
            tileC = {-1,1};
            
            break;
        case j:
            tileA = {1,0};
            tileB = {-1,0};
            tileC = {1,1};
            break;
        case t:
            tileA = {1,0};
            tileB = {-1,0};
            tileC = {0,1};
            break;
        case s:
            tileA = {1,0};
            tileB = {0,1};
            tileC = {-1,1};
            break;
        case z:
            tileA = {-1,0};
            tileB = {0, 1};
            tileC = {1,1};
            break;
        case o:
            tileA = {-0.5,-0.5};
            tileB = {0.5, -0.5};
            tileC = {-0.5,0.5};
            tileD = {0.5,0.5};
            center = {x+0.5, y+0.5};
            break;   
        case i:
            tileA = {0.5,0.5};
            tileB = {-0.5,0.5};
            tileC = {-1.5,0.5};
            tileD = {1.5,0.5};
            center = {x+0.5, y+0.5};
            break; 
    }
}




