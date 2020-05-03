#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));
  perso_t player;
  npc_t * enemy;
  stat_t * field;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available;
  creation_tab_item(Tab_Items, &nb_items_available);
  field=init_field();
  enemy=init_npc(Tab_Items);
  player.body=NULL;
  player.pv=100;
  player.left_hand=&Tab_Items[0];
  player.right_hand=&Tab_Items[0];
  player.head=NULL;
  printf("======== SOME INFO ============\nEnemy hp: %d\nEnemy weapon: %s\nEnemy armor: %s\n=============================\n",enemy->pv, enemy->weapon->name, enemy->armor->name);
  combat(&player, enemy, field);
  free(enemy);
  free(field);
  free(Tab_Items);
  enemy=NULL;
  field=NULL;
  Tab_Items=NULL;
}
