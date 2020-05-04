#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));
  clrscr();

  int choix;
  perso_t player;
  quete_t quete;
  cell_t map[D][D];
  int quest_map[6][2];
  int sortie = 0;
  item_t * rope = creer_item("rope",misc,0,0,0,0,0,0,0,0,0,40,50);
  item_t * walking_stick = creer_item("walking stick",misc,0,0,0,0,0,0,0,0,70,30,0);

  init_player(&player);
  map_init(map,quest_map,player);
  init_quete(&quete,quest_map);

  printf ("\033[34;01m\n   Menu test quête montagne\033[00m\n");
  printf("   1. Rope + Walking stick\n");
  printf("   2. Rope\n");
  printf("   3. Walking stick\n");
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
}
