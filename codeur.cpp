
#include "codeur.h"
#include "Arduino.h"

#define OE   43
#define SEL1 49
#define SEL2 47
#define RST  45
#define XY   41

void initCodeur()
{
  // Data
  pinMode(37,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
  pinMode(33,INPUT_PULLUP);
  pinMode(31,INPUT_PULLUP);
  pinMode(29,INPUT_PULLUP);
  pinMode(27,INPUT_PULLUP);
  pinMode(25,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
 
 // SEL1 et SEL2 en sortie
  pinMode(SEL1,OUTPUT);
  pinMode(SEL2,OUTPUT);
 
 // Output Enable en sortie (OE)
  pinMode(OE,OUTPUT);
  
  //XY, choix du codeur
  pinMode(XY,OUTPUT);
  
 // RST en sortie
  pinMode(RST,OUTPUT);
  
 // Reset des compteurs
  digitalWrite(RST,HIGH);
  delay(1); // au moin 10 ns requis
  digitalWrite(RST,LOW);
  
  // pas de lecture (OE)
  digitalWrite(OE,LOW);
  
  
}
  
unsigned char lectureOctet()
{
 unsigned char result = 0;
 
 if (digitalRead(37)== HIGH) result |= 1;
 if (digitalRead(35)== HIGH) result |= 2;
 if (digitalRead(33)== HIGH) result |= 4;
 if (digitalRead(31)== HIGH) result |= 8;
 if (digitalRead(29)== HIGH) result |= 16;
 if (digitalRead(27)== HIGH) result |= 32;
 if (digitalRead(25)== HIGH) result |= 64;
 if (digitalRead(23)== HIGH) result |= 128;
 
 return result;

}

unsigned int lectureRegistre()
{
  unsigned int result;
  
  digitalWrite(OE,HIGH);
  
  digitalWrite(SEL1,HIGH);
  digitalWrite(SEL2,LOW);
  result = lectureOctet() << 24;
  
  digitalWrite(SEL1,LOW);
  result |= lectureOctet() << 16;
  
  digitalWrite(SEL1,HIGH);
  digitalWrite(SEL2,HIGH);
  result |= lectureOctet() << 8;
   
  digitalWrite(SEL1,LOW);
  result |= lectureOctet();
  
  digitalWrite(OE,LOW);
  return result;
}

void getPosition(long & valGauche,long & valDroite)
{
  digitalWrite(XY, LOW);
  valGauche = -lectureRegistre();
  
  digitalWrite(XY, HIGH);
  valDroite = lectureRegistre();
}