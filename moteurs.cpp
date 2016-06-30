
#include "moteurs.h"
#include "Arduino.h"

#define IN1_U1   28
#define IN2_U1   26
#define IN1_U2   24
#define IN2_U2   22
#define MD        2
#define MG        3


void initMoteurs()
{
  // On initialise les moteurs
  
  pinMode(IN1_U1,OUTPUT);
  pinMode(IN2_U1,OUTPUT);
  pinMode(IN1_U2,OUTPUT);
  pinMode(IN2_U2,OUTPUT);
  pinMode(MD,OUTPUT);
  pinMode(MG,OUTPUT);
  
  // on initialise leur vitesse Ã  0
  setMoteurDroit(0);
  setMoteurGauche(0);
}

void setMoteurDroit(int speedM)
{  
    int absSpeed;
  //determine le sens de rotation, et la vitesse absolue.
  if(speedM < 0) {
    absSpeed = -speedM;
    digitalWrite(IN1_U1,HIGH);
    digitalWrite(IN2_U1,LOW);
  } 
  
  else {
    absSpeed = speedM;
    digitalWrite(IN1_U1,LOW);
    digitalWrite(IN2_U1,HIGH);
    
  }   
 
  int commande;
  //il faut 15 pour que le moteur commence Ã  bouger...
  if(absSpeed == 0) commande = 0;      //arret
  else commande = absSpeed+15;
  if(commande > 255) commande = 255; //saturation
  
  analogWrite(MD, commande); //porte NON  l'entree.
  
  
}


void setMoteurGauche(int speedM)
{
 int absSpeed;
  //determine le sens de rotation, et la vitesse absolue.
  if(speedM < 0) {
    absSpeed = -speedM;
    digitalWrite(IN1_U2,HIGH);
    digitalWrite(IN2_U2,LOW);
  } 
  
  else {
    absSpeed = speedM;
    digitalWrite(IN1_U2,LOW);
    digitalWrite(IN2_U2,HIGH);
  }   
 
  int commande;
  //il faut 15 pour que le moteur commence Ã  daigner bouger...
  if(absSpeed == 0) commande = 0;      //arret
  else commande = absSpeed+15;
  if(commande > 255) commande = 255; //saturation
  
  analogWrite(MG, commande); //porte NON  l'entree.
}


