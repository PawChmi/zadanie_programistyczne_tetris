
#include "tetris.h"
#include <curses.h>
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
    clearField();
}

console::console() 
{
    ::initscr();
    ::noecho();
    ::cbreak();
    ::curs_set(0);
    if(!has_colors()) {
        ::endwin();
    }
    out.resize();
    out.clear();
    ::start_color();
    ::init_pair(1, COLOR_BLUE, COLOR_BLACK);    //l
    ::init_pair(2, COLOR_YELLOW, COLOR_BLACK);   //j
    ::init_pair(3, COLOR_GREEN, COLOR_BLACK);//s
    ::init_pair(4, COLOR_RED, COLOR_BLACK);  //z
    ::init_pair(5, COLOR_MAGENTA, COLOR_BLACK);   //t
    ::init_pair(6, COLOR_CYAN, COLOR_BLACK); //i
    ::init_pair(7, COLOR_WHITE, COLOR_BLACK);  //o
}
/**
 * Funkcja odpowiedzialna za zamykanie konsoli
 * (zastąpić destruktorem)
 */
void console::close()
{
    ::endwin();
}
/**
 * Funkcja czyści wyświetlany ekran
 */
void display::clear()
{
    ::clear();
}
void display::move(int x, int y)
{
    ::move(y, x);
}

void display::print(std::string s)
{
    printw(s.c_str());
}

/**
 * Funkcja sprawdza wymiary wyświetlacza i zapisuje je do zmiennych width i height obiektu
 */
void display::resize()
{
    getmaxyx(stdscr, height, width);
}
/**
 * Funkcja ustawia czas oczekiwania na wciśnięcie klawisza
 * @param delay czas w milisekundach
 */
void keyboard::setTimeout(int delay)
{
    ::timeout(delay);
}
/**
 * Funkcja zwraca klawisz wciśnięty przez użytkownika
 * @return wartość ascii znaku z klawiatury. -1 gdy minął czas oczekiwania.
 */
int keyboard::getInput()
{
    return getch();
}
/**
 * Funkcja rysuje kafelek na podanych współrzędnych i w podanym kolorze
 * @param x współrzędna x w polu gry
 * @param y współrzędna y w polu gry
 * @param color wartość od 1-7 oznaczająca kolor kafelka
 */
void display::drawTile(int x, int y, int color)
{
    attron(COLOR_PAIR(color));
    attron(A_REVERSE);
    mvprintw(y, x*2+(width/2)-(fieldWidth), "  ");
    attroff(A_REVERSE);
    
}
/**
 * Funkcja rysuje prostokąt pustej przestrzeni na podanych współrzędnych o podanych wymiarach
 * @param x wpółrzędna x
 * @param y współrzędna y
 * @param w szerokość prostokąta
 * @param h wysokość prostokąta
 */
void display::drawEmpty(int x, int y, int w, int h)
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h;i++){
        for(int j = 0; j < w; j++){
            mvprintw(y+i, (x+j)*2+(width/2)-(fieldWidth), "..");
        }
    }
}

int display::getWidth()
{
    return width;
}



int engine::getScore()
{
    return score;
}


/** 
 * Funkcja przesuwa aktywny blok w lewo o 1 jednostkę
 */
void engine::left()
{
    if(activePiece.getY()>=0){
        activePiece.move(-1, 0);
        if(collisionCheck())activePiece.move(1, 0);
    }
}
/**
 * Funkcja przesuwa aktywny blok w prawo o 1 jednostkę
 */
void engine::right()
{
    if(activePiece.getY()>=0){
    activePiece.move(1, 0);
    if(collisionCheck())activePiece.move(-1, 0);
    }
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
    if(collisionCheck())activePiece.rotate(1);
}
/**
 * Funkcja obraca aktywny blok w kierunku zgodnym z ruchem wskazówek zegara
 */
void engine::rotateR()
{
    activePiece.rotate(1);
    if(collisionCheck())activePiece.rotate(0);
}
void engine::reset()
{
    clearField();
}

void engine::petrify()
{
    std::pair<int, int> *t;
    t = activePiece.getTileCoords();
    for(int i = 0; i<4; i++){
        std::pair<int, int> p = *(t+i);
        if(p.second<0)reset();
        field[p.second][p.first] = activePiece.getShape();
    }
    scanLines();
    activePiece.move(0, -fieldHeight);
    fallenUpdate = true;
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
    activePiece.set((fieldWidth/2)-1,-5, s);
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
    score += level*n;
    
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
        else if(p.second < 0)return false;
        else if(p.second>=fieldHeight)return true;
        else if(field[p.second][p.first])return true;
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
    offset = 1;
    switch(sh){
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
            offset = 0.5;
            break;   
        case i:
            tileA = {0.5,0.5};
            tileB = {-0.5,0.5};
            tileC = {-1.5,0.5};
            tileD = {1.5,0.5};
            offset = 0.5;
            center = {x+0.5, y+0.5};
            break; 
    }
}




