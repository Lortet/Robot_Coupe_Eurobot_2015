#include "Arduino.h"
#include "odometrie.h"
#include "moteurs.h"
#include "asservissement.h"
#include "codeur.h"
#include <math.h>

signed long NbTic_Droit = 0;
signed long NbTic_Gauche = 0;
long Nb_Tic_RD_Av = 0;
long Nb_Tic_RG_Av = 0;
signed long Vari_X_F;
signed long Vari_Y_F;
signed long Vari_X;
signed long Vari_Y;
position Pos;


/* mise a jour la nouvelle position du robot (x, y, O)
 * par approximation de segment de droite */
 
void calcul_position_segment(position *p, double distance, double angle)
{
  
  p->O -= ((angle/INIT_ENTRAXE/2)*(2*PI))/VALEUR_PAR_TOUR; // Calcul de la valeur de l'angle en Radian
 
 if ( p->O > ANGLE_ODO_MAX)
	{
          p->O -= 2*PI;
	}
  else if ( p->O < ANGLE_ODO_MIN)
	{
          p->O += 2*PI;
	}

          Vari_X_F += (double)sin(p->O)*distance/TICK_PAR_MM; // Calcul de la variation de X
          Vari_Y_F += (double)cos(p->O)*distance/TICK_PAR_MM; // Calcul de la variation de Y
		
          Vari_X = (signed long)Vari_X_F;
	  Vari_Y = (signed long)Vari_Y_F;
		
          Vari_X_F-=Vari_X;
	  Vari_Y_F-=Vari_Y;
		
	  p->x += Vari_X; // Valeur de X
	  p->y += Vari_Y; // Valeur de Y

}

 
/* delta_roue_droite et delta_roue_gauche sont les distance en pulses
 * parcourue par les roues droite et gauche en un cycle */
void odometrie(position *p)
{
  
  long delta_rg;
  long delta_rd;
  
  getPosition(NbTic_Gauche,NbTic_Droit);
  
  delta_rd = NbTic_Droit - Nb_Tic_RD_Av;
  delta_rg = NbTic_Gauche - Nb_Tic_RG_Av;
  
  Nb_Tic_RD_Av = NbTic_Droit;
  Nb_Tic_RG_Av = NbTic_Gauche;
  
  
  double delta_distance = 0, delta_angle = 0;

  delta_distance = ((double)(delta_rd + delta_rg))/2; // Calcul de la variation de la distance
  delta_angle = (double)(delta_rd - delta_rg)*2; // Calcul de la variation de l'angle
 
 calcul_position_segment(p,delta_distance, delta_angle);
 /*
 Serial.print("Postition X : ");
 Serial.println(p->x);
 Serial.print("Postition Y : ");
 Serial.println(p->y);
 Serial.print("Angle O : ");
 Serial.println(p->O);
 */
}

void Reset_Tics()
{
	Nb_Tic_RG_Av=0;
	Nb_Tic_RD_Av=0;
}

void Calcul_Trajectoire(double x, double y, int *tick, int *distance)
{
double X = x;
double Y = y;


//219.84/2 = 109.92 pour parcourir 1mm (hors asservissement)
// Calcul du module en tick, a reinjecter en tant que consigne en translation au robot. 109.92 est le nombre de tick par mm
*distance = sqrt(pow(((X)*109.92),2)+pow(((Y)*109.92),2));  
 
 
 
//calcul de l'angle de rotation du robot en fonction de x et y 
double deg = 0;
double rad = 0;

//differentes formule a utilisees en fonction de la valeur de x et y, cela nous permet de calculer l'angle entre 0 et 2PI.

if (X > 0 && Y >= 0) rad = atan(Y/X);
if (X > 0 && Y < 0) rad = atan(Y/X)+2*PI;
if (X < 0) rad = atan(Y/X)+PI;   
if (X == 0 && Y >0) rad = PI/2;
if (X == 0 && Y <0) rad = 3*(PI/2);

deg = (180*rad)/PI; // Conversion en degree
*tick = (NB_TICKS_PAR_TOUR*deg)/360; // Conversion en tick que nous rÃ©injectons ensuite comme consigne de rotation au robot
  
}

void Go(double x, double y)
{
  int tick = 0;
  int distance = 0;
  
  Calcul_Trajectoire(x,y,&tick,&distance); // Calcul de la l'angle (tick) et de la distance (distance) a effectuer pour atteindre la position x,y souhaité
  
  addConsigneTh(tick); // Le robot effectue la rotation
  do{ asservissement();}while(!robotArrete());
  stopRobot();
  delay(1000);
  
  addConsigneTr(distance*2); // Le robot avance la distance calculer en fonction de (x,y)
  do{
  odometrie(&Pos); 
  asservissement();
  }while(!robotArrete());
      
  stopRobot();
  delay(1000);
      
  addConsigneTh(-tick); // Le robot se remet dans l'axe trigonométrique 
  do{ 
  odometrie(&Pos);
  asservissement();
  }while(!robotArrete());
    
  stopRobot();
  delay(1000);
  }

