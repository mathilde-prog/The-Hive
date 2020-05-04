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

  init_player(&player);
  map_init(map,quest_map,player);
  init_quete(&quete,quest_map);

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

}
