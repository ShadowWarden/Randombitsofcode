/* trap.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple program that uses the trapezoidal rule to evaluate a 1D integral.
*  This particular program is very easy to parallelize. We'll get to that 
*  later on if you're interested. To run, compile and execute as follows:
*  $ gcc -o trap trap.c
*  $ ./trap [starting point] [Ending point] [Number of trapezoids]
*
*  NOTES ON COMPILING C IN LINUX
*  I'd recommend using C because C++ has changed a lot and you probably have
*  only used Turbo C++, which is 20 years old. Modern C is very very similar to
*  the old C++. The only real difference is printf in the place of cout. scanf
*  instead of cin and malloc() instead of new(). To compile, do the following.
*  In a terminal, go to the directory where the source code is and type
*  $ gcc [programname].c
*  If you do an 'ls' command, you should see a new executable called 'a.out'
*  if the compile was successful. To run, simply type
*  $ ./a.out
*  GCC has tons of options. For example, if you want your executable to be named
*  something specific, simply type
*  $ gcc -o [executablename] [programname].c
*  If you want to know more, type
*  $ man gcc
*  and that should bring up a man page with details on every single option.
*/

#include <stdio.h>
#include <stdlib.h>

float f(float);
float trap(float,float,int,float);

int main(int argc,char ** argv){
/* Inputs : the number of trapezoids (N) */
/* Input parsing : So, in unix (any OS actually), you can send in arguements
*  through your command line. When you run your code, you can type in something
*  like this
*  $ ./trap 3 4 1
*  The the values that you type in are stored in an array (argv) and are stored
*  by deafult as characters. argv[0] is simply the name of the program './trap'
*  argv[1] is 3, argv[2] is 4 etc. But all of them are stored as characters.
*  So convert them to floats, we need the atof() command from stdlib.h
*/
	float left = atof(argv[1]);
	float right = atof(argv[2]);
	int N = atoi(argv[3]);
	float h = (right-left)/N;
	float sum = trap(left,right,N,h);
	printf("The integral from %f to %f = %f\n",left,right,sum);
	return 1; 
}

float f (float x){
	return x*x;
}

float trap(float left, float right, int n, float h){
	float sum, x;
	int i;
	sum = (f(left)+f(right))/2;  	// Do the end points seperately
	x = left;
	for(i=1;i<n;i++){
		x = x+h;		// Now its just a matter of adding
		sum += f(x);		// each end point skipping the first
					// and last.
	}
	sum*=h;				// Normalize
	return sum;			// return
}

