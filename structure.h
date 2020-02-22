// structure.h

/************************************* ITEMS *************************************/
typedef enum {armor,weapon,misc,food} type_t; /* types of items available */
typedef enum {none,hand,body,head} equip_t; /* where the player may wear equipment */

typedef struct item_s{
	char name[20];
	type_t type;
 	int attack; 		// value of attack
	int defense; 		// value of defense
	equip_t equipable; 	// indicates whether the player can equip himself with this item and where
} item_t;

int creation_tab_item(item_t * Tab_Items, int * nb_items);
void display_item (item_t item);
/*********************************************************************************/

/************************************* PERSO *************************************/
#define INVENTORY_CAPACITY 10 /* 10 items version 1 */

typedef enum {normal,sprinter,metabolism,luck,scout} skill_t; /* possibilité compétence spéciale */

typedef struct perso_s {
  int pv; // Points de vie
  int pe; // Points d'énergie
  int pa; // Points d'action

  skill_t competence; // Compétence spéciale - dans la version 1 ?

  item_t inventory[INVENTORY_CAPACITY];
  int nb_items_inventory;

  item_t * left_hand; 	/* Pointeur sur item main gauche */
  item_t * right_hand; 	/* Pointeur sur item main droite */
  item_t * body; 				/* Pointeur sur item corps */
  item_t * head;				/* Pointeur sur item tête */

} perso_t;
/**********************************************************************************/

/*********************************** INVENTORY ***********************************/
int indice(perso_t player, item_t item);
int too_much_of_the_same_item(perso_t player, item_t item);
void display_inventory (perso_t player);
void delete_item_in_inventory(perso_t * player, item_t item);
void add_item_to_inventory(perso_t * player, item_t item);
/*********************************************************************************/

/*********************************** EQUIPMENT ***********************************/
#define NOT_EQUIPPED 0
#define LEFT_HAND 1
#define RIGHT_HAND 2
#define BODY 3
#define HEAD 4

void display_equipment_player(perso_t player);
int is_equipped(perso_t player, item_t item);
void swap_equipment_player(perso_t * player, item_t item);
void equip_player(perso_t * player);
void remove_equipment_player(perso_t * player);
/**********************************************************************************/
