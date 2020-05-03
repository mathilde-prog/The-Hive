#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));

  perso_t player;
  cell_t map[D][D];
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  npc_t enemy1;
  int quest_map[6][2];
  quete_t quete;
  int chance_weapon = rand()%2, chance_armor = rand()%2;

  if(creation_tab_item(Tab_Items, &nb_items_available)){
      init_player(&player);
      map_init(map,quest_map,player);
      init_quete(&quete,quest_map);
      clrscr();
      chance_weapon ? (enemy1.weapon = &Tab_Items[0]) : (enemy1.weapon = NULL); //pistol ou NULL
      chance_armor ? (enemy1.armor = &Tab_Items[7]) : (enemy1.armor = NULL);    // helmet ou NULL
      loot_enemy(Tab_Items, nb_items_available, &enemy1, &player);
      display_inventory(player);
      free(Tab_Items);
    }


  return EXIT_SUCCESS;
}
