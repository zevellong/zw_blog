#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int uptime = 6, dwtime = 4, sttime = 5;
    int sumtime = 0, pastfl = 0, nowfl = 0;
    int reqtime ;
    int i;
    cin >> i;
    for (int j=0; j < i; j++)
    {
        cin >> nowfl;
        if (nowfl > pastfl)
            reqtime = (nowfl - pastfl) * uptime + sttime;
        else if (nowfl < pastfl)
            reqtime = (pastfl - nowfl) * dwtime + sttime;
        else
            reqtime = sttime;
        sumtime += reqtime;
        pastfl = nowfl;
    }
    cout << sumtime << endl;
    return 0;
}