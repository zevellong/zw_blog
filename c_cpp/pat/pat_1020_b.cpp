#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct pItem
{
    double aw, ap, pp;
};
void pat_1020_b()
{
    int sz;
    double ct;
    cin >> sz >> ct;
    pItem *data = new pItem[sz];
    for (int i = 0; i < sz; i++)
        cin >> data[i].aw;
    for (int i = 0; i < sz; i++)
        cin >> data[i].ap;
    for (int i = 0; i < sz; i++)
        data[i].pp = data[i].ap / data[i].aw;

    
    sort(data, data + sz,
         [](const pItem &lhs, const pItem &rhs)
         { return lhs.pp > rhs.pp; });
    double sum = 0;
    for (int i = 0; ct > 0 && i < sz; i++)
    {
        double curW = data[i].aw;
        if (curW <= ct)
        {
            sum += data[i].pp * curW;
            ct -= curW;
        }else
        {
            sum += data[i].pp * ct;
            ct = 0.0;
        }
    }
    char out_str[30];
    std::snprintf(out_str, 30 - 1, "%0.2f", sum);
    cout << out_str << endl;
}

int main(int argc, const char **argv)
{
    pat_1020_b();
    return 0;
}