#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "lib/commun.h"

/**
 * \file items.c
 * \brief Items (création, affichage, génération aléatoire lors de fouille d'hexagones)
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/**
 * \fn item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military){
 * \brief Crée un item à partir des informations passées en paramètres
 * \param chaine Nom de l'item
 * \param type Type de l'item
 * \param attack0 Valeur d'attaque si distance égale à 0 pendant un combat
 * \param attack1 Valeur d'attaque si distance égale à 1 pendant un combat
 * \param attack2 Valeur d'attaque si distance égale à 2 pendant un combat
 * \param hitchance0 Probabilité en pourcentage de toucher l'ennemi si distance égale à 0 pendant un combat
 * \param hitchance1 Probabilité en pourcentage de toucher l'ennemi si distance égale à 1 pendant un combat
 * \param hitchance2 Probabilité en pourcentage de toucher l'ennemi si distance égale à 2 pendant un combat
 * \param defense Valeur de défense
 * \param equipable Indicateur si l'item est équipable et où
 * \param pc_nature Probabilité en pourcentage de trouver l'item créé dans un hexagone de catégorie nature
 * \param pc_urban Probabilité en pourcentage de trouver l'item créé dans un hexagone de catégorie urbaine
 * \param pc_military Probabilité en pourcentage de trouver l'item créé dans un hexagone de catégorie militaire
 * \return Un pointeur sur un objet de type item_t correspondant à l'item créé
*/
item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military){
  item_t * item = malloc(sizeof(item_t));

  strcpy(item->name,chaine);
  item->type = type;

  item->attack[0] = attack0;
  item->attack[1] = attack1;
  item->attack[2] = attack2;

  item->hitchance[0] = hitchance0;
  item->hitchance[1] = hitchance1;
  item->hitchance[2] = hitchance2;

  item->defense = defense;
  item->equipable = equipable;
  item->pc_nature = pc_nature;
  item->pc_urban = pc_urban;
  item->pc_military = pc_military;
  item->index = -1;

  return(item);
}

