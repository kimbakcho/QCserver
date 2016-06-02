#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mdb =QSqlDatabase::addDatabase("QMYSQL","remotedb");
    litedb = QSqlDatabase::addDatabase("QSQLITE","localdb");

    ui->setupUi(this);
    mainwidgetinit();

    litedb.setDatabaseName("local.db");
    if(!litedb.open()){
        qDebug()<<"localdb open fail";
    }
    QSqlQuery litequery1(litedb);
    litequery1.exec("CREATE TABLE  IF NOT EXISTS systemset (remoteserverip TEXT, remoteserverport TEXT);");
    litequery1.exec("insert into systemset(remoteserverip,remoteserverport ) select \'127.0.0.1\',\'3306\' where not exists(select * from systemset);");
    serversetform = new Serversetform();


}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mainwidgetinit(){
    ui->maintablewidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QIcon(":/icon/icon/link.png"),"connect"));
    ui->maintablewidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QIcon(":/icon/icon/clock.png"),"status"));
    ui->maintablewidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QIcon(":/icon/icon/ipaddress.png"),"ip"));
    ui->maintablewidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QIcon(":/icon/icon/screen.png"),"name"));
    ui->maintablewidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QIcon(":/icon/icon/sewing-machine.png"),"type"));
    ui->maintablewidget->setHorizontalHeaderItem(5,new QTableWidgetItem(QIcon(":/icon/icon/settings.png"),"setup"));

    itemmap = new QMap<QString,mslotitem *>;

}


void MainWindow::on_ipadderbtn_clicked()
{
    ui->maintablewidget->insertRow(ui->maintablewidget->rowCount());
    int countnumber = ui->maintablewidget->rowCount() - 1;
    mslotitem *temp_item = new mslotitem(ui->QLaddip->text());
    itemmap->insert(temp_item->iptext,temp_item);
    ui->maintablewidget->setCellWidget(countnumber,ITEMCONNECT,temp_item->connect);
    ui->maintablewidget->setCellWidget(countnumber,ITEMSTATUS,temp_item->status);
    ui->maintablewidget->setCellWidget(countnumber,ITEMIP,temp_item->ip);
    ui->maintablewidget->setCellWidget(countnumber,ITEMNAME,temp_item->machinename);
    ui->maintablewidget->setCellWidget(countnumber,ITEMTYPE,temp_item->type);
    ui->maintablewidget->setCellWidget(countnumber,ITEMSETUP,temp_item->setupbtn);
}

void MainWindow::on_actionStart_triggered()
{

}

void MainWindow::on_actionSetting_triggered()
{
    serversetform->show();
}
