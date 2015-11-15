/* doubleintegral.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Program that evaluates the double integral of a function at a uniform delta  
*  x and delta y, though delta x != delta y. Uses the same algorithm as 
*  integrate.c
*  File input:
*  Line 1: Matrix size (Square matrices for now)
*  Line 2: Delta x
*  Line 3: Delta y
*  Line 4: Matrix row 1
*  Line 5: row 2
*  etc.
*  Line n+3: Matrix row n
*/

#include <stdio.h>
#include <stdlib.h>

int getsize(FILE *);
float getdelta(FILE *);
void generate(FILE *,float *,int);
float add(float *,int,float);

int main (int argc, char ** argv){
	char *a;
	a = argv[1];
	FILE *fp;
	if(!(fp=fopen(a,"r"))){
		printf("Input file does not exist\n");
		exit(0);
	}	
	int res = integrate(fp);
	fclose(fp);
	return res;
}

int getsize(FILE *fp){
	int size;
	fseek(fp,SEEK_SET,0);
	fscanf(fp,"%d",&size);
	return size;
}

float getdelta(FILE *fp){
	fseek(fp,SEEK_SET,sizeof(int));
	int i;
	float area=1;
	float delta[2];
	for(i=0;i<2;i++){
		fscanf(fp,"%f",&delta[i]);
		area *= delta[i];
	}
	return area;
}

void generate(FILE *fp, float *array, int size){
	int i,j;
	fseek(fp,SEEK_SET,sizeof(int)+2*sizeof(float));
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			fscanf(fp,"%f",(array + size*i + j));
		}
	}
}

float add(float *array, int size, float delta){
	int i=0,counter=1;
	float sum=0;
	while(i<size*(size-1)){
		float average = ((*(array + i))+ (*(array + i+1))+ (*(array + i+size))+ (*(array + i+size+1)))/4;
		sum += average*delta;
		i++;
	}
	return sum;
}

int integrate(FILE *fp){
	int size = getsize(fp);
	float *array = (float *) malloc (size*size*sizeof(float));
	float delta = getdelta(fp);
	generate(fp,array,size);
	float sum = add(array,size,delta);
	printf("Integral: %f\n",sum);
	free(array);
	return 1;
}
