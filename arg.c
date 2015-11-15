#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int n=atoi(argv[1]);
	int i;
	printf("%s",argv[0]);
	for(i=1;i<=n;i++){
		printf("%d\n",i);
	}
}
