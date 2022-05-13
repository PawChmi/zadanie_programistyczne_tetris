#include "console.h"
#include <curses.h>


std::istream& operator >> (std::istream& i, key& K) {
    K = UNKNOWN;
    std::string S;
    if(i >> S) {
        if(S=="right")K = RIGHT;
        else if(S=="left")K = LEFT;
        else if(S=="drop")K = DROP;
        else if(S=="harddrop")K = HARDDROP;
        else if(S=="hold")K = HOLD;
        else if(S=="rotate_left")K = ROT_L;
        else if(S=="rotate_right")K = ROT_R;
        else if(S=="quit")K = QUIT;
        else if(S=="pause")K = PAUSE;
        else if(S=="refresh")K = REFRESH;

    }
    return i;
}


console::console()
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::noecho();
    ::cbreak();

    ::curs_set(0);
    if(!has_colors()) {
        ::endwin();
    }
    resize();
    clear();
    ::start_color();
    ::init_pair(1, COLOR_BLUE, COLOR_BLACK);    //l
    ::init_pair(2, COLOR_YELLOW, COLOR_BLACK);   //j
    ::init_pair(3, COLOR_GREEN, COLOR_BLACK);//s
    ::init_pair(4, COLOR_RED, COLOR_BLACK);  //z
    ::init_pair(5, COLOR_MAGENTA, COLOR_BLACK);   //t
    ::init_pair(6, COLOR_CYAN, COLOR_BLACK); //i
    ::init_pair(7, COLOR_WHITE, COLOR_BLACK);  //o
    bindings = {
        {27, QUIT},//escape
        {-1, NONE},
        {'a', LEFT},
        {'d', RIGHT},
        {'s', DROP},
        {' ', HARDDROP},
        {'q', ROT_L},
        {'e', ROT_R},
        {'f', HOLD},
        {'p', PAUSE},
        {'r', REFRESH},

    };
}
console::console(const std::string keybind_filename, const bool unicode, const bool reverse)
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::noecho();
    ::cbreak();
    ::keypad(stdscr, true);
    ::curs_set(0);
    if(!has_colors()) {
        ::endwin();
    }
    resize();
    clear();
    ::start_color();
    ::init_pair(1, COLOR_BLUE, COLOR_BLACK);    //l
    ::init_pair(2, COLOR_YELLOW, COLOR_BLACK);   //j
    ::init_pair(3, COLOR_GREEN, COLOR_BLACK);//s
    ::init_pair(4, COLOR_RED, COLOR_BLACK);  //z
    ::init_pair(5, COLOR_MAGENTA, COLOR_BLACK);   //t
    ::init_pair(6, COLOR_CYAN, COLOR_BLACK); //i
    ::init_pair(7, COLOR_WHITE, COLOR_BLACK);  //o
    bindings = {
        {27, QUIT},//escape
        {-1, NONE},
        {'a', LEFT},
        {'d', RIGHT},
        {'s', DROP},
        {' ', HARDDROP},
        {'q', ROT_L},
        {'e', ROT_R},
        {'f', HOLD},
        {'p', PAUSE},
        {'r', REFRESH},
        {KEY_DOWN, DROP},
        {KEY_RIGHT, RIGHT},
        {KEY_LEFT, LEFT},

    };
    std::ifstream file (keybind_filename);
    if(file) {
        key K;
        int N;

        while(file >> K>>N) {
            bindings[N] = K;
        }
    }
    if(unicode){
        font =  {0, "▫️️ ", "⏹️ ", "🔲", "━", "┃", "┓","┏", "┗", "┛"};
        
    }else if(reverse){
        font.empty = "::";
        font.block = "[]";
        font.ghost = "##";
    }
    if(reverse)font.reversed =!font.reversed;
    
}
/**
 * Destruktor konsoli
 */
console::~console()
{
    ::endwin();
}

/**
 * Funckcja ustawia w konsoli wielkość pola gry, żeby nie musiało być przekazywane za każdym razem kiedy chcemy coś wyświetlić.
 * @param w szerokość pola gry
 * @param h wysokość pola gry
 */
void console::setGameField(int w, int h)
{
    gameFieldWidth = w;
    gameFieldHeight = h;
}

/**
 * Funkcja czyści wyświetlany ekran
 */
void console::clear()
{
    ::clear();
}

void console::clear(int x, int y, int w, int h)
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            mvprintw(y+i+offsetY, (x+j)*2+(width/2)-(gameFieldWidth)+offsetX, "  ");
        }
    }
}

void console::clear_abs(int x, int y, int w, int h)
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            mvprintw(y+i, (x+j), " ");
        }
    }
}






void console::move(int x, int y)
{
    ::move(y+offsetY, x+offsetX);
}

void console::print(const std::string& s)
{

    printw(s.c_str());
}

void console::printCenter(std::string s, int y,  bool h)
{
    attron(COLOR_PAIR(7));
    move((int)(console::width/2)-(s.length()/2), y);
    if(h){
        print_highlight(s);
    }else{
        print(s);
    }
}



