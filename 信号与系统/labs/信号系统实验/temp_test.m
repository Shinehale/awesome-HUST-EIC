E=1; T1=1; w1=2*pi/T1;
t=linspace(-0.5,0.5,N);
f=0.5*square(2*pi*(t+T1/4));
CTFS(f,1000,1,10);