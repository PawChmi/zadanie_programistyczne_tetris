#include "menu.h"

menu::menu(console & c) {
    conptr = &c;
    choice = {0, 4};
    lvl = {1, 100, 1};
    height = {20, 100, 10};
    width = {10, conptr->getWidth()/2-1, 6};
    gamemode = {0, 2};
    conptr->setTimeout(250);
    std::ifstream scr_file("scores.dat");
    if(scr_file){
        std::string tmp;
        while(getline(scr_file, tmp))
        {
            int s;
            std::string name;
            std::stringstream ss(tmp);
            ss >> s;
            getline(ss, scores[-s]);
        }
        
    }scr_file.close();
}
menu::~menu(){
    std::ofstream scr_file("scores.dat");
    if(scr_file){
        for(auto el:scores){
            scr_file << -el.first << " " << el.second <<std::endl;
        }
    }
    scr_file.close();
}
void menu::record(int score, std::string name)
{
    if(name.find_first_not_of(" \n\t\v\f\r") == std::string::npos) //the string is just white spaces
        name = "Player";
    scores[-score] = name;
}

int dial::val()
{
    return value;
}
void dial::turnUp(){
    if(value<max)value++;
};
void dial::turnDown(){
    if(value>min)value--;
};
void menu::draw() {
    conptr->clear();
    for(int i = 0;i<logo.size(); ++i) {
        std::vector<int> l = logo[i];
        int t = l[2]+((animation_frame)%6);
        if(t>5) t -= 6;
        conptr->drawTile(l[0], l[1]+1-(l[2]+1==animation_frame%8), colors[t]);
    }
    int line = 8;
    switch(gamemode) {
    case 0:
        conptr->printCenter("Gamemode: Classic", line++, (choice==0));
        break;
    case 1:
        conptr->printCenter("Gamemode: Justice", line++, (choice == 0));
        break;
    case 2:
        conptr->printCenter("Gamemode: Ludicrous", line++, (choice==0));
        break;
    }

    conptr->printCenter("LVL:"+std::to_string(lvl), line++, (choice==1));
    conptr->printCenter("Width:"+std::to_string(width), line++, (choice==2));
    conptr->printCenter("Height:"+std::to_string(height), line++, (choice==3));
    conptr->printCenter("Controls", line++, (choice==4));
    ++line;
    conptr->printCenter("HIGH SCORES", line++);
    for(auto el : scores){
        if(line < conptr->getHeight())
            conptr->printCenter(el.second+"\t"+std::to_string(-el.first), line++);
    }
    



}

std::shared_ptr<engine> menu::result() {
    bool L1 = 1;
    conptr->setGameField(0, 0);
    while(L1) {
        draw();
        
        key ch = conptr -> getInput();
        if(ch == QUIT) return nullptr;
        else if(ch == RIGHT) choice++;
        else if(ch == LEFT) choice--;
        else if(ch == ROT_R) {
            switch(choice) {
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
            }
        }
        else if(ch == ROT_L) {
            switch(choice) {
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
            }
        }
        else if (ch == HARDDROP){
            if(!choice) {

                switch(gamemode) {
                case 0:
                    return std::make_shared<classic>(*conptr, width, height, lvl);
                    break;
                case 1:
                    return std::make_shared<justice>(*conptr, width, height, lvl);
                    break;
                case 2:
                    return std::make_shared<ludicrous>(*conptr, width, height, lvl);
                    break;
                }
            }else if(choice==4){
                configureKeyBinds();
            }

        }else if(ch==NONE){
            animation_frame++;
        }
    }
    return nullptr;
}

std::ostream& operator << (std::ostream& o, const key& K) {
    switch(K){
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
void menu::configureKeyBinds(){
    std::map<int, key> bindings;
    bindings[conptr->prompt_key("     left       ")] = LEFT;
    bindings[conptr->prompt_key("     right      ")] = RIGHT;
    bindings[conptr->prompt_key("   soft drop    ")] = DROP;
    bindings[conptr->prompt_key("   hard drop    ")] = HARDDROP;
    bindings[conptr->prompt_key("  rotate left   ")] = ROT_L;
    bindings[conptr->prompt_key("  rotate right  ")] = ROT_R;
    bindings[conptr->prompt_key("      hold      ")] = HOLD;
    std::ofstream kb_file(conptr->prompt("Filename?", 20));
    if(kb_file){
        for(auto k : bindings){
            kb_file << k.second << " ";
            if(k.first > 5)
                    kb_file << k.first ;
            else
                    kb_file << k.first+400;
            kb_file<<std::endl;
            
        }
    }
}
