#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "lib/structure.h"

void presentation_regle_jeu(){
  while(getchar() != '\n');
  clrscr();
  printf("\n   EXPLICATIONS DES REGLES DU JEU SUR CETTE PAGE \n\n");
  printf("\n   Appuyez sur la touche entrée pour commencer l'aventure ! ");
  while(getchar() != '\n');
}

void menu_principal_jeu(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv, item_t * Tab_Items, int nb_items_available){
  int choise, choix_combat, q;

  /* Pour combat */
  npc_t * enemy;
  stat_t * field;

  clrscr();

  while((player.turns != 0) && (player.pv != 0)){

    /*Si il y  une quête sur l'hexagone --> quête - pas de combat */
    if(map[player.posY][player.posX].quest_id != 0){
        q = quetes(&player, map, quest_map, &quete, Tab_Items, nb_items_available);
        /*Le joueur est mort lors de la quete*/
        if(q == 1)
            exit(1);
    }
    else if(map[player.posY][player.posX].encounter){
      field=init_field();
      enemy=init_npc(Tab_Items);
      printf("\n   Vous tombez nez à nez avec un %s!\n\n   Souhaitez vous le combattre ? (Oui : 1, Non : 0)\n", enemy->name);
      printf("   Votre réponse : ");
      do {
        scanf("%d",&choix_combat);
        if(choix_combat < 0 || choix_combat > 1){
          printf("   Le choix est pourtant simple. Veuillez ressaisir : ");
        }
      } while(choix_combat < 0 || choix_combat > 1);

      if(choix_combat){
        combat(&player, enemy, field, map, Tab_Items, nb_items_available);
      }
      else{
        printf("\n   Courage fuyons, vous prenez la poudre d'escampette!\n");
        sleep(2);

      }
      map[player.posY][player.posX].encounter = 0;
      clrscr();
    }

    display_player_characteristics(map,player);
    affichage_quete_search_en_cours(quete,map,player);

    printf ("\033[34;01m   [Menu principal]\033[00m\n");
    printf("    1 - Fouiller la zone\n");
    printf("    2 - Gérer l'inventaire\n");
    printf("    3 - Gérer l'équipement\n");
    printf("    4 - Se déplacer ailleurs\n");
    printf("    5 - Pêcher\n");
    printf("    6 - Regarder la carte (carte nécessaire)\n");
    printf("    7 - Se reposer et guérir\n");
    printf("    8 - Fin du tour\n");
    printf("    9 - Sauvegarder la progression\n");
    printf("   10 - Aide\n");
    printf("\n   Quitter sans sauvegarder : -1\n\n");
    printf("   Que souhaitez-vous faire ? ");

    jump:
    scanf("%d",&choise);
    switch(choise){
      case 1: clrscr(); scavenge(map,&player,Tab_Items,nb_items_available,quete); clrscr(); break;
      case 2: clrscr(); manage_inventory(&player); clrscr(); break;
      case 3: clrscr(); manage_equipment(&player); clrscr(); break;
      case 4: clrscr(); move(&player, map); clrscr(); break;
      case 5: clrscr(); fish(&player,map); clrscr(); break;
      case 6: clrscr(); check_the_map(player, map); clrscr(); break;
      case 7: clrscr(); rest_and_heal(&player); clrscr(); break;
      case 8: clrscr(); next_turn(&player); clrscr(); break;
      case 9: clrscr(); sauvegarder_progression(player,map,quest_map,quete,sauv); break;
      case 10: clrscr(); printf("FICHIER PDF"); clrscr(); break;
      case -1: exit(1); break;
      default: printf("   Commande inconnue. Veuillez ressaisir: "); goto jump; break;
    }
  }

  if(!player.turns){
    printf("   Malheureusement, vous n'avez pas eu le temps de vous échapper...\n");
  }
  if(!player.pv){
    printf("   Vous êtes mort.\n");
  }

  free(enemy);
  free(field);
  free(Tab_Items);
  enemy=NULL;
  field=NULL;
  Tab_Items=NULL;

  sleep(2);
  clrscr();
}

void choix_partie(sauv_t * sauv){
  int choix;
  char nom_partie[21];

  perso_t player;
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;
  creation_tab_item(Tab_Items, &nb_items_available);

  clrscr();
  affichage_parties(*sauv);
  printf("   A quelle partie souhaitez-vous jouer ?\n");
  printf("   Numéro partie : ");
  do {
    scanf("%d",&choix);
    if((choix < 1) || (choix > 3)){
      printf("   Valeur incorrecte. Veuillez ressaisir : ");
    }
  } while ((choix < 1) || (choix > 3));

  sauv->numPartie = choix;
  if(sauvegarde_existante(*sauv)){
      load(&player,map,quest_map,&quete,*sauv);
  }
  else {
    printf("\n   Quel nom souhaitez-vous donner à votre partie ? (20 caractères max)\n   ");
    scanf(" %[^\n]",nom_partie);

    switch(sauv->numPartie){
     case 1: strcpy(sauv->nomPartie1,nom_partie); break;
     case 2: strcpy(sauv->nomPartie2,nom_partie); break;
     case 3: strcpy(sauv->nomPartie3,nom_partie); break;
     default: break;
    }

    init_player(&player);
    map_init(map,quest_map,player);
    init_quete(&quete,quest_map,Tab_Items,nb_items_available);
    save(player,map,quest_map,quete,*sauv);
    printf("\n   >>> Initialisation. Sauvegarde automatique.\n"); sleep(1);
    presentation_regle_jeu();
  }

  menu_principal_jeu(player,map,quest_map,quete,*sauv,Tab_Items,nb_items_available);
}

int main(){
  sauv_t sauv;
  int choix;
  srand(time(NULL));

  menu:
  update_etat_sauvegarde(&sauv);
  clrscr();
  affichage_parties(sauv);
  printf("   BIENVENUE - Que souhaitez-vous faire ?\n");
  printf("   1. Choisir une partie\n");
  printf("   2. Effacer une partie\n");
  printf("   3. Quitter le jeu\n");
  printf("\n   Votre choix : ");
  do {
    scanf("%d",&choix);
    if(choix < 1 || choix > 3){
      printf("   Valeur incorrecte. Veuillez ressaisir : ");
    }
  } while (choix < 1 || choix > 3);

  if(choix == 1){
    choix_partie(&sauv);
  }
  else if(choix == 2){
    effacer_partie(sauv);
    goto menu;
  }
 clrscr();
}
