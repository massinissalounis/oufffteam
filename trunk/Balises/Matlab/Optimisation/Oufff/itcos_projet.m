function[a_cos]=itcos_projet(lambda,NR)
NH=length(lambda);
hmin=-(NH-1)/2;
hmax=(NH-1)/2;
H=[hmin:1:hmax];
% H=[1:1:NH];
% Le vecteur R doit avoir la meme taille que f_cherche
R=[0:1:NR-1];

% E est une matrice de taille R*H
E=R'*H;
E=cos(E);
a_cos=E*lambda;
% a_cos est un vecteur de taille R