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
      Tab_Items[*nb_items].index = -1;
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
	printf("\nITEM: %s\n",item.name);
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
  printf("pc_military = %d\n\n", item.pc_military);
}

/***************************************************************************************************************/
