/* inverse.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Reads in data from a file and uses gaussian elimination to find the 
*  inverse of a given square matrix
*  AX=B  
*  File Format:
*  Line 1: n
*  Line 2: a11 a12 ... a1n 
*  :
*  Line n+1: an1 an2 ... ann 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getsize(FILE*);  //Working!!
int invert(FILE*);  //Working!!!!!
void generate(float *,int ,FILE*); //Working!
void rowswap(float *,int,int); //Working!
void identity(float *,int,int);
float uppertriag(float *,int);
void lowertriag(float *,int);
void normalize(float *,int);
void print(float *,int,int);

int main(int argc, char **argv){
	/* Main routine. 
	*   Calls solve() to convert the matrix into an upper triangular 
	*   matrix and multiply across pivots
	*/
	char *a;
	a = argv[1]; // File to be inputted is in argv[1]
	FILE *fp;
	if(!(fp=fopen(a,"r"))){
		printf("Input file does not exist\n");
		exit(1);
	}
	int res=invert(fp);
	fclose(fp);
	return res;
}

int getsize(FILE* fp){
	int size;
	fseek(fp, SEEK_SET,0);
	if(!fscanf(fp,"%d",&size)){
		printf("Input file is not in the prescribed format\n");
		exit(0);
	}
	return size;	// Dont return *size with size being a pointer. I seem
			// to get a seg fault for some reason
}

void generate(float* array,int n,FILE* fp){
	int i,j;
	for(i=0;i<n;i++)	
		for(j=0;j<n;j++)
			if(!fscanf(fp,"%f",(array+(2*n*i+j)))){
				printf("Input file is not in the prescribed format\n");	
				exit(0);
			}
}

void rowswap(float *array,int j,int n){
	/* When called, this function needs to look at rows > j and swap 
	*  element by element when it encounters the first proper pivot.
	*  The outer loop takes you through the rows after j. And since the 
	*  first j elements are 0 because of previous row transformations, 
	*  it is enough to swap elements from j till n. 
	*/
	int i,k;
	for(i=j+1;i<n-1;i++){
		if(abs(*(array+(n)*i+j))>0.01){
			for(k=j;k<n;k++){
				float tmp=*(array+n*j+k);
				*(array+n*j+k)=*(array+n*i+k);
				*(array+n*i+k)=tmp;
			}					
			break;
		}
	}
}

void identity(float *array, int n, int offset){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			*(array + (n+offset)*(i) + j+offset) = (i == j)?1:0;
		}
	}
}

float uppertriag(float *array,int n){
	int i,j;
	for(j=0;j<n-1;j++){
		int k=j,l;
		float pivot1=*(array+(2*n)*j+j);
		if(abs(pivot1)<=0.01){  //Swap if pivots get too small
			rowswap(array,j,2*n);
			pivot1=*(array+(2*n)*j+j);
		}
		for(l=k+1;l<n;l++){	
			float next=*(array+(2*n)*(l)+j)/pivot1;
			for(i=j;i<2*n;i++)
				*(array+(2*n)*l+i)-=*(array+(2*n*k)+i)*next;
		}
	}
	return *(array + (2*n)*(n-1) + n-1);	
}


void lowertriag(float *array,int n){
	int i,j;
	for(j=n-1;j>=1;j--){
		int k=j,l;
		float pivot1=*(array+(2*n)*j+j);
		for(l=k-1;l>=0;l--){	
			float next=*(array+(2*n)*(l)+j)/pivot1;
			for(i=j;i>=0;i--){
				*(array+(2*n)*l+i)-=*(array+(2*n)*(k)+i)*next;
			}
			for(i=n;i<2*n;i++){
				*(array+(2*n)*l+i)-=*(array+(2*n)*(k)+i)*next;			
			}	
		}
	}	
}

void print(float *array,int n,int offset){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			float print = *(array + (2*n)*i + (j + offset));
			if(print >= 0)
				printf("%f ",print);
			else
				printf("%f ",print);
		}
		printf("\n");
	}
}

void normalize(float *array,int n){
	int i,j;
	for(i=0;i<n;i++){
		float pivot = *(array + 2*n*i + i);
		for(j=n;j<2*n;j++)
			*(array+ 2*n*i + j) /= pivot;
	}
}

int invert(FILE* fp){
	int n = getsize(fp),i,j;
	float *array = (float *) malloc ((2*n*n)*sizeof(float));
	generate(array,n,fp);
	identity(array,n,n);
	float checkdet = uppertriag(array,n);
	if (checkdet == 0){
		printf("The matrix is singular\n");
		return 1;
	}
	lowertriag(array,n);
	normalize(array,n);
	print(array,n,n);
	free(array);
	return 0;
}
