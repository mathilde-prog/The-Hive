// structure.h

/************************************* MAP *************************************/
#define NB_CATEG 3
#define ITEMS_MAX 5
#define D 15

typedef enum {prairie = 1, foret, ville, lac, camp_mil, camp_ban, market, favella, montagne, frontiere, mer, wasteland} hex_t;
typedef enum {nature, urbain, militaire} categ_hexa;

int coordonnees_valides (int x, int y);
void clrscr(); // fonction pour clear l'output de terminal
int range(int a,int b); // generates random number in range
int rng(int prob); // returns 0 or 1 with a given chance
void init_border(int map[D][D]);
int bordercross(int i, int j, int map[D][D]);
void topup(int map[D][D]);
int spawntype(int l, int c, int map[D][D]);
void nextgen(int map[D][D]);
void portable_switch(int i, int j, int map[D][D]);
void display_TEXT(int l, int c, int map[D][D]);
void init_base(int map[D][D]);
void count(const int map[D][D]);
void display_grid(const int map[D][D]);
void look_around(int i, int j, int map[D][D]);
void map_generation(int map[D][D]);
/*********************************************************************************/

/************************************* ITEMS *************************************/
typedef enum {armor,weapon,misc,food} type_t; /* types of items available */
typedef enum {none,hand,body,head} equip_t; 	/* where the player may wear equipment */

typedef struct item_s{
	char name[20];
	type_t type;
 	int attack; 				// value of attack
	int defense; 				// value of defense
	equip_t equipable; 	// indicates whether the player can equip himself with this item and where

	int pc_nature; 			// Percentage chance of finding this item in a nature hexagon
	int pc_urban;  			// Percentage chance of finding this item in an urban hexagon
	int pc_military;		// Percentage chance of finding this item in a military hexagon
} item_t;

int creation_tab_item(item_t * Tab_Items, int * nb_items);
void display_item (item_t item);
int nb_items_hexagone (int x, int y, int map[D][D], item_t * Tab_Items, int nb_items);
void items_generer(item_t * Tab_Items, int nb_items, categ_hexa categ);
void tests_item_generation(int map[D][D], item_t * Tab_Items, int nb_items_available); // Fonction pour Anaïs
/*********************************************************************************/

/************************************* PERSO *************************************/
#define INVENTORY_CAPACITY 10 /* 10 items version 1 */

typedef enum {normal,sprinter,metabolism,luck,scout} skill_t; /* possibilité compétence spéciale - version1 */

typedef struct perso_s {
  int pv; // Points de vie
  int pe; // Points d'énergie
  int pa; // Points d'action
	int posX;
	int posY;
	int turns; 

  skill_t competence; // Compétence spéciale - dans la version 1 ?

  item_t inventory[INVENTORY_CAPACITY];
  int nb_items_inventory;

  item_t * left_hand; 	/* Pointeur sur item main gauche */
  item_t * right_hand; 	/* Pointeur sur item main droite */
  item_t * body; 				/* Pointeur sur item corps */
  item_t * head;				/* Pointeur sur item tête */

} perso_t;

void display_player_characteristics(perso_t player);
void init_player(perso_t * player);
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

/*********************************** EAT ***********************************/
void eat_or_drink (perso_t * player, item_t item);
/***************************************************************************/

/*********************************** BACKUP AND LOAD ***********************************/
void save (perso_t player, int map[D][D]);
void save_inventory (perso_t player);
void save_info_player (perso_t player);
void save_equipment (perso_t player);
void save_map (int map[D][D]);

int load (perso_t * player, int map[D][D]);
int load_inventory (perso_t * player);
int load_info_player (perso_t * player);
int load_equipment (perso_t * player);
int load_map(int map[D][D]);
/***************************************************************************/
