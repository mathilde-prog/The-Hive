//main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

int main(){
  int choice, nb;

  printf ("\033[32;01m\n=============== WELCOME - THE HIVE ===============\n\033[00m\n");

  item_t Tab_Items[20]; /* Tab_Items: will contain all the items available in the game */
  int nb_items_available = 0;

  if(creation_tab_item(Tab_Items, &nb_items_available)) {
    perso_t player;
    player.nb_items_inventory = 0; /* The player starts the game with an empty inventory. */

    player.left_hand = NULL;
    player.right_hand = NULL;
    player.body = NULL;
    player.head = NULL;

    /* I'm adding items to the inventory to test the functions. */
    printf ("\033[34;01m\n=== ITEMS ADDED TO THE INVENTORY (TESTS) ===\033[00m\n");
    add_item_to_inventory(&player, Tab_Items[0]);
    add_item_to_inventory(&player, Tab_Items[7]);
    add_item_to_inventory(&player, Tab_Items[11]);
    add_item_to_inventory(&player, Tab_Items[1]);
    add_item_to_inventory(&player, Tab_Items[3]);
    add_item_to_inventory(&player, Tab_Items[2]);
    add_item_to_inventory(&player, Tab_Items[4]);
    add_item_to_inventory(&player, Tab_Items[3]);
    add_item_to_inventory(&player, Tab_Items[8]);
    add_item_to_inventory(&player, Tab_Items[3]);
    printf ("\033[34;01m===========================================\n\033[00m\n");

    /* I also equip my player a little bit to test some functions. */
    player.head = &player.inventory[1];
    player.right_hand = &player.inventory[0];
    player.left_hand = &player.inventory[3];

    /* MENU - TEST */
    do {
      printf ("\033[34;01m\n=============== MENU - TEST ===============\n\033[00m\n");

      printf ("\033[34;01mINVENTORY\033[00m\n");
      printf("1. Display inventory\n");
      printf("2. Get rid of an item\n");

      printf("\n");

      printf ("\033[34;01mEQUIPMENT\033[00m\n");
      printf("3. Display equipment\n");
      printf("4. Equip player\n");
      printf("5. Remove equipment player\n");

      printf("\n");

      printf ("\033[34;01mEXIT: -1\n\033[00m\n");

      printf ("\033[34;01m===========================================\n\033[00m\n");

      do {
        printf("N°");
        scanf("%d",&choice);
        if(choice != -1 && (choice < 1 || choice > 5)){
          printf("Entry error. Value must be between 1 et 5\n");
        }
      } while(choice != -1 && (choice < 1 || choice > 5));

      printf("\n");

      switch(choice){
          case 1:   display_inventory(player); break;
          case 2:   do {
              				display_inventory(player);
              				printf("Which item do you want to delete ? (-1 to cancel) N°");
              	 			scanf("%d", &nb);
              				if((nb != -1) && (nb < 0 || nb > (player.nb_items_inventory - 1))){
              					printf("Wrong number... This item isn't in your inventory!\n");
              				}
              			}while((nb != -1) && (nb < 0 || nb > (player.nb_items_inventory - 1)));
                    if(nb != -1){
                      delete_item_in_inventory(&player,player.inventory[nb]);
                    }
                    break;
          case 3:   display_equipment_player(player); break;
          case 4:   equip_player(&player); break;
          case 5:   remove_equipment_player(&player); break;
          case -1:  printf("Thanks for playing, see you next time!\n"); break;
          default:  printf("Error\n"); break;
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