/**
 * \fn int creation_tab_item(item_t * Tab_Items, int * nb_items)
 * \brief Récupère les items du fichier 'data/items.csv' et les stocke dans le tableau passé en paramètres.
 * \details Affiche un message d'erreur si fichier 'items.csv' introuvable
 * \param Tab_Items Tableau contenant tous les items disponibles dans le jeu
 * \param nb_items Pointeur sur un entier correspondant au nombre d'items extraits du fichier externe
 * \return Un \a int : 1 si récupération des items réalisée avec succès. 0 sinon.
*/
int creation_tab_item(item_t * Tab_Items, int * nb_items){
  * nb_items = 0;
  FILE * fichier = fopen("../data/items.csv","r");

  if(fichier){
    fscanf(fichier,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", (int *)(&Tab_Items[*nb_items].type), &Tab_Items[*nb_items].attack[0], &Tab_Items[*nb_items].attack[1],&Tab_Items[*nb_items].attack[2], &Tab_Items[*nb_items].hitchance[0], &Tab_Items[*nb_items].hitchance[1],&Tab_Items[*nb_items].hitchance[2],&Tab_Items[*nb_items].defense, (int *)(&Tab_Items[*nb_items].equipable), &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military, Tab_Items[*nb_items].name);
    while(!feof(fichier)){
      Tab_Items[(*nb_items)++].index = -1;
      fscanf(fichier,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]",(int *)(&Tab_Items[*nb_items].type), &Tab_Items[*nb_items].attack[0], &Tab_Items[*nb_items].attack[1],&Tab_Items[*nb_items].attack[2], &Tab_Items[*nb_items].hitchance[0], &Tab_Items[*nb_items].hitchance[1],&Tab_Items[*nb_items].hitchance[2],&Tab_Items[*nb_items].defense, (int *)(&Tab_Items[*nb_items].equipable), &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military, Tab_Items[*nb_items].name);
    }
    fclose(fichier);
    return 1;
  }
  else {
    printf("\n   Le fichier 'data/items.csv' est introuvable.\n");
    return 0;
  }
}

/**
 * \fn void display_item (item_t item)
 * \brief Affiche toutes les caractéristiques d'un item (nom, type, valeur d'attaque si arme, valeur de défense si armure, équipable ou non, pourcentage de chance de trouver cet item sur un hexagone de catégorie nature, urbain et militaire)
 * \param item Item à afficher
 * \return Rien
*/
void display_item (item_t item){
	printf("\n   Nom item: %s\n",item.name);
	printf("\n   Type : ");
	switch(item.type){
		case armor:  printf("armure\n");         break;
		case weapon: printf("arme\n");        break;
		case misc:   printf("divers\n\n");          break;
		case food:   printf("nourriture\n\n");          break;
		default:     printf("non reconnu\n\n");  break;
	}

	if(item.type == weapon){
		printf("\n   Valeur d'attaque :\n       Distance 0 : %d\n       Distance 1 : %d\n       Distance 2 : %d\n\n",item.attack[0], item.attack[1], item.attack[2]);
    printf("   Chance de toucher l'ennemi :\n       Distance 0 : %d\n       Distance 1 : %d\n       Distance 2 : %d\n\n", item.hitchance[0], item.hitchance[1], item.hitchance[2]);
	}
	else if(item.type == armor){
		printf("\n   Valeur de défense : %d\n\n",(int)(item.defense*100));
	}

  switch(item.equipable){
    case none: printf("   Pas équipable\n");   break;
    case hand: printf("   Equipable (main)\n");  break;
    case body: printf("   Equipable (corps)\n");  break;
    case head: printf("   Equipable (tête)\n");  break;
    default:   printf("   non reconnu\n");    break;
  }

  printf("\n   Chance de trouver cet item dans ces lieux : \n");
  printf("      Nature = %d%%\n", item.pc_nature);
  printf("      Urbain = %d%%\n", item.pc_urban);
  printf("      Militaire = %d%%\n\n", item.pc_military);
}

/**
 * \fn void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ)
 * \brief Génère aléatoirement 0 à #ITEMS_MAX items en prenant en compte le pourcentage de chance des items d'apparaître dans un type d'hexagone en particulier.
 * \details Propose au joueur de récupérer les items générés
 * \param Tab_Items Tableau contenant tous les items disponibles dans le jeu
 * \param nb_items_available Nombre d'items disponibles dans le jeu
 * \param player Pointeur sur un objet de type perso_t correspondant au joueur
 * \param categ Catégorie de l'hexagone inspecté
 * \return Rien
*/
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ){
    int i, ind, present, cpt = 0, choise, nb;
    // Remarque: cpt correspond au nombre d'items qui apparaissent sur l'hexagone

    int ind_items_found[ITEMS_MAX]; // tableau contenant les indices des items trouvés (à quels indices ils sont dans TabItems)
    // On initialise tout le tableau à -1 (Pourquoi -1 ? Signifie non-présent dans Tab_Items)
    for(i = 0; i < ITEMS_MAX; i++){
      ind_items_found[i] = -1;
    }

    // Génération aléatoire de 0 à ITEMS_MAX items
    for(i = 0; i < ITEMS_MAX; i++){
        ind = rand()%nb_items_available;
        switch(categ){
          case nature:    present = rng(Tab_Items[ind].pc_nature);   break;
          case urbain:    present = rng(Tab_Items[ind].pc_urban);    break;
          case militaire: present = rng(Tab_Items[ind].pc_military); break;
          default: present = 0; break;
        }
        if (present == 1){
          ind_items_found[cpt] = ind;
          cpt++;
        }
    }

    // Si items générés
    if (cpt != 0){
      // Cas 1 item
      if(cpt == 1){
        printf("\n   Félicitation, vous avez trouvé un item : %s\n", Tab_Items[ind_items_found[0]].name);
        printf("   Souhaitez-vous ajouter %s à votre inventaire ? (Oui = 1, Non = 0)\n", Tab_Items[ind_items_found[0]].name);
        printf("   Réponse : ");
        do {
          scanf("%d",&choise);
          if (choise < 0 || choise > 1){
            printf("   Valeur incorrecte. Veuillez ressaisir : ");
          }
        } while(choise < 0 || choise > 1);

        if(choise){
          add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
          sleep(2);
        }
      }
      // Plusieurs items trouvés
      else {
        printf("\n   Félicitation, vous avez trouvé %d items!\n", cpt);

        do{
          // Affichage des items trouvés
          printf("\n   ===== VOUS AVEZ TROUVE ====\n");
          for(i = 0; i < cpt; i++){
            printf("   N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
          }
          printf("   =========================\n\n");

          printf("   1. Ajouter un item trouvé dans votre inventaire\n");
          printf("   2. Rien récupérer\n");
          printf("   Réponse : ");
          do {
            scanf("%d",&choise);
            if (choise < 1 || choise > 2){
              printf("   Valeur incorrecte. Veuillez ressaisir : ");
            }
          } while(choise < 1 || choise > 2);

          if(choise == 1){
            printf("   Quel item souhaitez-vous ajouter votre inventaire? N°");
            do {
              scanf("%d",&nb);
              if (nb < 0 || nb > cpt-1){
                printf("   Valeur incorrecte. Veuillez ressaisir : ");
              }
            } while(nb < 0 || nb > cpt-1);

            if(add_item_to_inventory(player,Tab_Items[ind_items_found[nb]])){
              // Cet item a été ajouté à l'inventaire donc on l'enlève des items trouvés sur cet hexagone
              // Empêche qu'on puisse ajouter le même plusieurs fois !
              i = nb;
              while(i < cpt){
                ind_items_found[i] = ind_items_found[i+1];
                i++;
              }
              cpt--;
              sleep(2);
              clrscr();
            }
          }
          else {
            (cpt == 1) ? printf("   Vous ne prenez pas cet item.\n") : printf("   Vous ne prenez pas ces items.\n");
            sleep(1);
          }
        } while((choise != 2) && (cpt > 0));
      }
    }
    else{
        printf("\n   Il n'y a rien à récupérer ici...\n");
        sleep(1);
    }
}

/**
 * \fn void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available, quete_t * quete)
 * \brief Permet au joueur de fouiller l'hexagone sur lequel il se trouve pour récupérer des items
 * \param map[D][D] Matrice de la carte
 * \param player Pointeur sur un objet de type perso_t correspondant au joueur
 * \param Tab_Items Tableau contenant tous les items disponibles dans le jeu
 * \param nb_items_available Nombre d'items disponibles dans le jeu
 * \param quete Pointeur sur un objet de type quete_t correspondant à l'état des quêtes
 * \return Rien
*/
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available, quete_t * quete){
    categ_hexa categ = map[player->posY][player->posX].categ;

    // Si le joueur n'a pas déjà fouillé l'hexagone où il est
    if(map[player->posY][player->posX].scavenged == 1){
      printf("\n   Vous êtes déjà passé par là!\n");
      sleep(2);
    }
    else {
      if(categ != other){
        generate_items(Tab_Items, nb_items_available, player, categ);
        // Si la quête recherche est en cours et que le joueur a trouvé l'item recherché par l'homme
        if((quete->recherche.situation == 0) && (item_in_inventory(*player,quete->recherche.wanted.name) != -1)){
          printf("\n   Félicitations, vous avez trouvé l'item %s que l'homme vous a demandé ! Il faut maintenant aller le retrouver pour lui donner.\n\n", quete->recherche.wanted.name);
          quete->recherche.trouve = 1;
          entree_pour_continuer();
        }
      }
      else { // Aucun item généré
        printf("\n   Rien n'apparaît!\n");
        sleep(2);
      }

      map[player->posY][player->posX].scavenged = 1;
    }
}
