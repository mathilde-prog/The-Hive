//items.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "structure.h"

/************************************** CREATION + DISPLAY ITEMS (MATHILDE) **************************************/

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

/**************************************** GENERATION ITEMS (ANAIS) *********************************************/

/* generate_items: generates 0 to 5 items randomly according to the type of hexagon
and the percentage of chance of items appearing on this type of hexagon */
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ){
    int i, ind, present, cpt = 0, choise;
    // Remarque: cpt correspond au nombre d'items qui apparaissent sur l'hexagone

    int ind_items_found[ITEMS_MAX]; // tableau contenant les indices des items trouvés (à quels indices ils sont dans TabItems!)
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
        printf("Félicitation, vous avez trouvé un item : %s\n", Tab_Items[ind_items_found[0]].name);

        do {
          printf("Souhaitez-vous ajouter %s à votre inventaire ? (Oui = 1, Non = 0)\n", Tab_Items[ind_items_found[0]].name);
          scanf("%d",&choise);
          if (choise < 0 || choise > 1){
            printf("Valeur incorrecte. Veuillez resaissir.\n");
          }
        } while(choise < 0 || choise > 1);

        if(choise){
          add_item_to_inventory(player,Tab_Items[ind_items_found[0]]);
          sleep(2);
        }
      }
      // Plusieurs items trouvés
      else {
        printf("Félicitation, vous avez trouvé %d items!\n", cpt);

        do{
          // Affichage des items trouvés
          printf("===== VOUS AVEZ TROUVE ====\n");
          for(i = 0; i < cpt; i++){
            printf("N°%d\t%s\n", i, Tab_Items[ind_items_found[i]].name);
          }
          printf("=========================\n");

          do {
            printf("1. Ajouter un item trouvé dans votre inventaire\n");
            printf("2. Rien récupérer\n");
            scanf("%d",&choise);
            if (choise < 1 || choise > 2){
              printf("Valeur incorrecte. Veuillez resaissir.\n");
            }
          } while(choise < 1 || choise > 2);

          if(choise == 1){
              do {
                printf("Quel item souhaitez-vous ajouter votre inventaire? N°");
                scanf("%d",&choise);
                if (choise < 0 || choise > cpt-1){
                  printf("Valeur incorrecte. Veuillez resaissir.\n");
                }
              } while(choise < 0 || choise > cpt-1);

              if(add_item_to_inventory(player,Tab_Items[ind_items_found[choise]])){
                // Cet item a été ajouté à l'inventaire donc on l'enlève des items trouvés sur cet hexagone
                // Empèche qu'on puisse en ajouter plusieurs!
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
            (cpt == 1) ? printf("Vous ne prenez pas cet item.\n") : printf("Vous ne prenez pas ces items.\n");
            sleep(1);
          }
        } while((choise != 2) && (cpt > 0));
      }
    }
    else{
        printf("Il n'y a rien à récupérer ici...\n");
        sleep(1);
    }
}

/***********************************************************************************************/
