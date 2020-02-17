//items.c

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

/* creation_tab_item: retrieves items from the file 'items.txt' and stores them in a table passed in parameters
                      displays error message if file 'items.txt' not found
                      returns whether the creation of the items has been successfully completed (0 or 1)
*/
int creation_tab_item(item_t * Tab_Items, int * nb_items){
  * nb_items = 0;
  FILE * fichier = fopen("items.txt","r");

  if(fichier){
    fscanf(fichier,"%s%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable);
    while(!feof(fichier)){
      (*nb_items)++;
      fscanf(fichier,"%s%d%d%d%d",Tab_Items[*nb_items].name, &Tab_Items[*nb_items].type, &Tab_Items[*nb_items].attack, &Tab_Items[*nb_items].defense, &Tab_Items[*nb_items].equipable);
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
    case hand: printf("Equipable (hand)");  break;
    case body: printf("Equipable (body)");  break;
    case head: printf("Equipable (head)");  break;
    default:   printf("unrecognized\n");    break;
  }

	printf("\n");
}

/* display_1_to_5_items: displays 1 to 5 items randomly */
void display_1_to_5_items(item_t * Tab_Items, int nb_items_available){
  int i, nb_items = rand()%5+1;
  item_t item;

  printf("%d random items : ", nb_items);
  for(i = 0; i < nb_items; i++){
    item = Tab_Items[rand()%nb_items_available];
    if((i == nb_items - 1) || (nb_items == 1)){
      printf("%s\n", item.name);
    }
    else {
      printf("%s, ", item.name);
    }
  }
}
