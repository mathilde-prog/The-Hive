#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

int main(){
  /* Tab_Items Declaration (= table containing ALL the items available in the game) */
  item_t Tab_Items[20];
  int nb_items_available = 0;

  /* Player Declaration */
  perso_t player;
  printf("Initialisation Joueur\n");
  init_player(&player);
  printf("\n");

  if(creation_tab_item(Tab_Items, &nb_items_available)) {
    printf ("\033[34;01m=== ITEMS ADDED TO THE INVENTORY (TESTS) ===\033[00m\n");
    /* I'm adding items to the inventory to test functions */
    add_item_to_inventory(&player, Tab_Items[13]); //fruits
    add_item_to_inventory(&player, Tab_Items[14]); //fish
    add_item_to_inventory(&player, Tab_Items[15]); //can_food
    add_item_to_inventory(&player, Tab_Items[16]); //energy_drink
    add_item_to_inventory(&player, Tab_Items[17]); //bottle_water

    add_item_to_inventory(&player,Tab_Items[0]);  // pistol
    add_item_to_inventory(&player,Tab_Items[7]);  // helmet
    add_item_to_inventory(&player,Tab_Items[12]); // map

    printf ("\033[34;01m===========================================\n\n\033[00m");

    eat_or_drink(&player,player.inventory[0]); // fruits
    (player.nb_items_inventory == 7) ? printf("fruits - Test OK\n") : printf("fruits - Test KO\n");
    (player.pe == 110) ? printf("fruits - Test OK\n\n") : printf("fruits - Test KO\n\n");

    eat_or_drink(&player,player.inventory[0]); // fish
    (player.nb_items_inventory == 6) ? printf("fish - Test OK\n") : printf("fish - Test KO\n");
    (player.pe == 125) ? printf("fish - Test OK\n\n") : printf("fish - Test KO\n\n");

    eat_or_drink(&player,player.inventory[0]); // can_food
    (player.nb_items_inventory == 5) ? printf("can_food - Test OK\n") : printf("can_food - Test KO\n");
    (player.pe == 175) ? printf("can_food - Test OK\n\n") : printf("can_food - Test KO\n\n");

    eat_or_drink(&player,player.inventory[0]); // energy_drink
    (player.nb_items_inventory == 4) ? printf("energy_drink - Test OK\n") : printf("energy_drink - Test KO\n");
    (player.pe == 195) ? printf("energy_drink - Test OK\n") : printf("energy_drink - Test KO\n");
    (player.pa == 4) ? printf("energy_drink - Test OK\n\n") : printf("energy_drink - Test KO\n\n");

    eat_or_drink(&player,player.inventory[0]); // bottle_water
    (player.nb_items_inventory == 3) ? printf("bottle_water - Test OK\n") : printf("bottle_water - Test KO\n");
    (player.pe == 205) ? printf("bottle_water - Test OK\n\n") : printf("bottle_water - Test KO\n\n");

    eat_or_drink(&player,player.inventory[0]); // pistol
    (player.nb_items_inventory == 3) ? printf("pistol - Test OK\n\n") : printf("pistol - Test KO\n\n");

    eat_or_drink(&player,player.inventory[1]); // helmet
    (player.nb_items_inventory == 3) ? printf("helmet - Test OK\n\n") : printf("helmet - Test KO\n\n");

    eat_or_drink(&player,player.inventory[2]); // map
    (player.nb_items_inventory == 3) ? printf("map - Test OK\n\n") : printf("map - Test KO\n\n");
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
