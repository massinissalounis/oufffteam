%Partie recherche linéaire de l'algo d'optimisation
function xsvt=rlpascons(x,d,t,simu)

xsvt = x + t*d;
[fsvt,g]=feval(simu,xsvt);
[f,g]=feval(simu,x);
dt=0.5*t; % 10 °/0 de t

while(fsvt>f & t>0)
    dt=0.5*t;
    t = t -dt;
    xsvt = x + t*d;
    [fsvt,g]=feval(simu,xsvt);
end

%Tracé de l'évolution des itérés
l = norm(xsvt-x,2);
du=l*0.1;
u=0.0:du:l;
e = (xsvt-x)/l;
u1 = x(1) + u*e(1);
u2 = x(2) + u*e(2);
plot(u1,u2,'Color','black');
plot(x(1),x(2),'o','Color','green');
