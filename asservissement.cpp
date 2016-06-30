#include "codeur.h"
#include "moteurs.h"
#include "asservissement.h"
#include "odometrie.h"


//indique l'etat du robot: A L'arret.
static volatile bool aLarret;
//consigne en translation (en demi-ticks).
static volatile long __consigneTr;
//consigne en rotation.
static volatile long __consigneTh;

void initAsservisssement()
{
  aLarret = true;
  __consigneTh = 0;
  __consigneTr = 0;
}

void asservissement()
{
  long codeurD;
  long codeurG;

  getPosition(codeurG, codeurD); // On rÃ©cupÃ¨re les informations des codeurs

 Serial.print("Postition X : ");
 Serial.println(codeurD);
 Serial.print("Postition Y : ");
 Serial.println(codeurG);

  const long mConsigneTr = __consigneTr;
  const long mConsigneTh = __consigneTh;


  //ecart en translation
  float erreurTr = mConsigneTr - (codeurG + codeurD);
  float SerreursTr = SerreursTr + erreurTr;
  float erreur_precedenteTr = erreurTr;
  float variation_erreurTr = erreurTr - erreur_precedenteTr;


  //commande en translation
  float commandeTr = KpTr * erreurTr + KiTr * SerreursTr + KdTr * variation_erreurTr ;
  erreur_precedenteTr = erreurTr;

  //saturation en commande translation
  if (commandeTr > SATURATION_COMMANDE)commandeTr = SATURATION_COMMANDE;

  //ecart en angle
  float erreurTh = mConsigneTh - (codeurG - codeurD);

  float SerreursTh = SerreursTh + erreurTh;
  float erreur_precedenteTh = erreurTh;
  float variation_erreurTh = erreurTh - erreur_precedenteTh;

  //commande en rotation
  float commandeTh = KpTh * erreurTh + KiTh * SerreursTh + KdTh * variation_erreurTh ;
  erreur_precedenteTh = erreurTh;

  //saturation en de la commande en rotation
  if (commandeTh > SATURATION_COMMANDE)commandeTh = SATURATION_COMMANDE;

  //commande moteur.
  int commandeD = commandeTr - commandeTh;
  int commandeG = commandeTr + commandeTh;
//la gestion des saturations de commandes est dans le driver du moteur.

//arret a destination (evite les vibrations).
  if (abs(commandeD) < 10) commandeD = 0;
  if (abs(commandeG) < 10) commandeG = 0;
  aLarret = (commandeD == 0 && commandeG == 0);
  
  setMoteurDroit(commandeD);
  setMoteurGauche(commandeG);

  
}



// Test de l'arret ou non
bool robotArrete()
{
  return aLarret;
}

// permet de modifier l'asservissement en tour (NB_T...PAR_TOUR) ou en cm (NB_T...PAR_M)
void addConsigneTr(long consigneTr)
{
  __consigneTr += consigneTr;
}

void addConsigneTh(long consigneTh)
{
  __consigneTh += consigneTh;
}

void stopRobot()
{
  long codeurD;
  long codeurG;
  getPosition(codeurG, codeurD);
  __consigneTr = codeurG + codeurD;
  __consigneTh = codeurG - codeurD;
}
