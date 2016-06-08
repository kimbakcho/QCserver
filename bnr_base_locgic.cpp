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

        QString mancine_name = parent_item->machinename->text();
        QSqlQuery mysqlquery1(remotedb);

        QString update_temp = QString("UPDATE `temp_table` SET "
                                      "`temp1_set`=%1, `temp1_up`=%2, `temp1_down`=%3, `temp1_real`=%4, "
                                      "`temp2_set`=%5, `temp2_up`=%6, `temp2_down`=%7, `temp2_real`=%8, "
                                      "`temp3_set`=%9, `temp3_up`=%10, `temp3_down`=%11, `temp3_real`=%12, "
                                      "`temp4_set`=%13, `temp4_up`=%14, `temp4_down`=%15, `temp4_real`=%16, "
                                      "`temp5_set`=%17, `temp5_up`=%18, `temp5_down`=%19, `temp5_real`=%20, "
                                      "`temp6_set`=%21, `temp6_up`=%22, `temp6_down`=%23, `temp6_real`=%24, "
                                      "`temp7_set`=%25, `temp7_up`=%26, `temp7_down`=%27, `temp7_real`=%28, "
                                      "`temp8_set`=%29, `temp8_up`=%30, `temp8_down`=%31, `temp8_real`=%32, "
                                      "`temp9_set`=%33, `temp9_up`=%34, `temp9_down`=%35, `temp9_real`=%36, "
                                      "`temp10_set`=%37, `temp10_up`=%38, `temp10_down`=%39, `temp10_real`=%40, "
                                      "`temp11_set`=%41, `temp11_up`=%42, `temp11_down`=%43, `temp11_real`=%44, "
                                      "`temp12_set`=%45, `temp12_up`=%46, `temp12_down`=%47, `temp12_real`=%48, "
                                      "`temp13_set`=%49, `temp13_up`=%50, `temp13_down`=%51, `temp13_real`=%52, "
                                      "`temp14_set`=%53, `temp14_up`=%54, `temp14_down`=%55, `temp14_real`=%56, "
                                      "`temp15_set`=%57, `temp15_up`=%58, `temp15_down`=%59, `temp15_real`=%60, "
                                      "`temp16_set`=%61, `temp16_up`=%62, `temp16_down`=%63, `temp16_real`=%64, "
                                      "`temp17_set`=%65, `temp17_up`=%66, `temp17_down`=%67, `temp17_real`=%68, "
                                      "`temp18_set`=%69, `temp18_up`=%70, `temp18_down`=%71, `temp18_real`=%72, "
                                      "`temp19_set`=%73, `temp19_up`=%74, `temp19_down`=%75, `temp19_real`=%76, "
                                      "`temp20_set`=%77, `temp20_up`=%78, `temp20_down`=%79, `temp20_real`=%80, "
                                      "`temp21_set`=%81, `temp21_up`=%82, `temp21_down`=%83, `temp21_real`=%84 "
                                      "WHERE  `machine_name`='%85'")
                .arg(datamap->value("REC_DATA.HC.Zone[0].ST")->value)     //temp1_set
                .arg(datamap->value("REC_DATA.HC.Zone[0].STpTol")->value) //temp1_up
                .arg(datamap->value("REC_DATA.HC.Zone[0].STnTol")->value) //temp1_down
                .arg(datamap->value("ACT_DATA.Zone[0].AT")->value)        //temp1_real
                .arg(datamap->value("REC_DATA.HC.Zone[1].ST")->value)     //temp2_set
                .arg(datamap->value("REC_DATA.HC.Zone[1].STpTol")->value) //temp2_up
                .arg(datamap->value("REC_DATA.HC.Zone[1].STnTol")->value) //temp2_down
                .arg(datamap->value("ACT_DATA.Zone[1].AT")->value)        //temp2_real
                .arg(datamap->value("REC_DATA.HC.Zone[2].ST")->value)     //temp3_set
                .arg(datamap->value("REC_DATA.HC.Zone[2].STpTol")->value) //temp3_up
                .arg(datamap->value("REC_DATA.HC.Zone[2].STnTol")->value) //temp3_down
                .arg(datamap->value("ACT_DATA.Zone[2].AT")->value)        //temp3_real
                .arg(datamap->value("REC_DATA.HC.Zone[3].ST")->value)     //temp4_set
                .arg(datamap->value("REC_DATA.HC.Zone[3].STpTol")->value) //temp4_up
                .arg(datamap->value("REC_DATA.HC.Zone[3].STnTol")->value) //temp4_down
                .arg(datamap->value("ACT_DATA.Zone[3].AT")->value)        //temp4_real
                .arg(datamap->value("REC_DATA.HC.Zone[4].ST")->value)     //temp5_set
                .arg(datamap->value("REC_DATA.HC.Zone[4].STpTol")->value) //temp5_up
                .arg(datamap->value("REC_DATA.HC.Zone[4].STnTol")->value) //temp5_down
                .arg(datamap->value("ACT_DATA.Zone[4].AT")->value)        //temp5_real
                .arg(datamap->value("REC_DATA.HC.Zone[5].ST")->value)     //temp6_set
                .arg(datamap->value("REC_DATA.HC.Zone[5].STpTol")->value) //temp6_up
                .arg(datamap->value("REC_DATA.HC.Zone[5].STnTol")->value) //temp6_down
                .arg(datamap->value("ACT_DATA.Zone[5].AT")->value)        //temp6_real
                .arg(datamap->value("REC_DATA.HC.Zone[6].ST")->value)     //temp7_set
                .arg(datamap->value("REC_DATA.HC.Zone[6].STpTol")->value) //temp7_up
                .arg(datamap->value("REC_DATA.HC.Zone[6].STnTol")->value) //temp7_down
                .arg(datamap->value("ACT_DATA.Zone[6].AT")->value)        //temp7_real
                .arg(datamap->value("REC_DATA.HC.Zone[7].ST")->value)     //temp8_set
                .arg(datamap->value("REC_DATA.HC.Zone[7].STpTol")->value) //temp8_up
                .arg(datamap->value("REC_DATA.HC.Zone[7].STnTol")->value) //temp8_down
                .arg(datamap->value("ACT_DATA.Zone[7].AT")->value)        //temp8_real
                .arg(datamap->value("REC_DATA.HC.Zone[8].ST")->value)     //temp9_set
                .arg(datamap->value("REC_DATA.HC.Zone[8].STpTol")->value) //temp9_up
                .arg(datamap->value("REC_DATA.HC.Zone[8].STnTol")->value) //temp9_down
                .arg(datamap->value("ACT_DATA.Zone[8].AT")->value)        //temp9_real
                .arg(datamap->value("REC_DATA.HC.Zone[9].ST")->value)     //temp10_set
                .arg(datamap->value("REC_DATA.HC.Zone[9].STpTol")->value) //temp10_up
                .arg(datamap->value("REC_DATA.HC.Zone[9].STnTol")->value) //temp10_down
                .arg(datamap->value("ACT_DATA.Zone[9].AT")->value)        //temp10_real
                .arg(datamap->value("REC_DATA.HC.Zone[10].ST")->value)     //temp11_set
                .arg(datamap->value("REC_DATA.HC.Zone[10].STpTol")->value) //temp11_up
                .arg(datamap->value("REC_DATA.HC.Zone[10].STnTol")->value) //temp11_down
                .arg(datamap->value("ACT_DATA.Zone[10].AT")->value)        //temp11_real
                .arg(datamap->value("REC_DATA.HC.Zone[11].ST")->value)     //temp12_set
                .arg(datamap->value("REC_DATA.HC.Zone[11].STpTol")->value) //temp12_up
                .arg(datamap->value("REC_DATA.HC.Zone[11].STnTol")->value) //temp12_down
                .arg(datamap->value("ACT_DATA.Zone[11].AT")->value)        //temp12_real
                .arg(datamap->value("REC_DATA.HC.Zone[12].ST")->value)     //temp13_set
                .arg(datamap->value("REC_DATA.HC.Zone[12].STpTol")->value) //temp13_up
                .arg(datamap->value("REC_DATA.HC.Zone[12].STnTol")->value) //temp13_down
                .arg(datamap->value("ACT_DATA.Zone[12].AT")->value)        //temp13_real
                .arg(datamap->value("REC_DATA.HC.Zone[13].ST")->value)     //temp14_set
                .arg(datamap->value("REC_DATA.HC.Zone[13].STpTol")->value) //temp14_up
                .arg(datamap->value("REC_DATA.HC.Zone[13].STnTol")->value) //temp14_down
                .arg(datamap->value("ACT_DATA.Zone[13].AT")->value)        //temp14_real
                .arg(datamap->value("REC_DATA.HC.Zone[14].ST")->value)     //temp15_set
                .arg(datamap->value("REC_DATA.HC.Zone[14].STpTol")->value) //temp15_up
                .arg(datamap->value("REC_DATA.HC.Zone[14].STnTol")->value) //temp15_down
                .arg(datamap->value("ACT_DATA.Zone[14].AT")->value)        //temp15_real
                .arg(datamap->value("REC_DATA.HC.Zone[15].ST")->value)     //temp16_set
                .arg(datamap->value("REC_DATA.HC.Zone[15].STpTol")->value) //temp16_up
                .arg(datamap->value("REC_DATA.HC.Zone[15].STnTol")->value) //temp16_down
                .arg(datamap->value("ACT_DATA.Zone[15].AT")->value)        //temp16_real
                .arg(datamap->value("REC_DATA.HC.Zone[16].ST")->value)     //temp17_set
                .arg(datamap->value("REC_DATA.HC.Zone[16].STpTol")->value) //temp17_up
                .arg(datamap->value("REC_DATA.HC.Zone[16].STnTol")->value) //temp17_down
                .arg(datamap->value("ACT_DATA.Zone[16].AT")->value)        //temp17_real
                .arg(datamap->value("REC_DATA.HC.Zone[17].ST")->value)     //temp18_set
                .arg(datamap->value("REC_DATA.HC.Zone[17].STpTol")->value) //temp18_up
                .arg(datamap->value("REC_DATA.HC.Zone[17].STnTol")->value) //temp18_down
                .arg(datamap->value("ACT_DATA.Zone[17].AT")->value)        //temp18_real
                .arg(datamap->value("REC_DATA.HC.Zone[18].ST")->value)     //temp19_set
                .arg(datamap->value("REC_DATA.HC.Zone[18].STpTol")->value) //temp19_up
                .arg(datamap->value("REC_DATA.HC.Zone[18].STnTol")->value) //temp19_down
                .arg(datamap->value("ACT_DATA.Zone[18].AT")->value)        //temp19_real
                .arg(datamap->value("REC_DATA.HC.Zone[19].ST")->value)     //temp20_set
                .arg(datamap->value("REC_DATA.HC.Zone[19].STpTol")->value) //temp20_up
                .arg(datamap->value("REC_DATA.HC.Zone[19].STnTol")->value) //temp20_down
                .arg(datamap->value("ACT_DATA.Zone[19].AT")->value)        //temp20_real
                .arg(datamap->value("REC_DATA.HC.Oil.ST")->value)     //temp21_set //oil
                .arg('0') //temp21_up
                .arg('0') //temp21_down
                .arg(datamap->value("ACT_DATA.System.ATOil")->value)        //temp21_real//il
                .arg(mancine_name)
                ;
        mysqlquery1.exec(update_temp);

        parent_item->set_connectlabel_text("<img src=\":/icon/icon/play-button16.png\">  connect");
        parent_item->set_status_text("<img src=\":/icon/icon/play-button16.png\">  play");

    }else {
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect");
        parent_item->set_status_text("<img src=\":/icon/icon/stop.png\">  STOP");

    }
    //qDebug()<<temp_data;
    delete reply;
}
