/* integrate.c
*  Omkar H. Ramchandran 
*  omkar13@iisertvm.ac.in
*  Program that takes function samples at a uniform delta x, approximates the 
*  function to the step function which has the values y'=(y(n)+y(n+1))/2. Once
*  this is done, the function simply adds up y'*(delta x)
*  File input:
*  Line 1: Array size
*  Line 2: Delta x
*  Line 3: array (space seperated, floating point numbers)
*/

#include <stdio.h>
#include <stdlib.h>

int integrate (FILE *);
int getsize(FILE *);
void generate(float *, int, FILE *);
float add(float *,float,int);
float getspace(FILE *);

int main(int argc, char ** argv){
	/* Main routine.
	*  Calls integrate() which calls another funciton to build the
	*  step function and then adds the areas of each small rectangle to
	*  get the integrated value. Smallar the delta x, more accurate the 
	*  value.
	*/
	char *a;
	a=argv[1];
	FILE *fp;
	if(!(fp = fopen(a,"r"))){
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
	printf("%d\n",size);
	return size;
}

float getspace(FILE *fp){
	float delta;
	fseek(fp,SEEK_SET,sizeof(float));
	fscanf(fp,"%f",&delta);
	printf("%f\n",delta);
	return delta;
}

void generate(float* array, int n, FILE *fp){
	int i;
	fseek(fp,SEEK_CUR,sizeof(float));
	for(i=0;i<n;i++){
		fscanf(fp,"%f",(array+i));
	}
}

float add(float* array,float delta,int n){
	int i;
	float sum=0;
	for(i=0;i<n-1;i++){
		float lower=*(array+i);
		float upper=*(array+i+1);
		sum+=delta*(lower+upper)/2;
	}
	return sum;
}

int integrate (FILE *fp){
	int size = getsize(fp);
	float *array= (float *) malloc (size*sizeof(float));
	float delta=getspace(fp);
	float soln;
	generate(array,size,fp);
	float sum=add(array,delta,size);
	printf("Integral: %f\n",sum);
	free(array);
	return 1;
}
