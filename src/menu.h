#pragma once
#include "console.h"
#include "upsidedown.h"
#include "shakey.h"
#include "infection.h"
#include "classic.h"
#include "dial.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>

/**
 * Obiekt, który wyświetla menu główne, które pozwala użytkownikowi na regulację ustawień gry, wybór wariantu gry oraz zestawu bloków.
 */

class Menu
{
    Dial choice, gamemode, lvl, width, height, theme, block_set;
    Console * conptr;
    size_t animation_frame=0;
    const int colors[6] = {4, 2, 3, 6,  1, 5};
    std::map<int, std::string> scores;
    std::vector< std::vector<std::shared_ptr<Block>>> blockSets = {
        {
            std::make_shared<block_J> ( ),
            std::make_shared<block_I> ( ),
            std::make_shared<block_O> ( ),
            std::make_shared<block_L> ( ),
            std::make_shared<block_S> ( ),
            std::make_shared<block_Z> ( ),
            std::make_shared<block_T> ( ),
        },{
            std::make_shared<block_A> ( ),
            std::make_shared<block_B> ( ),
            std::make_shared<block_C> ( ),
            std::make_shared<block_D> ( ),
            std::make_shared<block_E> ( ),
            std::make_shared<block_F> ( ),
            std::make_shared<block_G> ( ),
            std::make_shared<block_H> ( ),
            std::make_shared<block_I> ( ),
            std::make_shared<block_J> ( ),
            std::make_shared<block_K> ( ),
            std::make_shared<block_L> ( ),
            std::make_shared<block_M> ( ),
            std::make_shared<block_N> ( ),
            std::make_shared<block_O> ( ),
            std::make_shared<block_P> ( ),
            std::make_shared<block_Q> ( ),
            std::make_shared<block_R> ( ),
            std::make_shared<block_S> ( ),
            std::make_shared<block_T> ( ),
            std::make_shared<block_U> ( ),
            std::make_shared<block_V> ( ),
            std::make_shared<block_W> ( ),
            std::make_shared<block_X> ( ),
            std::make_shared<block_Y> ( ),
            std::make_shared<block_Z> ( ),
        },{
            std::make_shared<block_T> ( ),
        },{
            std::make_shared<block_dot> ( 0,0, yellow),
            std::make_shared<block_dot> ( 0,0, red),
            std::make_shared<block_dot> ( 0,0, green),
            std::make_shared<block_dot> ( 0,0, blue),
            std::make_shared<block_dot> ( 0,0, cyan),
            std::make_shared<block_dot> ( 0,0, orange),
            std::make_shared<block_dot> ( 0,0, purple),

        }
    };

    std::vector<Font> fonts = {
        {1,"Boxy", "[]", "[]", "  ", "-", "|", "+","+", "+", "+"},
        {0,"Thin", "::", "##", "[]", "-", "|", "+","+", "+", "+"},
        {0,"Bubble", "::", "@@", "()", "-", "|", "O","O", "O", "O"},
        {0,"Classic", "▫️️ ", "⏹️ ", "🔲", "━", "┃", "┓","┏", "┗", "┛"},
        {1,"Inverted Classic", "▫️️ ", "⏹️ ", "🔲", "━", "┃", "┓","┏", "┗", "┛"}
    };
    const std::vector<std::vector<int>>logo = {
        /*T*/    {-12,1,0},{-11,1,0},{-10,1,0},{-11,2,0},{-11,3,0},{-11,4,0},{-11,5,0},
        /*E*/    {-8,1,1},{-7,1,1},{-6,1,1},{-8,2,1},{-8,3,1},{-7,3,1},{-8,4,1},{-8,5,1},{-7,5,1},{-6,5,1},
        /*T*/    {-4,1,2},{-3,1,2},{-2,1,2},{-3,2,2},{-3,3,2},{-3,4,2},{-3,5,2},
        /*R*/    {0,1,3},{1,1,3},{0,2,3},{2,2,3},{0,3,3},{1,3,3},{0,4,3},{2,4,3},{0,5,3},{2,5,3},
        /*I*/    {5,1,4},{5,3,4},{5,4,4},{5,5,4},
        /*S*/    {8,1,5},{9,1,5},{10,1,5},{8,2,5},{8,3,5},{9,3,5},{10,3,5},{10,4,5},{8,5,5},{9,5,5},{10,5,5}
    };

