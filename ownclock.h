#ifndef OWNCLOCK_H
#define OWNCLOCK_H

#include "basicsign.h"

class ownClock:public basicSign
{
private:
    QTimer *increase = new QTimer;
    int timeClock=0;
public:
    ownClock(QString principalSign,int number);
    ~ownClock();

    int getTimeClock() const;
    void setTimeClock(int value);

public slots:
    void counting();
};

#endif // OWNCLOCK_H
