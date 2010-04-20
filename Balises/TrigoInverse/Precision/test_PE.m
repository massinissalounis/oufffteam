clear all;
close all;
clc;

% Données connues
L = 3000;
l = 2100;

u = sqrt(L^2 + (l/2)^2);
v = u;
w = l;

% Angles connus
q = asin( L / v );
s = acos( L / v );
r = s * (1);
t = q * (1);

[alpha, beta, gamma] = AngleFromXY(2000, 1500);


j = CalculAngle(u,w,beta,alpha,s) * 1;
i = CalculAngle(v,w,gamma,alpha,r);

o = CalculAngle(v,u,gamma,beta,r);
m = CalculAngle(w,u,alpha,beta,s);

k = CalculAngle(w,v,alpha,gamma,r);
p = CalculAngle(u,v,beta,gamma,s);

j1=j*180/pi;
i1=i*180/pi;

o1=o*180/pi;
m1=m*180/pi;
p1=p*180/pi;

alpha1=alpha*180/pi;
beta1=beta*180/pi;
gamma1=gamma*180/pi;

erreur = (pi-j-i-alpha)*180/pi;

a1 = w * (sin(j)/sin(alpha));
b1 = w * (sin(i)/sin(alpha));
x = a1*cos(pi-alpha-j);
y = L - a1*sin(pi-alpha-j);

(j+m+s)*180/pi

(m)*180/pi

c= u * (sin(m)/sin(beta))

b= w * (sin(i)/sin(alpha))