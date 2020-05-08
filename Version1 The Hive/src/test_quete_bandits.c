#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file test_quete_bandits.c
 * \brief Fichier TEST - Quête bandits
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

int main(){
  srand(time(NULL));

  int choix;
  int arme;
  perso_t player;
  quete_t quete;
  cell_t map[D][D];
  int quest_map[6][2];
  int sortie = 0;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  creation_tab_item(Tab_Items, &nb_items_available);

  item_t * pistol = creer_item("pistolet",weapon,5,25,15,30,85,60,0,1,0,20,60);
  item_t * shotgun = creer_item("fusil",weapon,10,40,30,40,85,60,0,1,0,15,50);
  item_t * bulletproof_vest = creer_item("gilet pare-balles",armor,0,0,0,0,0,0,0.7,2,0,10,70);
  item_t * helmet = creer_item("casque",armor,0,0,0,0,0,0,0.6,3,0,0,0);
  item_t * knife = creer_item("couteau",weapon,20,0,0,75,0,0,0,1,0,70,70);

  map_init(map,quest_map);
  init_player(&player,map);
  init_quete(&quete,quest_map,Tab_Items,nb_items_available);

  add_item_to_inventory(&player,*pistol);
  add_item_to_inventory(&player,*shotgun);
  add_item_to_inventory(&player,*knife);
  add_item_to_inventory(&player,*bulletproof_vest);
  add_item_to_inventory(&player,*helmet);

  clrscr();
  printf ("\033[34;01m\n   Menu test quête bandits\033[00m\n");
  printf("   0. Aucun équipement\n");
  printf("   1. Un équipement\n");
  printf("   2. Deux équipements\n");
  printf("   3. Trois équipements\n");
  printf("   4. Quatres équipements\n");
  printf("\n   Votre réponse : ");
  saisie:
  scanf("%d", &choix);
  switch(choix){
      case 0: break;
      case 1: clrscr();
              printf("\n   Souhaitez-vous tester avec fusil (1) ou pistolet (2) ? \n");
              printf("   Votre choix : ");
              do {
                scanf("%d",&arme);
                if(arme < 1 || arme > 2){
                  printf("   Valeur incorrecte. Veuillez ressaisir : ");
                }
              } while(arme < 1 || arme > 2);
              player.right_hand = ((arme == 1) ? &player.inventory[1] : &player.inventory[0]);
              break;
      case 2: player.right_hand = &player.inventory[0]; // pistol
              player.left_hand = &player.inventory[1];  // shotgun
              break;
      case 3: player.right_hand = &player.inventory[2];  //knife
              player.head = &player.inventory[4];       // helmet
              player.body = &player.inventory[3];       // bulletproof_vest
              break;
      case 4: player.right_hand = &player.inventory[0]; // pistol
              player.left_hand = &player.inventory[1];  // shotgun
              player.head = &player.inventory[4];       // helmet
              player.body = &player.inventory[3];       // bulletproof_vest
              break;
      default: printf("   Veuillez ressaisir : "); goto saisie; break;
  }


  clrscr();
  sortie = quete_bandits(&player,&quete,Tab_Items,nb_items_available,map);
  switch(sortie){
    case 0: printf("\n   Le jeu continue!\n"); break;
    case 1: printf("\n   Fin du jeu\n"); break;
    case -1: printf("\n   Pb dans la quête\n"); break;
    default: break;
  }

  free(pistol);
  free(shotgun);
  free(bulletproof_vest);
  free(helmet);
  free(knife);
}
