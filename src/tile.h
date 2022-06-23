#pragma once


typedef std::pair<double, double> coords;

/**
 * Obiekt "kafelka", z pojedyńczych kafelków zbudowane są bloki
 */

class Tile {
    coords Offset;
public:
    double x()const noexcept {
        return Offset.first;
    }
    double y()const noexcept {
        return Offset.second;
    }
    Tile(double x, double y) noexcept : Offset(x, y) {};
    void rotR() noexcept{
        double temp = -Offset.second;
        Offset.second = Offset.first;
        Offset.first = temp;
    }
    void rotL() noexcept{
        double temp = -Offset.first;
        Offset.first = Offset.second;
        Offset.second = temp;
    }
};
