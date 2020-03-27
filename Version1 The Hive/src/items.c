//items.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "structure.h"

/************************************** CREATION + DISPLAY ITEMS (MATHILDE) **************************************/
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

/**************************************** GENERATION ITEMS (ANAIS) *********************************************/

/* generate_items: generates 0 to 5 items randomly according to the type of hexagon
and the percentage of chance of items appearing on this type of hexagon */
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ){
    int i, ind, present, cpt = 0, choise;
    // Remarque: cpt correspond au nombre d'items qui apparaissent sur l'hexagone

    int ind_items_found[ITEMS_MAX]; // tableau contenant les indices des items trouv�s (� quels indices ils sont dans TabItems!)
    // On initialise tout le tableau � -1 (Pourquoi -1 ? Signifie non-pr�sent dans Tab_Items)
    for(i = 0; i < ITEMS_MAX; i++){
      ind_items_found[i] = -1;
    }

    // G�n�ration al�atoire de 0 � ITEMS_MAX items
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

    // Si items g�n�r�s
    if (cpt != 0){
      // Cas 1 item
      if(cpt == 1){
        printf("Congratulations, you found %d item : %s\n", cpt, Tab_Items[ind_items_found[0]].name);

        do {
          printf("Do you want to add %s to your inventory ? (Yes = 1, No = 0)\n", Tab_Items[ind_items_found[0]].name);
          scanf("%d",&choise);
          if (choise < 0 || choise > 1){
            printf("Incorrect value. Please re-enter.\n");
          }
        } while(choise < 0 || choise > 1);

        if(choise){
          add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
          sleep(2);
        }
      }
      // Plusieurs items trouves
      else {
        printf("Congratulations, you just found %d items!\n", cpt);

        do{
          // Affichage des items trouv�s
          printf("===== YOU HAVE FOUND ====\n");
          for(i = 0; i < cpt; i++){
            printf("N�%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
          }
          printf("=========================\n");

          do {
            printf("1. Add an item to my inventory\n");
            printf("2. Retrieve no items\n");
            scanf("%d",&choise);
            if (choise < 1 || choise > 2){
              printf("Incorrect value. Please re-enter.\n");
            }
          } while(choise < 1 || choise > 2);

          if(choise == 1){
              do {
                printf("Which item do you want to add to your inventory? N�");
                scanf("%d",&choise);
                if (choise < 0 || choise > cpt-1){
                  printf("Incorrect value. Please re-enter.\n");
                }
              } while(choise < 0 || choise > cpt-1);

              if(add_item_to_inventory(player,Tab_Items[ind_items_found[choise]])){
                // Cet item a �t� ajout� � l'inventaire donc on l'enl�ve des items trouv�s sur cet hexagone
                // Emp�che qu'on puisse en ajouter plusieurs!
                i = choise;
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
            (cpt == 1) ? printf("You don't take this item.\n") : printf("You don't take these items.\n");
            sleep(1);
          }
        } while((choise != 2) && (cpt > 0));
      }
    }
    else{
        printf("There's nothing to pick up here...\n");
        sleep(1);
    }
}

/***********************************************************************************************/
