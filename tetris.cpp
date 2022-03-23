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
    conptr->out.setGameField(w, h);
    std::queue<blockType> empty;
    std::swap(blockQ, empty);
    field = new int* [h];
    width = w;
    height = h;
    for(int i = 0; i < h; ++i){
        field[i] = new int[w];
    }
    clearField();
    shuffle();
    spawn();
    spawn();
    level = lvl;
    goal = std::min(100, (level+1)*10);
    holder = n;
    held = false;
}

engine::~engine()
{
    for(int i = 0; i < engine::height; ++i){
        delete[] field[i] ;
    }
    delete [] field;
}



/**
 * Funckja zwraca wynik który gracz osiągnął w obecnej grze
 */
int engine::getScore()
{
    return score;
}

void engine::giveUp()
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
void engine::left()
{

    activePiece.move(-1, 0);
    if(collisionCheck(activePiece))activePiece.move(1, 0);
    ghostDrop();
    incrementClock();
}
/**
 * Funkcja przesuwa aktywny blok w prawo o 1 jednostkę
 */
void engine::right()
{
    
    activePiece.move(1, 0);
    if(collisionCheck(activePiece))activePiece.move(-1, 0);
    ghostDrop();
    incrementClock();
    
}
/**
 * Funkcja przesuwa aktywny blok w dół o 1 jednostkę.
 * Jeżeli natrafi na przeszkodę - petryfikuje blok
 */
void engine::gravity()
{
    activePiece.move(0, 1);
    if(collisionCheck(activePiece)){
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
    if(collisionCheck(activePiece))activePiece.move(0, -1);
    incrementClock(DEFAULT_TIME_ADDED/4);
    
}
void engine::harddrop()
{
    while(!collisionCheck(activePiece)){
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
    if(collisionCheck(activePiece)){
        activePiece.rotate(1);
        left();
        activePiece.rotate(0);
        if(collisionCheck(activePiece)){
            activePiece.rotate(1);
            right();
            activePiece.rotate(0);
            if(collisionCheck(activePiece)){
                activePiece.rotate(1);
            }
        }
    }
    ghostDrop();
    incrementClock(DEFAULT_TIME_ADDED/4);
}
/**
 * Funkcja obraca aktywny blok w kierunku zgodnym z ruchem wskazówek zegara
 */
void engine::rotateR()
{
    activePiece.rotate(1);
    if(collisionCheck(activePiece)){
        activePiece.rotate(0);
        right();
        activePiece.rotate(1);
        if(collisionCheck(activePiece)){
            activePiece.rotate(0);
            left();
            activePiece.rotate(1);
            if(collisionCheck(activePiece)){
                activePiece.rotate(0);
            }
        }
    }
    ghostDrop();
    incrementClock(DEFAULT_TIME_ADDED/4);
}
void engine::ghostDrop(){
    ghostPiece = activePiece;
    ghostPiece.makeGhost();
    while(!collisionCheck(ghostPiece)){
        ghostPiece.move(0, 1);
    }
    ghostPiece.move(0, -1);
}

bool engine::ended()
{
    return end;
}

void engine::petrify()
{
    std::pair<int, int> *t;
    t = activePiece.getTileCoords();
    for(int i = 0; i<4; i++){
        std::pair<int, int> p = *(t+i);
        if(p.second<=0)end = true;
        else field[p.second][p.first] = activePiece.getShape();
    }
    scanLines();
    activePiece.move(0, -height);
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
    ghostPiece.draw(o);
    activePiece.draw(o);
}

void engine::drawSide(display o)
{
    o.printData(score, level, goal);
    if(holder)holdPiece.draw(o); 
    nextPiece.set(width+2, 10, next);
    nextPiece.draw(o);
}

void engine::hold()
{
    if(!held){
        held = true;
        blockType temp = holder;
        holder = activePiece.getShape();
        holdPiece.set(width+2, 5, holder);
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
    std::vector<blockType> blocks={l, s,z,o,i,j,t};
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
void engine::spawn(const blockType s)
{
    activePiece.set((width/2)-1,-3, s);
    ghostDrop();
}
void engine::spawn()
{
    activePiece.set((width/2)-1,-3, next);
    
    if(!blockQ.size())shuffle();
    next = blockQ.front();
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
void engine::drawField(display disp)
{
    for(int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            if(field[y][x]){
                disp.drawTile(x,y,field[y][x]);
            }else{
                disp.drawEmpty(x,y);
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
    drawField(conptr->out);
    for(int x =0; x<width;x++){
     conptr->out.drawTile(x, y, field[y][x], true);   
    }
    conptr->in.getInput();
    
    conptr->out.drawEmpty(0, y, width);
    conptr->in.getInput();
    
    while(y>1){//kopiuj zawartość linijki nad y do y, powtarzaj aż dojdziesz do ostatniej linijki
        std::copy(field[y-1], field[y-1]+width, field[y]);
        y--;
    }
        
}
/**
 * Funkcja sprawdza czy blok wyszedł poza ramy pola gry lub nachodzi na zajęte już komórki
 * @return true jeśli nastąpiła kolizja, w przeciwnym razie false
 */
bool engine::collisionCheck(block &b)
{
    std::pair<int, int> *t;
    t = b.getTileCoords();
    for(int i = 0; i<4; i++){
        std::pair<int, int> p = *(t+i);
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
std::pair<int, int> * block::getTileCoords()
{
    static std::pair<int, int> a[4];
    a[0]= {center.first+tileA.x, center.second+tileA.y};//tileA
    a[1]= {center.first+tileB.x, center.second+tileB.y};//tileB
    a[2]= {center.first+tileC.x, center.second+tileC.y};//tileC
    a[3]= {center.first+tileD.x, center.second+tileD.y};//tileD
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
void block::draw(display disp)
{
    disp.drawTile(center.first+tileA.x, center.second+tileA.y, shape, ghost);//tileA
    disp.drawTile(center.first+tileB.x, center.second+tileB.y, shape, ghost);//tileB
    disp.drawTile(center.first+tileC.x, center.second+tileC.y, shape, ghost);//tileC
    disp.drawTile(center.first+tileD.x, center.second+tileD.y, shape, ghost);//tileD
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




