#include "console.h"
#include <curses.h>

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
 * Destruktor konsoli
 */
console::~console()
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

void display::clear(int x, int y, int w, int h)
{
    attron(COLOR_PAIR(7));
    for(int i = 0; i < h;i++){
        for(int j = 0; j < w; j++){
            mvprintw(y+i+offsetY, (x+j)*2+(width/2)-(fieldWidth)+offsetX, "  ");
        }
    }    
}

/**
 * Funckcja wypisuje stan gry czyli wynik, poziom oraz ile linii trzeba skasować żeby wejść na wyższy poziom
 * @param scr Wynik gracza
 * @param lvl Poziom trudności
 * @param goal Ile jeszcze brakuje do następnego poziomu
 */


void display::printData(int scr, int lvl, int goal)
{
    clear(fieldWidth+1, 1, 6, fieldHeight);
    move((width/2)+fieldWidth+2, 1);
    print("Level:"+std::to_string(lvl));
    move((width/2)+fieldWidth+2, 2);
    print("To LvlUp:"+std::to_string(goal));
    move((width/2)+fieldWidth+2, 3);
    print("Score:"+std::to_string(scr));
    move((width/2)+fieldWidth+2, 4);
    print("Hold:");
    move((width/2)+fieldWidth+2, 9);
    print("Next:");
    
}


void display::move(int x, int y)
{
    ::move(y+offsetY, x+offsetX);
}

void display::print(std::string s)
{
    attron(COLOR_PAIR(7));
    printw(s.c_str());
}

/**
 * Funkcja sprawdza wymiary wyświetlacza i zapisuje je do zmiennych width i height obiektu
 */
void display::resize()
{
    getmaxyx(stdscr, height, width);
//     offsetX = -width/4;
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
void display::drawTile(int x, int y, int color, bool ghost)
{
    attron(COLOR_PAIR(color));
    attron(A_REVERSE);
    if(!ghost)
        mvprintw(y+offsetY, x*2+(width/2)-(fieldWidth)+offsetX, "  ");
    else
        mvprintw(y+offsetY, x*2+(width/2)-(fieldWidth)+offsetX, "[]");
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
            mvprintw(y+i+offsetY, (x+j)*2+(width/2)-(fieldWidth)+offsetX, "[]");
        }
    }
}

int display::getWidth()
{
    return width;
}

 
