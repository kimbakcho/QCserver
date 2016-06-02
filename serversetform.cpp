#include "serversetform.h"
#include "ui_serversetform.h"

Serversetform::Serversetform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serversetform)
{
    ui->setupUi(this);
    litedb = QSqlDatabase::database("localdb");
    QSqlQuery query1(litedb);
    query1.exec("select * from systemset;");
    query1.next();

    QString setip = query1.value("remoteserverip").toString();
    ui->remoteserverip->setText(setip);
    QString setport = query1.value("remoteserverport").toString();
    ui->remoteserverport->setText(setport);

}

Serversetform::~Serversetform()
{
    delete ui;
}
