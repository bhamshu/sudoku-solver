#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<process.h>
//#include<iomanip>
#include<time.h>
#include<math.h>
#include<windows.h> //for functions used in gotoxy
void gotoxy(int x,int y)
{
	static HANDLE h=NULL;
	if(!h)
		h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c={x,y};
	SetConsoleCursorPosition(h,c);
}

int m[9][9],t=0;char caar[10][10];

int box(int v, int x, int y)  //to check the small 3*3 boxes
{   int k;
	x=((x-1)/3)*3+1; y=((y-1)/3)*3+1;
	int X=x+3,Y=y+3;
	for(;x<X;x++)
		for(k=y;k<Y;k++)  //i had developed tools 1,3,4V&H at the time of writing this. my box code was: for(;x<X;x++)for(;y<Y;y++) if(v==m[x][y]) return 1; the code as a whole was fine but later i found that tool1 wasn't running as it should have been and after much labor found that it's sth. in the box fuction.Only after much labor again could i fix it. Lesson learned: don't compromise the code for aesthetics.I don't wanna do that :'(.
			if(v==m[x][k])
				return 1;
	return 0;	
}
void screen();
void board();
void load();
void player();
void tool1();//traditional: checks if a cell can take only one number(can't take any of the other 8 that is). if yes,puts that number in it 
void tool3();//box by box: checks which all elements a box needs and if only one cell can take a number, puts it theres
void tool4V();void tool4H();//line by line: checks which all elements a line needs and if only one cell can take a number, puts it there
//I can't help but think these three tools as dimensions which seldom, if at all, overlap. And they complement each other so well! 
int score();
int  check(int ,int);
void tool1()
{    int i,j;
	int s=1;
	while(s)
	{	//clrscr();
		s=0;
		int x,y,v,count,V;
		for(x=1;x<=9;x++)
		{ 
			for(y=1;y<=9;y++)
			{    count=0;
			if(m[x][y]==0)
			{	for(v=1;v<=9;v++)
				{   int flag=0;
				for(i=1;i<=9;i++)
				{	if(v==m[x][i]||v==m[i][y]||box(v,x,y)==1)
					{flag=1;break; }	}			
				if(flag==1){count++; }
				else V=v;
				}
			if(count==8)
			{m[x][y]=V;s=1;}//if(count==6)printf("%d%d",x,y);
		    }
			}
		}
	}
}

void tool3()
{   int s=1;	int i,j;
int h,k,v,x,y,flag,a,arr[9][9],grp_a[9];//arr[grp no][indices from 0 to 8]=values that group needs; where grp no=3*h+k
while(s)
{  s=0;
for(h=0;h<=2;h++)// Going in the order:   0 3 6
{				 //						  1 4 7
	for(k=0;k<=2;k++)//					  2	5 8
	{   a=0;
	for(v=1;v<=9;v++)
	{	flag=0;
	for(x=1+3*h;x<4+3*h;x++)
	{
		for(y=1+3*k;y<4+3*k;y++)
		{
			if(m[x][y]==v)flag=1;
		}
	}
	if(!flag){ arr[3*h+k][a]=v; a++;}
	}
	grp_a[3*h+k]=a;	
	}
}
int c0unt,count,X,Y;
for(h=0;h<=2;h++)
{				 
	for(k=0;k<=2;k++)
	{
		for(a=0;a<grp_a[3*h+k];a++)
		{ v=arr[3*h+k][a]; c0unt=0;count=0;
		for(x=1+3*h;x<4+3*h;x++)
		{
			for(y=1+3*k;y<4+3*k;y++)
			{   flag=0;
			if(m[x][y]==0)  { 
				c0unt++;
				for(i=1;i<=9;i++)
					if(v==m[x][i]||v==m[i][y])
						flag=1;
				if(flag)count++;
				else {X=x;Y=y;}	}	
			}
		}
		if(count==c0unt-1)//You could totally eliminate the variable c0unt by replacing "c0unt-1" by "grp_a[3*h+k]" in this statement <--. Tway you have one less variable but c"0"unt makes it clear that you are counting empty places
		{m[X][Y]=v;s=1;}
		}
	}
}
}
}

