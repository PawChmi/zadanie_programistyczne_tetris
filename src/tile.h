#pragma once


typedef std::pair<double, double> coords;

class tile {
    coords Offset;
public:
    double x(){
        return Offset.first;
    }
    double y(){
        return Offset.second;
    }
    tile(double x, double y) : Offset(x, y) {}; 
    void rotR(){
        double temp = -Offset.second;
        Offset.second = Offset.first;
        Offset.first = temp;
    }
    void rotL(){
        double temp = -Offset.first;
        Offset.first = Offset.second;
        Offset.second = temp;
    }
};
