/* bact.c v 1.1
*  Omkar H. Ramachandran
*  University of Colorado Boulder
*  omkar.ramachandran@colorado.edu
*  Program that simulates the motion of many particles that collide elastically
*  (momentum and energy conserved). In addition each of these particles divide
*  into two new particles every so many time steps
*
*  As of now, there's no active momentum/energy conservation. A collision sends
*  both particles in random directions.
*
*  Input parameters: output file. Later on add an input that can provide the 
*  initial position of multiple bacterium and the program can start from there
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BACT 8192
#define MAX_TIME 41
#define BACT_RAD 1
#define TIME_DIV 3
#define NUMARGS 1

int simulate(FILE *);
void collide(int,int);
void setnewpos(int);
void replicate(int);
float bact[MAX_BACT][5];

int main(int argc,char **argv){
	if(argc!=NUMARGS+1){
		printf("Incorrect number of parameters\n");
	}
	time_t t;
	FILE *fout = fopen(argv[1],"w");
	srand((unsigned) time(&t));
	int res = simulate(fout);
	fclose(fout);
	return res;
}

void setcollide(int cur){
	int i;
	for(i=0;i<cur;i++)
		bact[i][4] = 0;
}

void normalize(int i){
	float sqr = sqrt(bact[i][2]*bact[i][2]+bact[i][3]*bact[i][3]);
	bact[i][2]/=sqr;
	bact[i][3]/=sqr;
}

void collide(int i,int cur){
	int j;
	for(j=i;j<cur;j++){
		if(bact[j][0]<=bact[i][0] && bact[j][1]<=bact[i][1]){
			bact[j][2] = rand()%5000-2500;
			bact[j][3] = rand()%5000-2500;
			normalize(j);
			bact[i][4] = 1;
			bact[j][4] = 1;
		}
	}
}

void setnewpos(int cur){
	int i;
	for(i=0;i<cur;i++){
		bact[i][0] += bact[i][2];
		bact[i][1] += bact[i][3];
	}
}

void replicate(int cur){
	int i;
	for(i=0;i<cur;i++){
		bact[cur+i][0] = bact[i][0];
		bact[cur+i][1] = bact[i][1];
	}
}

void tumble(int cur){
	int i;
	for(i=0;i<cur;i++){
		bact[i][2] = rand()%5000-2500;
		bact[i][3] = rand()%5000-2500;
		normalize(i);
	}
}

int simulate(FILE *fout){
	int cur = 1,time=1,i;
	bact[0][0] = 0;		//Start at origin
	bact[0][1] = 0;
	bact[0][2] = rand()%5000-2500;
	bact[0][3] = rand()%5000-2500;
	bact[0][4] = 0;
	normalize(0);
	while(cur<=MAX_BACT && time<=MAX_TIME){
		setcollide(cur);
		for(i=0;i<cur;i++){
			if(bact[i][4] == 0)
				collide(i,cur);
		}
		setnewpos(cur);
		if(time%TIME_DIV == 0){
			replicate(cur);
			cur*=2;
		}
		tumble(cur);
		time++;
	}
	for(i=0;i<cur;i++){
		fprintf(fout,"%f %f\n",bact[i][0],bact[i][1]);
	}
	return 1;
}
