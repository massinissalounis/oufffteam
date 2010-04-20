%Partie optimiseur : méthode du gradient
function [x,f]=BFGS(xinit,epsilon,simu)

[f,g]=feval(simu,xinit);
fprintf('Valeur initiale de f=%f et |g|=%f',f,norm(g,1));

W = eye(size(g),size(g))

x=xinit;
iter=0
while(norm(g,2)>epsilon & iter<1500)
    iter = iter + 1;
    d=-W*g; %direction
    t=1;
    %x=rlpascons(x,d,t,simu) % recherche linéaire =>x suivant
    xsvt=Wolfe(x,d,t,simu) % recherche linéaire méthode de Wolfe
    [f,gsvt]=feval(simu,xsvt);
    
    %Calcul de la matrice Hessienne approchée
    s = xsvt-x;
    y = gsvt-g;
    D = y'*s;
    A = (s*y'*W + W*y*s')/D;
    B = (1 + (y'*W*y)/D)*(s*s')/(y'*s);
    Wsvt = W - A + B;
    
    %itérées suivantes
    x = xsvt;
    g = gsvt;
    W = Wsvt;
    fprintf('Itertn %d:\tf=%f et |g|=%f\n',iter,f,norm(g,1));
    %c=input('pause');
end

    