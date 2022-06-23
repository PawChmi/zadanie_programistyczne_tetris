#include "console.h"
#include <curses.h>

Console::Console(const std::string& keybind_filename) noexcept
{
    ::setlocale(LC_ALL, "");
    ::initscr();
    ::noecho();
    ::cbreak();
    ::keypad(stdscr, true);
    ::curs_set(0);
    if(!has_colors()) 
        ::endwin();
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
    attron(A_BOLD);
    rebind(keybind_filename);
    ::endwin();
}

void Console::rebind(const std::string& keybind_filename) noexcept
{
    bindings.clear();
    bindings = {//default keybinds
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
    std::ifstream file (keybind_filename);
    if(file) {
        keyCode K;
        int N;

        while(file >> K>>N) {
            bindings[N] = K;
        }
    }
}
/**
 * Destruktor konsoli
 */
Console::~Console() noexcept
{
    ::endwin();
}

/**
 * Funckcja ustawia w konsoli wielkość pola gry, żeby nie musiało być przekazywane za każdym razem kiedy chcemy coś wyświetlić.
 * @param w szerokość pola gry
 * @param h wysokość pola gry
 */
void Console::setGameField(const int w, const int h) noexcept
{
    gameFieldWidth = w;
    gameFieldHeight = h;
}

/**
 * Funkcja czyści wyświetlany ekran
 */
void Console::clear() const noexcept
{
    ::clear();
}

void Console::clear(int x, int y, int w, int h) noexcept
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            mvprintw(y+i+offsetY, (x+j)*2+(width/2)-(gameFieldWidth)+offsetX, "  ");
        }
    }
}

void Console::clear_abs(int x, int y, int w, int h) noexcept
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            mvprintw(y+i, (x+j), " ");
        }
    }
}

void Console::move(const int x, const int y) noexcept
{
    ::move(y+offsetY, x+offsetX);
}

int Console::getX() const noexcept {
    int x, y;
    getyx(stdscr, y, x);
    return x;
}
void Console::print(const std::string& s) noexcept
{

    printw(s.c_str());
}
void Console::print(const std::string& s, const short int c) noexcept
{
    attron(COLOR_PAIR(c));
    printw(s.c_str());
    attroff(COLOR_PAIR(c));
}

void Console::printCenter(std::string s, int y,  bool h) noexcept
{
    attron(COLOR_PAIR(7));
    move((int)(Console::width/2)-(s.length()/2), y);
    if(h) {
        print_highlight(s);
    } else {
        print(s);
    }
}

void Console::print_highlight(std::string& s) noexcept
{
    attron(A_REVERSE);
    print(s);
    attroff(A_REVERSE);
}

/**
 * Funkcja sprawdza wymiary wyświetlacza i zapisuje je do zmiennych width i height obiektu
 */
void Console::resize() noexcept
{
    getmaxyx(stdscr, height, width);
}

/**
 * Funkcja ustawia czas oczekiwania na wciśnięcie klawisza
 * @param delay czas w milisekundach
 */

void Console::setTimeout(const int delay) noexcept
{
    ::timeout(delay);
}

void Console::wait() const  noexcept
{
    while(getch()>0) {}
    return;
}

/**
 * Funkcja zwraca klawisz wciśnięty przez użytkownika
 * @return wartość ascii znaku z klawiatury. -1 gdy minął czas oczekiwania.
 */
keyCode Console::getInput() noexcept
{
    return bindings[getch()];
}
/**
 * Funkcja rysuje kafelek na podanych współrzędnych i w podanym kolorze
 * @param x współrzędna x w polu gry
 * @param y współrzędna y w polu gry
 * @param color wartość od 1-7 oznaczająca kolor kafelka
 */
void Console::drawTile(int x, int y, int color, bool ghost) noexcept
{
    if(y>0 and y<gameFieldHeight) {
        attron(COLOR_PAIR(color));
        move(x*2+(width/2)-(gameFieldWidth), y);
        if(font.reversed) {
            print_highlight(ghost? font.ghost: font.block);
        } else {
            print(ghost? font.ghost: font.block);
        }
    }
}

std::string centrify(std::string& str, int &w) noexcept
{
    int rem = w-str.length();
    std::string out;
    for(int i = 0; i < rem/2; ++i) {
        out += " ";
    }
    out += str;
    while((int)out.length() < w) {
        out +=" ";
    }
    return out;
}

int Console::prompt_key(std::string question) noexcept
{
    return (int) prompt(question, 1)[0];
}

std::string Console::prompt(std::string question, int limit) noexcept
{
    attron(COLOR_PAIR(7));
    std::string out;
    if(!limit)limit=question.length();
    int corX, corY;
    int w = std::max((int)question.length(), limit);
    question = centrify(question, w);
    corX = (width/2)-(w/2);
    corY = height/2-3;
    clear_abs(corX, corY, w+2, 5);
    move(corX, corY+1);
    print(font.corNE);
    for(int i = 0; i<w; ++i) {
        print(font.hLine);
    }
    print(font.corNW);
    move(corX, corY+5);
    print(font.corSW);
    for(int i = 0; i<w; ++i) {
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
    while(loop) {
        q = ::getch();
        if(q>0) {
            if(q=='\n'||q==27)
                loop = false;
            else {
                if(q==8||q==127) {
                    if(out.length()) {
                        out.pop_back();
                        //clear_abs(corX+1, corY+3, out.length()+1, 1);
                    }
                } else if((int)out.length()<limit) {
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
void Console::drawEmpty(int x, int y, int w, int h) noexcept
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

void Console::printData(const int scr,const int lvl,const int goal) noexcept
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
