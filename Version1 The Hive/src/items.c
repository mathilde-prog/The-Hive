#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "lib/structure.h"

/**
 * \file items.c
 * \brief Fonctions relatives aux items
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/************************************** CREATION + DISPLAY ITEMS (MATHILDE) **************************************/
/**
 * \fn item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military){
 * \brief Crée un item à partir des informations passées en paramètres
 * \param char * chaine
 * \param type_t type
 * \param int attack0
 * \param int attack1
 * \param int attack2
 * \param int hitchance0
 * \param int hitchance1
 * \param int hitchance2
 * \param float defense
 * \param int equipable
 * \param int pc_nature
 * \param int pc_urban
 * \param int pc_military
 * \return Un pointeur sur l'item créé
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
 * \details Affiche un message d'erreur si fichier 'items.csv' non trouvé
 * \param char * Tab_Items
 * \param int * nb_items
 * \return Un \a int : 1 si création des items réalisée avec succès. 0 sinon.
*/
int creation_tab_item(item_t * Tab_Items, int * nb_items){
  * nb_items = 0;
  FILE * fichier = fopen("../data/items.csv","r");

  if(fichier){
    fscanf(fichier,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack[0], &Tab_Items[*nb_items].attack[1],&Tab_Items[*nb_items].attack[2], &Tab_Items[*nb_items].hitchance[0], &Tab_Items[*nb_items].hitchance[1],&Tab_Items[*nb_items].hitchance[2],&Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable, &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military, Tab_Items[*nb_items].name);
    while(!feof(fichier)){
      Tab_Items[(*nb_items)++].index = -1;
      fscanf(fichier,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack[0], &Tab_Items[*nb_items].attack[1],&Tab_Items[*nb_items].attack[2], &Tab_Items[*nb_items].hitchance[0], &Tab_Items[*nb_items].hitchance[1],&Tab_Items[*nb_items].hitchance[2],&Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable, &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military, Tab_Items[*nb_items].name);
    }
    fclose(fichier);
    return 1;
  }
  else {
    printf("\n   Le fichier 'items.csv' est introuvable. Impossible de récupérer les items pour jouer.\n");
    return 0;
  }
}

/**
 * \fn void display_item (item_t item)
 * \brief Affiche toutes les caractéristiques d'un item (nom, type, valeur d'attaque si arme, valeur de défense si armure, équipable ou non, pc_nature, pc_urban, pc_military)
 * \param item_t item
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

/***************************************************************************************************************/
