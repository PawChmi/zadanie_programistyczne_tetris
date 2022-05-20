#pragma once
#include "console.h"
#include "gamemodes.h"
#include "dial.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

class menu
{
    dial choice, gamemode, lvl, width, height, theme;
    console * conptr;
    int animation_frame;
    const int colors[6] = {4, 2, 3, 6,  1, 5};
    std::map<int, std::string> scores;
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
    void draw()
    {
        conptr->clear();
        for ( int i = 0; i<(int)logo.size(); ++i ) {
            std::vector<int> l = logo[i];
            int t = l[2]+ ( ( animation_frame ) %6 );
            if ( t>5 ) t -= 6;
            conptr->drawTile ( l[0], l[1]+1- ( l[2]+1==animation_frame%8 ), colors[t] );
        }
        int line = 8;
        switch ( gamemode ) {
        case 0:
            conptr->printCenter ( "Gamemode: Classic", line++, ( choice== 0 ) );
            break;
        case 1:
            conptr->printCenter ( "Gamemode: Justice", line++, ( choice == 0 ) );
            break;
        case 2:
            conptr->printCenter ( "Gamemode: Ludicrous", line++, ( choice== 0 ) );
            break;
        }

        conptr->printCenter ( "LVL:"+std::to_string ( lvl ), line++, ( choice== 1 ) );
        conptr->printCenter ( "Width:"+std::to_string ( width ), line++, ( choice== 2 ) );
        conptr->printCenter ( "Height:"+std::to_string ( height ), line++, ( choice== 3 ) );
        conptr->printCenter ( "Theme: "+fonts[theme].name, line++, ( choice== 4 ) );
        

        conptr->printCenter ( "Controls", line++, ( choice== 5 ) );
        ++line;
        conptr->printCenter ( "HIGH SCORES", line++ );
        for ( auto el : scores ) {
            if ( line < conptr->getHeight() )
                conptr->printCenter ( el.second+"\t"+std::to_string ( -el.first ), line++ );
        }




    }
    void configureKeyBinds()
    {
        std::map<int, key> bindings;

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
                kb_file << k.second << " ";
                if ( k.first > 5 )
                    kb_file << k.first ;
                else
                    kb_file << k.first+400;
                kb_file<<std::endl;

            }
            kb_file.close();
            conptr->rebind ( kb_file_name );

        }
    }
public:
    std::shared_ptr<Engine> result()
    {
        bool L1 = 1;
        conptr->setGameField ( 0, 0 );
        while ( L1 ) {
            draw();

            key ch = conptr -> getInput();
            if ( ch == QUIT ) return nullptr;
            else if ( ch == RIGHT ) choice++;
            else if ( ch == LEFT ) choice--;
            else if ( ch == ROT_R ) {
                switch ( choice ) {
                case 0:
                    gamemode++;
                    break;
                case 1:
                    lvl++;
                    break;
                case 2:
                    width++;
                    break;
                case 3:
                    height++;
                    break;
                case 4:
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
                    lvl--;
                    break;
                case 2:
                    width--;
                    break;
                case 3:
                    height--;
                    break;
                case 4:
                    theme--;
                    conptr->setFont(fonts[theme]);
                    break;
                }
            } else if ( ch == HARDDROP ) {
                if ( !choice ) {

                    switch ( gamemode ) {
                    case 0:
                        return std::make_shared<classic> ( *conptr, width, height, lvl );
                        break;
                    case 1:
                        return std::make_shared<justice> ( *conptr, width, height, lvl );
                        break;
                    case 2:
                        return std::make_shared<ludicrous> ( *conptr, width, height, lvl );
                        break;
                    }
                } else if ( choice==5 ) {
                    configureKeyBinds();
                }

            } else if ( ch==NONE ) {
                animation_frame++;
            }
        }
        return nullptr;
    }
    menu ( console & c, const int thm )
    {
        conptr = &c;
        choice = {0, 5};
        theme = {thm, (int)fonts.size()-1, 0};
        lvl = {1, 100, 1};
        height = {20, 100, 10};
        width = {10, conptr->getWidth() /2-1, 6};
        gamemode = {0, 2};
        conptr->setTimeout ( 250 );
        std::ifstream scr_file ( "scores.dat" );
        if ( scr_file ) {
            std::string tmp;
            while ( getline ( scr_file, tmp ) ) {
                int s;
                std::string name;
                std::stringstream ss ( tmp );
                ss >> s;
                getline ( ss, scores[-s] );
            }

        }
        scr_file.close();
    }
    ~menu()
    {
        std::ofstream scr_file ( "scores.dat" );
        if ( scr_file ) {
            for ( auto el:scores ) {
                scr_file << -el.first << " " << el.second <<std::endl;
            }
        }
        scr_file.close();
    }

    void record ( int score, std::string name )
    {
        if ( name.find_first_not_of ( " \n\t\v\f\r" ) == std::string::npos ) //the string is just white spaces
            name = "Player";
        scores[-score] = name;
    }
};


std::ostream& operator << ( std::ostream& o, const key& K )
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

