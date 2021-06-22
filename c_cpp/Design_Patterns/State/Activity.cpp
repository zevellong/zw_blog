#include "Activity.h"

Activity::Activity()
{

    s1 = make_shared<noRaffle>(this);
    s2 = make_shared<canRaffle>(this);
    s3 = make_shared<dispenseState>(this);
    s4 = make_shared<outState>(this);
    _st = s1;
}
Activity::~Activity()
{
    
}
void Activity::setState(shared_ptr<StateBase> st)
{
    _st = st;
}
void Activity::reduceMoney()
{
    _st->deduceMoney();
}
void Activity::raffle()
{
    if (prizeNm == 0)
    {
        _st->dispensePrize();
    }
    if (_st->ruffle())
    {
        _st->dispensePrize();
        prizeNm -= 1;
    }
}