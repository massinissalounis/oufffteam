%Recherche linéaire de Wolfe
function xsvt=Wolfe(x,d,t,simu)

%Initialisation
tg=0;
td = 0;
m1 = 0.1; %coeff d'Armijo
m2 = 0.9; %coeff de Wolfe

%Calcul de q(0) et q'(0)
[f,g]=feval(simu,x);
q0 = f;
Dq0 = g'*d;

%Calcul de q(t_init) et q'(t_init)
xsvt = x + t*d;
[fsvt,g]=feval(simu,xsvt);
qt = fsvt;
Dqt = g'*d;

%test d'arret
test_a = (qt <= q0 + m1*t*Dq0) & (Dqt >= m2*Dq0); %OK
test_b = (qt >  q0 + m1*t*Dq0); %t trop grand
test_c = (qt <= q0 + m1*t*Dq0) & (Dqt < m2*Dq0); %t trop petit

while(~test_a)
    %Modification de l'intervalle de recherche
    if(test_b)
        td = t;
    else 
        if(~test_a) %alors test_c est vrai
            tg = t;
        end
    end
    
    %Mise à jours de t
    if(td ==0)
        t = 10*t;
    else
        t = 0.5*(tg + td);
    end
    
    %Calcul de xsvt
    xsvt = x + t*d;
    [fsvt,g]=feval(simu,xsvt);
    qt = fsvt;
    Dqt = g'*d;

    %test d'arret
    test_a = (qt <= q0 + m1*t*Dq0) & (Dqt >= m2*Dq0);
    test_b = (qt >  q0 + m1*t*Dq0);
    
end

%Tracé de l'évolution des itérés
l = norm(xsvt-x,2);
du=l*0.1;
u=0.0:du:l;
e = (xsvt-x)/l;
u1 = x(1) + u*e(1);
u2 = x(2) + u*e(2);
plot(u1,u2,'Color','black');
plot(x(1),x(2),'o','Color','black');
    
            
