#ifndef __ASSERVISSEMENT_H__
#define __ASSERVISSEMENT_H__

// Plus il est grand => Plus la vitesse  est elever et plus le robot risque de deriver 
#define SATURATION_COMMANDE 70


#define KpTr 0.04 // Action Proportionnelle
#define KiTr 0 // Action Integrale
#define KdTr 0 // Action Derive

#define KpTh 0.15
#define KiTh 0
#define KdTh 0

//diametre roue = 7.5 cm. perimetre de le roue = 22 cm
//24000 ticks/tour
//1 tick = 0.00916mm                                                            
// 1000/219.84 = 4.51 tour pour faire 1 metre
// 4.51 * 24 000 = nombre de tick pour 1 metre       
// ATTENTION VALEUR A DOUBLER
#define NB_TICKS_PAR_M 207400 

// 219.84 tick pour parcourir 1 mm  

//NB_TICK_PAR_TOUR est fonction des dimensions de la roue et de la longueur de l'entre-axe         25.8
//distance entre les roues : 26 cm, diamÃ¨tre du cercle = 2*Pi*13 = 81.68 cm                       77.91
// 816.8 mm * 1 / 235.8.84 = 3.464 tour de roue par Tour de robot                                  3.543941048 tour
// donc 3.715 * 24 000 = 89160 tick                                                                85054 tick
#define NB_TICKS_PAR_TOUR 85054

// Initialise l'asservissement
void initAsservisssement();

// Assevisement en rotation et translation

void asservissement();


// permet de modifier l'asservissement en tour (NB_T...PAR_TOUR) ou en cm (NB_T...PAR_M)
void addConsigneTr(long consigneTr);
void addConsigneTh(long consigneTh);

// return true si le robot est Ã  l'arret
bool robotArrete();

// Stop le robot en le bloquant Ã  la position actuelle
void stopRobot();

#endif