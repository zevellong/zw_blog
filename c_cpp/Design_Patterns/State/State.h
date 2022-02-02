#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;
using std::string;

#ifndef STATE_HEADER
#define STATE_HEADER
#include  "Activity.h"
class Activity;
class StateBase
{
public:
    StateBase(Activity* spa);
    virtual void deduceMoney() = 0;
    virtual bool ruffle() = 0;
    virtual void dispensePrize() = 0;

protected:
    //shared_ptr<Activity> sa;
    Activity* sa;
};
class noRaffle : public StateBase
{
public:
    noRaffle(Activity* spa);
    virtual void deduceMoney() override;
    virtual bool ruffle() override;
    virtual void dispensePrize() override;

};
class canRaffle : public StateBase
{
public:
    canRaffle(Activity* spa);
    virtual void deduceMoney() override;
    virtual bool ruffle() override;
    virtual void dispensePrize() override;
};
class dispenseState : public StateBase
{
public:
    dispenseState(Activity* spa);
    virtual void deduceMoney() override;
    virtual bool ruffle() override;
    virtual void dispensePrize() override;
};
class outState : public StateBase
{
public:
    outState(Activity* spa);
    virtual void deduceMoney() override;
    virtual bool ruffle() override;
    virtual void dispensePrize() override;
};

#endif // !STATE_HEADER