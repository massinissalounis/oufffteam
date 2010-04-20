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

NbTest = 10;
Dist = 5;
compteur = 0;

for itL = L-NbTest:L
    for itl = (l-NbTest)/2:(l+NbTest)/2

        MesX = 0;
        MesY = 0;
        compteur = compteur + 1;
            
         [alpha, beta, gamma] = AngleFromXY(1050, 1500);
            
        % Algo
        j = CalculAngle(u,w,beta,alpha,s) * (1);
        i = CalculAngle(v,w,gamma,alpha,r);

        k = CalculAngle(w,v,alpha,gamma,r) * (1);
        p = CalculAngle(u,v,beta,gamma,s);

        o = CalculAngle(v,u,gamma,beta,r) * (1);
        m = CalculAngle(w,u,alpha,beta,s);

        % Calcul dans les 3 triangles
        % Cas 1
        a1 = w * (sin(j)/sin(alpha));
        b1 = w * (sin(i)/sin(alpha))
        x(1) = a1*cos(i);
        y(1) = L + sin(pi+j)*b1;

        % Cas 2
        a2 = v * (sin(p)/sin(gamma));
        c2 = v * (sin(k)/sin(gamma)); 
        x(2) = w/2 + cos(pi - (p+q)) * c2;
        y(2) = c2 * sin(pi - (p+q));

        % Cas 3
        b = u * (sin(o)/sin(beta)) 
        x(3) = l + cos(-pi/2 - s - m) * b;
        y(3) = L + sin(-pi/2 - s - m) * b;
            
        Sortie(compteur,:) = [x(1) x(2) x(3) 0  y(1) y(2) y(3)];
        
    end
end
