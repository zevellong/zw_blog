#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
#define BUF_SIZE 1024
static int buf[BUF_SIZE];

int main()
{
    int cnt, tmp;
    cin >> cnt;
    int testNum[5], flag[5];
    for (int i = 0; i < 5; i++)
    {
        testNum[i] = 0;
        flag[i] = 0;
    }    
    testNum[4] = -0x10000000;
    int flag2 = 1;
    for (int i = 0; i < cnt; i++)
    {
        cin >> tmp;
        switch (tmp % 5)
        {
        case 0: 
            if (tmp % 10 == 0)
            {
                testNum[0] += tmp;
                flag[0]++;
            }
                 
            break;
        case 1:
            flag[1]++;
            testNum[1] += flag2 ? tmp : -tmp;
            flag2 = !flag2;
            break;
        case 2:
            flag[2]++;
            testNum[2]++; break;
        case 3:
            flag[3]++;
            
            testNum[3] += tmp; break;
        case 4:
            flag[4]++;
            if (tmp > testNum[4])
                testNum[4] = tmp;
            break;
        }
    }
    string out;
   
    if (flag[0])
        printf("%d ", testNum[0]);
    else
        printf("N ");    
    if (flag[1])
        printf("%d ", testNum[1]);
    else
        printf("N ");
    if (flag[2])
        printf("%d ", testNum[2]);
    else
        printf("N ");
    if (flag[3])
        printf("%f ", (float) testNum[3]/flag[3]);
    else
        printf("N ");
    if (flag[4])
        printf("%d \n", testNum[4]);
    else
        printf("N \n");
    return 0;
}