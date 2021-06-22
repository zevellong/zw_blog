#include <stdio.h>
#include <stdlib.h>

#define WIN_MAX 10001

struct cum{
	int arriveTime;
	int ProcessTime;
};
void rrtime(const char* t, struct cum* cum1)
{
	char* p = t;
	int i,j,a[7];
	char c;
	for (i=0,j=0; i < 8; i++)
	{
		c = *(p+i);
		if (c < '0' || c > '9')
			continue;
		a[j++] = (int) (c - '0');
	}
	cum1->arriveTime = ((a[0]*10 + a[1]) * 3600 + (a[2]*10 + a[3])*60 + (a[4]*10+a[5]));
	cum1->ProcessTime = atoi(t+i) * 60;
}
void printCum(struct cum* cumT,int size){
	int i;
	for (i=0; i < size; i++){
		printf("%d arr=%d  pro=%d\n",i,cumT[i].arriveTime,cumT[i].ProcessTime);
	}
}
void swapCum(struct cum* cum1, struct cum* cum2)
{
	struct cum cmp;
	cmp.arriveTime = cum1->arriveTime;
	cmp.ProcessTime = cum1->ProcessTime;

	cum1->arriveTime = cum2->arriveTime;
	cum1->ProcessTime = cum2->ProcessTime;
	cum2->arriveTime = cmp.arriveTime;
	cum2->ProcessTime = cmp.ProcessTime;

}
void mysort(struct cum* cumTable, int sortSize)
{
	int i,j;
	for (i=0,j=0; i<sortSize - 1;i++)
	{
		for (j=i+1;j<sortSize;j++)
		{
			if (cumTable[i].arriveTime > cumTable[j].arriveTime)
			{
				swapCum(&cumTable[i],&cumTable[j]);
			}
		}
	}
}
//返回正数表示最早能够服务的窗口号
int findWin(int arrtime, int nowtime, int* winTable,int winsize){
	int minWin = 0;
	int i,minTime;
	for (i=0, minTime=winTable[0]; i<winsize;i++){
		 //printf("in minwin: minwin=%d\n",minWin);
		if (winTable[i] <= nowtime)
			return i;
		if (minTime > winTable[i])
		{
			minWin = i;
			minTime = winTable[i];
		}
	}
	
	return minWin;
}

int main(int argc, char* argv[])
{ 
	int winSize,cumSize,i,j,nowtime,waittime,arrtime,fdwin,count;
	int winTable[100];
	struct cum cumarr[WIN_MAX];
	char buf[30];
	int time5 = 8*3600;

	scanf("%d %d",&cumSize, &winSize);
	if (cumSize == 0){
		printf("0.0\n");
		exit(EXIT_SUCCESS);
	}
	while (getchar() != '\n')
		continue;
	for (i=0; i< cumSize ; i++){
		gets(buf);
		rrtime(buf, &(cumarr[i]));
	}
	for (i=0;i< winSize;i++)
		winTable[i] = time5;
	//printCum(cumarr,cumSize);
	mysort(cumarr,cumSize);
	//printCum(cumarr,cumSize);

	for (i=1,count=0;   ; i++)
	{
		if (cumarr[cumSize - i].arriveTime > 17*3600)
			count++;
		else
			break;	
	}

	for (i=0, waittime =0,nowtime=time5;  i < cumSize; i++)
	{

		if (nowtime > 17*3600){
			break;
		}
		arrtime = cumarr[i].arriveTime;
		if (arrtime < time5){
			waittime += time5 - arrtime;
			//printf("%d:add %d  | waittime=%d\n",i,time5 - arrtime, waittime);
		}
		fdwin = findWin(arrtime, nowtime, winTable, winSize);
		//printf("minwin%d || win:%-6d  %-6d  %-6d\n",fdwin,winTable[0],winTable[1],winTable[2]);
		if (arrtime > nowtime){
			nowtime = arrtime;
			i--;
			continue;
		}
		if (winTable[fdwin] <= nowtime)
		{                     
			winTable[fdwin] = nowtime + cumarr[i].ProcessTime;
			continue;
		}
		else
		{
			waittime += winTable[fdwin] - arrtime;
			//printf("**%d:add %d  | waittime=%d\n",i, winTable[fdwin] - arrtime, waittime);
			nowtime = winTable[fdwin];
			
			i--;
			continue;
			
		}
		
	}
	printf("%0.1f\n",((float) waittime)/60/(cumSize - count));

	exit(EXIT_SUCCESS);
} 
