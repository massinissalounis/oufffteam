%Partie optimiseur : méthode du gradient
function [x,f]=grapasco(xinit,epsilon,simu)

[f,g]=feval(simu,xinit);
fprintf('Valeur initiale de f=%f et |g|=%f',f,norm(g,1));

x=xinit;
iter=0
while(norm(g,2)>epsilon & iter<1000)
    iter = iter + 1;
    d=-g; %direction
    t=0.1;
    x=rlpascon(x,d,t,simu); % recherche linéaire =>x suivant
    %x=Wolfe(x,d,t,simu) % recherche linéaire méthode de Wolfe
    [f,g]=feval(simu,x);
    fprintf('Itertn %d:\tf=%f et |g|=%f\n',iter,f,norm(g,1));
    %c=input('pause');
end

    