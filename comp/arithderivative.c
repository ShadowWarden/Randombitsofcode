/*  Arithderivative.c
*   Omkar H. Ramachandran
*   omkar13@iisertvm.ac.in
*
*/

#include<stdio.h>
#include<stdlib.h>

int arithderivative(int a[],int n){
	int i,j,product,sum=0;
	for(i=0;i<n;i++){
		product=1; 
		for(j=0;j<n;j++){
			if(i!=j){
				product*=a[j];
			}
		}
		sum+=product;
	}
	return sum;
}

int prime(int a[],int m,int primes[],int primelen){
	int k=0,i;
	for(i=0;i<primelen;i++){
		if(m%i == 0){
			a[k]=primes[i];
			k++;
		}
	}
	return k;
}

int primegen(int a[], int n){
	int i,j,flag;
	a[0]=2;
	a[1]=3;
	int len=2;
	for(i=5;len<=n;i++){
		flag=0;
		for(j=2;j<i/2;j++){
			if(i%j==0){
				flag++;
				break;
			}
		}
		if(!flag){
			// i is a prime
			a[len]=i;
			len++;	
		}
	}
	return len;
}

int main(int argc, char ** argv){
	int num,arithder;
	int primes[20];
	int primeseed[50];
	num=atoi(argv[1]);
	int primelen=primegen(primeseed,50);
	int len=prime(primes,num,primegen,primelen);
	if(len==1){
		arithder=1;
	}else{
		arithder=arithderivative(primes,len);
	}
	printf("%d",arithder);
	return arithder;
}	
