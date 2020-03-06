//items.c

#include <stdio.h>
#include <stdlib.h>
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

/* display_1_to_5_items: displays 1 to 5 items randomly -- seulement pour TEST*/
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

/***************************************************************************************************************/

/*************************************** GENERATION_ITEMS (ANAIS) **********************************************/
//Renvoie le nombre de d'items qu'on peut trouver sur l'hexagone
int nb_items_hexagone (int x, int y, int map[D][D], item_t * Tab_Items, int nb_items){
    int nb_item_possible = 0, i = 0;
    categ_hexa categ;
    hex_t hexagone;

    if(coordonnees_valides(x,y)){
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
    else {
      printf("Probleme... Coordonnées invalides\n");
      return 0;
    }
}

//Genere les items de façon aleatoires
void items_generer(item_t * Tab_Items, int nb_items, categ_hexa categ){
    int i, r, ok, cpt = 0;

    /*for(i = 0; (i < nb_items) && (cpt < ITEMS_MAX); i++){
        switch(categ){
          case nature:    r = rng(Tab_Items[i].pc_nature);   break;
          case urbain:    r = rng(Tab_Items[i].pc_urban);    break;
          case militaire: r = rng(Tab_Items[i].pc_military); break;
          default: r = 0; break;
        }
        if(r == 1){
          printf("Item %d : %s\n", cpt+1, Tab_Items[i].name);
          cpt++;
        }
    }
    */
    for(i=0; i<ITEMS_MAX; i++){
        r = rand()%nb_items;
        switch(categ){
          case nature:    ok = rng(Tab_Items[r].pc_nature);   break;
          case urbain:    ok = rng(Tab_Items[r].pc_urban);    break;
          case militaire: ok = rng(Tab_Items[r].pc_military); break;
          default: ok = 0; break;
        }
        if (ok == 1){
            cpt++;
            printf("Item %d : %s\n", cpt, Tab_Items[r].name);
        }
    }

    if (cpt != 0) {
        printf("Félicitations, vous venez de trouver %d items !\n", cpt);
    }
    else {
        printf("Désolé, il n'y a rien à récuperer ici...");
    }
}

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
      printf("Camp mil : %d items possibles (13 attendus)\n", nb);
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
/***************************************************************************************************************/
