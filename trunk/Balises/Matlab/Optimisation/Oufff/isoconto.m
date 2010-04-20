
%Tracé de l'isocontour de la fonction f
function z=isoconto(f)

%[X,Y] = meshgrid(-0.75:0.05:0.75,-0.75:0.05:0.75); %pour simu2 ou sim1
%[X,Y] = meshgrid(-0.5:0.01:1.0,-0.5:0.01:1.0);%pour simu3
%[X,Y] = meshgrid(-0.25:0.01:0.25,-0.25:0.01:0.25);%pour simu3
%[X,Y] = meshgrid(-1.2:.01:1.2,-5:.1:5);%pour simu3
[X,Y] = meshgrid(-16:1:16,-13:1:13);

x=X(:);
x=x';

y=Y(:);
y=y';

n=length(x');
p=[x;y];

for i=1:n
    z(i) = feval(f,p(:,i));
end

z = z';
[H,L]=size(X);
Z=reshape(z,H,L);
%Z = (1-X).^2 + 100.0*(Y-X.^2).^2;

figure(1),
%plot3(X,Y,Z),grid on
surfc(X,Y,Z),grid on,colormap hsv
hold on

figure(2);
[C,h] = contour(X,Y,Z,30);
axis square
hold on


%clabel(C,h)
%colormap default