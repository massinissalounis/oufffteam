%Optimisation
clear;
close all;

f = 'FctCout';

%isoconto(f);
hold on
% contrainte(f);

% Position des balises
%P=[-1 2 1 -3 
 %   3 2.5 -1.2 -1];
P=[3000 3000 0
   0    2100 1050];
plot(P(2,:),P(1,:),'*');
save P;

% Position du robot
X_true=[145;10];


TX=X_true*ones(1,3);
TX;
PosRel=P-TX;

% Les données
% Angles entre les balises
%angles(1)=69.98*pi/180; % alpha
%angles(2)=145.01*pi/180; % beta
%angles(3)=145.01*pi/180; % gamme

angles(1)=115.33*pi/180; % alpha
angles(2)=98.90*pi/180; % beta
angles(3)=145.77*pi/180; % gamme

save angles;

angles




xinit=[0;0];

erreur=0.000000001;

%[xopt,fopt]=grapasco(xinit,erreur,f);

[xopt,fopt]=BFGS(xinit,erreur,f)

xopt