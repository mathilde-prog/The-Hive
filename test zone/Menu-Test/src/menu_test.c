//main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

int main(){
  printf ("\033[32;01m\n=============== WELCOME MENU_TEST - THE HIVE ===============\n\033[00m\n");
  int choice, nb;

  /* Tab_Items Declaration (= table containing ALL the items available in the game) */
  item_t Tab_Items[20];
  int nb_items_available = 0;

  /* Map Declaration */
  int map[D][D]={{0}};

  if(creation_tab_item(Tab_Items, &nb_items_available)) {

    printf ("\033[34;01m====== INITIALISATION PLAYER ======\033[00m\n");
    perso_t player;
    init_player(&player);
    printf ("\033[34;01m===================================\n\n\033[00m");

    printf ("\033[34;01m=== DISPLAY PLAYER ===\033[00m\n");
    display_player_characteristics(player);
    printf ("\033[34;01m======================\n\n\033[00m");

    printf ("\033[34;01m=== ITEMS ADDED TO THE INVENTORY (TESTS) ===\033[00m\n");
    /* I'm adding items to the inventory to test functions */
    add_item_to_inventory(&player, Tab_Items[0]);
    add_item_to_inventory(&player, Tab_Items[2]);
    add_item_to_inventory(&player, Tab_Items[4]);
    add_item_to_inventory(&player, Tab_Items[6]);
    add_item_to_inventory(&player, Tab_Items[7]);
    add_item_to_inventory(&player, Tab_Items[8]);
    add_item_to_inventory(&player, Tab_Items[10]);
    add_item_to_inventory(&player, Tab_Items[12]);
    add_item_to_inventory(&player, Tab_Items[14]);
    add_item_to_inventory(&player, Tab_Items[17]);
    printf ("\033[34;01m===========================================\n\033[00m");

    /* I also equip my player a little bit to test some functions. */
    player.head = &player.inventory[4];
    player.right_hand = &player.inventory[0];
    player.left_hand = &player.inventory[1];

    /* MENU - TEST */
    do {
      printf ("\033[34;01m\n=============== MENU - TEST ===============\n\033[00m\n");

      printf("\033[34;01mMAP V1\033[00m\n");
      printf("1. Map generation\n\n");

      printf("\033[34;01mGENERATION ITEMS\033[00m\n");
      printf("2. Tests - Generation items\n\n");

      printf ("\033[34;01mINVENTORY\033[00m\n");
      printf("3. Display inventory\n");
      printf("4. Get rid of an item\n\n");

      printf ("\033[34;01mEQUIPMENT\033[00m\n");
      printf("5. Display equipment\n");
      printf("6. Equip player\n");
      printf("7. Remove equipment player\n\n");

      printf ("\033[34;01mEXIT: -1\n\033[00m\n");
      printf ("\033[34;01m===========================================\n\033[00m\n");

      /* The user makes his choice */
      do {
        printf("N°");
        scanf("%d",&choice);
        if(choice != -1 && (choice < 1 || choice > 7)){
          printf("Entry error. Value must be between 1 et 7\n");
        }
      } while(choice != -1 && (choice < 1 || choice > 7));

      printf("\n");

      switch(choice){
        case 1: map_generation(map); break;
        case 2: items_generer(Tab_Items, nb_items_available, militaire); break;
        case 3: display_inventory(player); break;
        case 4: do {
              		display_inventory(player);
              		printf("Which item do you want to delete ? (-1 to cancel) N°");
              		scanf("%d", &nb);
              		if((nb != -1) && (nb < 0 || nb > (player.nb_items_inventory - 1))){
              			printf("Wrong number... This item isn't in your inventory!\n");
              		}
              	} while((nb != -1) && (nb < 0 || nb > (player.nb_items_inventory - 1)));
                if(nb != -1){
                    delete_item_in_inventory(&player,player.inventory[nb]);
                }
                break;
          case 5: display_equipment_player(player); break;
          case 6: equip_player(&player); break;
          case 7: remove_equipment_player(&player); break;
          case -1: printf("Thanks for playing, see you next time!\n"); break;
          default: printf("Error\n"); break;
      }

    } while(choice != -1);

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