    void drawLogo() noexcept {
        switch(gamemode) {
        case 3:
            for ( int i = 0; i<(int)logo.size(); ++i ) {
                std::vector<int> l = logo[i];
                int a = animation_frame%20/2-2;
                conptr->drawTile ( l[0], l[1]+2, colors[1-(a<l[2])+(a>l[2])] );
            }
            break;
        case 1:
            for ( int i = 0; i<(int)logo.size(); ++i ) {
                std::vector<int> l = logo[i];
                conptr->drawTile ( l[0], 5-l[1]+2+( l[2]+1==animation_frame%8 ), colors[l[2]] );
            }
            break;
        case 2:
            for ( int i = 0; i<(int)logo.size(); ++i ) {
                std::vector<int> l = logo[i];
                conptr->drawTile ( l[0]+( l[2]+1==animation_frame%8 ), l[1]+2, colors[l[2]] );
            }
            break;
        default:
            for ( int i = 0; i<(int)logo.size(); ++i ) {
                std::vector<int> l = logo[i];
                conptr->drawTile ( l[0], l[1]+2-( l[2]+1==animation_frame%8 ), colors[l[2]] );
            }
            break;
        }
    }

    void draw() noexcept
    {
        conptr->clear();
        conptr->setGameField(0, 10);
        drawLogo();
        int line = 9;
        switch ( gamemode ) {
        case 0:
            conptr->printCenter ( "Gamemode: Classic", line++, ( choice== 0 ) );
            break;
        case 1:
            conptr->printCenter ( "Gamemode: UpsideDown ", line++, ( choice== 0 ) );
            break;
        case 2:
            conptr->printCenter ( "Gamemode: Shakey ", line++, ( choice== 0 ) );
            break;
        case 3:
            conptr->printCenter ( "Gamemode: Infection ", line++, ( choice== 0 ) );
            break;
        }
        std::string s((int)blockSets[block_set].size(), ' ');
        conptr->printCenter ( "Block Set: "+ s, line, ( choice== 1 ) );

        conptr->move(conptr->getX()-(int)blockSets[block_set].size(), line++);
        for(auto B : blockSets[block_set]) {
            conptr->print(B->getName(), (int)B->getColor());
        }
        conptr->printCenter ( "LVL:"+std::to_string ( lvl ), line++, ( choice== 2 ) );
        conptr->printCenter ( "Width:"+std::to_string ( width ), line++, ( choice== 3 ) );
        conptr->printCenter ( "Height:"+std::to_string ( height ), line++, ( choice== 4 ) );
        conptr->printCenter ( "Theme: "+fonts[theme].name, line++, ( choice== 5 ) );


        conptr->printCenter ( "Controls", line++, ( choice== 6 ) );
        ++line;
        if(choice!=6)
            conptr->printCenter ( "Press <HARDDROP> to start", line++, true);
        else 
            conptr->printCenter ( "Press <HARDDROP> to configure key binds", line++, true);

        conptr->printCenter ( "HIGH SCORES", line++ );
        for ( auto el : scores ) {
            if ( line < conptr->getHeight() )
                conptr->printCenter ( el.second+"\t"+std::to_string ( -el.first ), line++ );
        }

    }
    void configureKeyBinds() noexcept
    {
        std::map<int, keyCode> bindings;

        bindings[conptr->prompt_key ( "     left       " )] = LEFT;
        bindings[conptr->prompt_key ( "     right      " )] = RIGHT;
        bindings[conptr->prompt_key ( "   soft drop    " )] = DROP;
        bindings[conptr->prompt_key ( "   hard drop    " )] = HARDDROP;
        bindings[conptr->prompt_key ( "  rotate left   " )] = ROT_L;
        bindings[conptr->prompt_key ( "  rotate right  " )] = ROT_R;
        bindings[conptr->prompt_key ( "      hold      " )] = HOLD;
        std::string kb_file_name=conptr->prompt ( "Filename?", 20 );
        std::ofstream kb_file ( kb_file_name );
        if ( kb_file ) {
            for ( auto k : bindings ) {
                kb_file << (keyCode)k.second << " "<<k.first+256*( k.first <= 5 );
                kb_file<<std::endl;
            }
            kb_file.close();
            conptr->rebind ( kb_file_name );
        }
    }
public:
    std::shared_ptr<Engine> result() noexcept
    {
        conptr->setGameField ( 0, 0 );
        while ( true ) {
            draw();
            keyCode ch = conptr -> getInput();
            if ( ch == QUIT ) 
                return nullptr;
            else if ( ch == RIGHT ) 
                choice++;
            else if ( ch == LEFT ) 
                choice--;
            else if ( ch == ROT_R ) {
                switch ( choice ) {
                case 0:
                    gamemode++;
                    break;
                case 1:
                    block_set++;
                    break;
                case 2:
                    lvl++;
                    break;
                case 3:
                    width++;
                    break;
                case 4:
                    height++;
                    break;
                case 5:
                    theme++;
                    conptr->setFont(fonts[theme]);
                    break;
                }
            } else if ( ch == ROT_L ) {
                switch ( choice ) {
                case 0:
                    gamemode--;
                    break;
                case 1:
                    block_set--;
                    break;
                case 2:
                    lvl--;
                    break;
                case 3:
                    width--;
                    break;
                case 4:
                    height--;
                    break;
                case 5:
                    theme--;
                    conptr->setFont(fonts[theme]);
                    break;
                }
            } else if ( ch == HARDDROP ) {
                if ( choice==6 ) {
                    configureKeyBinds();
                }
                else {

                    switch ( gamemode ) {
                    case 0:
                        return std::make_shared<Classic> ( *conptr, blockSets[block_set], width, height, lvl  );
                        break;
                    case 1:
                        return std::make_shared<UpsideDown> ( *conptr, blockSets[block_set], width, height, lvl );
                        break;
                    case 2:
                        return std::make_shared<Shakey> ( *conptr, blockSets[block_set], width, height, lvl );
                        break;
                    case 3:
                        return std::make_shared<Infection> ( *conptr, blockSets[block_set], width, height, lvl );
                        break;
                    }
                }

            } else if ( ch==NONE ) {
                animation_frame++;
            }
        }
        return nullptr;
    }
    Menu ( Console & c, const int thm=0 ) noexcept
    {
        conptr = &c;
        choice = {0, 6};

        theme = {((thm<(int)fonts.size())?thm:0), (int)fonts.size()-1, 0};

        block_set = {0, (int)blockSets.size()-1, 0};
        conptr->setFont(fonts[theme]);

        lvl = {1, 100, 1};
        height = {20, 100, 10};
        width = {10, conptr->getWidth() /2-20, 6};
        gamemode = {0, 3};
        conptr->setTimeout ( 250 );
        std::ifstream scr_file ( "scores.dat" );
        try {
            LoadScores(scr_file);
        } catch(...) {
            scores.clear();
            scores[1]="ERROR LOADING SCORES";
            scores[2]="Please inspect \"scores.dat\" file";
        }

    }
    void LoadScores(std::ifstream &file) {

        if ( file ) {
            std::string tmp;
            while ( getline ( file, tmp ) ) {
                int score;
                std::string name;
                std::stringstream ss ( tmp );
                ss >> score;
                getline ( ss, name );
                this->scores[-score] = name.substr(1);
            }
        }
        file.close();

    }
    ~Menu() noexcept
    {
        std::ofstream scr_file ( "scores.dat" );
        if ( scr_file ) {
            for ( auto el:scores ) {
                if(el.first<=0)
                    scr_file << -el.first << " " << el.second <<std::endl;
            }
        }
        scr_file.close();
    }

    void record ( int score, std::string name, std::string mode) noexcept
    {
        if ( name.find_first_not_of ( " \n\t\v\f\r" ) == std::string::npos ) //the string is just white spaces
            name = "Player";
        scores[-score] = name+mode;
    }
};


