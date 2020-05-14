#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/commun.h"

/**
 * \file test_creation_items.c
 * \brief Fichier TEST - Extraction des items du fichier externe
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \brief Programme principal pour tester l'extraction des items à partir du fichier externe "items.csv" (dossier data)
 * \details Objectif : Tester la fonction #creation_tab_item.
*/
int main(){
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int i, nb_items_available = 0;

  // On vérifie si l'allocation a marché ou non
  if(Tab_Items == NULL) {
    printf("\n   ECHEC allocation dynamique\n");
    exit(0); // On arrête tout
  }

  printf("\n   SUCCES allocation dynamique\n");

  if(creation_tab_item(Tab_Items, &nb_items_available)){
    if(nb_items_available == 18){
      printf("\n   ==> Tous les items ont bien été récupérés.\n");
    }
    else {
      printf("\n   ==> 18 items étaient attendus. Or, on en a récupéré %d\n", nb_items_available);
    }
    for(i = 0; i < nb_items_available; i++){
      display_item(Tab_Items[i]);
      printf("   Index : %d", Tab_Items[i].index);
      if(Tab_Items[i].index == -1){
        printf(" OK\n");
      }
    }
    printf("\n   SUCCES récupération des informations sur les items\n");
  }
  else {
    printf("\n   ECHEC récupération des données items\n");
  }

  free(Tab_Items);
}
