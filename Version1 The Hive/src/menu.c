#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

perso_t player;
int nb_items_available = 0;

int main(){
  int choise;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  cell_t map[D][D];

  srand(time(NULL));
  clrscr();

  // Creation items
  if(creation_tab_item(Tab_Items, &nb_items_available)){

    // Start a new game or continue if saved game
    if(init_or_load_game(&player,map)){
      clrscr();

      while(player.turns != 0 && player.pv != 0){

        display_player_characteristics(map, player);

        printf ("\033[34;01m[Menu principal]\033[00m\n");
        printf("1 - Fouiller la zone\n");
        printf("2 - Gérer l'inventaire\n");
        printf("3 - Gérer l'équipement\n");
        printf("4 - Se déplacer ailleurs\n");
        printf("5 - Pêcher\n");
        printf("6 - Regarder la carte (carte nécessaire)\n");
        printf("7 - Se reposer et guérir\n");
        printf("8 - Fin du tour\n");
        printf("9 - Sauvegarder le jeu et quitter\n");
        printf("10 - Aide\n");
        printf("Quitter: -1\n");
        printf("\nQue souhaitez-vous faire ? ");

        jump:
        scanf("%d",&choise);
        switch(choise){
          case 1: clrscr(); scavenge(map,&player,Tab_Items,nb_items_available); clrscr(); break;
          case 2: clrscr(); manage_inventory(&player); clrscr(); break;
          case 3: clrscr(); manage_equipment(&player); clrscr(); break;
          case 4: clrscr(); move(&player, map); clrscr(); break;
          case 5: clrscr(); fish(&player,map); clrscr(); break;
          case 6: clrscr(); check_the_map(player, map); clrscr(); break;
          case 7: clrscr(); rest_and_heal(&player); clrscr(); break;
          case 8: clrscr(); next_turn(&player); clrscr(); break;
          case 9: clrscr(); save(player,map); exit(1); break;
          case 10: clrscr(); help(&player); clrscr(); break;
          case -1: exit(1); break;
          default: printf("Commande inconnue. Veuillez resaissir: "); goto jump; break;
        }
      }

      if(!player.turns){
        printf("Malheureusement, vous n'avez pas eu le temps de vous échapper...\n");
      }
      if(!player.pv){
        printf("Vous êtes mort.\n");
      }

      free(Tab_Items);
      sleep(2);
      clrscr();
    }
  }
}