void console::print_highlight(std::string s)
{
    attron(A_REVERSE);
    print(s);
    attroff(A_REVERSE);
}

/**
 * Funkcja sprawdza wymiary wyświetlacza i zapisuje je do zmiennych width i height obiektu
 */
void console::resize()
{
    getmaxyx(stdscr, height, width);
//     offsetX = -width/4;
}
/**
 * Funkcja ustawia czas oczekiwania na wciśnięcie klawisza
 * @param delay czas w milisekundach
 */
void console::setTimeout(int delay)
{
    ::timeout(delay);
}

void console::wait() {
    while(getch()>0) {}
    return;
}

/**
 * Funkcja zwraca klawisz wciśnięty przez użytkownika
 * @return wartość ascii znaku z klawiatury. -1 gdy minął czas oczekiwania.
 */
key console::getInput()
{
    return bindings[getch()];
}
/**
 * Funkcja rysuje kafelek na podanych współrzędnych i w podanym kolorze
 * @param x współrzędna x w polu gry
 * @param y współrzędna y w polu gry
 * @param color wartość od 1-7 oznaczająca kolor kafelka
 */
void console::drawTile(int x, int y, int color, bool ghost)
{
    if(y>0) {
        attron(COLOR_PAIR(color));
        move(x*2+(width/2)-(gameFieldWidth), y);
        if(font.reversed){
            if(!ghost) {
                print_highlight(font.block);
            } else {
                print_highlight(font.ghost);
            }
            
        }else{
            if(!ghost) {
                print(font.block);
            } else {
                print(font.ghost);
            }
        }
    }
}

std::string centrify(std::string str, const int &w){
    int rem = w-str.length();
    std::string out;
    for(int i = 0; i < rem/2; ++i){
        out += " ";
    }
    out += str;
    while(out.length() < w){
        out +=" ";
    }
    return out;
}

int console::prompt_key(std::string question)
{
    return (int) prompt(question, 1)[0];
}

std::string console::prompt(std::string question, int limit)
{
    attron(COLOR_PAIR(7));
    std::string out;
    if(!limit)limit=question.length();
    int corX, corY;
    int w = std::max((int)question.length(), limit);
    question = centrify(question, w);
    corX = (width/2)-(w/2);
    corY = height/2-3;
    clear_abs(corX, corY, w+2, 6);
    move(corX, corY+1);
    print(font.corNE);
    for(int i = 0; i<w;++i){
        print(font.hLine);
    }
    print(font.corNW);
    move(corX, corY+5);
    print(font.corSW);
    for(int i = 0; i<w;++i){
        print(font.hLine);
    }
    print(font.corSE);
    move(corX, corY+2);
    print(font.vLine+question+font.vLine);
    move(corX, corY+3);
    print(font.vLine);
    move(corX+w+1, corY+3);
    print(font.vLine);
    move(corX, corY+4);
    print(font.vLine);
    move(corX+w+1, corY+4);
    print(font.vLine);
    int q;
    bool loop = true;
    while(loop){
        q = ::getch();
        if(q>0){
            if(q=='\n'||q==27) 
                loop = false;
            else{
                if(q==8||q==127){
                    if(out.length()){
                        out.pop_back(); 
                        //clear_abs(corX+1, corY+3, out.length()+1, 1);
                    }
                }else if(out.length()<limit){
                    out+=(char)q;
                }
                
                move(corX+1, corY+4);
                print(centrify(out, w));
                
                
                
            }
        }
    }
    return out;
}



/**
 * Funkcja rysuje prostokąt pustej przestrzeni na podanych współrzędnych o podanych wymiarach
 * @param x wpółrzędna x
 * @param y współrzędna y
 * @param w szerokość prostokąta
 * @param h wysokość prostokąta
 */
void console::drawEmpty(int x, int y, int w, int h)
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            move( (x+j)*2+(width/2)-(gameFieldWidth), y+i); 
            print(font.empty);
        }
    }
}

/**
 * Funckcja wypisuje stan gry czyli wynik, poziom oraz ile linii trzeba skasować żeby wejść na wyższy poziom
 * @param scr Wynik gracza
 * @param lvl Poziom trudności
 * @param goal Ile jeszcze brakuje do następnego poziomu
 */

void console::printData(int scr, int lvl, int goal)
{
    clear(gameFieldWidth, 1, 7, gameFieldHeight);
    attron(COLOR_PAIR(7));
    move((width/2)+gameFieldWidth+2, 1);
    print("Level:"+std::to_string(lvl));
    move((width/2)+gameFieldWidth+2, 2);
    print("To LvlUp:"+std::to_string(goal));
    move((width/2)+gameFieldWidth+2, 3);

    print("Score: "+std::to_string(scr));



    move((width/2)+gameFieldWidth+2, 4);
    print("Hold:");
    move((width/2)+gameFieldWidth+2, 9);
    print("Next:");
}


int console::getWidth()
{
    return width;
}
int console::getHeight()
{
    return height;
}


