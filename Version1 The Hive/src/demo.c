#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file combat.c
 * \brief Démo
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void demo_afficher_items(perso_t * player, item_t * Tab_Items, int nb_items_available)
 * \brief Permettre au joueur de choisir les items qu'il souhaite ajouter à son inventaire (cheat)
 * \details Cette fonction est appelée UNIQUEMENT en mode demo 
 * \param perso_t * player
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Rien
*/
void demo_afficher_items(perso_t * player, item_t * Tab_Items, int nb_items_available){
  int i, num;
  clrscr();

  items:
  if(player->nb_items_inventory > 0){
    display_inventory(*player);
  }
  else {
    printf("\n   Vote inventaire est vide.\n");
  }

  // Affichage de tous les items disponibles
  printf("\n   Items disponibles : \n");
  for(i = 0; i < nb_items_available; i++){
      printf("   %2d - %s\n",i+1,Tab_Items[i].name);
  }

  // Choix item(s)
  printf("\n   Quel(s) item(s) souhaitez-vous ajouter (-1 pour quitter) ? ");
  do {
    scanf("%d", &num);
    if((num != -1) && (num < 1 || num > nb_items_available)){
      printf("   Valeur incorrecte. Veuillez ressaisir : ");
    }
    else if(num != -1) {
      add_item_to_inventory(player,Tab_Items[num-1]);
      sleep(1);
      clrscr();
      goto items;
    }
  } while (num != -1);

  clrscr();
}
