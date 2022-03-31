#include "basicsign.h"


basicSign::basicSign(QString principalSign, int number)
{
    setNumber(number);
    setPrincipalSign(principalSign);
    setPlainText(QString(principalSign)+QString::number(number));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Times New Roman",30));
}

void basicSign::updateSign(int number)
{
    setPlainText(QString(getPrincipalSign())+QString::number(number));
}
QString basicSign::getPrincipalSign() const
{
    return principalSign;
}

void basicSign::setPrincipalSign(const QString &value)
{
    principalSign = value;
}

int basicSign::getNumber() const
{
    return number;
}

void basicSign::setNumber(int value)
{
    number = value;
}
