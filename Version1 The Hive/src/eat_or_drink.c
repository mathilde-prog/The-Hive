#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/structure.h"

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
    printf("   Vous gagnez %d points d'énergie.\n", val);
  }
  else {
    printf("\n   Vous êtes déjà au max de votre forme. Vous ne gagnez aucun point d'énergie.\n");
  }
}

/**
 * \fn void eat_or_drink (perso_t * player, item_t item)
 * \brief Permet au joueur de boire ou manger un item de type \a food et récupérer des points d'énergie ou action (si cela est possible).
 * \details Retire l'item mangé / bu de l'inventaire
 * \param perso_t * player
 * \param item_t item
 * \return Rien
*/
void eat_or_drink (perso_t * player, item_t item){
  printf("\n");
  if(item.type == food){
    if(!strcmp(item.name,"fruits")){
      printf("   Ces fruits sont délicieux! ");
      gain_energie(player,10);
    }
    else if(!strcmp(item.name,"poisson")){
      printf("   Attention aux arrêtes... ");
      gain_energie(player,15);
    }
    else if (!strcmp(item.name,"boite de conserve")){
      printf("   Qui aurait pensé qu'une boîte de conserve ferait un si bon repas! ");
      gain_energie(player,50);
    }
    else if (!strcmp(item.name,"soda")){
      printf("   Ce soda est très sucré. ");
      gain_energie(player,12);
    }
    else if(!strcmp(item.name,"boisson energie+")){
      printf("   Une boisson - énergisante - ! ");
      if(player->pa < 5){
        player->pa++;
        printf("   Vous gagnez 1 point d'action. ");
      }
      gain_energie(player,20);
    }
    else if(!strcmp(item.name,"bouteille eau")){
      printf("   C'est rafraichissant! ");
      gain_energie(player,10);
    }
    delete_item_in_inventory(player, item);
  }
  else {
    printf("   Vous ne pouvez pas manger ou boire cet item, ");
    switch(item.type){
      case weapon: printf("c'est une arme.\n"); break;
      case armor: printf("c'est une armure.\n"); break;
      case misc: printf("c'est un objet.\n"); break;
      default: break;
    }
  }
  printf("\n");
}
