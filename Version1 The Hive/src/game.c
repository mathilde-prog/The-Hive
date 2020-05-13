#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include "lib/commun.h"

/**
 * \file game.c
 * \brief Jeu
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

static struct option longopts[] = {
  {"demo", no_argument, NULL, (int)'d'},
  {0, 0, 0, 0}
};

/**
 * \fn void presentation_regle_jeu()
 * \brief Présentation des règles du jeu quand le joueur commence une nouvelle partie
 * \return Rien
*/
void presentation_regle_jeu(){
  while(getchar() != '\n');
  clrscr();
  printf ("\033[34;01m\n   Que faites-vous ici ?\033[00m\n");
  printf("\n   Vous êtes un survivant dans un monde post-apocalyptique ravagé par une guerre nucléaire.\n");
  printf("   Situé dans une zone contaminée, vous devez survivre dans ce monde hostile et trouver une sortie le plus vite possible !\n");
  printf("   Vous disposez de 15 tours pour vous échapper avant de mourir ici ! Vos points de vie sont à 100, tout comme vos points d'énergie et vous avez 5 points d'action.\n");
  printf("\n   Pour trouver une des sorties possibles, explorez les prairies, montagnes, villes, lacs... des environs.\n");
  printf("   Lors de votre aventure, vous risquez de faire des rencontres (plus ou moins amicales) qui nécessiteront parfois de combattre pour sauver votre vie.\n");
  printf("\n   En fouillant la zone, vous devriez trouver certains items utiles à votre survie : armes, armures, objets divers ou nourriture.\n");
  printf("   Pour le moment, vous n'avez aucun équipement sur vous, juste votre sac à dos. Vide pour l'instant, il a une capacité de 10 items maximum.\n");
  printf("\n\n   \033[1;32m>>> Appuyez sur la touche entrée pour commencer l'aventure !\033[00m");
  while(getchar() != '\n');
}

/**
 * \fn void menu_principal_jeu(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv, item_t * Tab_Items, int nb_items_available)
 * \brief Menu principal du jeu. Le joueur choisit ce qu'il souhaite faire.
 * \param player Joueur
 * \param map[D][D] Matrice de la carte
 * \param quete Etat des quêtes
 * \param sauv Etat des sauvegardes
 * \param Tab_Items Tableau contenant tous les items disponibles dans le jeu
 * \param nb_items_available Nombre d'items disponibles dans le jeu
 * \return Rien
*/
void menu_principal_jeu(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv, item_t * Tab_Items, int nb_items_available){
  int choise, choix_combat, q;
  npc_t * enemy;
  stat_t * field;

  clrscr();

  while((player.turns != 0) && (player.pv != 0)){

    /*Si il y  une quête sur l'hexagone --> quête - pas de combat */
    if(map[player.posY][player.posX].quest_id != 0){
        q = quetes(&player, map, quest_map, &quete, Tab_Items, nb_items_available);
        /*Le joueur est mort lors de la quete*/
        if(q == 1)
            exit(0);
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
      case 10: clrscr(); printf("Fichier PDF"); clrscr(); break;
      case -1: clrscr(); exit(0); break;
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

/**
 * \fn void choix_partie(sauv_t * sauv, int demo)
 * \brief Propose au joueur de choisir une partie (sauvegardée ou nouvelle partie)
 * \details Initialisation différente si le joueur continue une partie précédemment sauvegardée ou en commence une nouvelle.
 * \param sauv Pointeur sur un objet de type sauv_t correspondant à l'état des sauvegardes
 * \param demo Indicateur si mode demo
 * \return Rien
*/
void choix_partie(sauv_t * sauv, int demo){
  int choix;
  char nom_partie[21];

  perso_t player;
  cell_t map[D][D];
  int quest_map[6][2];
  quete_t quete;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;

  if(creation_tab_item(Tab_Items, &nb_items_available)){
    clrscr();
    affichage_parties(*sauv);
    // Choix partie
    printf("   A quelle partie souhaitez-vous jouer ?\n");
    printf("   Numéro partie : ");
    do {
      scanf("%d",&choix);
      if((choix < 1) || (choix > 3)){
        printf("   Valeur incorrecte. Veuillez ressaisir : ");
      }
    } while ((choix < 1) || (choix > 3));

    sauv->numPartie = choix;
    // Si le joueur souhaite jouer à une partie précédemment sauvegardée
    if(sauvegarde_existante(*sauv)){
        // Chargement des données sauvegardées
        load(&player,map,quest_map,&quete,*sauv);
        if(demo){
          demo_afficher_items(&player,Tab_Items,nb_items_available);
        }
    }
    // Nouvelle partie
    else {
      // Choix du nom de la nouvelle partie
      printf("\n   Quel nom souhaitez-vous donner à votre partie ? (20 caractères max)\n   ");
      scanf(" %[^\n]",nom_partie);

      switch(sauv->numPartie){
       case 1: strcpy(sauv->nomPartie1,nom_partie); break;
       case 2: strcpy(sauv->nomPartie2,nom_partie); break;
       case 3: strcpy(sauv->nomPartie3,nom_partie); break;
       default: break;
      }

      // Initialisations carte, joueur et quêtes
      map_init(map,quest_map);
      init_player(&player,map);
      init_quete(&quete,quest_map,Tab_Items,nb_items_available);

      if(demo){
        demo_afficher_items(&player,Tab_Items,nb_items_available);
      }

      // Sauvegarde automatique
      save(player,map,quest_map,quete,*sauv);
      printf("\n   >>> Initialisation. Sauvegarde automatique.\n"); sleep(1);

      // Présentation des règles du jeu
      presentation_regle_jeu();
    }

    menu_principal_jeu(player,map,quest_map,quete,*sauv,Tab_Items,nb_items_available);
  }
  else {
    printf("   Erreur lors de la récupération des données items.\n");
    exit(1);
  }
}

/**
 * \fn int main(int argc, char * argv[], char * env[])
 * \brief Programme principal - Menu début de jeu : choisir une partie pour jouer, effacer une partie ou quitter le jeu
 * \details Exécuter ./game --demo ou ./game -d pour mode demo
 * \param sauv Pointeur sur un objet de type sauv_t correspondant à l'état des sauvegardes
 * \param demo Indicateur si mode demo
 * \return Rien
*/
int main(int argc, char * argv[], char * env[]){
  sauv_t sauv;
  int choix, demo = 0;
  char c;
  srand(time(NULL));

  while ((c = getopt_long(argc,argv,"d",longopts,NULL)) != -1){
    if(c == 'd'){
      demo = 1;
    }
  }
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
    choix_partie(&sauv,demo);
  }
  else if(choix == 2){
    effacer_partie(sauv);
    goto menu;
  }
 clrscr();
}
