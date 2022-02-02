#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string itostr(int num, int radix)
{
    string rtn = "";
    do
    {
        int t = num % radix;
        if (t < 10)
            rtn += '0' + t;
        else
            rtn += 'a' + t - 10;
        num /= radix;
    } while (num != 0);
    reverse(rtn.begin(), rtn.end());
    return rtn;
}
int rad_reve(int num, int radix)
{
    string rtn = "";
    int flag = 0;
    if (num == 0)
        return 0;
    do
    {
        int t = num % radix;
        if (t == 0)
        {
            if (flag == 1)
                rtn += '0' + t;
        }
        else if (t < 10)
        {
            rtn += '0' + t;
            flag = 1;
        }
        else
        {
            rtn += 'a' + t - 10;
            flag = 1;
        }
        num /= radix;
    } while (num != 0);

    return stoi(rtn, 0, radix);
}
bool isPrime(int num)
{
    if (num < 2)
        return false;
        
    int cutoff = (int)sqrt(num);
    int i = 2;
    while (i <= cutoff)
    {
        //cout << num << "%" << i << "=" << num%i << endl;
        if (num % i++ == 0)
            return false;
    }
    return true;
}
void line_1015(int num, int rad)
{
    if (num < 0)
        exit(EXIT_SUCCESS);
    if (isPrime(num))
    {
        int rev = rad_reve(num, rad);
        //cout << "num=" << num << "  rev=" << rev << endl;
        if (isPrime(rev))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
void pat_1015_A()
{
    int num = 1, rad;
    while (1)
    {
        cin >> num;
        if (num < 0)
            break;
        cin >> rad;
        line_1015(num, rad);
    }
}

int main(int argc, const char **argv)
{
    pat_1015_A();
    return 0;
}