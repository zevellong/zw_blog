#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;
using std::string;

#ifndef ACTIVITY_HEADER
#define ACTIVITY_HEADER
#include "State.h"
class StateBase;
class Activity
{
private:
    shared_ptr<StateBase> _st;
    int prizeNm = 1;
public:
    Activity();
    ~Activity();
    shared_ptr<StateBase> s1,s2,s3,s4;
    void setState(shared_ptr<StateBase> st);
    void reduceMoney();
    void raffle();
    void nullThis();
};
#endif // !ACTIVITY_HEADER