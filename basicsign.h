#ifndef BASICSIGN_H
#define BASICSIGN_H

#include <QGraphicsTextItem>
#include <QFont>
#include<QTimer>

class basicSign: public QGraphicsTextItem
{
private:
    QString principalSign="";
    int number=0;
public:
    basicSign(QString principalSign,int number);
    void updateSign(int number);

    QString getPrincipalSign() const;
    void setPrincipalSign(const QString &value);
    int getNumber() const;
    void setNumber(int value);
};

#endif // BASICSIGN_H
