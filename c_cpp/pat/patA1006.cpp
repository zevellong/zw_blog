#include <iostream>
#include <memory>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string outtime = "00:00:00", gotime = "25:00:00";
    string go, out;
    int flg[2] = {0, 0};
    string* nameList = new string[1024]();
    for (int i =0; i < n; i++)
    {
        cin >> nameList[i] >> go >> out;
        if (go < gotime)
        {
            gotime = go;
            flg[0] = i;
        }
        if (out > outtime)
        {
            outtime = out;
            flg[1] = i;
        }
    }
    cout << nameList[flg[0]] << " " << nameList[flg[1]] << endl;
    delete[] nameList;
    return 0;
}