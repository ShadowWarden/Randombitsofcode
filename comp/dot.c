/* dot.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Simple dot product. Takes inputs from files of the following format
*  Line 1: m1,n1,m2,n2
*  Line 2 -> n1+2: Elements of the first matrix
*  Line n1+2 -> n1+5: Elements of the second matrix
*/

#include <stdio.h>
#include <stdlib.h>

int* getsize(FILE *);

int main(int argc,char ** argv[]){
	char *a;
	FILE *fp;
	if(!(fp = fopen(*a,"r"))){
		printf("Input file does not exist\n");
		exit(1);
	}
	int res = dot(fp);
	return res;
}

int* getsize(FILE *fp){
	int size = (int *) malloc(4*sizeof(int));
	int i;
	fseek(fp,SEEK_SET,0);
	for(i=0;i<4;i++){
		fscanf(fp,"%d",(size+i));
	}
	return size;
}
