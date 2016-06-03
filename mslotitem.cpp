#include "mslotitem.h"

mslotitem::mslotitem(QString iptext, QString machinenametext, QObject *parent) :
    QObject(parent)
{
    remotedb  = QSqlDatabase::database("remotedb");
    QSqlQuery mysqlquery1(remotedb);
    this->iptext = iptext;
    this->machinenametext = machinenametext;
    connectlabel = new QLabel();
    status = new QLabel();
    ip = new QLabel(iptext);
    machinename = new QLabel(machinenametext);
    type = new QComboBox();
    setupbtn = new QPushButton(tr("설치"));
    connectlabel->setTextFormat(Qt::RichText);
    connectlabel->setText(tr("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect"));
    type->addItem(tr("gefranseven"));
    type->addItem(tr("es600"));
    type->addItem(tr("BNR"));
    status->setTextFormat(Qt::RichText);
    status->setText(tr("<img src=\":/icon/icon/stop.png\">  STOP"));
    QString quertstr2 =  QString("INSERT INTO Systeminfo ("
                                 "machine_name,"
                                 "ipaddress,"
                                 "ITEMCONNECT,"
                                 "ITEMSTATUS,"
                                 "ITEMTYPE"
                                 ") values ("
                                 "'%1',"  //machine_name
                                 "'%2',"  // ipaddress
                                 "'%3',"  //ITEMCONNECT
                                 "'%4',"  //ITEMSTATUS
                                 "'%5'"   //ITEMTYPE
                                 ") ON DUPLICATE KEY UPDATE "
                                 "ITEMCONNECT = '%3',"
                                 "ITEMSTATUS = '%4'"
                                 ).arg(machinenametext)
                                  .arg(iptext)
                                  .arg(connectlabel->text())
                                  .arg(status->text())
                                  .arg(type->currentText());
                                  ;

    mysqlquery1.exec(quertstr2);

    quertstr2 = QString("select ITEMTYPE from Systeminfo where machine_name = '%1'").arg(machinenametext);
    qDebug()<<quertstr2;
    mysqlquery1.exec(quertstr2);
    if(mysqlquery1.next()){
        type->setCurrentText(mysqlquery1.value("ITEMTYPE").toString());
    }
    connect(type,SIGNAL(currentTextChanged(QString)),this,SLOT(typechange(QString)));
}
void mslotitem::typechange(QString data){
    QSqlQuery mysqlquery1(remotedb);

    QString quertstr2 = QString("UPDATE Systeminfo set ITEMTYPE = '%1' "
                                "where machine_name='%2'")
                                .arg(data)
                                .arg(machinenametext);

    mysqlquery1.exec(quertstr2);
}
