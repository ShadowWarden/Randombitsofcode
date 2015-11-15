/* gsolve.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  Reads in data from a file (which contains the co-efficients for a system of 
*  equations, along with the right hand side) and uses gaussian elimination to 
*  solve a system of linear equations of the form
*  AX=B  
*  File Format:
*  Line 1: n
*  Line 2: a11 a12 ... a1n b1
*  :
*  Line n: an1 an2 ... ann bn
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getsize(FILE*);  //Working!!
int solve(FILE*);  //Working!!!!!
void generate(float *,int ,FILE*); //Working!
void print(float *,int);  //Working!
void rowswap(float *,int,int); //Working!

int main(int argc, char **argv){
	/* Main routine. 
	*   Calls solve() to convert the matrix into an upper triangular 
	*   matrix and print the array that is obtained after back-substitution
	*/
	char *a;
	a = argv[1]; // File to be inputted is in argv[1]
	FILE *fp;
	fp=fopen(a,"r");
	int res=solve(fp);
	fclose(fp);
	return res;
}

int getsize(FILE* fp){
	int size;
	fseek(fp, SEEK_SET,0);
	fscanf(fp,"%d",&size);
	return size;	// Dont return *size with size being a pointer. I seem
			// to get a seg fault for some reason
}

void print(float *v,int n){
	int i;
	for(i=0;i<n;i++){
		if(*(v+i)>=0)
			printf("%0.3f ",*(v+i));
		else
			printf("%0.2f ",*(v+i));
	}
	printf("\n");
}

void generate(float* array,int n,FILE* fp){
	int i,j;
	for(i=0;i<n;i++)	
		for(j=0;j<n;j++)
			fscanf(fp,"%f",(array+(n*i+j)));	
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

int solve(FILE* fp){
	int n = getsize(fp),i,j;
	float *array = (float *) malloc (((n+1)*n)*sizeof(float));
	float *soln = (float *) malloc (n*sizeof(float));
	printf("Inside solve()\n");
	generate(array,n+1,fp);
	printf("Generated main matrix\n");
	for(j=0;j<n-1;j++){
		int k=j,l;
		float pivot=*(array+(n+1)*j+j);
		if(abs(pivot)<=0.01){  //Swap if pivots get too small
			rowswap(array,j,n+1);
			pivot=*(array+(n+1)*j+j);
		}
		for(l=k+1;l<n;l++){	
				float next=*(array+(n+1)*(l)+j)/pivot;
			for(i=j;i<n+1;i++)
				*(array+(n+1)*l+i)-=*(array+(n+1)*(k)+i)*next;				}		
	}
	for(i=n-1;i>=0;i--){
		*(soln+i)=*(array+(n+1)*i+n);
		for(j=i+1;j<n;j++)
			*(soln+i)-=*(array+(n+1)*i+j)*(*(soln+j));
		*(soln+i)/=*(array+(n+1)*i+i);
	}
	printf("Solutions\n");
	print(soln,n);
	free(array);
	free(soln);
	return 0;
}
