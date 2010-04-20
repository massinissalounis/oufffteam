function [AngleSortie] = CalculAngle( dist1, dist2, angle1, angle2, angle3)

  inter1 = (dist1/sin(angle1));
  inter2 = (dist2/sin(angle2));
  inter3 = (angle3 - angle1 + pi/2);
  inter4 = (angle2 - pi);
  
  % Calcul du numerateur
  inter5 = ((inter1 * cos(inter3) + inter2 * cos(inter4))^2);
  
  % Calcul du denominateur
  inter6 = ((inter1 * sin(inter3) + inter2 * sin(inter4))^2);
  
  AngleSortie =  (acos(sqrt(inter5/(inter5+inter6))));
end