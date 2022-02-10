#ifndef STONK_CANDLE_H_INCLUDED
#define STONK_CANDLE_H_INCLUDED
#include <ctime>


using namespace std;


class stonk_candle { 
private:
    

public:
    float open_price, high_price, low_price, close_price;
    int value;
    tm time;

    stonk_candle() {};
    stonk_candle(float op, float hp, float lp, float cp, int val, tm tt):open_price(op), high_price(hp),
        low_price(lp), close_price(cp), value(val), time(tt) {};

};



#endif //
