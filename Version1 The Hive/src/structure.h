// structure.h
typedef struct perso_s perso_t;
typedef struct item_s item_t;

/************************************* MAP *************************************/
#define ITEMS_MAX 5 // maximum number of items retrievable on a hexagon of the map
#define D 15 				// dimensions of the map

typedef enum {prairie = 1, foret, ville, lac, camp_mil, camp_ban, market, favella, montagne, frontiere, mer, wasteland} hex_t;
typedef enum {other, nature, urbain, militaire} categ_hexa;
// other : camp_ban + frontiere

typedef struct cell_s{ // structure d'hexagone
  hex_t type;
  int encounter;
  int quest_id;
	categ_hexa categ;
	char fname[20];
}cell_t;


int coordonnees_valides(int l, int c); 						//world_generation.c
void clrscr(); 																		//world_generation.c
int range(int a,int b); 													//world_generation.c
int rng(int prob); 																//world_generation.c
void init_border(int map[D][D]);									//world_generation.c
int bordercross(int i, int j, int map[D][D]); 		//world_generation.c
void topup(int map[D][D]); 												//world_generation.c
int spawntype(int l, int c, int map[D][D]); 			//world_generation.c
void nextgen(int map[D][D]); 											//world_generation.c
void portable_switch(int i, int j, int map[D][D]); //world_generation.c
void display_TEXT(int l, int c, int map[D][D]); 	//world_generation.c
void init_base(int map[D][D]); 										//world_generation.c
void count(const int map[D][D]); 									//world_generation.c
void display_grid(const int map[D][D]); 					//world_generation.c
void map_init(int map[D][D]); 										//world_generation.c
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
	int index; 					// Index of an item in the inventory (-1 if absent)
} item_t;

int creation_tab_item(item_t * Tab_Items, int * nb_items); //items.c
void display_item (item_t item); //items.c
categ_hexa category_hexagon (int map[D][D], int x, int y); //items.c
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ); //items.c
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

void init_player(perso_t * player); //perso.c
void display_player_characteristics(int map[D][D], perso_t player); //perso.c

/**********************************************************************************/


/************************************* MOVE *************************************/
int move_lose_pa (hex_t type_hexa); 						//move.c
void look_around(int i, int j, int map[D][D]);  //move.c
void move (perso_t * player, int map[D][D]);		//move.c
/*********************************************************************************/


/*********************************** INVENTORY ***********************************/
int map_in_inventory(perso_t player); //inventory.c
int too_much_of_the_same_item(perso_t player, item_t item); //inventory.c
void display_inventory (perso_t player); //inventory.c
void delete_item_in_inventory(perso_t * player, item_t item); //inventory.c
int add_item_to_inventory(perso_t * player, item_t item); //inventory.c
void manage_inventory(perso_t * player); //inventory.c
/*********************************************************************************/


/*********************************** EQUIPMENT ***********************************/
#define NOT_EQUIPPED 0
#define LEFT_HAND 1
#define RIGHT_HAND 2
#define BODY 3
#define HEAD 4

void display_equipment_player(perso_t player); //equipment.c
int is_equipped(perso_t player, item_t item); //equipment.c
void swap_equipment_player(perso_t * player, item_t item); //equipment.c
void equip_player(perso_t * player); //equipment.c
void remove_equipment_player(perso_t * player); //equipment.c
void manage_equipment(perso_t * player); //equipment.c
/**********************************************************************************/


/*********************************** EAT_OR_DRINK ***********************************/
void eat_or_drink (perso_t * player, item_t item); //eat_or_drink.c
/************************************************************************************/


/*********************************** TURN ***********************************/
void next_turn(perso_t * player);
void scavenge(int map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available); //turn.c
void rest_and_heal(perso_t * player); //turn.c
/************************************************************************************/


/*********************************** BACKUP AND LOAD ***********************************/
void save (perso_t player, int map[D][D]); //backup_and_load.c
void save_inventory (perso_t player);			 //backup_and_load.c
void save_info_player (perso_t player);		 //backup_and_load.c
void save_equipment (perso_t player);			 //backup_and_load.c
void save_map (int map[D][D]);						 //backup_and_load.c

int load (perso_t * player, int map[D][D]); //backup_and_load.c
int load_inventory (perso_t * player);			//backup_and_load.c
int load_info_player (perso_t * player);		//backup_and_load.c
int load_equipment (perso_t * player);			//backup_and_load.c
int load_map(int map[D][D]);								//backup_and_load.c

int backup_exists (); //backup_and_load.c
int init_or_load_game (perso_t * player, int map[D][D]); //backup_and_load.c
/***************************************************************************************/


/************************************* EXIT & HELP *************************************/
int exit_game(); //exit_help.c
void help(perso_t * player); //exit_help.c
/***************************************************************************************/
