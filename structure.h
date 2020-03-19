// structure.h

/************************************* MAP *************************************/
#define ITEMS_MAX 5 // maximum number of items retrievable on a hexagon of the map
#define D 15 				// dimensions of the map

typedef enum {prairie = 1, foret, ville, lac, camp_mil, camp_ban, market, favella, montagne, frontiere, mer, wasteland} hex_t;
typedef enum {other, nature, urbain, militaire} categ_hexa;
// + other : camp_ban + frontiere

typedef struct hex_s{ // structure d'hexagone
  int type;
  int encounter;
  int quest_id;
	int categ;
	char fname[20];
}hex_t;

void clrscr();
int range(int a,int b);
int rng(int prob);
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
void map_init(int map[D][D]);

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
//void tests_item_generation(int map[D][D], item_t * Tab_Items, int nb_items_available); // Fonction pour Anaïs
/*********************************************************************************/

/************************************* PERSO *************************************/
#define INVENTORY_CAPACITY 10 /* 10 items version 1 */

typedef enum {normal,sprinter,metabolism,luck,scout} skill_t;

typedef struct perso_s {
  int pv; // Points de vie
  int pe; // Points d'énergie
  int pa; // Points d'action
	int posX;
	int posY;
	int turns; //nb tours

  skill_t competence; // Compétence spéciale

  item_t inventory[INVENTORY_CAPACITY];
  int nb_items_inventory;

  item_t * left_hand; 	/* Pointeur sur item main gauche */
  item_t * right_hand; 	/* Pointeur sur item main droite */
  item_t * body; 				/* Pointeur sur item corps */
  item_t * head;				/* Pointeur sur item tête */

} perso_t;

void init_player(perso_t * player);
void display_player_characteristics(int map[D][D], perso_t player);

/**********************************************************************************/

/*********************************** INVENTORY ***********************************/
int indice(perso_t player, item_t item);
int too_much_of_the_same_item(perso_t player, item_t item);
void display_inventory (perso_t player);
void delete_item_in_inventory(perso_t * player, item_t item);
int add_item_to_inventory(perso_t * player, item_t item);
void manage_inventory(perso_t * player);
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
void manage_equipment(perso_t * player);
/**********************************************************************************/

/*********************************** EAT_OR_DRINK ***********************************/
void eat_or_drink (perso_t * player, item_t item);
/************************************************************************************/

/*********************************** SCAVENGE ***********************************/
categ_hexa category_hexagon (int map[D][D], int x, int y);
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ);
void scavenge(int map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available);
/************************************************************************************/

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

int backup_exists ();
int init_or_load_game (perso_t * player, int map[D][D]);
/***************************************************************************/
