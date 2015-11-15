/* determinant.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Reads in data from a file and uses gaussian elimination to find the 
*  determinant of a given square matrix
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
int solve(FILE*);  //Working!!!!!
void generate(float *,int ,FILE*); //Working!
int rowswap(float *,int,int); //Working!

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
		exit(0);
	}
	int res=solve(fp);
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
			if(!fscanf(fp,"%f",(array+(n*i+j)))){
				printf("Input file is not in the prescribed format\n");	
				exit(0);
			}
}

int rowswap(float *array,int j,int n){
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
	return 1;
}
int solve(FILE* fp){
	int n = getsize(fp),i,j;
	float *array = (float *) malloc (((n+1)*n)*sizeof(float));
	float det = 1.0;
	generate(array,n,fp);
	int flag = 0;
	for(j=0;j<n-1;j++){
		int k=j,l;
		float pivot=*(array+(n)*j+j);
		if(abs(pivot)<=0.01){  //Swap if pivots get too small
			flag += rowswap(array,j,n);
			pivot=*(array+(n)*j+j);
		}
		for(l=k+1;l<n;l++){	
			float next=*(array+(n)*(l)+j)/pivot;
			for(i=j;i<n+1;i++)
				*(array+(n)*l+i)-=*(array+(n)*(k)+i)*next;			}		
	}
	for(i=0;i<n;i++){
		float ii = *(array + n*i + i);
		det *= ii;
	}
	for(i=0;i<flag;i++){
		det*=-1;
	}
	printf("Determinant: %f\n",det);
	free(array);
	return 0;
}
