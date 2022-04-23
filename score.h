#ifndef score_H
#define score_H

#include "basicsign.h"

class score:public basicSign
{
public:
    score(QString principalSign,int number);
    void increaseScore();
};

#endif // score_H
