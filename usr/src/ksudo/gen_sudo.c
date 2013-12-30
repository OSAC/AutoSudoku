#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
char** gen(int level){
	srand(time(NULL));
	int row[9][9];
	int solution[9][9];
	int puzzle[9][9];
	int i,j,cur_ran,temp;
	
	int defficulty=(level%4)*2;/* no of space to made blank*/
	
	for(i=0;i<9;i++)
		{
			cur_ran = 1+(rand()%9);
			for(j=0;j<i;j++)
				if(row[0][j] == cur_ran){
					i--;
					break;
				}
				if(j==i)
					row[0][i]=cur_ran;
		}
	for(i=0;i<9;i++){
		row[1][i] = row[0][(i+3)%9];
		row[2][i] = row[0][(i+6)%9];
	}
	
	for(i=0;i<9;i++){
		row[3][i] = row[0][i];
		row[6][i] = row[0][i];
	}
	for(i=0;i<9;){
		for(j=0;j<3;j++){
			row[3][i+j] = row[0][i+(j+1)%3];
			row[6][i+j] = row[0][i+(j+2)%3];
		}
	i+=3;	
	}
	for(i=0;i<9;i++){
		row[4][i] = row[3][(i+3)%9];
		row[5][i] = row[3][(i+6)%9];
		
	
		row[7][i] = row[6][(i+3)%9];
		row[8][i] = row[6][(i+6)%9];
	}
	
	
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			solution[i][j] = row[i][j];
		

for(i=0;i<9;i++)
	for(j=0;j<9;j++)
		puzzle[i][j]=solution[i][j];

for(i=0;i<9;i++)
	for(j=0;j<defficulty;j++)
			puzzle[i][(rand()%9)] = 0;
return puzzle;		
}


