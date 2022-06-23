#ifndef console_H
#define console_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

/**
 * Struktura przechowująca ciągi znaków, które konsola używa do wyświetlania określonych elementów
 */
struct Font {
    bool reversed; ///< czy odwracać kolory
    std::string name;
    std::string empty; ///< puste pole, niezajęte przez blok
    std::string ghost; ///< blok ducha
    std::string block; ///< normalny blok i zajęte pola
    std::string hLine; ///< pionowa linia
    std::string vLine; ///< pozioma linia
    std::string corNW; ///< lewy góny róg
    std::string corNE; ///< prawy górny róg
    std::string corSW; ///< lewy dolny róg
    std::string corSE; ///< prawy dolny róg

};


enum keyCode {
    NONE = -1,
    UNKNOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    DROP = 3,
    HARDDROP = 4,
    ROT_L = 5,
    ROT_R = 6,
    HOLD = 7,
    PAUSE = 8,
    QUIT = 9,
    REFRESH = 10

};

inline std::ostream& operator << ( std::ostream& o, const keyCode& K )
{
    switch ( K ) {
    case LEFT:
        o << "left";
        break;
    case RIGHT:
        o << "right";
        break;
    case DROP:
        o << "drop";
        break;
    case HARDDROP:
        o << "harddrop";
        break;
    case HOLD:
        o << "hold";
        break;
    case ROT_L:
        o << "rotate_left";
        break;
    case ROT_R:
        o << "rotate_right";
        break;
    case PAUSE:
        o << "pause";
        break;
    case REFRESH:
        o << "pause";
        break;
    case QUIT:
        o << "pause";
        break;
    default:
        o << "unknown";
    };
    return o;
}

inline std::istream& operator >> (std::istream& i, keyCode& K)
{
    K = UNKNOWN;
    std::string S;
    if(i >> S)
    {
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

/**
 * Konsola, która wyświetla dane na ekranie i wczytuje wejście z klawiatury
 */
class Console {
    std::map<int, keyCode> bindings;
    int height;
    int width;
    int offsetX=0;
    int offsetY=-1;
    int gameFieldWidth=0;
    int gameFieldHeight=10;
    Font font;
    void clear_abs(int x, int y, int w=1, int h=1) noexcept;
public:
    Console(const std::string& keybind_filename) noexcept;
    ~Console() noexcept;
    keyCode getInput() noexcept;
    void wait() const noexcept;
    void rebind(const std::string& keybind_filename) noexcept;
    void setTimeout(const int delay) noexcept;
    void printData(const int scr,const int lvl, const int goal) noexcept;
    void drawTile(int x, int y, int color, bool ghost=false) noexcept;
    void drawEmpty(int x, int y, int w=1, int h=1) noexcept;
    void clear(const int x, const int y, const int w=1, const int h=1) noexcept;
    void clear() const noexcept;
    void resize() noexcept;
    void setGameField(const int w, const int h) noexcept;
    void setFont(const Font &f) noexcept
    {
        font = f;
    }
    int getWidth() const noexcept
    {
        return width;
    }
    int getHeight() const noexcept
    {
        return height;
    }
    int getX() const noexcept;
    void move(const int x, const int y) noexcept;
    void print(const std::string& s) noexcept;
    void print(const std::string& s, const short int c) noexcept;
    void print_highlight(std::string& s) noexcept;
    std::string prompt(std::string question, int limit = 0) noexcept;
    int prompt_key(std::string question) noexcept;
    void printCenter(std::string s, int y, bool h=false) noexcept;

};



#endif // console_ASCII_H
