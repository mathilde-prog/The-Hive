#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

void details(cell_t map[D][D]){
  int l, c;

  printf("TYPE : \n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      printf("%2d ", map[l][c].type);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("CATEG : \n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      printf("%2d ", map[l][c].categ);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("ENCOUNTER : \n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      printf("%2d ", map[l][c].encounter);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("QUEST ID : \n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      printf("%2d ", map[l][c].quest_id);
    }
    printf("\n");
  }
  printf("\n\n");

  printf("SCAVENGED : \n");
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      printf("%2d ", map[l][c].scavenged);
    }
    printf("\n");
  }
  printf("\n\n");
}

void info_quetes(int quest_map[6][2], quete_t quete){
  clrscr();
  int l,c;

  printf("\nAFFICHAGE MATRICE QUEST_MAP : \n");
  for(l = 0; l < 6; l++){
    for(c = 0; c < 2; c++){
      printf("%2d ",quest_map[l][c]);
    }
      printf("\n");
  }

  printf("\nAFFICHAGE STRUCTURE QUETE : \n");
  printf("soin : %d\n", quete.soin);
  printf("recherche : %d %d %d\n", quete.recherche.situation, quete.recherche.butX, quete.recherche.butY);
  printf("bunker : %d\n", quete.bunker);
  printf("montagne : %d\n", quete.montagne);
  printf("frontiere : %d\n", quete.frontiere);
  printf("bandits : %d\n\n", quete.bandits);
}

int main(){
  srand(time(NULL));
  int nb;

  /* Tab_Items Declaration (= table containing ALL the items available in the game) */
  item_t Tab_Items[20];
  int nb_items_available = 0;

  /* Map Declaration */
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;

  if(creation_tab_item(Tab_Items, &nb_items_available)) {

    perso_t player;
    player.left_hand = NULL;
    player.right_hand = NULL;
    player.body = NULL;
    player.head = NULL;

    /* TESTS UNITAIRES */
    /*
    printf ("\033[34;01m========== LOAD PERSO ==========\033[00m\n");
    load_info_player(&player);
    display_player_characteristics(player);
    printf ("\033[34;01m================================\033[00m\n\n");

    printf ("\033[34;01m=== LOAD & DISPLAY INVENTORY ===\033[00m\n");
    load_inventory(&player);
    display_inventory(player);
    printf ("\033[34;01m===========================================\n\033[00m");

    printf ("\033[34;01m=== LOAD EQUIPMENT ===\033[00m\n");
    load_equipment(&player);
    display_equipment_player(player);
    printf ("\033[34;01m===========================================\n\033[00m");
    */

    printf ("\033[34;01m[CHARGER]\033[00m\n");
    if(load(&player,map,quest_map,&quete)){
      printf("Chargement réussi\n\n");
      do {
        printf("Menu test_load :\n");
        printf("1. Afficher les caractéristiques du joueur\n");
        printf("2. Afficher l'inventaire\n");
        printf("3. Afficher l'équipement\n");
        printf("4. Afficher la carte\n");
        printf("5. Détails carte\n");
        printf("6. Détails quêtes\n");
        printf("Quitter -1\n");
        do {
          printf("N°");
          scanf("%d",&nb);
          if((nb != -1) && (nb < 1 || nb > 6)){
            printf("Valeur incorrecte. Veuillez ressaisir\n");
          }
        } while ((nb != -1) && (nb < 1 || nb > 6));

        if(nb != -1){
          switch(nb){
            case 1: display_player_characteristics(map, player); break;
            case 2: display_inventory(player); break;
            case 3: display_equipment_player(player); break;
            case 4: display_TEXT(player.posX,player.posY,map);
                    count(map);
                    printf("\n");
                    break;
            case 5: details(map); break;
            case 6: info_quetes(quest_map,quete);
            default: break;
          }
        }
      } while (nb != -1);
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
  }

  return EXIT_SUCCESS;
}
