#ifndef OWNCLOCK_H
#define OWNCLOCK_H

#include "basicsign.h"

class ownClock:public basicSign
{
private:
    QTimer *increase = new QTimer;
public:
    ownClock(QString principalSign,int number);
    ~ownClock();

    QTimer *getIncrease() const;

public slots:
    void counting();
};

#endif // OWNCLOCK_H
