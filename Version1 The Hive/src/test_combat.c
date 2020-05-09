#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file test_combat.c
 * \brief Fichier TEST - Combat
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

int main(){
  srand(time(NULL));

  perso_t player;
  npc_t * enemy;
  stat_t * field;
  cell_t map[D][D];
  int quest_map[6][2];
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available;
  int choix, num_arme, num_arme1, num_arme2;

  map_init(map,quest_map);
  init_player(&player,map);
  creation_tab_item(Tab_Items, &nb_items_available);

  field=init_field();
  enemy=init_npc(Tab_Items);

  clrscr();
  printf ("\033[34;01m\n   Menu test combat\033[00m\n");
  printf("\n   [Le joueur a une armure]\n");
  printf("      1. Aucune arme\n");
  printf("      2. 1 arme (main gauche)\n");
  printf("      3. 1 arme (main droite)\n");
  printf("      4. 2 armes\n");
  printf("\n   [Le joueur n'a pas d'armure]\n");
  printf("      5. Aucune arme\n");
  printf("      6. 1 arme (main gauche)\n");
  printf("      7. 1 arme (main droite)\n");
  printf("      8. 2 armes\n");
  printf("\n   Votre réponse : ");
  do {
    scanf("%d", &choix);
    if(choix < 1 || choix > 8){
      printf("   Valeur incorrecte. Veuillez ressaisir : ");
    }
  }while (choix < 1 || choix > 8);

  if(choix >= 1 && choix <= 4){
    player.body = &Tab_Items[6]; // bulletproof vest
  }

  if(choix == 2 || choix == 3 || choix == 6 || choix == 7){
    clrscr();
    printf("\n   Vous avez choisi de porter 1 arme.\n   Avec quelle arme souhaitez-vous combattre ?\n");
    printf("   0. pistolet\n   1. grand bâton\n   2. fusil\n   3. couteau\n   4. arc et flèches\n   5. batte de baseball\n");
    printf("\n   Votre réponse : ");
      do {
        scanf("%d",&num_arme);
        if(num_arme < 0 || num_arme > 5){
          printf("   Valeur incorrecte. Veuillez ressaisir : ");
        }
      } while (num_arme < 0 || num_arme > 5);

      if(choix == 2 || choix == 6){
        player.left_hand = &Tab_Items[num_arme];
      }
      else if(choix == 3 || choix == 7){
        player.right_hand = &Tab_Items[num_arme];
      }
  }
  else if (choix == 4 || choix == 8){
    clrscr();
    printf("\n   Vous avez choisi de porter 1 arme.\n   Avec quelles armes souhaitez-vous combattre ?\n");
    printf("   0. pistolet\n   1. grand bâton\n   2. fusil\n   3. couteau\n   4. arc et flèches\n   5. batte de baseball\n");

    printf("\n   Votre réponse pour Arme 1 (main gauche): ");
    do {
      scanf("%d",&num_arme1);
      if(num_arme1 < 0 || num_arme1 > 5){
        printf("   Valeur incorrecte. Veuillez ressaisir : ");
      }
    } while (num_arme1 < 0 || num_arme1 > 5);

    player.left_hand = &Tab_Items[num_arme1];

    printf("\n   Votre réponse pour Arme 2 (main droite): ");
    do {
      scanf("%d",&num_arme2);
      if(num_arme2 < 0 || num_arme2 > 5){
        printf("   Valeur incorrecte. Veuillez ressaisir : ");
      }
    } while (num_arme2 < 0 || num_arme2 > 5);
    player.right_hand = &Tab_Items[num_arme2];
  }

  clrscr();
  combat(&player,enemy,field,map,Tab_Items,nb_items_available);
  clrscr();
  free(enemy);
  free(field);
  free(Tab_Items);
}
