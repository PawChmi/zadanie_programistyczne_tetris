#include "menu.h"
menu::menu(console & c) {
    conptr = &c;
    choice = {0, 3};
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
    ++line;
    conptr->printCenter("HIGH SCORES", line++);
    for(auto el : scores){
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
        else if (ch == HARDDROP&&!choice) {

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

        }else if(ch==NONE){
            animation_frame++;
        }
    }
    return nullptr;
}
