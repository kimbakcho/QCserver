#ifndef MSLOTITEM_H
#define MSLOTITEM_H
/*
 *
 * maintablewidget 에 들어갈 아이템
 *
 *
*/

#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QTimer>
#include <bnr_base_locgic.h>
#include <globalheader.h>

class mslotitem : public QObject
{
    Q_OBJECT
public:
    explicit mslotitem(QString iptext,QString machinenametext,QObject *parent = 0);
    QLabel *connectlabel;
    QLabel *status;
    QLabel *ip;
    QLabel *machinename;
    QComboBox *type;
    QPushButton *setupbtn;
    QString iptext;
    QSqlDatabase remotedb;
    QString machinenametext;
    QTimer maintimer;
    Bnr_base_locgic *bnr_base_logic;
    void set_connectlabel_text(QString data);
    void set_status_text(QString data);



signals:

public slots:
    void typechange(QString data);
    void maintimer_timeout();


};

#endif // MSLOTITEM_H
