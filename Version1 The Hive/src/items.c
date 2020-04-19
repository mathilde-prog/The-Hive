#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "structure.h"

/**
 * \file items.c
 * \brief Fonctions relatives aux items
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/************************************** CREATION + DISPLAY ITEMS (MATHILDE) **************************************/
/**
 * \fn item_t * creer_item (char * chaine, type_t type, int attack, int defense, int equipable, int pc_nature, int pc_urban, int pc_military)
 * \brief Crée un item à partir des informations passées en paramètres
 * \param char * chaine
 * \param type_t type
 * \param int attack
 * \param int defense
 * \param int equipable
 * \param int pc_nature
 * \param int pc_urban
 * \param int pc_military
 * \return Un pointeur sur l'item créé
*/
item_t * creer_item (char * chaine, type_t type, int attack, int defense, int equipable, int pc_nature, int pc_urban, int pc_military){
  item_t * item = malloc(sizeof(item_t));

  strcpy(item->name,chaine);
  item->type = type;
  item->attack = attack;
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
 * \brief Récupère les items du fichier 'items.txt' et les stocke dans le tableau passé en paramètres.
 * \details Affiche un message d'erreur si fichier 'items.txt' non trouvé
 * \param char * Tab_Items
 * \param int * nb_items
 * \return Un \a int : 1 si création des items réalisée avec succès. 0 sinon.
*/
/* creation_tab_item: retrieves items from the file 'items.txt' and stores them in a table passed in parameters
                      displays error message if file 'items.txt' not found
                      returns whether the creation of the items has been successfully completed (0 or 1)
*/
int creation_tab_item(item_t * Tab_Items, int * nb_items){
  * nb_items = 0;
  FILE * fichier = fopen("../txt/items.txt","r");

  if(fichier){
    fscanf(fichier,"%s%d%d%d%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable, &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military);
    while(!feof(fichier)){
      Tab_Items[(*nb_items)++].index = -1;
      fscanf(fichier,"%s%d%d%d%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable,  &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military);
    }
    fclose(fichier);
    return 1;
  }
  else {
    printf("Le fichier 'items.txt' est introuvable. Impossible de récupérer les items pour jouer.\n");
    return 0;
  }
}

/**
 * \fn void display_item (item_t item)
 * \brief Affiche toutes les caractéristiques d'un item (nom, type, valeur d'attaque si arme, valeur de défense si armure, équipable ou non, pc_nature, pc_urban, pc_military)
 * \param item_t item
 * \return Rien
*/
/* display_item: displays all the characteristics of an item (name, type, value of attack, value of defense, equipable or not) */
void display_item (item_t item){
	printf("\nITEM: %s\n",item.name);
	printf("Type : ");
	switch(item.type){
		case armor:  printf("armure\n");         break;
		case weapon: printf("arme\n");        break;
		case misc:   printf("divers\n");          break;
		case food:   printf("nourriture\n");          break;
		default:     printf("non reconnu\n");  break;
	}

  /* Displays attack value if the item is a weapon and defense value if the item is armor */
	if(item.type == weapon){
		printf("Attaque : %d\n",item.attack);
	}
	else if(item.type == armor){
		printf("Défense : %d\n",item.defense);
	}

  switch(item.equipable){
    case none: printf("Pas équipable\n");   break;
    case hand: printf("Equipable (main)\n");  break;
    case body: printf("Equipable (corps)\n");  break;
    case head: printf("Equipable (tête)\n");  break;
    default:   printf("non reconnu\n");    break;
  }

  printf("pc_nature = %d\n", item.pc_nature);
  printf("pc_urban = %d\n", item.pc_urban);
  printf("pc_military = %d\n\n", item.pc_military);
}

/***************************************************************************************************************/
