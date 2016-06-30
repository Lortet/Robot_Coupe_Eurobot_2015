#ifndef __MOTEURS_H__
#define __MOTEURS_H__

#include "Arduino.h"



//initialisation des commandes pour les 2 moteurs
void initMoteurs();

// Fonction qui commande le moteur droit
void setMoteurDroit(int speedM);

//Fonction qui commande le moteur droit
void setMoteurGauche(int speedM);

#endif

