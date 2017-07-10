//#include<conio.h>
//#include<string.h>
#include<stdio.h>
//#include<stdlib.h>
//#include<dos.h>
//#include<process.h>
//#include<iomanip>
//#include<time.h>
//#include<math.h>
#include<windows.h> //for functions used in gotoxy
void gotoxy(int x,int y)
{
	static HANDLE h=NULL;
	if(!h)
		h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c={x,y};
	SetConsoleCursorPosition(h,c);
}

int m[9][9];char caar[9][9];
int aa[10],ai=0;

int box(int v, int x, int y,int M[][9])  //to check the small 3*3 boxes
{  	int k;
	x=(x/3)*3; y=(y/3)*3;
	int X=x+3,Y=y+3;
	for(;x<X;x++)
		for(k=y;k<Y;k++)  //i had developed tools 1,3,4V&H at the time of writing this. my box code was: for(;x<X;x++)for(;y<Y;y++) if(v==m[x][y]) return 1; the code as a whole was fine but later i found that tool1 wasn't running as it should have been and after much labor found that it's sth. in the box fuction.Only after much labor again could i fix it. Lesson learned: don't compromise the code for aesthetics.I don't wanna do that :'(.
			if(v==M[x][k])
				return 1;
	return 0;	
}
void screen();
void board(int [][9]);
void load();
void player(int [][9]);
void tool1(int [][9], int tol);//traditional: checks if a cell can take only one number(can't take any of the other 8 that is). if yes,puts that number in it 
void tool3(int [][9]);//box by box: checks which all elements a box needs and if only one cell can take a number, puts it theres
void tool4V(int [][9]);void tool4H(int M[][9]);//line by line: checks which all elements a line needs and if only one cell can take a number, puts it there
//I can't help but think these three tools as dimensions which seldom, if at all, overlap. And they complement each other so well! 
int score(int [][9]);
int  check(int ,int);
void tne();
void tool1(int M[][9], int tol)
{  	int i,j;
	int s=1;
	while(s)
	{	//clrscr();
		s=0;
		int x,y,v,count,V;
		for(x=0;x<9;x++)
		{ 
			for(y=0;y<9;y++)
			{    count=0;
			if(M[x][y]==0)
			{	for(v=1;v<=9;v++)
				{   int flag=0;
				for(i=0;i<9;i++)
				{	if(v==M[x][i]||v==M[i][y]||box(v,x,y,M)==1)
					{flag=1;break; }	}			
				if(flag==1){count++; }
				else V=v;
				}
			if(tol==1&&count==8)//9-tol=8
			{M[x][y]=V;s=1;}
			 else if(tol==2&&count==9-tol)
			 { aa[ai] = x*10+y;ai++;}
		    }
			}
		}
	}
}

