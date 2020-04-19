#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/**
 * \file eat_or_drink.c
 * \brief Fonctionnalité : manger ou boire un item de son inventaire
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void gain_energie(perso_t * player, int val_e)
 * \brief Calcule et met à jour les points d'énergie du joueur selon la valeur énergétique de l'item mangé / bu
 * \param perso_t * player
 * \param int val_e
 * \return Rien
*/
void gain_energie(perso_t * player, int val_e){
  int val = val_e;

  if((player->pe + val) > 100){
    val = (100 - player->pe);
  }
  if(val != 0){
    player->pe += val;
    printf("Vous gagnez %d points d'énergie.\n", val);
  }
  else {
    printf("C'était bon mais vous êtiez déjà au max de votre forme!\n");
  }
}

/**
 * \fn void eat_or_drink (perso_t * player, item_t item)
 * \brief Permet au joueur de boire ou manger un item de type \a food et récupérer des points d'énergie ou action (si cela est possible).
 * \details Retire l'item de l'inventaire
 * \param perso_t * player
 * \param item_t item
 * \return Rien
*/
/* eat_or_drink: allows the player to drink or eat an item (if type food) and to recover pe and pv when it's possible */
void eat_or_drink (perso_t * player, item_t item){
  if(item.type == food){
    if(!strcmp(item.name,"fruits")){
      gain_energie(player,10);
    }
    else if(!strcmp(item.name,"fish")){
      gain_energie(player,15);
    }
    else if (!strcmp(item.name,"can_food")){
      gain_energie(player,50);
    }
    else if (!strcmp(item.name,"soda")){
      gain_energie(player,12);
    }
    else if(!strcmp(item.name,"energy_drink")){
      if(player->pa < 5){
        player->pa++;
        printf("Vous gagnez 1 point d'action.\n");
      }
      gain_energie(player,20);
    }
    else if(!strcmp(item.name,"bottle_water")){
      gain_energie(player,10);
    }
    delete_item_in_inventory(player, item);
  }
  else {
    printf("Vous ne pouvez pas manger ou boire ça!\n\n");
  }
}
