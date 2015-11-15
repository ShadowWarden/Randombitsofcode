from pylab import *
b = loadtxt("output.txt");
x = b[:,0]
y = b[:,1]
plot(x,y,'r.')
show()
