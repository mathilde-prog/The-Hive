#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/commun.h"

/**
 * \file turn.c
 * \brief Fonctions relatives à un tour du jeu
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void next_turn(perso_t * player)
 * \brief Calcule le nombre de points d’action récupérés à partir de la valeur des points d'énergie du joueur puis passe au tour suivant.
 * \param player Pointeur sur un objet de type perso_t correspondant au joueur
 * \return Rien
*/
void next_turn(perso_t * player){
  int base_value, prev_value;
  if(player->pa<5){
    printf("\n   On passe au tour suivant!\n");
    prev_value=player->pa;
    if((player->pe%20)>=10){
      base_value=(player->pe/20)+1;
      player->pa+=base_value+1;
      if((player->pa)>5){
        player->pa=5;
        printf("   Vous récupérez %d points d'action!\n", 5 - prev_value);
      }else{
        printf("   Vous récupérez %d points d'action!\n", player->pa - prev_value);
      }
    }else{
      base_value=(player->pe/20)+1;
      player->pa+=base_value;
      if((player->pa)>5){
        player->pa=5;
        printf("   Vous récupérez %d points d'action!\n", 5 - prev_value);
      }else{
        printf("   Vous récupérez %d points d'action!\n", player->pa - prev_value);
      }
    }
  }else{
    printf("\n   On passe au tour suivant!\n");
  }
  player->pe-=15; //Perd 15 points d'énergie
  if(player->pe < 0){
    player->pe=0;
  }
  player->turns--;
  sleep(2);
}

/**
 * \fn void rest_and_heal(perso_t * player)
 * \brief Permet au joueur de se reposer et récupérer des points de vie et points d'énergie (proportionnellement au nombre de points d'action)
 * \param player Pointeur sur un objet de type perso_t correspondant au joueur
 * \return Rien
*/
void rest_and_heal(perso_t * player){
  int value_pv = player->pa*5;
  int value_pe = player->pa*5;

  printf("\n   Reposez vous un instant zzZZ\n");
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

  printf("   PV +%d\tPE +%d\n",value_pv,value_pe);
  sleep(2);
  next_turn(player);
}
