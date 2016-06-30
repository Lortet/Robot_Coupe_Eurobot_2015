#include "codeur.h"
#include "moteurs.h"
#include "asservissement.h"
#include "odometrie.h"

void setup() 
{
  pinMode(5,OUTPUT);
  initCodeur();
  initMoteurs();
  initAsservisssement();
  Serial.begin(115200);
}

/////////////PREVOIR DES FONCTIONS POUR RENDRE PLUS SIMPLE LUTILISATION DES DEPLACEMENT CI DESSOUS////////

  /*
  addConsigneTr(NB_TICKS_PAR_M); // Le robot avance d'un mètre
  do{ 
  asservissement();
  }while(!robotArrete());
  stopRobot();
  
  addConsigneTh(NB_TICKS_PAR_TOUR/4); // Le robot tourne de 1/4 de tour sur lui même
  do{ 
  asservissement();
  }while(!robotArrete());
  stopRobot();
  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
  addConsigneTr(NB_TICKS_PAR_M); 
  do{ 
  asservissement();
  }while(!robotArrete());
  stopRobot();
  delay(1000);
  
  addConsigneTh(NB_TICKS_PAR_TOUR/4); // Le robot avance la distance calculer en fonction de (x,y)
  do{ 
  asservissement();
  }while(!robotArrete());
  stopRobot();
  delay(1000);
}