#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ITEMCONNECT 0
#define ITEMSTATUS 1
#define ITEMIP 2
#define ITEMNAME 3
#define ITEMTYPE 4
#define ITEMSETUP 5
#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include "mslotitem.h"
#include "serversetform.h"
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMap<QString,mslotitem *> *itemmap;
    void mainwidgetinit();
    QSqlDatabase mdb;
    QSqlDatabase litedb;
    Serversetform *serversetform;

    ~MainWindow();

private slots:


    void on_ipadderbtn_clicked();

    void on_actionStart_triggered();

    void on_actionSetting_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
