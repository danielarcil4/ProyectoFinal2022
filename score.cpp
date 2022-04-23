#include "score.h"

score::score(QString principalSign,int number):basicSign(principalSign,number)
{

}

void score::increaseScore()
{
    setNumber(getNumber()+1);
    updateSign(getNumber());
}
