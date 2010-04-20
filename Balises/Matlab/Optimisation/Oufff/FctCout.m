%Partie Simulateur de l'algo d'optimisation
function [f,g] = simu1(Position)



L=3000;
l=2100;

% On recoit la position x=Position(1),y=Position(2) 

% on va creer les angles

u = sqrt( L^2 + (l/2)^2 );
v = u;
w = l;

a = sqrt( (L-Position(2))^2 + Position(1)^2 );
b = sqrt( (L-Position(2))^2 + (l-Position(1))^2 );
c = sqrt( Position(2)^2 + ((l/2)-Position(1))^2 );
  
angles_estime(1) = acos( ( a^2 + b^2 - w^2 ) / (2*a*b) );
angles_estime(2) = acos( ( b^2 + c^2 - u^2 ) / (2*b*c) );
angles_estime(3) = acos( ( a^2 + c^2 - v^2 ) / (2*a*c) );

%180*angles_estime/pi

angles_estime;

% Calcul de la fonction cout

load angles;


% F est un vecteur contenant la difference quadratique de chaque angle
f=sum((angles_estime-angles).^2)

x=Position(1);
y=Position(2);

angles_derive_x(1)=-0.2e1 * (((4 * x - 4200) * (9000000 - 6000 * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (13410000 - 6000 * y + y ^ 2 - 4200 * x + x ^ 2) ^ (-0.1e1 / 0.2e1)) / 0.2e1 - ((18000000 - 12000 * y + 2 * y ^ 2 + 2 * x ^ 2 - 4200 * x) * (9000000 - 6000 * y + y ^ 2 + x ^ 2) ^ (-0.3e1 / 0.2e1) * (13410000 - 6000 * y + y ^ 2 - 4200 * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * x) / 0.2e1 - ((18000000 - 12000 * y + 2 * y ^ 2 + 2 * x ^ 2 - 4200 * x) * (9000000 - 6000 * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (13410000 - 6000 * y + y ^ 2 - 4200 * x + x ^ 2) ^ (-0.3e1 / 0.2e1) * (-4200 + 2 * x)) / 0.4e1) * ((4 - (18000000 - 12000 * y + 2 * y ^ 2 + 2 * x ^ 2 - 4200 * x) ^ 2 / (9000000 - 6000 * y + y ^ 2 + x ^ 2) / (13410000 - 6000 * y + y ^ 2 - 4200 * x + x ^ 2)) ^ (-0.1e1 / 0.2e1));
angles_derive_x(2)=-(((-3 * l + 4 * x) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1)) - ((-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.3e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1) * (-2 * l + 2 * x)) / 0.2e1 - ((-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.3e1 / 0.2e1) * (-4 * l + 8 * x)) / 0.2e1) * ((1 - (-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) ^ 2 / (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) / (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2)) ^ (-0.1e1 / 0.2e1));
angles_derive_x(3)=-(((4 * x - l) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1)) - ((-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.3e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1) * x) - ((-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.3e1 / 0.2e1) * (-4 * l + 8 * x)) / 0.2e1) * ((1 - (-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) ^ 2 / (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) / (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2)) ^ (-0.1e1 / 0.2e1));

angles_derive_y(1)=-0.2e1 * (((-4 * L + 4 * y) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1)) / 0.2e1 - ((2 * L ^ 2 - 4 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - 2 * l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.3e1 / 0.2e1) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * (-2 * L + 2 * y)) / 0.4e1 - ((2 * L ^ 2 - 4 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - 2 * l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.3e1 / 0.2e1) * (-2 * L + 2 * y)) / 0.4e1) * ((4 - (2 * L ^ 2 - 4 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - 2 * l * x) ^ 2 / (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) / (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2)) ^ (-0.1e1 / 0.2e1));
angles_derive_y(2)=-(((-2 * L + 4 * y) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1)) - ((-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.3e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1) * (-2 * L + 2 * y)) / 0.2e1 - (4 * (-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) * (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.3e1 / 0.2e1) * y)) * ((1 - (-2 * L * y + 2 * y ^ 2 + l ^ 2 - 3 * l * x + 2 * x ^ 2) ^ 2 / (L ^ 2 - 2 * L * y + y ^ 2 + l ^ 2 - 2 * l * x + x ^ 2) / (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2)) ^ (-0.1e1 / 0.2e1));
angles_derive_y(3)=-(((-2 * L + 4 * y) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1)) - ((-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.3e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.1e1 / 0.2e1) * (-2 * L + 2 * y)) / 0.2e1 - (4 * (-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) * (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) ^ (-0.1e1 / 0.2e1) * (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2) ^ (-0.3e1 / 0.2e1) * y)) * ((1 - (-2 * L * y + 2 * y ^ 2 + 2 * x ^ 2 - l * x) ^ 2 / (L ^ 2 - 2 * L * y + y ^ 2 + x ^ 2) / (4 * y ^ 2 + l ^ 2 - 4 * l * x + 4 * x ^ 2)) ^ (-0.1e1 / 0.2e1));


angles_derive_x;
angles_derive_y;

 
% tmp=(PosRel(2,:)./PosRel(1,:)).^2 + 1;
% 
% g(1)=2*sum(((Azimut_simul-Azimut))./tmp.*PosRel(2,:)./PosRel(1,:).^2);
% g(2)=2*sum(((Azimut_simul-Azimut))./tmp.*(-1)./PosRel(1,:));

g(1)=2*( ((angles_estime(1)-angles(1))*angles_derive_x(1)) + ((angles_estime(2)-angles(2))*angles_derive_x(2)) + ((angles_estime(3)-angles(3))*angles_derive_x(3)));
g(2)=2*( ((angles_estime(1)-angles(1))*angles_derive_y(1)) + ((angles_estime(2)-angles(2))*angles_derive_y(2)) + ((angles_estime(3)-angles(3))*angles_derive_y(3)));

g=g';