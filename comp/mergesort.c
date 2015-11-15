/* mergesort.c
*  Omkar H. Ramachandran
*  omkar13@iisertvm.ac.in
*  A program that illustrates the mergesort algorithm (Ascending order).
*  Step 1: Tear the list down into subgroups of maximum size 2
*  Step 2: Arrange each sub group in ascending order
*  Step 3: Merge the subgroups
*  The input is a text file of the following format:
*  Line 1: Size of list (1D)
*  Line 2: Array elements (space seperated)
*/

#include <stdio.h>
#include <stdlib.h>

int getsize(FILE *);
int sort(FILE *);
void generate(FILE *,float *,int);
void print(float *,int);

int main(int argc, char **argv){
	/* Main routine
	*  Calls sort() which calls another function mergesort() to 
	*  sort the given list.
	*/
	char *a;
	a = argv[1];  //File name is stored in argv[1]
	FILE *fp;
	if(!(fp = fopen(a,"r"))){
		printf("Input file does not exist");
		exit(0);
	}
	int res = sort(fp);
	fclose(fp);
	return res;
}

int getsize(FILE *fp){
	int size;
	fseek(fp,SEEK_SET,0);
	fscanf(fp,"%d",&size);
	return size;
}

void generate(FILE *fp,float *array, int size){
	int i;
	fseek(fp,SEEK_SET,sizeof(int));
	for(i=0;i<size;i++){
		fscanf(fp,"%f",(array+i));
	}
}

void print(float *array,int size){
	int i;
	for(i=0;i<size;i++){
		printf("%0.2f ",*(array+i));
	}	
	printf("\n");
}

void mergesort(float *array, int size){
	/* Step 1:
	*  Arrange the individual sub-groups of two in ascending order
	*/
	int limit = (size % 2 == 0)? size : size -1;
	int i;
	char ch;
	for(i=0;i<limit;i+=2){
		float ent1 = *(array + i);
		float ent2 = *(array + i+1);
		if(ent1 > ent2){
			*(array + i) = ent2;
			*(array + i+1) = ent1;
			printf("Swapping %f %f",ent1,ent2);
			scanf("%c",&ch);
		}
	}
	/* Step 2:
	*  Merge the individual subgroups.
	*  Create an 'original array' of size cursize+2
	*  
	*/
	int cursize=2;
	while (cursize < size){
		// Merging subgroups
		int j=0;
		int klim=2;
		if(limit<size && cursize==(limit)){
			klim=1;
		}	
		while(j<cursize){
			float ent1= *(array + j);
			float ent2= *(array + cursize);
			if(ent2 < ent1){
				*(array + cursize) = ent1;
				*(array + j) = ent2; 
			}
			j++;
			ent1 = *(array + cursize+1);
			if(ent1<ent2 && klim==2){
				*(array + cursize) = ent1;
				*(array + cursize+1) = ent2; 
			}
		}
		cursize+=2;
		print(array,size);
	}
}

int sort(FILE *fp){
	int size = getsize(fp);
	float *array = (float *) malloc (size*sizeof(float));
	generate(fp, array, size);
	mergesort(array, size);
	print(array, size);
	free(array);
	return 1;
}
