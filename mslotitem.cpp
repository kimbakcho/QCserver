#include "mslotitem.h"

mslotitem::mslotitem(QString iptext, QObject *parent) :
    QObject(parent)
{
    this->iptext = iptext;
    connect = new QLabel();
    status = new QLabel();
    ip = new QLabel(iptext);
    machinename = new QLineEdit();
    type = new QComboBox();
    setupbtn = new QPushButton(tr("설치"));
    connect->setTextFormat(Qt::RichText);
    connect->setText(tr("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect"));
    type->addItem(tr("gefranseven"));
    type->addItem(tr("es600"));
    type->addItem(tr("BNR"));
    status->setTextFormat(Qt::RichText);
    status->setText(tr("<img src=\":/icon/icon/stop.png\">  STOP"));
}