void tool4V()
{  int s=1; int i,j;
int x,y,V[10][10],a,v,flag,V_a[10];//V[X][indices or "a"]=no.s the row X doesn't have	
while(s)
{	s=0;
for(x=1;x<=9;x++)
{a=0;	
for(v=1;v<=9;v++)
{flag=0;
for(y=1;y<=9;y++)
{
	if(m[x][y]==v)
		flag=1;
} 
if(flag==0) {V[x][a]=v;a++;}
}
V_a[x]=a;
}	

int X,Y,count,c0unt;
for(x=1;x<=9;x++)
{	c0unt=0;
for(y=1;y<=9;y++)
	if(m[x][y]==0)
		c0unt++;
for(a=0;a<V_a[x];a++)
{   count=0;
v=V[x][a]; 
for(y=1;y<=9;y++)
{   flag=0;
	if(m[x][y]==0)
{   if(box(v,x,y)==1)flag=1;
	for(i=1;i<=9;i++)
	{if(m[i][y]==v){flag=1;/*system("cls");screen();board();printf("&%d %d %d&",i,y,v);/**/}}
	if(flag==1){count++;/*printf("(%d %d) %d ",x,y,v);getch();/**/}
	else{X=x;Y=y;} }
} 
//printf(" %d %d %d ",v,count,c0unt);
if(count==c0unt-1)
{m[X][Y]=v;c0unt--;s=1;} 
//printf("/%d %d %d %d/",x,V[x][a],count,c0unt);//getch();
}
}
}
}

void tool4H()
{  int s=1; int i,j;
int x,y,V[10][10],a,v,flag,V_a[10];//V[y][indices or "a"]=no.s the column y doesn't have	
while(s)
{	s=0;
for(y=1;y<=9;y++)
{a=0;	
for(v=1;v<=9;v++)
{flag=0;
for(x=1;x<=9;x++)
{
	if(m[x][y]==v)
		flag=1;
} 
if(flag==0) {V[y][a]=v;a++;}
}
V_a[y]=a;
}	

int X,Y,count,c0unt;
for(y=1;y<=9;y++)
{	c0unt=0;
for(x=1;x<=9;x++)
	if(m[x][y]==0)
		c0unt++;
for(a=0;a<V_a[y];a++)
{   count=0;
v=V[y][a]; 
for(x=1;x<=9;x++)
{   flag=0;
	if(m[x][y]==0)
{   if(box(v,x,y)==1)flag=1;
	for(i=1;i<=9;i++)
	{if(m[x][i]==v){flag=1;/*system("cls");screen();board();printf("&%d %d %d&",i,y,v);/**/}}
	if(flag==1){count++;/*printf("(%d %d) %d ",x,y,v);getch();/**/}
	else{X=x;Y=y;} }
} 
//printf(" %d %d %d ",v,count,c0unt);
if(count==c0unt-1)
{m[X][Y]=v;c0unt--;s=1;}
//printf("/%d %d %d %d/",x,V[x][a],count,c0unt);//getch();
}
}
}
}

void player()
{  screen();board();getch();int prevscore,Score;
do{
	prevscore=Score;
	tool1();
	tool3();
	tool4H();
	tool4V();
	Score=score();}while(Score!=prevscore&&Score!=81);board();printf("\nScore=%d",Score);getch();
}


main()
{   //clrscr();
	load();
	player();
}
void load()
{   FILE *a;int i,j;
int c=1,ar[81];char ch;
a=fopen("sudoku.txt","r"); 
for(i=1;i<=81;i++)
{
	ch=fgetc(a);
	ar[i]=ch-48;
}
for(i=1;i<=9;i++)
{
	for(j=1;j<=9;j++)
	{
		m[i][j]=ar[c];
		caar[i][j]=ar[c]+48;
		c++;
	}
}
fclose(a);
}

void screen()
{
    int i;
	gotoxy(1,1);printf("    1   2   3   4   5   6   7   8   9 ");
	for(i=1;i<=9;i++)
	{ printf("\n    \n%d",i);
	}
}
void board()
{
	int i,j;
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=9;j++)
		{
			if(!check(i,j))
			{ gotoxy(4*i,2*j+1);
			printf(":%d:",m[i][j]);
			}
			else
			{ gotoxy(4*i+1,2*j+1);
			m[i][j]==0?printf(" "):printf("%d",m[i][j]);
			}
		}
	}
}
int check(int x,int y)//for putting : : around default ones
{
	if(caar[x][y]!='0')
	{
		return 0;
	}
	else
		return 1;
}
int score()
{   int i,j;
	int score=0;
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			if(m[i][j]!=0) score++;
	return score;
}

