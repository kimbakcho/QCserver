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
#include "mslotitem.h"
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
    ~MainWindow();

private slots:


    void on_ipadderbtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
