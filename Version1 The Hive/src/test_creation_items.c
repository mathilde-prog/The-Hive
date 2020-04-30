// test_creation_items.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/structure.h"

int main(){
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int i, nb_items_available = 0;

  // On vérifie si l'allocation a marché ou non
  if(Tab_Items == NULL) {
    printf("ECHEC allocation dynamique\n");
    exit(0); // On arrête tout
  }

  printf("SUCCES allocation dynamique\n");

  if(creation_tab_item(Tab_Items, &nb_items_available)){
    if(nb_items_available == 18){
      printf("==> Tous les items ont bien été récupérés.\n");
    }
    else {
      printf("==> 18 items étaient attendus. Or, on en a récupéré %d\n", nb_items_available);
    }
    for(i = 0; i < nb_items_available; i++){
      display_item(Tab_Items[i]);
      printf("Index : %d\n", Tab_Items[i].index);
    }
    printf("SUCCES récupération des informations sur les items\n");
  }
  else {
    printf("ECHEC récupération des données items\n");
  }

  free(Tab_Items);
}
