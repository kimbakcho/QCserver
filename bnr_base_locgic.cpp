#include "bnr_base_locgic.h"
#include "mslotitem.h"

Bnr_base_locgic::Bnr_base_locgic(QObject *parentmslot,QObject *parent) :
    QObject(parent)
{
    this->parentmslot = parentmslot;
    initflag=false;
}
bool Bnr_base_locgic::init(){
    mslotitem *parent_item = (mslotitem *)parentmslot; //부모 위젯
    datamap = new QMap<QString,BNRvalue *>;
    connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(managerfinished(QNetworkReply*)));
    remotedb  = QSqlDatabase::database("remotedb");
    initflag=true;
}
void Bnr_base_locgic::loop(){
    mslotitem * parent_item = (mslotitem *)parentmslot; //부모 위젯
    QString ip = parent_item->ip->text();
    //qDebug()<<ip;
    requst_read_value(ip,"BNRbase.asp");
    if(parent_item->type->currentText().split("/").at(1).compare("TAC1XX11")==0){
        requst_read_value(ip,"TAC1XX11warning.asp");
    }

}
void Bnr_base_locgic::requst_read_value(QString ip,QString address){
    QString url = QString("http://%1/%2").arg(ip).arg(address);
    requast.setUrl(url);
    manager.get(requast);
}
void Bnr_base_locgic::managerfinished(QNetworkReply *reply){
    QByteArray temp_data;
    mslotitem * parent_item = (mslotitem *)parentmslot; //부모 위젯
    temp_data = reply->readAll();
    if(temp_data.size()>0){
        webpage.mainFrame()->setHtml(temp_data);
        documents = webpage.mainFrame()->findAllElements("div");
        for(int i=0;i<documents.count();i++){
            document = documents.at(i);
            QString name = document.attribute("name");
            BNRvalue *tempbnrdata;
            if(!datamap->contains(name)){
                tempbnrdata = new BNRvalue();
                tempbnrdata->name = name;
                datamap->insert(name,tempbnrdata);
            } else {
                tempbnrdata = datamap->value(name);
            }
            QString dom  = QString(".value");

            tempbnrdata->value = document.findFirst(dom).toPlainText();
            //qDebug()<<QString("BNRhttp web var = %1, data = %2").arg(tempbnrdata->name).arg(tempbnrdata->value);
        }
        if(reply->url().toString().indexOf("BNRbase.asp")>0){
            url_bnrbaseloop();
        }else if(reply->url().toString().indexOf("TAC1XX11warning.asp")>0){
            url_tac1xx11warningloop();
        }



        parent_item->set_connectlabel_text("<img src=\":/icon/icon/play-button16.png\">  connect");
        parent_item->set_status_text("<img src=\":/icon/icon/play-button16.png\">  play");

    }else {
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect");
        parent_item->set_status_text("<img src=\":/icon/icon/stop.png\">  STOP");

    }
    //qDebug()<<temp_data;
    delete reply;
}

void Bnr_base_locgic::url_bnrbaseloop(){
    mslotitem * parent_item = (mslotitem *)parentmslot; //부모 위젯
    QString mancine_name = parent_item->machinename->text();
    QSqlQuery mysqlquery1(remotedb);

    QString update_temp = QString("UPDATE `temp_table` SET ");
    for(int i=1;i<=21;i++){
        QString temp_append ;
        if(i == 7){
          temp_append = QString("`temp%1_set`=%2, `temp%1_up`=%3, `temp%1_down`=%4, `temp%1_real`=%5, temp%1_onoff = %6, ")
                                        .arg(i)
                                        .arg(datamap->value(QString("REC_DATA.HC.Oil.ST"))->value)
                                        .arg(0)
                                        .arg(0)
                                        .arg(datamap->value(QString("ACT_DATA.System.ATOil"))->value)
                                        .arg(1);

        }else if(i == 21){
            temp_append = QString("`temp%1_set`=%2, `temp%1_up`=%3, `temp%1_down`=%4, `temp%1_real`=%5, temp%1_onoff = %6 ")
                                        .arg(i)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].ST").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].STpTol").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].STnTol").arg(i-1))->value)
                                        .arg(datamap->value(QString("ACT_DATA.Zone[%1].AT").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].SbOn").arg(i-1))->value);

        }else {
            temp_append = QString("`temp%1_set`=%2, `temp%1_up`=%3, `temp%1_down`=%4, `temp%1_real`=%5, temp%1_onoff = %6, ")
                                        .arg(i)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].ST").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].STpTol").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].STnTol").arg(i-1))->value)
                                        .arg(datamap->value(QString("ACT_DATA.Zone[%1].AT").arg(i-1))->value)
                                        .arg(datamap->value(QString("REC_DATA.HC.Zone[%1].SbOn").arg(i-1))->value);

        }
        update_temp.append(temp_append);
    }
    QString temp_append1 = QString("WHERE  `machine_name`='%1'").arg(mancine_name);
    update_temp.append(temp_append1);

    mysqlquery1.exec(update_temp);

    double object_count = datamap->value("udTotalProd_setpcs")->value.toDouble();
    double production_count = datamap->value("udTotalProd_actpcs")->value.toDouble();
    double achievemen_rate = (production_count/object_count)*100.0;
    int cycle_time = datamap->value("ACT_DATA.System.AtCycleTime")->value.toInt()/100;
    QTime time;
    time.setHMS(0,0,0);
    QTime cycletime;
    cycletime = time.addSecs(cycle_time);

    int mode = datamap->value("MMI_DATA.Mode")->value.toInt();
    QString modestr;
    if(mode == 1){
        modestr=tr("전자동");
    }else if(mode ==2){
        modestr=tr("반자동");
    }else if(mode ==4){
        modestr=tr("수동");
    }else if(mode ==5){
        modestr=tr("금형취부");
    }

    update_temp = QString("UPDATE Systeminfo SET production_count = %1,"
                          "object_count = %2,"
                          "cabity = %3,"
                          "achievemen_rate = %4,"
                          "cycle_time = \'%5\',"
                          "run_mode = \'%6\',"
                          "warning_flag = %7 "
                          "where machine_name = \'%8\'")
                            .arg(datamap->value("udTotalProd_actpcs")->value)
                            .arg(datamap->value("udTotalProd_setpcs")->value)
                            .arg(datamap->value("uiNoOfCavity")->value)
                            .arg(achievemen_rate)
                            .arg(cycletime.toString("hh:mm:ss"))
                            .arg(modestr)
                            .arg(datamap->value("MA_STAT.AbAlarmPending")->value)
                            .arg(mancine_name);
    mysqlquery1.exec(update_temp);

}
void Bnr_base_locgic::url_tac1xx11warningloop(){

}

