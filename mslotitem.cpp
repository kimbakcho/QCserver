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
    type->addItem("gefranseven");
    type->addItem("es600");
    type->addItem("BNR");
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

    mysqlquery1.exec(quertstr2);
    if(mysqlquery1.next()){
        type->setCurrentText(mysqlquery1.value("ITEMTYPE").toString());
    }
    maintimer.setInterval(MAINTIMERTIME);
    bnr_base_logic = new Bnr_base_locgic(this);

    connect(type,SIGNAL(currentTextChanged(QString)),this,SLOT(typechange(QString)));
    connect(&maintimer,SIGNAL(timeout()),this,SLOT(maintimer_timeout()));

}
void mslotitem::typechange(QString data){
    QSqlQuery mysqlquery1(remotedb);

    QString quertstr2 = QString("UPDATE Systeminfo set ITEMTYPE = '%1' "
                                "where machine_name='%2'")
                                .arg(data)
                                .arg(machinenametext);

    mysqlquery1.exec(quertstr2);
}
//maintimer loop
void mslotitem::maintimer_timeout(){

    if(type->currentText().compare("BNR")==0){
        if(!bnr_base_logic->initflag){
            bnr_base_logic->init();
        }
        //loop logic
        bnr_base_logic->loop();
    }else if(type->currentText().compare("gefranseven")==0){

    }else if(type->currentText().compare("es600")==0){

    }

}

