#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

int main(){
  srand(time(NULL));
  int nb;

  /* Tab_Items Declaration (= table containing ALL the items available in the game) */
  item_t Tab_Items[20];
  int nb_items_available = 0;

  /* Map Declaration */
  cell_t map[D][D];

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

    printf ("\033[34;01m[LOAD]\033[00m\n");
    if(load(&player, map)){
      printf("Successful loading\n\n");
      do {
        printf("Menu test_load :\n");
        printf("1. Display player characteristics\n");
        printf("2. Display inventory\n");
        printf("3. Display equipment\n");
        printf("4. Display map\n");
        printf("Exit -1\n");
        do {
          printf("N°");
          scanf("%d",&nb);
          if((nb != -1) && (nb < 1 || nb > 4)){
            printf("Incorrect value. Please re-enter\n");
          }
        } while ((nb != -1) && (nb < 1 || nb > 4));

        if(nb != -1){
          switch(nb){
            case 1: display_player_characteristics(map, player); break;
            case 2: display_inventory(player); break;
            case 3: display_equipment_player(player); break;
            case 4: display_TEXT(player.posX,player.posY,map);
                    count(map);
                    printf("\n");
                    break;
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
