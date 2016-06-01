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

class mslotitem : public QObject
{
    Q_OBJECT
public:
    explicit mslotitem(QString iptext,QObject *parent = 0);
    QLabel *connect;
    QLabel *status;
    QLabel *ip;
    QLineEdit *machinename;
    QComboBox *type;
    QPushButton *setupbtn;
    QString iptext;


signals:

public slots:

};

#endif // MSLOTITEM_H
