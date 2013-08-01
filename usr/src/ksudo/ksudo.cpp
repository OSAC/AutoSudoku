#include<stdio.h>	//program to solve 9*9 sudoku problem
#include<stdlib.h>	//Date : 27th july 2012
#include<string.h>
#include<termios.h>
#include<unistd.h>	
#include<iomanip>
#include<iostream>
using namespace std;
int getch() {
struct termios oldt,newt;
int ch;
tcgetattr( STDIN_FILENO, &oldt );
newt = oldt;
newt.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newt );
ch = getchar();
tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
return ch;
}
//////////////////////////////////////////////////
class sudoku
{
int sudo[9][9][10];
int sudo1[9][9][10];
int i,j,k,uf,hf,count,nu;//uf-undo flag, hf-hide flag, count-step_counter, nu-no.of_undo
int filled;
public:
FILE *inp;
FILE *oup;
sudoku(); //constructor
void readfile();
void write();
void show();
void eliminate();
int update();
void solve();
int check_row(int ith,int val);
int check_col(int jth,int val);
int check_sqr(int ith,int jth,int val);
int issolved();
void print_line(int pos);
void print_val(int val,int pos);
void input();
int index(int);
void countfilled();
void backup();
void help();
};
//////////////////////////////////////////////////
sudoku :: sudoku() //constructor definition
{
uf=0;hf=1;nu=0;count=0;
filled=0;
for(i=0;i<9;i++)
for(j=0;j<9;j++)
for(k=0;k<=9;k++){
sudo[i][j][k]=0;
sudo1[i][j][k]=0;}
}
//////////////////////////////////////////////////
void sudoku :: backup() //for undo option.
{
for(i=0;i<9;i++)
for(j=0;j<9;j++)
for(k=0;k<=9;k++)
sudo1[i][j][k]=sudo[i][j][k];
}
//////////////////////////////////////////////////
void sudoku :: readfile() //reads input sudoku problem from file input.txt
{
if(inp==NULL){
cout<<"Couldn't locate any input file ...Program terminated !!\n"<<endl;
exit(0);}
else
cout<<"  Reading data form file ...";
for(i=0;i<9;i++)
for(j=0;j<9;j++){
fscanf(inp,"%d",&sudo[i][j][0]);
//cout<<"copying 1 through 9\n";
if(sudo[i][j][0]==0){
	for(k=1;k<=9;k++)
	sudo[i][j][k]=k;
//cout<<"Copied in ["<<i<<"]["<<j<<"]"<<endl;
	}}
countfilled();
}
////////////////////////////////////////////////////////
void sudoku :: print_line(int pos)
{
int i;
if(pos==0|pos==3|pos==6|pos==9)
{
for(i=0;i<=36;i++)
if(i==0|i==12|i==24|i==36)
cout<<char(43);//+
else
cout<<char(45);//-
}
/*else		//one extra line in each new line !!
{
for(i=0;i<=36;i++)
if(i==0|i==12|i==24|i==36)
cout<<char(43);
else
cout<<char(32);
}*/
}
////////////////////////////////////////////////////////////
void sudoku :: print_val(int val,int pos)
{
if(pos==3|pos==6|pos==9)
{if(val==0)
cout<<char(32)<<"."<<char(32)<<char(124);
else
cout<<char(32)<<val<<char(32)<<char(124);
}
else
{if(val==0)
cout<<char(32)<<"."<<char(32)<<char(32);
else
cout<<char(32)<<val<<char(32)<<char(32);
}
}
///////////////////////////////////////////////////////
void sudoku :: show() //display module
{
int sr,sc,m,n;
cout<<endl;
for(i=0;i<9;i++)
{cout<<"\t\t";
print_line(i);
if(i==0|i==3|i==6)
cout<<"\n\t\t|";
else cout<<"|";
for(j=0;j<9;j++)
print_val(sudo[i][j][0],j+1);
cout<<endl;
}cout<<"\t\t";
print_line(i);
cout<<"\tstep:"<<count;
cout<<endl;

if(hf!=1){
cout<<"\n  Possible values with respective positions ... \n";
//cout<<"\t";
for(j=0;j<9;j++)
cout<<"\t"<<"["<<j+1<<"]";
cout<<endl<<endl;
for(i=0;i<9;i++){
cout<<"["<<i+1<<"]";
for(j=0;j<9;j++)
{
cout<<"\t";
if(sudo[i][j][0]==0)
	{for(k=1;k<=9;k++)
	if(sudo[i][j][k]!=0)
	cout<<sudo[i][j][k];}
else
cout<<'*';
}
cout<<endl;
}//for i
}//if
if(oup!=NULL)
write();
if(issolved()==1)
 {
cout<<"[Solved] no.of undo = "<<nu;
cout<<"\nCONGRATULATIONS!\n";
exit(0);
 }
}
//////////////////////////////////////////////////////////
int sudoku :: check_row(int ith,int val)
{
for(int j=0;j<9;j++)
if(val==sudo[ith][j][0])
{cout<<" match found in row!";
return 1;}
return 0;
}
//////////////////////////////////////////////////////////
int sudoku :: check_col(int jth,int val)
{
for(int i=0;i<9;i++)
if(val==sudo[i][jth][0])
{cout<<" match found in column!";
return 1;}
return 0;
}
//////////////////////////////////////////////////////////
int sudoku :: check_sqr(int ith,int jth,int val)
{
int m,n,sr,sc;
sr=3*(ith/3);
sc=3*(jth/3);
for(n=sr;n<(sr+3);n++)
for(m=sc;m<(sc+3);m++)
if(sudo[n][m][0]==val){
cout<<" Match found in square!";	
return 1;}
return 0;
}
//////////////////////////////////////////////////////////
void sudoku :: countfilled()
{
for(i=0;i<9;i++)
for(j=0;j<9;j++)
{
if(sudo[i][j][0]==0)
continue;
else 
filled++;
}
cout<<endl;
cout<<filled<<" positions are filled...Remaining positions : "<<81-filled;
}
//////////////////////////////////////////////////////////
int sudoku :: index(int x)
{
if(x>=0&&x<3)
return(1);
else if(x>=3&&x<6)
return(2);
else if(x>=6&&x<9)
return(3);
}
//////////////////////////////////////////////////////////
int sudoku :: issolved()
{
int val,m,n,chk=1,chk1,sc,sr;
for(i=0;i<9;i++)
for(j=0;j<9;j++)	//first test -all field sud be filled
if(sudo[i][j][0]==0) 	//if check fail.
chk=0;
if(chk==1) //only if check passed.
{
for(i=0;i<9;i++)
for(j=0;j<9;j++)
{
val=sudo[i][j][0];
	for(m=0;m<9&&m!=j;m++) //check row
	if(sudo[i][m][0]==val){
	cout<<"Match in "<<i+1<<"th row, Value: "<<val<<"\n"; //match found in row
	chk=0;}
	for(n=0;n<9&&n!=i;n++) //check column
	if(sudo[n][j][0]==val){
cout<<"Match in "<<j+1<<"th column, Value: "<<val<<"\n"; //match found in column
	chk=0;}
	sr=3*(i/3);		//check square
	sc=3*(j/3);
	for(n=sr;n<(sr+3);n++)
	for(m=sc;m<(sc+3);m++)
	if(n==i&&m==j)
	continue;
	else if(sudo[n][m][0]==val){
	chk=0;
int indx=index(sr);
int indy=index(sc);
cout<<"Match in the square, Value: "<<val<<" --("<<indx<<","<<indy<<")square\n";}
}//for
} //if chk==1
return chk;
}
///////////////////////////////////////////////////////
void sudoku :: write() //writes solved values to a file
{
rewind(oup);
for(i=0;i<9;i++){
for(j=0;j<9;j++)
fprintf(oup,"%d\t",sudo[i][j][0]);
fprintf(oup,"\n");}
}
/////////////////////////////////////////////////////////
void sudoku :: eliminate() //eliminate the not possibel values
{
count++;
int m, n;
int val,sc,sr;
for(i=0;i<9;i++)
for(j=0;j<9;j++)
if(sudo[i][j][0]!=0)
{	val=sudo[i][j][0];
	//cout<<"Checking row\n";
	for(m=0;m<9;m++)  //row ko k lai laddu
	{
	if(sudo[i][m][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[i][m][k]){
	sudo[i][m][k]=0; }
	}
	//cout<<"Checking column"<<endl;
	for(n=0;n<9;n++)   //column ko k lai laddu
	{
	if(sudo[n][j][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[n][j][k]){
	sudo[n][j][k]=0;}
	}
	sr=3*(i/3);
	sc=3*(j/3);
	//cout<<"Checking small square\n";
	for(n=sr;n<(sr+3);n++)
	for(m=sc;m<(sc+3);m++)  //small square ko k lai laddu
	{
	if(sudo[n][m][0]==0)
	for(k=1;k<=9;k++)
	if(val==sudo[n][m][k]){
	sudo[n][m][k]=0;}
	}
}//if
}//eliminate
//////////////////////////////////////////////////////////
int sudoku :: update() //fetch the single possible value in each field
{			//for auto solve only.
int count,ans,ct=0; 
cout<<endl;
for(i=0;i<9;i++)
for(j=0;j<9;j++)
if(sudo[i][j][0]==0)
{
	count=0;
	for(k=1;k<=9;k++)
	if(sudo[i][j][k]!=0)
	{
	ans=sudo[i][j][k];
	count++;
	}//if !=0
	if(count==1&&ans!=0){
	sudo[i][j][0]=ans;ct++;
	cout<<"Replaced ["<<i+1<<"]["<<j+1<<"] by unique value "<<ans<<endl;}
}
cout<<ct<<" places are automatically solved.";
if(ct>0)
return 1;
else return 0;
}//update
///////////////////////////////////////////////////////
void sudoku :: help()
{
cout<<"\n***********************************************************************************************\n";
cout<<"\t\t\t\tCONTROL COMMAND HELP\n";
cout<<"***********************************************************************************************\n";
cout<<"<shft+h>\t--display this help menu.\n";
cout<<"<ctrl+a>\t--to complete, program itsesf solves the problem.\n";
cout<<"<ctrl+y>\t--undo (only one time undo after each new step).\n";
cout<<"<space> \t--for user input, provides user to input at desired location.\n";
cout<<"<ctrl+f>\t--for force input ,provides user to fill non empty positions too (not recomended!).\n";
cout<<"<ctrl+h>\t--show/hide possible values at respective positions (default hidden).\n";
cout<<"NOTE: you can input multiple values at once providing string of three digits seperated by (,).\n";
cout<<"***********************************************************************************************\n";
}
///////////////////////////////////////////////////////
void sudoku :: solve() //solve sudoku problem.
{
char ch,str[3],c[1];
int row, col, val,updt;
this->show();
do{cout<<"\nPress <space> to input OR <ctrl+a> for Auto-Solve $";
	ch=getch();
	if(ch==1){//ctrl+a
		backup();uf=1;	//backup before auto update
		updt=this->update();
		if(updt==0)
		cout<<"\nSorry,the algorithm couldn't go any futher...\nBUT still you can find any way to solve...Try it.";
		else{ this->eliminate();
		this->show();}}
		//break;
	else if(ch==32){//<space>
		cout<<"\nType position and value to ENTER... \n";
		cout<<"(e.g 129 to replace value[1][2] by 9) # ";
		cin>>str;
sprintf(c,"%c",str[0]);row=atoi(c);
sprintf(c,"%c",str[1]);col=atoi(c);
sprintf(c,"%c",str[2]);val=atoi(c);
		if(val<1||val>9||row<1||row>9||col<1||col>9)
		cout<<"\t\"Stupid User...Invalid input!!\"";
		else if(sudo[row-1][col-1][0]!=0){
		cout<<"\tField already occupied!";
		cout<<"\n\t\"Value not replaced\"";}
		else{
		int ch_col=check_col(col-1,val);
		int ch_row=check_row(row-1,val);
		int ch_sqr=check_sqr(row-1,col-1,val);		
		if(sudo[row-1][col-1][0]==0 && ch_row!=1 && ch_col!=1 && ch_sqr!=1)
		{
		backup();uf=1; //backup before updating user input
		sudo[row-1][col-1][0]=val;
		for(k=1;k<=9;k++)
		sudo[row-1][col-1][k]=0;
		this->eliminate();
		cout<<"\tReplaced ["<<row<<"]["<<col<<"] by "<<val;
		}
		else
		cout<<"\n\t\"Value not replaced\"";
		}//else
		}//else if
	else if(ch==6)	//force to input value <ctrl+f>
		{//value input at users risk
		cout<<"\nThis input is at your own risk... \n";
		cout<<"Type position and value to ENTER # ";
		cin>>str;
sprintf(c,"%c",str[0]);row=atoi(c);
sprintf(c,"%c",str[1]);col=atoi(c);
sprintf(c,"%c",str[2]);val=atoi(c);
		if(val<1||val>9||row<1||row>9||col<1||col>9)
		cout<<"\t\"Stupid User...Invalid input!!\"";
		else{
		backup();uf=1;	//backup before force update
		sudo[row-1][col-1][0]=val;
		for(k=1;k<=9;k++)
		sudo[row-1][col-1][k]=0;
		this->eliminate();
		cout<<"\tReplaced ["<<row<<"]["<<col<<"] by "<<val;
		}//else
		}//else if
	else if(ch==25) //undo <ctrl+y>
		{
		if(uf==0)
		cout<<"\n**Operation cann't be undo now!";
		else{
		nu++;
		for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		for(k=0;k<=9;k++)
		sudo[i][j][k]=sudo1[i][j][k];
		this->show();
		uf=0;}
		}
	else if(ch==10)	//return key 
		this->show();	//resolving bug...
	else if(ch==8) //ctrl+h hide/unhide possible values
		{
		hf=(hf+1)%2; //if hf==0,hf->1 && if hf==1,hf->0
		system("clear");
		this->show();
		}
	else if(ch==72)
	help();
	else cout<<"\n**Undefined value input**\n";
}while(ch!=27);
cout<<"\t**Program Terminated... Bye"<<endl;
}
//////////////////////////////////////////////////////////
void sudoku :: input()
{
char inp[10];
char c[1];
cout<<("Enter values (one row at a time placing 0 at empty locations ) : \n");
for(int i=0;i<9 ;i++)
{
scanf("%s",inp);
for(int j=0;j<9;j++)
{
sprintf(c,"%c",inp[j]);
sudo[i][j][0]= atoi(c);
if(sudo[i][j][0]==0)
for(int k=1;k<=9;k++)
sudo[i][j][k]=k;
}
}
cout<<("Input prarsing finished....");
countfilled();
}
//////////////////////////////////////////////////////////
int main(int argc,char *argv[]) //main control
{
sudoku s;
if(argv[1]==NULL)
cout<<"\t-->No input method....**Program Terminated !!\n";
else{
if(strcmp(argv[1],"--input")==0)//==NULL)
s.input();
else{
s.inp=fopen(argv[1],"r");
s.readfile();}
s.oup=fopen(argv[2],"w");
s.eliminate();
s.solve();}
return 0;
}