void tool3(int M[][9])
{
int i,j;
int s=1;
int h,k,v,x,y,flag,a,arr[9][9],grp_a[9];//arr[grp no][indices from 0 to 8]=values that group needs; where grp no=3*h+k
while(s)
{  s=0;
for(h=0;h<=2;h++)// Going in the order:   0 3 6
{				 //						  1 4 7
	for(k=0;k<=2;k++)//					  2	5 8
	{   a=0;
	for(v=1;v<=9;v++)
	{	flag=0;
	for(x=3*h;x<3*h+3;x++)
	{
		for(y=3*k;y<3*k+3;y++)
		{
			if(M[x][y]==v)flag=1;
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
		for(x=3*h;x<3*h+3;x++)
		{
			for(y=3*k;y<3*k+3;y++)
			{   flag=0;
			if(M[x][y]==0)  { 
				c0unt++;
				for(i=0;i<9;i++)
					if(v==M[x][i]||v==M[i][y])
						flag=1;
				if(flag)count++;
				else {X=x;Y=y;}	}	
			}
		}
		if(count==c0unt-1)//You could totally eliminate the variable c0unt by replacing "c0unt-1" by "grp_a[3*h+k]" in this statement <--. Tway you have one less variable but c"0"unt makes it clear that you are counting empty places
		{M[X][Y]=v;s=1;}
		}
	}
}
}
}

void tool4V(int M[][9])
{  
int i,j;
int s=1;
int x,y,V[9][9],a,v,flag,V_a[9];//V[X][indices or "a"]=no.s the row X doesn't have	
while(s)
{	s=0;
for(x=0;x<9;x++)
{a=0;	
for(v=1;v<=9;v++)
{flag=0;
for(y=0;y<9;y++)
{
	if(M[x][y]==v)
		flag=1;
} 
if(flag==0) {V[x][a]=v;a++;}
}
V_a[x]=a;
}	

int X,Y,count,c0unt;
for(x=0;x<9;x++)
{	c0unt=0;
for(y=0;y<9;y++)
	if(M[x][y]==0)
		c0unt++;
for(a=0;a<V_a[x];a++)
{   count=0;
v=V[x][a]; 
for(y=0;y<9;y++)
{   flag=0;
	if(M[x][y]==0)
{   if(box(v,x,y,M)==1)flag=1;
	for(i=0;i<9;i++)
	{if(M[i][y]==v){flag=1;/*system("cls");screen();board();printf("&%d %d %d&",i,y,v);/**/}}
	if(flag==1){count++;/*printf("(%d %d) %d ",x,y,v);getch();/**/}
	else{X=x;Y=y;} }
} 
//printf(" %d %d %d ",v,count,c0unt);
if(count==c0unt-1)
{M[X][Y]=v;c0unt--;s=1;} 
//printf("/%d %d %d %d/",x,V[x][a],count,c0unt);//getch();
}
}
}
}

void tool4H(int M[][9])
{  
int i,j;
int s=1; 
int x,y,V[9][9],a,v,flag,V_a[9];//V[y][indices or "a"]=no.s the column y doesn't have	
while(s)
{	s=0;
for(y=0;y<9;y++)
{a=0;	
for(v=1;v<=9;v++)
{flag=0;
for(x=0;x<9;x++)
{
	if(M[x][y]==v)
		flag=1;
} 
if(flag==0) {V[y][a]=v;a++;}
}
V_a[y]=a;
}	

int X,Y,count,c0unt;
for(y=0;y<9;y++)
{	c0unt=0;
for(x=0;x<9;x++)
	if(M[x][y]==0)
		c0unt++;
for(a=0;a<V_a[y];a++)
{   count=0;
v=V[y][a]; 
for(x=0;x<9;x++)
{   flag=0;
	if(M[x][y]==0)
{   if(box(v,x,y,M)==1)flag=1;
	for(i=0;i<9;i++)
	{if(M[x][i]==v){flag=1;/*system("cls");screen();board();printf("&%d %d %d&",i,y,v);/**/}}
	if(flag==1){count++;/*printf("(%d %d) %d ",x,y,v);getch();/**/}
	else{X=x;Y=y;} }
} 
//printf(" %d %d %d ",v,count,c0unt);
if(count==c0unt-1)
{M[X][Y]=v;c0unt--;s=1;}
//printf("/%d %d %d %d/",x,V[x][a],count,c0unt);//getch();
}
}
}
}

void player(int M[][9])
{  screen();board(M);getch();int prevscore,Score;
do{
	prevscore=Score;
	tool1(M,1);
	tool3(M);
	tool4H(M);
	tool4V(M);
	Score=score(M);}while(Score!=prevscore&&Score!=81);
	board(M);printf("\nScore=%d",Score);getch();
}

void tne()  //trial and error
{
int i,j;
int t,x,y;
tool1(m,2);
int s=0;
while(s<ai)
{
int M[9][9]; for(i=0;i<9;i++)for(j=0;j<9;j++)M[i][j]=m[i][j];
t=aa[s];
x=t/10;y=t%10;
int a[2];
t=0;int v,i;
for(v=1;v<=9;v++)
{
	int flag=0;
	for(i=1;i<=9;i++)
	{	if(v==m[x][i]||v==m[i][y]||box(v,x,y,M)==1)
	{flag=1;break; }	}			
	if(flag!=1){a[t]=v;t++;}
}

M[x][y]=a[1];
player(M);

if(score(M)!=81)
 { 
 for(i=0;i<9;i++)for(j=0;j<9;j++)M[i][j]=m[i][j];
 M[x][y]=a[0];
 player(M);
 }

if(score(M)==81)
return;

s++;
}
}


main()
{   //clrscr();
	load();
	player(m);
	if(score(m)!=81)
	tne();
}


void load()
{   FILE *a;int i,j;
int c=0,ar[81];char ch;
a=fopen("sudoku.txt","r"); 
for(i=0;i<81;i++)
{
	ch=fgetc(a);
	ar[i]=ch-48;
}
for(i=0;i<9;i++)
{
	for(j=0;j<9;j++)
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
	gotoxy(1,1);printf("    0   1   2   3   4   5   6   7   8 ");
	for(i=0;i<9;i++)
	{ printf("\n    \n%d",i);
	}
}
void board(int M[][9])
{	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(!check(i,j))
			{ gotoxy(4*i+4,2*j+3);
			printf(":%d:",M[i][j]);
			}
			else
			{ gotoxy(4*i+5,2*j+3);
			M[i][j]==0?printf(" "):printf("%d",M[i][j]);
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
int score(int M[][9])
{   int i,j;
	int score=0;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(M[i][j]!=0) score++;
	return score;
}
