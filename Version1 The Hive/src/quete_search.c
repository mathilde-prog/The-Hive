#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file quete_search.c
 * \brief Fonctions utilis�es dans la quete "recherche".
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

void affichage_quete_search_en_cours(quete_t quete, cell_t map[D][D], perso_t player){
  //Si la quete "recherche" est en cours + joueur cherche l'item demande par l'homme

  if(quete.recherche.trouve == 0){
    printf("          +-----------------------------------------------------------------+\n");
    printf("          |                         INFORMATIONS                            |\n");
    printf("          +-----------------------------------------------------------------+\n");
    if(map[player.posY][player.posX].categ != urbain){
     printf("          | Item à trouver pour l'homme : %-20s              |\n          | Allez en ville, au marché ou dans une favella pour le trouver ! |\n", quete.recherche.wanted.name);
     printf("          +-----------------------------------------------------------------+\n\n");
   }
   else {
     printf("          | Item à trouver pour l'homme : %-20s              |\n          | Vous pourriez trouver cet item ici !                            |\n", quete.recherche.wanted.name);
     printf("          +-----------------------------------------------------------------+\n\n");
   }
  }
  //Si la quete "recherche" est en cours + joueur a trouvé l'item demandé par l'homme
  else if((quete.recherche.trouve == 1) && (quete.recherche.situation == 0)){
    printf("          +-----------------------------------------------------------------+\n");
    printf("          |                         INFORMATIONS                            |\n");
    printf("          +-----------------------------------------------------------------+\n");
    printf("          | Retrouver l'homme pour lui donner l'item %-20s   | \n",quete.recherche.wanted.name);
    printf("          +-----------------------------------------------------------------+\n\n");
  }
  //Si la quete "recherche" est fini
  else if(quete.recherche.situation == 1){
    printf("          +-----------------------------------------------------------------+\n");
    printf("          |                         INFORMATIONS                            |\n");
    printf("          +-----------------------------------------------------------------+\n");
    printf("          | Coordonnées du lieu sécurisé donné par l'homme : X = %2d, Y = %2d |\n",quete.recherche.bunkerX, quete.recherche.bunkerY);
    printf("          +-----------------------------------------------------------------+\n\n");
  }
}

void init_items_recherche(item_t * Tab_items_search, item_t * Tab_Items, int nb_items_available){
    int i, cpt;

    for(i = 0, cpt = 0; i < nb_items_available; i++){
        /*Si l'item peut etre trover d'un hexagone de categorie urbain*/
        if(Tab_Items[i].pc_urban != 0){
            Tab_items_search[cpt++] = Tab_Items[i];
        }
    }
}

int compte_items_urbain(item_t * Tab_Items, int nb_items_available){
    int i, cpt;

    for(i=0, cpt=0; i<nb_items_available; i++){
        if(Tab_Items[i].pc_urban != 0)
            cpt++;
    }

    return cpt;
}



/**
 * \fn int compter_items_urbain(item_t * Tab_Items, int nb_items_available)
 * \brief Compte le nombre d'items trouvables dans un hexagone de cat�gorie "urbain" (pc_urban > 0).
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Retourne un \a int : nombre de items ayant un pc_urban > 0
*/
int compter_items_urbain(item_t * Tab_Items, int nb_items_available){
    int i, cpt;

    for(i=0, cpt=0; i<nb_items_available; i++){
        if(Tab_Items[i].pc_urban != 0)
            cpt++;
    }
    return cpt;
}


/**
 * \fn void init_Tab_Items_urbain(item_t * Tab_Items_urbain, item_t * Tab_Items, int nb_items_urbain)
 * \brief Initialise un tableau contenant tous les items trouvable dans un hexagone de cat�gorie "urbain".
 * \param item_t * Tab_Items_urbain
 * \param item_t * Tab_Items
 * \param int nb_items_urbain
 * \return Rien
*/
void init_Tab_Items_urbain(item_t * Tab_Items_urbain, item_t * Tab_Items, int nb_items_urbain){
    int i, num, cpt;

    for(i=0, cpt=0; i<nb_items_urbain; i++){
        num = rand()%nb_items_urbain;
        /*Si l'item peut etre trouver d'un hexagone de categorie urbain*/
        if(Tab_Items[num].pc_urban != 0)
           Tab_Items_urbain[cpt++] = Tab_Items[num];
    }
}


