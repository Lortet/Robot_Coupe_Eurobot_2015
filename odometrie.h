#ifndef __ODOMETRIE_H__
#define __ODOMETRIE_H__

#define ANGLE_ODO_MAX 3.1415
#define ANGLE_ODO_MIN -3.1415
#define INIT_ENTRAXE 2560
#define TICK_PAR_MM 103.7
#define VALEUR_PAR_TOUR 33.224


typedef struct
{
  double x;     /* en pulse */
  double y;
  double O;     /* en rad */
} position;
 

 
void calcul_position_segment(position *p,double distance, double angle); // la fonction qui est appelé par la fonction odometrie pour calculer les paramètres necessaire au calcul des coordonnées
void odometrie(position *p); // la fonction a appeler pour calculer la position du robot sur le terrain
void Reset_Tics();

/* Ces fonctions sont la pour que le robot calcule et se déplace aux coordonées entrés par l'utilisateur */ 

void Calcul_Trajectoire(double x, double y, int *tick, int *distance); // La fonction de calcul, la fonction Go s'occupe de l'appeler.
void Go(double x, double y); // fonction a utiliser pour que le robot se déplace aux coordonées souhaité 


#endif

