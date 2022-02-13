// median_value.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "median_chart.h"
#include <string>

int draft()
{
    ifstream ofs("gazp.txt");
    int size = 0;
    string tmp_str;
    while (ofs) { getline(ofs, tmp_str, '\n'); size++; }
    time_frame TF = time_frame::M5;
    median_chart mc(size-2, TF);

    ofs.clear(),
    ofs.seekg(0);
    
    getline(ofs, tmp_str, '\n');
    
    int i = 0;
    tmp_str.clear();
    while (ofs && i < size-2)
    {
        getline(ofs, tmp_str, ';');
        getline(ofs, tmp_str, ';');//missing name and timeframe
        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].time.tm_year = stoi(tmp_str.substr(0, 4));
        mc[i].time.tm_mon = stoi(tmp_str.substr(4, 2)) - 1;
        mc[i].time.tm_mday = stoi(tmp_str.substr(6, 2));

        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].time.tm_hour = stoi(tmp_str.substr(0, 2));
        mc[i].time.tm_min = stoi(tmp_str.substr(2, 2));
        mc[i].time.tm_sec = stoi(tmp_str.substr(4, 2));

        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].open_price = stof(tmp_str);
        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].high_price = stof(tmp_str);
        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].low_price = stof(tmp_str);
        tmp_str.clear();
        getline(ofs, tmp_str, ';');
        mc[i].close_price = stof(tmp_str);

        getline(ofs, tmp_str, '\n');
        mc[i].value = stoi(tmp_str);
        i++;
    }



    list< m_vanlue_price> lee = mc.calculateMVal(300000000, condition_func::mvalPerPeriod);

    for (auto mvp : lee)
    {
        cout << mvp.price << ' '<< mvp.value <<' ' << mvp.time.tm_mday << '.' << mvp.time.tm_mon+1 <<endl;;
    } 

    
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
