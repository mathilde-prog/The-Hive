// test_item.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/commun.h"

#define NB_SIMULATIONS 10

/**
 * \file test_item.c
 * \brief Fichier TEST - Génération aléatoire d'items sur différentes catégories d'hexagone (10 simulations)
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \void void simulation_suivante()
 * \brief Fonction mineure pour passer à la simulation suivante
*/
void simulation_suivante(){
  int rep;

  do {
    printf("Passer à la simulation suivante (1) : ");
    scanf("%d", &rep);
  } while (rep != 1);
}

/**
 * \void int main()
 * \brief Programme principal pour tester la génération d'items sur plusieurs hexagones aléatoires
 * \details Objectif : Tester la fonction #scavenge
*/
int main(){
  srand(time(NULL));

  /* DECLARATIONS */
  int i, nb_items_available = 0;
  perso_t player;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;

  clrscr();

  // Creation des items
  if(creation_tab_item(Tab_Items, &nb_items_available)){
    map_init(map,quest_map);
    init_player(&player,map);
    init_quete(&quete,quest_map,Tab_Items,nb_items_available);

    // SIMULATIONS
    for(i = 0; i < NB_SIMULATIONS; i++){
      player.posX = rand()%D;
      player.posY = rand()%D;

      printf("=== Simulation n°%d === \n", i+1);
      display_player_characteristics(map,player);
      scavenge(map, &player, Tab_Items, nb_items_available,quete);
      printf("\n");
      display_inventory(player);
      printf("\n");
      simulation_suivante();
      clrscr();
    }
  }

  /* Free memory */
  player.left_hand = NULL;
  player.right_hand = NULL;
  player.body = NULL;
  player.head = NULL;

  free(player.left_hand);
  free(player.right_hand);
  free(player.body);
  free(player.head);

  free(Tab_Items);

  printf(">>> Fin du test\n");
  return EXIT_SUCCESS;
}
