%Partie Simulateur de l'algo d'optimisation
function [f,g] = simu1(X)

load Azimut
load P

TX=X*ones(1,3);
PosRel=P-TX

%les donn�es
Azimut_simul=atan2(PosRel(2,:),PosRel(1,:))

f=sum((Azimut_simul-Azimut).^2)

tmp=(PosRel(2,:)./PosRel(1,:)).^2 + 1;

g(1)=2*sum(((Azimut_simul-Azimut))./tmp.*PosRel(2,:)./PosRel(1,:).^2);
g(2)=2*sum(((Azimut_simul-Azimut))./tmp.*(-1)./PosRel(1,:));

g=g'