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

[alpha, beta, gamma] = AngleFromXY(251, 201);


        j = CalculAngle(u,w,beta,alpha,s);
        i = CalculAngle(v,w,gamma,alpha,r);

        k = CalculAngle(w,v,alpha,gamma,r);
        if( gamma > pi )
            k=-k;
        end

        m = CalculAngle(w,u,alpha,beta,s);
        if beta > pi
            m=-m;
        end


        % Calcul dans les 3 triangles
        % Cas 1
        a = w * (sin(j)/sin(alpha));
        x(1) = a*cos(i);
        y(1) = L - a*sin(i);

        % Cas 2
        b= u * (sin(pi-m-beta)/sin(beta));
        
        x(2) = l - b*cos(j);
        y(2) = L - b*sin(j);
        
        % Cas 3
        a= v * (sin(pi-k-gamma)/sin(gamma));
        
        x(3) = a*cos(i);
        y(3) = L - a*sin(i);
        
        x
        y