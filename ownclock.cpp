#include "ownclock.h"

ownClock::ownClock(QString principalSign,int number):basicSign(principalSign,number)
{
    connect(increase,&QTimer::timeout,this,&ownClock::counting);
    increase->start(1000);
}

ownClock::~ownClock()
{
    delete increase;
}

void ownClock::counting()
{
    setNumber(getNumber()+1);
    updateSign(getNumber());
}

QTimer *ownClock::getIncrease() const
{
    return increase;
}
