function[a_sin]=itsin_projet(lambda,NR)
NH=length(lambda);
hmin=-(NH-1)/2;
hmax=(NH-1)/2;
H=[hmin:1:hmax];
% H=[1:1:NH];
R=[0:1:NR-1];

% E est une matrice de taille R*H
E=R'*H;
E=sin(E);
a_sin=E*lambda';