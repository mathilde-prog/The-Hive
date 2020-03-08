//items.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

/************************************** CREATION + DISPLAY ITEMS (MATHILDE) **************************************/
/* creation_tab_item: retrieves items from the file 'items.txt' and stores them in a table passed in parameters
                      displays error message if file 'items.txt' not found
                      returns whether the creation of the items has been successfully completed (0 or 1)
*/
int creation_tab_item(item_t * Tab_Items, int * nb_items){
  * nb_items = 0;
  FILE * fichier = fopen("txt/items.txt","r");

  if(fichier){
    fscanf(fichier,"%s%d%d%d%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable, &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military);
    while(!feof(fichier)){
      (*nb_items)++;
      fscanf(fichier,"%s%d%d%d%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable,  &Tab_Items[*nb_items].pc_nature, &Tab_Items[*nb_items].pc_urban, &Tab_Items[*nb_items].pc_military);
    }
    fclose(fichier);
    return 1;
  }
  else {
    printf("The file 'items.txt' does not exist. Impossible to retrieve items!\n");
    return 0;
  }
}

/* display_item: displays all the characteristics of an item (name, type, value of attack, value of defense, equipable or not) */
void display_item (item_t item){
	printf("Item : %s\n",item.name);

	printf("Type : ");
	switch(item.type){
		case armor:  printf("armor\n");         break;
		case weapon: printf("weapon\n");        break;
		case misc:   printf("misc\n");          break;
		case food:   printf("food\n");          break;
		default:     printf("unrecognized\n");  break;
	}

  /* Displays attack value if the item is a weapon and defense value if the item is armor */
	if(item.type == weapon){
		printf("Attack : %d\n",item.attack);
	}
	else if(item.type == armor){
		printf("Defense : %d\n",item.defense);
	}

  switch(item.equipable){
    case none: printf("Not equipable\n");   break;
    case hand: printf("Equipable (hand)\n");  break;
    case body: printf("Equipable (body)\n");  break;
    case head: printf("Equipable (head)\n");  break;
    default:   printf("unrecognized\n");    break;
  }

  printf("pc_nature = %d\n", item.pc_nature);
  printf("pc_urban = %d\n", item.pc_urban);
  printf("pc_military = %d\n", item.pc_military);
	printf("\n");
}

/***************************************************************************************************************/

/************************************** PARTIE ANAIS  **************************************/

//Renvoie le nombre de d'items qu'on peut trouver sur l'hexagone
int nb_items_hexagone (int x, int y, int map[D][D], item_t * Tab_Items, int nb_items){
    int nb_item_possible = 0, i = 0;
    categ_hexa categ;
    hex_t hexagone;

    hexagone = map[x][y];

    switch(hexagone){
        case prairie   : categ = nature;    break;     //prairie
        case foret     : categ = nature;    break;     //foret
        case ville     : categ = urbain;    break;     //ville
        case lac       : categ = nature;    break;     //lac
        case camp_mil  : categ = militaire; break;     //camp mil
        /* -> Absence de l'hexagone camp bandits car ils attaquent immédiatement le joueur */
        case market    : categ = urbain;    break;     //market
        case favella   : categ = urbain;    break;     //favella
        case montagne  : categ = nature;    break;     //montagne
        /* -> Absence de l'hexagone frontiere */
        case mer       : categ = nature;    break;     //mer
        case wasteland : categ = nature;    break;     //wasteland
        default : return 0;
    }

    /* Nombre d'items que l'on peut trouver dans la zone */
    for (i = 0; i < nb_items; i++){
      if(categ == nature){
        if (Tab_Items[i].pc_nature != 0){
          nb_item_possible++;
        }
      }
      if(categ == urbain){
        if (Tab_Items[i].pc_urban != 0){
          nb_item_possible++;
        }
      }
      if(categ == militaire){
        if (Tab_Items[i].pc_military != 0){
          nb_item_possible++;
        }
      }
    }
    return nb_item_possible;
}

/*
void tests_item_generation(int map[D][D], item_t * Tab_Items, int nb_items_available){
  int x = 2, y = 3, x1 = 10, y1 = 5, nb;
  map[x][y] = prairie;
  map[x1][y1] = camp_mil;

  // SIMULATION PRAIRIE
  nb = nb_items_hexagone(x, y, map, Tab_Items, nb_items_available);
  if (nb == 0)
      printf ("ERREUR : nb_items_hexagones = 0");
  else {
      printf("Prairie : %d items possibles (5 attendus)\n", nb);
  }

  // SIMULATION CAMP_MIL
  nb = nb_items_hexagone(x1, y1, map, Tab_Items, nb_items_available);
  if (nb == 0)
      printf ("ERREUR : nb_items_hexagones = 0");
  else {
      printf("Camp mil : %d items possibles (14 attendus)\n", nb);
  }

  if(nb == 5){  //Type Nature
      items_generer(Tab_Items, nb_items_available, nature);
  }
  else{
      if(nb == 15){  //Type Urbain
          items_generer(Tab_Items, nb_items_available, urbain);
      }
      else{  //Type Militaire
          items_generer(Tab_Items, nb_items_available, militaire);
      }
  }
}
*/
/***************************************************************************************************************/
