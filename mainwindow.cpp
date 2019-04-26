#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


#include "candlestickdatareader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMinKLineChart();
    initAmountChart();
    intiMinLineChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow:: initMinKLineChart()
{
     //! [1]
     QCandlestickSeries *acmeSeries = new QCandlestickSeries();
     acmeSeries->setName("分钟k线图");
     acmeSeries->setIncreasingColor(QColor(Qt::green));
     acmeSeries->setDecreasingColor(QColor(Qt::red));
     //! [1]

     //! [2]
     QFile acmeData(":acme");
   //  if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
    //     return 1;
     acmeData.open(QIODevice::ReadOnly | QIODevice::Text);

     QStringList categories;

     CandlestickDataReader dataReader(&acmeData);
     while (!dataReader.atEnd()) {
         QCandlestickSet *set = dataReader.readCandlestickSet();
         if (set) {
             acmeSeries->append(set);
             categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
         }
     }
     //qDebug()<< categories;
     //! [2]

     //! [3]
     QChart *chart = new QChart();
     chart->legend()->hide();
     chart->addSeries(acmeSeries);
     //chart->setTitle("平安银行");
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
     //chart->legend()->setVisible(true);
     //chart->legend()->setAlignment(Qt::AlignBottom);
     //! [5]

     //! [6]
     //QChartView *chartView = new QChartView(chart);
     //chartView->setRenderHint(QPainter::Antialiasing);
     //! [6]
     //!
     chart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
     chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
     chart->setBackgroundRoundness(0);//设置背景区域无圆角

     ui->minKWidget->setChart(chart);
     ui->minKWidget->setRenderHint(QPainter::Antialiasing);
}
 void MainWindow::initAmountChart()
 {
     QBarSet *set0 = new QBarSet("Up");
     QBarSet *set1 = new QBarSet("Down");


     //set0->setColor(Qt::red);
     set0->setColor(Qt::green);
     set1->setColor(Qt::red);

     *set0 << 1 << 0 << 0 << 4 << 0 << 6
           << 5 << 0 << 0 << 4 << 0 << 7
           << 1 << 0 << 0 << 4 << 0 << 6;
     *set1 << 0 << 5 << 8 << 0 << 8 << 0
           << 0 << 6 << 7 << 0 << 4 << 0
           << 0 << 5 << 8 << 0 << 8 << 0;
 //![1]

 //![2]
     QBarSeries *series = new QBarSeries();
     series->append(set0);
     series->append(set1);

 //![2]

 //![3]
     QChart *chart = new QChart();
     chart->legend()->hide();
     chart->addSeries(series);
     //chart->setTitle("交易量");
     chart->setAnimationOptions(QChart::SeriesAnimations);
 //![3]

 //![4]
     QStringList categories;
     categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
     QBarCategoryAxis *axisX = new QBarCategoryAxis();
     //axisX->append(categories);
     chart->addAxis(axisX, Qt::AlignBottom);
     series->attachAxis(axisX);

     QValueAxis *axisY = new QValueAxis();
     axisY->setRange(0,15);
     chart->addAxis(axisY, Qt::AlignLeft);
     series->attachAxis(axisY);
 //![4]

 //![5]
     //chart->legend()->setVisible(true);
     //chart->legend()->setAlignment(Qt::AlignBottom);
         chart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
         chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
         chart->setBackgroundRoundness(0);//设置背景区域无圆角

         ui->amountWidget->setChart(chart);
         ui->amountWidget->setRenderHint(QPainter::Antialiasing);
 }
void MainWindow::intiMinLineChart()
{
    //![1]
        QLineSeries *series = new QLineSeries();
    //![1]

    //![2]
        series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);
        *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6)
                << QPointF(18, 3) << QPointF(20, 2);
    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        //chart->setTitle("分时图");
    //![3]

    //![4]
        //QChartView *chartView = new QChartView(chart);
        //chartView->setRenderHint(QPainter::Antialiasing);
    //![4]
    //!
        chart->layout()->setContentsMargins(0, 0, 0, 0);//设置外边界全部为0
        chart->setMargins(QMargins(0, 0, 0, 0));//设置内边界全部为0
        chart->setBackgroundRoundness(0);//设置背景区域无圆角

        ui->minLineWidget->setChart(chart);
        ui->minLineWidget->setRenderHint(QPainter::Antialiasing);
}
