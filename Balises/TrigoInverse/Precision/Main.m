close all;
clear all;
clc;

% Résolution angulaire en degré et cartesienne en mm
Rangulaire = 0.04;
RCartesienne = 10;
Pas = 50;
Compteur = 0;

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


for itL = 1:Pas:L
    if mod(itL,10) == 0
        itL
    end
    
    for itl = 1:Pas:l

        MesX = 0;
        MesY = 0;
        Compteur = Compteur + 1;        

        [alpha, beta, gamma] = AngleFromXY(itl, itL);

        % Mise au point de la précision angulaire sur les mesures
         alpha = (round((alpha*180/pi) / Rangulaire) * Rangulaire) /180*pi;
         beta = (round((beta*180/pi) / Rangulaire) * Rangulaire) /180*pi;
         gamma = (round((gamma*180/pi) / Rangulaire) *Rangulaire) /180*pi;

        % Algo
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


        Precision([itl:itl+Pas],[itL:itL+Pas]) = 0;
        MesPrecision([itl:itl+Pas],[itL:itL+Pas]) = 0;
        MesPrecision([itl:itl+Pas],[itL:itL+Pas]) = sqrt((x(1)-itl)^2+(y(1)-itL)^2);

        for it1 = 1:3
            if (sqrt((x(it1)-itl)^2+(y(it1)-itL)^2) < RCartesienne) 
                Precision([itl:itl+Pas],[itL:itL+Pas]) = 1;
            end
        end
    end
end

figure(1);
imshow(Precision);
title(['Précision de ', num2str(RCartesienne), 'mm pour une resolution angulaire de ', num2str(Rangulaire),'°']);

figure(2);
imagesc(MesPrecision(:,:));
max(max(MesPrecision))