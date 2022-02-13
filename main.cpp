#include "mainwindow.h"

#include <QApplication>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    QCandlestickSeries *stonk = new QCandlestickSeries();
    stonk->setName("Stonk Name template");
    stonk->setIncreasingColor(QColor(Qt::green));
    stonk->setDecreasingColor(QColor(Qt::red));
    //! [1]

    //! [2]

    QStringList categories;
    using namespace std;
    std::ifstream ifs("gazp.txt");
    median_chart FullChart= getCandleData(ifs);

    int qwa=0;
    for (int i=0; i < FullChart.size(); i++)
    {
        QCandlestickSet *set = fillGraph(FullChart[i]);
        if (set) {
            stonk->append(set);qwa++;
            //categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
            categories << QString::number(i);
        }
    }
    //! [2]

    //! [3]
    QChart *chart = new QChart();
    chart->addSeries(stonk);
    chart->setTitle("Stonk name template");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //! [3]

    //! [4]
    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);
    //! [4]

    //! [5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //! [5]

    //! [6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [6]


    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
