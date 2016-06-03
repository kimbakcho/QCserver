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


signals:

public slots:
    void typechange(QString data);

};

#endif // MSLOTITEM_H
