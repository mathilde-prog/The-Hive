#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file test_quete_frontiere.c
 * \brief Fichier TEST - Quête frontière
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

int main(){
  srand(time(NULL));
  clrscr();

  int choix;
  perso_t player;
  quete_t quete;
  cell_t map[D][D];
  int quest_map[6][2];
  int sortie = 0;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  creation_tab_item(Tab_Items, &nb_items_available);

  map_init(map,quest_map);
  init_player(&player,map);
  init_quete(&quete,quest_map,Tab_Items,nb_items_available);

  printf ("\033[34;01m\n   Menu test quête frontière\033[00m\n");
  printf("   1. Le joueur a aidé l'homme blessé (quête soin)\n");
  printf("   2. Le joueur a voulu aidé l'homme blessé (quête soin) mais sans succès\n");
  printf("   3. Le joueur ne connait pas de soldat\n");
  printf("\n   Votre réponse : ");
  saisie:
  scanf("%d", &choix);
  switch(choix){
      case 1: quete.soin = 2; break;
      case 2: quete.soin = 3; break;
      case 3: quete.soin = -1; break;
      default: printf("   Veuillez ressaisir : "); goto saisie; break;
  }

  clrscr();
  sortie = quete_frontiere(&player,&quete);
  switch(sortie){
    case 0: printf("\n   Le jeu continue!\n"); break;
    case 1: printf("\n   Fin du jeu\n"); break;
    case -1: printf("\n   Pb dans la quête\n"); break;
    default: break;
  }

  free(Tab_Items);
}
