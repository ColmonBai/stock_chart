#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMinKLineChart();
    void initAmountChart();
    void intiMinLineChart();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
