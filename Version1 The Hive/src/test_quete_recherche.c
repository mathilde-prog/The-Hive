#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/commun.h"

/**
 * \file test_quete_recherche.c
 * \brief Fichier TEST - Quête recherche
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \void int main()
 * \brief Programme principal pour tester l'affichage et le bon fonctionnement de la quête recherche
 * \details Avant de commencer la quête, l'utilisateur choisit :
    - Première fois sur la quête
    - Recherche de l'item (pas sur une case urbain)
    - Recherche de l'item (case urbain)
    - Donner l'item (case quête)
    - Donner l'item (pas case quête)
*/
int main(){
  srand(time(NULL));

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

  clrscr();
  printf ("\033[34;01m\n   Menu test quête recherche\033[00m\n");
  printf("   1. Première fois sur la quête\n");
  printf("   2. Recherche de l'item (pas sur une case urbain)\n");
  printf("   3. Recherche de l'item (case urbain)\n");
  printf("   4. Donner l'item (case quête) \n");
  printf("   5. Donner l'item (pas case quête) \n");
  printf("\n   Votre réponse : ");
  saisie:
  scanf("%d", &choix);
  switch(choix){
      case 1:  player.posY = quest_map[5][0];
               player.posX = quest_map[5][1];
               quete.recherche.situation = -1;
               quete.recherche.trouve = -1;
               clrscr();
               sortie = quete_recherche(&player,map,&quete);break;
      case 2:  player.posY = quest_map[5][0];
               player.posX = quest_map[5][1];
               quete.recherche.situation = 0;
               quete.recherche.trouve = 0;
               clrscr();
               sortie = quete_recherche(&player,map,&quete);break;
      case 3:  quete.recherche.situation = 0;
               quete.recherche.trouve = 0;
               do {
                 player.posY = rand()%D;
               } while(player.posY == quest_map[5][0]);
               do {
                 player.posX = rand()%D;
               } while(player.posX == quest_map[5][1]);
                map[player.posY][player.posX].type = ville;
               map[player.posY][player.posX].categ = urbain;
               clrscr();
               sortie = quete_recherche(&player,map,&quete);
               break;
      case 4:  player.posY = quest_map[5][0];
               player.posX = quest_map[5][1];
               quete.recherche.situation = 0;
               add_item_to_inventory(&player,quete.recherche.wanted);
               quete.recherche.trouve = 1;
               clrscr();
               sortie = quete_recherche(&player,map,&quete);
               break;
      case 5 : quete.recherche.situation = 0;
               add_item_to_inventory(&player,quete.recherche.wanted);
               quete.recherche.trouve = 1;
               do {
                 player.posY = rand()%D;
               } while(player.posY == quest_map[5][0]);
               do {
                player.posX = rand()%D;
              } while(player.posX == quest_map[5][1]);
               break;
      default: printf("   Veuillez ressaisir : "); goto saisie; break;
  }


  switch(sortie){
    case 0: printf("\n   Le jeu continue!\n"); break;
    case 1: printf("\n   Fin du jeu\n"); break;
    case -1: printf("\n   Pb dans la quête\n"); break;
    default: break;
  }
  clrscr();
  display_player_characteristics(map,player);
  affichage_quete_search_en_cours(quete,map,player);
  printf ("\033[34;01m   [Menu principal]\033[00m\n");
  printf("    1 - Fouiller la zone\n");
  printf("    2 - Gérer l'inventaire\n");
  printf("    3 - Gérer l'équipement\n");
  printf("    4 - Se déplacer ailleurs\n");
  printf("    5 - Pêcher\n");
  printf("    6 - Regarder la carte (carte nécessaire)\n");
  printf("    7 - Se reposer et guérir\n");
  printf("    8 - Fin du tour\n");
  printf("    9 - Sauvegarder la progression\n");
  printf("   10 - Aide\n");
  printf("\n   Quitter sans sauvegarder : -1\n\n");
  entree_pour_continuer();
  clrscr();

  free(Tab_Items);
}
