/* linspace.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Generates an array of evenly spaced elements.  
*/

#include <stdio.h>
#include <stdlib.h>

int linspace(float*,float,float,int);
void print(float *,int);

int main(int argc, char **argv){
	// Format: ./linspace 1 10 101 => linspace(1,10,101)
	float start = atof(argv[1]);
	float finish = atof(argv[2]);
	int num = atoi(argv[3]);
	float * array = (float *) malloc (num*sizeof(float));
	int res = linspace(array,start,finish,num);
	print(array,num);
	return res;
}

int linspace(float *array,float start, float finish, int num){
	float diff = (finish-start)/(num-1);
	int i;
	*(array) = start;
	for(i=1;i<num;i++){
		*(array + i) = *(array + i-1) +diff;
	}
	return 0;
}

void print(float *array, int size){
	int i;
	for(i=0;i<size;i++)
		printf("%0.2f ",*(array+i));
	printf("\n");
}
