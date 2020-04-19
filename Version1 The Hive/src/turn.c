#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file turn.c
 * \brief Fonctions relatives à un tour du jeu
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void next_turn(perso_t * player)
 * \brief Passer au tour suivant
 * \param perso_t * player
 * \return Rien
*/
/* Passer au prochain tour */
void next_turn(perso_t * player){
  printf("On passe au tour suivant!\n");
  printf("Vous récupérez %d points d'action!\n", 5-player->pa);
  player->pa = 5; //Récupère 5 points d'actions
  player->turns--;
  sleep(2);
}

/**
 * \fn void rest_and_heal(perso_t * player)
 * \brief Permet au joueur de se reposer et récupérer des points de vie et points d'énergie (proportionnellement au nombre de points d'action)
 * \param perso_t * player
 * \return Rien
*/
/* rest_and_heal: allows the player to rest and gain pv and pe (proportionate to his number of pa) */
void rest_and_heal(perso_t * player){
  int value_pv = player->pa*5;
  int value_pe = player->pa*5;

  printf("Reposez vous un instant zzZZ\n");
  sleep(1);

  /* PV */
  if((player->pv + value_pv) > 100){
    value_pv = (100 - player->pv);
  }
  player->pv += value_pv;

  /* PE */
  if((player->pe + value_pe) > 100){
    value_pe = (100 - player->pe);
  }
  player->pe += value_pe;

  printf("PV +%d\tPE +%d\n",value_pv,value_pe);
  sleep(2);
  next_turn(player);
}
