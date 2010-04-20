%Optimisation
clear;
close all;

f = 'FctCout';

% isoconto(f);
hold on
% contrainte(f);

%position des balises
%P=[-1 2 1 -3 
 %   3 2.5 -1.2 -1];
P=[0 0    3000
   0 2100 1050];
plot(P(2,:),P(1,:),'*')

save P;
%position du robot
X_true=[1050;1500];

%P2=[2100  1050 0
 %  0     3000  0];
TX=X_true*ones(1,3);
TX
PosRel=P-TX

%les données
Azimut=atan2(PosRel(2,:),PosRel(1,:));
Azimut_2(1) = mod(Azimut(1) - Azimut(3),pi); 
Azimut_2(2) = mod(Azimut(3) - Azimut(2),pi); 
Azimut_2(3) = mod(Azimut(2) - Azimut(1),pi);
save Azimut;
save Azimut_2;
Azimut*360/(2*pi)
Azimut_2*360/(2*pi)

xinit=[10;20];

erreur=0.000001;

%[xopt,fopt]=grapasco(xinit,erreur,f);
[xopt,fopt]=BFGS(xinit,erreur,f)

xopt