#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/commun.h"

/**
 * \file test_quete_montagne.c
 * \brief Fichier TEST - Quête montagne
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \brief Programme principal pour tester l'affichage et le bon fonctionnement de la quête montagne
 * \details Avant de commencer la quête, l'utilisateur choisit s'il a une corde et/ou un bâton de marche dans son inventaire ou aucun des deux.
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

  item_t * rope = creer_item("corde",misc,0,0,0,0,0,0,0,0,0,40,50);
  item_t * walking_stick = creer_item("baton de marche",misc,0,0,0,0,0,0,0,0,70,30,0);

  map_init(map,quest_map);
  init_player(&player,map);
  init_quete(&quete,quest_map,Tab_Items,nb_items_available);

  printf ("\033[34;01m\n   Menu test quête montagne\033[00m\n");
  printf("   1. Corde + Bâton de marche\n");
  printf("   2. Corde\n");
  printf("   3. Bâton de marche\n");
  printf("   4. Rien\n");

  printf("\n   Votre réponse : ");
  saisie:
  scanf("%d", &choix);
  switch(choix){
      case 1: add_item_to_inventory(&player,*rope);
              add_item_to_inventory(&player,*walking_stick);
              break;
      case 2: add_item_to_inventory(&player,*rope); break;
      case 3: add_item_to_inventory(&player,*walking_stick); break;
      case 4: printf("\n   Aucun item ajouté\n"); break;
      default: printf("   Veuillez ressaisir : "); goto saisie; break;
  }

  clrscr();
  sortie = quete_montagne(&player,&quete);
  clrscr();
  switch(sortie){
    case 0: printf("\n   Le jeu continue!\n"); break;
    case 1: printf("\n   Fin du jeu\n"); break;
    case -1: printf("\n   Pb dans la quête\n"); break;
    default: break;
  }

  free(rope);
  free(walking_stick);
  free(Tab_Items);
}
