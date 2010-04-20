#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 3000
#define l 2100

double u;
double v;
double w;

double angle_calcul( double dist1, double dist2, double angle1, double angle2, double angle3 )
{

  double inter1;
  double inter2;
  double inter3;
  double inter4;
  double inter5;
  double inter6;
  
  inter1 = dist1/sin(angle1);
//  printf("inter1 = %f\n",inter1); 
  inter2 = dist2/sin(angle2);
//  printf("inter2 = %f\n",inter2); 
  inter3 = angle3 - angle1 + M_PI_2;
//  printf("inter3 = %f\n",inter3); 
  inter4 = angle2 - M_PI;
//  printf("inter4 = %f\n",inter4); 
  
  // Calcul du numerateur
  inter5 = pow(inter1 * cos(inter3) + inter2 * cos(inter4),2);
//  printf("inter5 = %f\n",inter1); 
  
  // Calcul du denominateur
  inter6 = pow(inter1 * sin(inter3) + inter2 * sin(inter4),2);
//  printf("inter6 = %f\n",inter1); 
    
  return acos(      sqrt(     1/(1+(inter6/inter5))       )          );      
       
}


int main(int argc, char *argv[])
{
  // Angles interbalises mesures
  double alpha = 35.76*M_PI/180;
  double beta = 58.06*M_PI/180;
  double gamma = 93.83*M_PI/180;
  
  // Distances balises-robot inconnues
  double a;
  double b;
  double c;
  
  // Angles inconnus  
  double i;
  double j;
  double k;
  double m;
  double o;
  double p;
  
  // Distances entre les balises connues
  u = sqrt( pow(L,2) + pow(l/2,2) );
  v = u;
  w = l;
  
  // Angles connus
  double q = asin( L / v );
  double r = acos( L / v );
  double s = r;
  double t = q;
  
  
  printf(" Distances entre les balises : u = %f, v = %f, w = %f\n",u,v,w);
  printf(" Angles connus : q = %f, r = %f, s = %f, t = %f\n",(180*q)/M_PI,(180*r)/M_PI,(180*s)/M_PI,(180*t)/M_PI); 
  
  j = angle_calcul(u,w,beta,alpha,s);
  i = angle_calcul(v,w,gamma,alpha,r);
  
//  k = angle_calcul(w,v,alpha,gamma,r);
//  p = angle_calcul(u,v,beta,gamma,s);
  
//  m = angle_calcul(w,u,alpha,beta,s);
//  o = angle_calcul(v,u,gamma,beta,r);  
  
  printf(" j = %f\n",j*180/M_PI);
  printf(" i = %f\n",i*180/M_PI);
  
  printf(" erreur = %f\n", ( M_PI-i-j-alpha)*180/M_PI);
  
//  printf(" k = %f\n",k*180/M_PI);
//  printf(" p = %f\n",p*180/M_PI);
  
//  printf(" m = %f\n",m*180/M_PI);
//  printf(" o = %f\n",o*180/M_PI);
  
//  printf("\n");
  
  a = w * (sin(j)/sin(alpha)); // Trouver une meilleure méthode
  
  printf("a = %f\n",a);   
  
  double x = a*cos(M_PI-alpha-j);
  
  printf("i par j = %f\n",(M_PI-alpha-j)*180/M_PI);  
  
  x = a*cos(i);
  
  double y = L - a*sin(M_PI-alpha-j);
  
  y = L - a*sin(i);

  printf("cas 1 :x = %f, y = %f\n",x,y);
  
  
  
//  j = angle_calcul(u,w,alpha,gamma,s);
  
 //   a = w * (sin(j)/sin(alpha)); // Trouver une meilleure méthode
  
//  printf("a = %f\n",a);   
  
 // x = a*cos(M_PI-alpha-j);
  
 // y = L - a*sin(M_PI-alpha-j);
  
//  printf("cas 2 :x = %f, y = %f\n",x,y);
  
  
 // j = angle_calcul(u,w,gamma,beta,s);
  
//  a = w * (sin(j)/sin(alpha)); // Trouver une meilleure méthode
  
//  printf("a = %f\n",a);   
  
//  x = a*cos(M_PI-alpha-j);
  
//  y = L - a*sin(M_PI-alpha-j);
  
//  printf("cas 3 :x = %f, y = %f\n",x,y);
  
  
  
  
  
  
  
  system("PAUSE");	
  return 0;
}