/**
 * \fn void quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete, quest_map[6][2], item_t * Tab_Items, int nb_items_available)
 * \brief Acc�s � la quete "recherche".
 * \details
    Le joueur doit aller � un endroit donn� pour trouver un item et le ramener.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \param quete_t * quete
 * \param quest_map[6][2];
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Retourne un \a int : 0 si le jeu continue et -1 si problème dans la quete.
*/
int quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete){
    int choix, conf, ind;

    /*Si la quete n'est pas encore commenc�, ou que le joueur y a deja renonc�*/
    if(quete->recherche.trouve==-1){
        quete->recherche.situation=0;

        /*Description de la situation*/
        printf("\n   Vous croisez le chemin d'un homme qui paraît sympathique. Il vient à votre rencontre, vous commencez à discuter.\n");
        printf("   Il vous explique qu'il connait très bien les environs, et qu'il pourrait vous aider à vous mettre en sécurité dans un lieu discret.\n");
        printf("\n   Vous êtes très intéressé par l'aide qu'il vous propose, et il l'a très bien compris. Il vous propose un marché :\n");
        printf("   \"J'ai besoin de trouver l'item %s, si tu acceptes d'aller me chercher cet item et de me le ramener par la suite, je t'aiderai à te sortir d'ici.\"\n", quete->recherche.wanted.name);

        printf("\n   Vous avez deux possibilités :\n");
        printf("   1 - Accepter la requête de l'homme\n");
        printf("   2 - Ne pas l'accepter\n");
        printf("\n   Que choisissez vous ? ");
        do{
            scanf("%d", &choix);
            if(choix<1 || choix>2)
                printf("   Valeur incorrecte. Veuillez ressaisir : ");
        }while(choix<1 || choix>2);

        clrscr();

        /*Le joueur souhaite trouver l'item*/
        if(choix==1){
            printf("\n   L'homme est heureux de votre réponse, il vous donne plus de détails sur votre mission :\n");

            // Si le joueur a déjà l'item sur lui
            if(item_in_inventory(*player,quete->recherche.wanted.name) != -1){
              printf("   \"Oh mais tu as déjà %s, l'item que je recherche! ", quete->recherche.wanted.name);
              printf("\n   Souhaitez-vous donner l'item %s à l'homme ?\n",quete->recherche.wanted.name);
              printf("   1 - Oui\n");
              printf("   2 - Non\n");
              printf("\n   Votre choix : ");
              do{
                  scanf("%d", &conf);
                  if(conf<1 || conf>2)
                      printf("   Valeur incorrecte. Veuillez ressaisir : ");
              }while(conf<1 || conf>2);

              clrscr();
              if(conf == 1){
                ind = item_in_inventory(*player,quete->recherche.wanted.name);
                delete_item_in_inventory(player, player->inventory[ind]);
                printf("\n   Il vous remercie énormément de lui avoir rendu ce service.\n");
                printf("   Pour vous remercier, et comme il vous l'avait promis il vous indique le lieu où vous pourrez vous réfugier et ainsi vous mettre en sécurité.\n");
                printf("\n   Voilà les coordonnées : X = %2d, Y = %2d\n\n", quete->recherche.bunkerX, quete->recherche.bunkerY);
                quete->recherche.situation=1;
                entree_pour_continuer();
                return 0;
              }
              else if (conf == 2){
                printf("\n   Vous lui annoncez ne pas souhaiter honorer cette requête, il est déçu mais vous laisse repartir explorer la map.\n\n");
                entree_pour_continuer();
                return 0;
              }
            }
            else {
              printf("   \"Tu as le choix d'aller dans une ville, dans un marché ou dans une favella pour trouver l'item %s. Une fois que tu as trouvé l'item il faudra que tu reviennes ici pour me le redonner.\n", quete->recherche.wanted.name);

              printf("\n   Souhaitez-vous toujours trouver l'item demandé par l'homme ?\n");
              printf("   1 - Oui\n");
              printf("   2 - Non\n");
              printf("\n   Votre choix : ");
              do{
                  scanf("%d", &conf);
                  if(conf<1 || conf>2)
                      printf("   Valeur incorrecte. Veuillez ressaisir : ");
              }while(conf<1 || conf>2);

              clrscr();
              /*Le joueur renonce à la requete*/
              if(conf==2){
                  printf("\n   Vous lui annoncez renoncer à cette requête, il est déçu mais vous laisse repartir explorer la map.\n\n");
                  entree_pour_continuer();
                  return 0;
              }
              /*Le joueur continue la requete*/
              else if(conf==1){
                  printf("\n   C'est parti, à vous de trouver l'item %s que l'homme vous demande !\n\n", quete->recherche.wanted.name);
                  quete->recherche.trouve=0;
                  entree_pour_continuer();
                  return 0;
              }
            }
        }
        /*Le joueur ne souhaite pas trouver l'item demandé par l'homme*/
        else if(choix==2){
            printf("\n   Vous lui annoncez ne pas souhaiter honorer cette requête, il est déçu mais vous laisse repartir explorer la map.\n\n");
            entree_pour_continuer();
            return 0;
        }
        return (-1);
    }
    /*Si la quete est déjà commencé par le joueur, et qu'il est entrain de chercher l'item, il souhaite rechercher les items sur l'hexagone actuel*/
    else if(quete->recherche.trouve==0){
        /*Le joueur n'est pas sur un hexagone de categorie urbain*/
          printf("\n   L'homme vous demande ce que vous faîtes encore ici... \n");
          printf("   Allez trouver %s dans une ville, un marché ou une favella.\n", quete->recherche.wanted.name);
          printf("   Continuez votre route sur la map, afin d'aller dans un des lieux cités ci-dessus.\n\n");
          entree_pour_continuer();
          return 0;
    }
    /*Le joueur a trouvé par l'item, il doit maintenant le donner à l'homme*/
    else if(quete->recherche.trouve==1){
        /*Le joueur est sur le bon hexagone pour retrouver l'homme*/
        printf("\n   Vous êtes dans le lieu où vous avez rencontré l'homme !\n");
        printf("   Il se tient face a vous avec un grand sourire. Vous lui donnez son item, il est au passage retiré de votre inventaire.\n");
        ind = item_in_inventory(*player,quete->recherche.wanted.name);
        delete_item_in_inventory(player, player->inventory[ind]);

        printf("\n   Il vous remercie énormément de lui avoir rendu ce service.\n");
        printf("   Pour vous remercier, et comme il vous l'avait promis il vous indique le lieu où vous pourrez vous réfugier et ainsi vous mettre en sécurité.\n");
        printf("\n   Voilà les coordonnées : X = %2d, Y = %2d\n\n", quete->recherche.bunkerX, quete->recherche.bunkerY);
        quete->recherche.situation=1;
        entree_pour_continuer();
        return 0;
  }

  return (-1);
}
