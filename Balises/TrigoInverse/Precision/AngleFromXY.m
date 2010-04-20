function [alpha, beta, gamma] = AngleFromXY(x, y)

    % Constantes
    TAILLE_MAP_L_Y = 3000;
    TAILLE_MAP_l_X = 2100;

    u = sqrt( TAILLE_MAP_L_Y^2 + (TAILLE_MAP_l_X/2)^2);
    v = u;
  	w = TAILLE_MAP_l_X;
  
  	a = sqrt( (TAILLE_MAP_L_Y-y)^2 + x^2 );
  	b = sqrt( (TAILLE_MAP_L_Y-y)^2 + (TAILLE_MAP_l_X-x)^2 );
  	c = sqrt ( y^2 + ((TAILLE_MAP_l_X/2)-x)^2 );
    
    s = acos( TAILLE_MAP_L_Y / v );
    r = s;
    
    alpha = (acos( ( a^2 + b^2 - w^2 ) / (2*a*b) ));    
  	beta  = (acos( ( b^2 + c^2 - u^2 ) / (2*b*c) ));
  	gamma = (acos( ( a^2 + c^2 - v^2 ) / (2*a*c) ));

    Angle1 = abs(acos((-TAILLE_MAP_L_Y*(y-TAILLE_MAP_L_Y)) / (TAILLE_MAP_L_Y * sqrt((TAILLE_MAP_L_Y - y)^2 + (x)^2))));
    
    Angle2 = abs(acos((-TAILLE_MAP_L_Y*(y-TAILLE_MAP_L_Y)) / (TAILLE_MAP_L_Y * sqrt((TAILLE_MAP_L_Y - y)^2 + (TAILLE_MAP_l_X-x)^2))));
    
    
    if Angle1 < r
       gamma = 2 * pi - gamma;
    end
    if Angle2 < s
       beta = 2 * pi - beta ;
    end
end