#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

void loot_enemy (npc_t * enemy, perso_t * player){
  int answer;

  if(enemy->weapon == NULL && enemy->armor == NULL){
    printf("Aucun item sur votre ennemi\n");
  }
  else {
    if(enemy->weapon != NULL){
      do {
        printf("Souhaitez-vous prendre son arme (%s) ? (Oui: 1  Non: 0)\n",enemy->weapon->name);
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("Valeur incorrecte. Veuillez ressaisir.\n");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->weapon)){
          enemy->weapon = NULL;
        }
      }
    }
    if(enemy->armor != NULL){
      do {
        printf("Souhaitez-vous prendre son armure (%s) ? (Oui: 1  Non: 0)\n",enemy->armor->name);
        scanf("%d", &answer);
        if(answer < 0 || answer > 1){
          printf("Valeur incorrecte. Veuillez ressaisir\n");
        }
      } while (answer < 0 || answer > 1);

      if(answer){
        if(add_item_to_inventory(player, *enemy->armor)){
          enemy->armor = NULL;
        }
      }
    }
  }
}

int main(){
  perso_t player;
  cell_t map[D][D];
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  npc_t enemy1;

  srand(time(NULL));

  if(creation_tab_item(Tab_Items, &nb_items_available)){
    if(init_or_load_game(&player,map)){
      enemy1.weapon = &Tab_Items[0];
      enemy1.armor = &Tab_Items[7];
      loot_enemy(&enemy1, &player);
      display_inventory(player);
      free(Tab_Items);
    }
  }

  return EXIT_SUCCESS;
}
