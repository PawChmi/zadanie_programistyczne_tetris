#include "console.h"

#include <iostream>


 std::istream& operator >> (std::istream& i, key& K){
    K = UNKNOWN;
    std::string S;
    if(i >> S){
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
}

console::console(std::string keybind_filename) 
{

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
    std::ifstream file (keybind_filename);
    if(file){
        key K;
        int N;
        
        while(file >> K>>N){
            bindings[N] = K;
        }
    }
    std::cout << "bindings:"<<std::endl;
    for(auto p : bindings){
        std::cout << p.first << ":" << p.second << std::endl;
    }
}


/**
 * Destruktor konsoli
 */


/**
 * Funckcja ustawia w konsoli wielkość pola gry, żeby nie musiało być przekazywane za każdym razem kiedy chcemy coś wyświetlić.
 * @param w szerokość pola gry
 * @param h wysokość pola gry
 */
void console::setGameField(int w, int h)
{
    std::cout << "Wymiary" << w<<":"<<h<<std::endl;
    gameFieldHeight = h;
    gameFieldWidth = w;
    field = new char* [h];
    for(int i = 0; i < h; ++i){
        field[i] = new char[w];
    }
    
    
}

console::~console(){
    for(int i = 0; i < gameFieldHeight; ++i){
        delete[] field[i] ;
    }
    delete [] field;
}
/**
 * Funkcja czyści wyświetlany ekran
 */
void console::clear()
{
   for(int y = 0;y<gameFieldHeight;++y){
        for(int x = 0; x<gameFieldWidth;++x){
            field[y][x] = 0;
        }
        
    } 
}

void console::clear(int x, int y, int w, int h)
{  
}


void console::move(int x, int y)
{
    std::cout<< "Nowa pozycja"<<y+offsetY<<" "<< x+offsetX<<std::endl;
}

void console::print(std::string s)
{
std::cout << s<<std::endl;
}

/**
 * Funkcja sprawdza wymiary wyświetlacza i zapisuje je do zmiennych width i height obiektu
 */
void console::resize()
{
//     offsetX = -width/4;
}
/**
 * Funkcja ustawia czas oczekiwania na wciśnięcie klawisza
 * @param delay czas w milisekundach
 */
void console::setTimeout(int delay)
{

}
/**
 * Funkcja zwraca klawisz wciśnięty przez użytkownika
 * @return wartość ascii znaku z klawiatury. -1 gdy minął czas oczekiwania.
 */
key console::getInput()
{
    key x; std::cin >> x;
    return (key)x;
}
/**
 * Funkcja rysuje kafelek na podanych współrzędnych i w podanym kolorze
 * @param x współrzędna x w polu gry
 * @param y współrzędna y w polu gry
 * @param color wartość od 1-7 oznaczająca kolor kafelka
 */

void console::wait(){
    
}

void console::drawTile(int x, int y, int color, bool ghost)
{
    if(y<gameFieldHeight && x<gameFieldWidth && x>=0&&y>=0){
        if(ghost) {
            field[y][x] = 'x';
            
        }else { field[y][x] = color+'0';}
    }
//std::cout << "k:"<<x<<":"<<y<<"{"<<color<<","<<ghost<<"}"<<std::endl;

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
    if(y<gameFieldHeight && x<gameFieldWidth&& x>=0&&y>=0)
    field[y][x] = 0;
}

/**
 * Funckcja wypisuje stan gry czyli wynik, poziom oraz ile linii trzeba skasować żeby wejść na wyższy poziom
 * @param scr Wynik gracza
 * @param lvl Poziom trudności
 * @param goal Ile jeszcze brakuje do następnego poziomu
 */

void console::printData(int scr, int lvl, int goal)
{
    
    std::cout <<"Level:"<<std::to_string(lvl)<<std::endl;
    std::cout <<"goal:"<<std::to_string(goal)<<std::endl;
    std::cout <<"score:"<<std::to_string(scr)<<std::endl;
    for(int y = 0;y<gameFieldHeight;++y){
        for(int x = 0; x<gameFieldWidth;++x){
            if(field[y][x])std::cout << field[y][x];
            else std::cout << " ";
        }
        std::cout << std::endl;
    }
}


int console::getWidth()
{
    return width;
}

 
