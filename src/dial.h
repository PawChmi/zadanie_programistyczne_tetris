#pragma once

class dial
{
    int value;
    int max;
    int min;
public:
    dial ( int val=0, int max=0, int min = 0 ) : value ( val ), max ( max ),  min ( min ) {};
    void turnUp()
    {
        if ( value<max ) value++;
    }
    void turnDown()
    {
        if ( value>min ) value--;
    }
    void operator++ ( int )
    {
        turnUp();
    }
    void operator-- ( int )
    {
        turnDown();
    }
    int val() const noexcept
    {
        return value;
    }
    operator int()
    {
        return value;
    }

};
