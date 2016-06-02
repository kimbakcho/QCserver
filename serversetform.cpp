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


void Serversetform::on_applybtn_clicked()
{
    QSqlQuery query2(litedb);
    QString str = QString("update systemset set remoteserverip = \'%1\';").arg(ui->remoteserverip->text());
    query2.exec(str);
    str =  QString("update systemset set remoteserverport = \'%1\';").arg(ui->remoteserverport->text());
    query2.exec(str);
}
