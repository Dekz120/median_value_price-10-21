#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QCandlestickSet>
#include <QtCore/QTextStream>

#include "medial_value_price/median_chart.h"
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
};

class CandlestickDataReader : public QTextStream
{
public:
    explicit CandlestickDataReader(QIODevice *device);
    ~CandlestickDataReader();

    void readFile(QIODevice *device);
    QCandlestickSet *readCandlestickSet();
};

median_chart getCandleData(std::ifstream& ifs);
QCandlestickSet *fillGraph(stonk_candle& candle);

#endif // MAINWINDOW_H
