#ifndef MEDIAN_CHART_H_INCLUDED
#define MEDIAN_CHART_H_INCLUDED
#include "stonk_candle.h"
#include <vector>
#include <list>
#include <memory>
#include <functional>

using namespace std;
enum class time_frame { M1 , M5 , M30 , M60 , H4 , D1 , W , M  };
enum class condition_func {mvalPerPeriod=1, mvalPerValue=2};

struct m_vanlue_price {
    float price;
    unsigned long long value;
    tm time; //0-11 month
    m_vanlue_price() :price(0), value(0) {};
};

class median_chart {
private:
    time_frame tf;
    unique_ptr< vector<stonk_candle>> mchart;
public:
    median_chart(const int chart_size, time_frame tmfr) : mchart(new vector < stonk_candle>(chart_size)), tf(tmfr){}
    list< m_vanlue_price> calculateMVal(const int value, condition_func cf);
    stonk_candle& operator[](const int i)
    {
        return (*mchart)[i];
    }
};

list< m_vanlue_price> median_chart::calculateMVal(const int var, condition_func cf)
{
    list< m_vanlue_price> horizon_chart;
    m_vanlue_price tmp_mvp;
    int i;

    std::function<bool(int&)> cond[2];
    cond[0] = [&](int& k) {return (k % var == 0); };
    cond[1] = [&](int& k) {return (0.95 < (unsigned long double)tmp_mvp.value / var || k == 0); };
    for (i = 0; i < mchart->size(); i++)
    {
        if (cond[(int)cf - 1](i)) //The diffirence is condition only
        {
            if (i != 0)
            {
                tmp_mvp.price = tmp_mvp.price / tmp_mvp.value;
                horizon_chart.push_back(tmp_mvp);
                tmp_mvp.price = 0; tmp_mvp.value = 0;
            }
            tmp_mvp.time = (*mchart)[i].time;
        }
        tmp_mvp.value += (*mchart)[i].value;
        tmp_mvp.price += ((*mchart)[i].high_price + (*mchart)[i].low_price) / 2 * ((*mchart)[i].value);

    }
    tmp_mvp.price = tmp_mvp.price / tmp_mvp.value;
    horizon_chart.push_back(tmp_mvp);
    return horizon_chart;
}

#endif //
