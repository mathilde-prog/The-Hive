#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/commun.h"

/**
 * \file test_item_in_inventory.c
 * \brief Fichier TEST - Fonction item_in_inventory
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \brief Programme principal pour tester si un item est présent dans l'inventaire du joueur
 * \details Objectif : Tester la fonction #item_in_inventory
*/
int main(){
  srand(time(NULL));

  cell_t map[D][D];
  int quest_map[6][2];
  perso_t player;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;

  creation_tab_item(Tab_Items, &nb_items_available);

  map_init(map,quest_map);
  init_player(&player,map);

  check_the_map(player,map);

  item_t * fishing_rod = creer_item("canne a peche",misc,0,0,0,0,0,0,0,0,0,0,0);
  item_t * map_item = creer_item("carte",misc,0,0,0,0,0,0,0,0,0,0,0);
  item_t * medical_kit = creer_item("kit medical",misc,0,0,0,0,0,0,0,0,0,0,0);

  printf("TEST carte : \n");
  (item_in_inventory(player,"carte") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*map_item);
  (item_in_inventory(player,"carte") != -1) ? printf("Test OK\n\n") : printf("Test KO\n\n");

  printf("TEST canne à pêche : \n");
  (item_in_inventory(player,"canne a peche") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*fishing_rod);
  item_in_inventory(player,"canne a peche") != -1 ? printf("Test OK\n\n") : printf("Test KO\n\n");

  printf("TEST kit médical : \n");
  (item_in_inventory(player,"kit medical") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*medical_kit);
  (item_in_inventory(player,"kit medical") != -1) ? printf("Test OK\n") : printf("Test KO\n");

  return EXIT_SUCCESS;
}
