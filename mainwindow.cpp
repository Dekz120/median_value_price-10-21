#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medial_value_price/median_chart.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : QTextStream(device)
{
}

CandlestickDataReader::~CandlestickDataReader()
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

median_chart getCandleData(std::ifstream& ifs)
{
    int size = 0;
    string tmp_str;
    while (ifs) { getline(ifs, tmp_str, '\n'); size++; }
    time_frame TF = time_frame::M5;
    median_chart mc(size-2, TF);

    ifs.clear(),
    ifs.seekg(0);

    getline(ifs, tmp_str, '\n');

    int i = 0;
    tmp_str.clear();
    while (ifs && i < size-2)
    {
        getline(ifs, tmp_str, ';');
        getline(ifs, tmp_str, ';');//missing name and timeframe
        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].time.tm_year = stoi(tmp_str.substr(0, 4));
        mc[i].time.tm_mon = stoi(tmp_str.substr(4, 2)) - 1;
        mc[i].time.tm_mday = stoi(tmp_str.substr(6, 2));

        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].time.tm_hour = stoi(tmp_str.substr(0, 2));
        mc[i].time.tm_min = stoi(tmp_str.substr(2, 2));
        mc[i].time.tm_sec = stoi(tmp_str.substr(4, 2));

        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].open_price = stof(tmp_str);
        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].high_price = stof(tmp_str);
        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].low_price = stof(tmp_str);
        tmp_str.clear();
        getline(ifs, tmp_str, ';');
        mc[i].close_price = stof(tmp_str);

        getline(ifs, tmp_str, '\n');
        mc[i].value = stoi(tmp_str);
        i++;
    }
    return mc;

}

QCandlestickSet *fillGraph(stonk_candle& candle)
{

    QCandlestickSet *candlestickSet = new QCandlestickSet(candle.time.tm_wday);
    candlestickSet->setOpen(candle.open_price);
    candlestickSet->setHigh(candle.high_price);
    candlestickSet->setLow(candle.low_price);
    candlestickSet->setClose(candle.close_price);
    //! [4]

    return candlestickSet;
}


