#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>

#include  "Activity.h"
#include "State.h"

int main(int argc, char const *argv[])
{
    Activity a;
    for (int i = 0; i < 5 ; i++)
    {
        cout << "-------" << i << "--------" <<endl;
        a.reduceMoney();
        a.raffle();
    }
    return 0;
}

/*
shared_ptr<Thing> sp_for_this(this)
*/