/*
void tool2V();//vertical
void tool2H();//horizontal
void tool2V()
{   board();
int s=1; 
int x,y,v,V[9][3],a,V_a[9];int h;
while(s)
{s=0;
for(h=0;h<=2;h++)
{    for(v=1;v<=9;v++)	
{  a=0;
for(x=1+3*h;x<4+3*h;x++)
{	for(y=1;y<=9;y++)
{
if(m[x][y]==v)
{V[v][a]=x*10+y;a++;break;}
}
V_a[v]=a;
}
}
//printf("\n%d  %d  %d",9,V[9][0],V[9][1]);//Error9
//for(v=1;v<=9;v++)for(a=0;a<V_a[v];a++)printf("\n%d  %d  %d",v,a,V[v][a]);
//----By various methods(taking output of the values), it has been established that the tool2 code is absolutely correct till here and does what is intended-----
int flag,Y,count;//printf("\n");
for(v=1;v<=9;v++)	
{   //printf("\n%d   %d  %d  %d",v,9,V[9][0],V[9][1]);//Error9
if(V_a[v]==2)
{    //"The problem arises when the statements x3=i and grpC=i are executed. //Error9 statements refer to the problem which arises when the "q" is eliminated, i.e. writing grpC=i right away. 
//" In fact this q was introducing by running many diagnostic tests and taking output of the values at each nook and corner possible. Strangely, the q managed to handle the error that apperently surfaced due to the line x3=i as well" 
int grpA,grpB,grpC;
int x1=V[v][0]/10,y1=V[v][0]%10,x2=V[v][1]/10,y2=V[v][1]%10,x3,y3;//printf("\n%d  %d  %d",9,V[9][0],V[9][1]);//Error9
for(i=1+3*h;i<4+3*h;i++) if(i!=x1&&i!=x2){x3=i;break;}//printf("\n%d  %d  %d",9,V[9][0],V[9][1]);//Error9  
switch(y1){case 1:case 2: case 3: grpA=1;break; case 4:case 5: case 6: grpA=2;break; case 7: case 8: case 9: grpA=3;break; }
switch(y2){case 1:case 2: case 3: grpB=1;break; case 4:case 5: case 6: grpB=2;break; case 7: case 8: case 9: grpB=3;break; }//printf("\n%d  %d  %d",9,V[9][0],V[9][1]);//Error9
for(i=1;i<=3;i++)if(i!=grpA&&i!=grpB){int q=i;grpC=q;break;} //printf("\n%d  %d  %d",9,V[9][0],V[9][1]);//Error9
count=0;
for(y3=3*(grpC-1)+1;y3<3*(grpC-1)+4;y3++)
{  flag=0;
if(m[x3][y3]!=0) count++;
else{
for(i=1;i<=9;i++)
{
if(v==m[x3][i]||v==m[i][y3])//No need to check the box condition as V_a[v]=2 guarantees that there is no "v" in the third box(grp)
flag=1; 
}
if(flag==0) Y=y3;
else count++;}
}	
if(count==2)
{m[x3][Y]=v;s=1;}
}		
} 
}
}
}
void tool2H()
{   board();
int s=1;
int y,x,v,V[9][3],a,V_a[9];int h;
while(s)
{ s=0;
for(h=0;h<=2;h++)
{ 	for(v=1;v<=9;v++)	
{  a=0;
for(y=1+3*h;y<4+3*h;y++)
{	for(x=1;x<=9;x++)
{
if(m[x][y]==v)
{V[v][a]=x*10+y;a++;break;}
}
V_a[v]=a;
}
}
int flag,X,count;//printf("\n");
for(v=1;v<=9;v++)	
{   
if(V_a[v]==2)
{   
int grpA,grpB,grpC;
int x1=V[v][0]/10,y1=V[v][0]%10,x2=V[v][1]/10,y2=V[v][1]%10,x3,y3;
for(i=1+3*h;i<4+3*h;i++) if(i!=y1&&i!=y2){y3=i;break;}  
switch(x1){case 1:case 2: case 3: grpA=1;break; case 4:case 5: case 6: grpA=2;break; case 7: case 8: case 9: grpA=3;break; }
switch(x2){case 1:case 2: case 3: grpB=1;break; case 4:case 5: case 6: grpB=2;break; case 7: case 8: case 9: grpB=3;break; }
for(i=1;i<=3;i++)if(i!=grpA&&i!=grpB){int q=i;grpC=q;break;} 
count=0;
for(x3=3*(grpC-1)+1;x3<3*(grpC-1)+4;x3++)
{  flag=0;
if(m[x3][y3]!=0) count++;
else{
for(i=1;i<=9;i++)
{
if(v==m[x3][i]||v==m[i][y3])//No need to check the boy condition as V_a[v]=2 guarantees that there is no "v" in the third boy(grp)
flag=1; 
}
if(flag==0) X=x3;
else count++;}
}	
if(count==2)
{m[X][y3]=v;s=1;}
}		
} 
}
}
}
 */
// firstly the tool 1 was developed, then 2V and the 2V was modified to get 2H. 1,2V &2H in themselves were not sufficient.
//Then the tool 3 came and 12 hours later came the realisation that tools 2 were no longer needed! 3 did their work too...

