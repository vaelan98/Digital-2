lamda=0.9;
ts=1e-3;
f=10;
Vmax=3;

num1=[(1-lamda),0];
den1=[1,-lamda];
H1=tf(num1,den1,ts);

num2=[lamda,-lamda];
den2=[1,-lamda];
H2=tf(num2,den2,ts);

num3=[1e-3,1e-3];
den3=[2,-2];
H3=tf(num3,den3,ts);