#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int allcity;
int alledge;
int alltime;
//int nowtime;
int totalscore=0;
int totalcost=0;
int space;
int space2;
int endtime;
int endtime2;
int firstscore;

float dis[100][100]={0};
float score[100]={0};
char name[100][100];
int nowtime[1000]={0};
int road[1000];
/*class edge
{
public:
	string city1;
	string city2;
	int cost;
};
class city
{
public:
	string name;
	int happyscore;
	edge *list;
	edge *point;
//	string nextcity(city now); 	
};
class route
{
	route *next;
	string nameofcitynow;
	void print(route now);
}
*/
int main(int argc, char **argv)
{
	string filename = "./";
	string studentID = argv[1];
	string tp = "/tp.data";
	string final = "/ans1.txt";
	string final2 = "/ans2.txt";	
	string filenameinput =filename+studentID+tp;
	string filenameoutput =filename+studentID+final;
	string filenameoutput2 =filename+studentID+final2;	
	ifstream fileinput;
	ofstream fileoutput;
	fileinput.open(filenameinput.c_str());
	for(int i =0;i<1000;i++)
	{
		road[i]=-1;
	}
	road[0]=0;
	fileinput>>allcity>>alledge>>alltime>>nowtime[0];
	for(int i =0;i<allcity;i++)
	{
		fileinput>>name[i]>>score[i]>>space>>space2;
		if(i==0){endtime=space;endtime2=space2;firstscore=score[0];}
	}
	for(int j =0;j<alledge;j++)
	{
		int a1=0;
		int b1=0;
		char a[50];
		char b[50];
		fileinput>>a>>b;
		for(int k =0;k<allcity;k++)
		{
			if(strcmp(a, name[k])==0)
				a1=k;
		}
		for(int w =0;w<allcity;w++)
		{
			if(strcmp(b, name[w])==0)
				b1=w;			
		}	
		fileinput>>dis[a1][b1];
		dis[b1][a1]=dis[a1][b1];
	}	
	int f=1;int t=1;int nowcity=0;int time=alltime;int nowt=0;
	totalscore=score[0];
	score[0]=0;
	fileinput.close();
	fileoutput.open(filenameoutput.c_str());	
	while(f==1&&t==1)
	{
		float want[50]={0};
		float compare=0;
		int go=-1; 
		for(int i=0;i<allcity;i++)
		{
			if(dis[nowcity][i]!=0)
			{
				want[i]=score[i]/dis[nowcity][i];
			}
		}
		f=0;
		for(int i=0;i<allcity;i++)
		{
			if(want[i]!=0)f=1;
			if(want[i]>=compare&&want[i]!=0)
			{
				go=i;
				compare=want[go];
			}
		}
		t=0; 
		if(go!=-1&&time-dis[nowcity][go]>0)
		{
			t=1;
			time=time-dis[nowcity][go];
			if(dis[go][0]>time||(dis[go][0]==0&&alltime>time*2))
			{
				t=0;
				nowcity=go;
			}						
			else
			{
				nowtime[nowt+1]=nowtime[nowt]+dis[nowcity][go];nowt++;
				road[nowt]=go;
				totalscore+=score[go];
				totalcost+=dis[nowcity][go];
				score[go]=0;
				nowcity=go;
			}
		}
	}

	int x=road[nowt];int y=-1;
	if(dis[nowcity][0]>time){totalcost+=dis[x][0];y=0;}
	else
	{
		if(dis[nowcity][0]==0&&alltime>time*2){totalcost=totalcost*2;y=1;}
		else
		{
			//fileoutput<<totalcost<<endl; 
			if(dis[x][0]!=0)
			{
				
				if(totalcost>dis[x][0])
				{
					totalcost+=dis[x][0];y=0;
				}
				else
				{
					totalcost=totalcost*2;y=1;
				}
			}
			if(dis[x][0]==0){totalcost=totalcost*2;}
		}
	}
	fileoutput<<totalscore<<" "<<totalcost<<endl;	
	for(int i=0;i<=nowt;i++)
	{
		fileoutput<<name[road[i]]<<" "<<nowtime[i]<<" "<<nowtime[i]<<endl;
	}
	if(y=0)
	{
		fileoutput<<name[road[0]]<<" "<<nowtime[nowt]+dis[x][0]<<" "<<nowtime[nowt]+dis[x][0]<<endl;
	}
	else//if(dis[nowcity][0]==0&&alltime>time*2)
	{
		int endtime=nowtime[nowt];
		for(int i=nowt-1;i>0;i--)
		{
			endtime=endtime+dis[road[i]][road[i+1]];
			fileoutput<<name[road[i]]<<" "<<endtime<<" "<<endtime<<endl;
		}		
		fileoutput<<name[road[0]]<<" "<<nowtime[nowt]+(totalcost/2)<<" "<<nowtime[nowt]+(totalcost/2)<<endl;
	}
	fileoutput.close();
	fileoutput.open(filenameoutput2.c_str());
	if(nowtime[0]<=endtime2&&nowtime[0]>=endtime)
		fileoutput<<firstscore<<" "<<"0"<<endl;
	else
		fileoutput<<"0"<<" "<<"0"<<endl;
	fileoutput<<name[road[0]]<<" "<<nowtime[0]<<" "<<nowtime[0]<<endl;		
}
 
