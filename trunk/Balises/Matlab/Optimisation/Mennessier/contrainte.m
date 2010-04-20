function contrainte(f)

x1=0:0.5:20;
x2=1-x1;
ind=find(x2);
Px1=x1(ind);
Px2=x2(ind);
T=[Px1;Px2];

for i=1:length(Px1)
    x=[T(1,i);T(2,i)];
    val(i)=feval(f,x);
end
figure(1),plot3(Px1,Px2,val,'*');

