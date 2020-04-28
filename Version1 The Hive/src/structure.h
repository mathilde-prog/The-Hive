/**
 * \file structure.h
 * \brief Toutes les fonctions, énumérations, structures, macros
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/************************************* MAP *************************************/
#define ITEMS_MAX 5 /**< ITEMS_MAX représente le nombre maximum d'items générés sur un hexagone de la carte */
#define D 15 				/**< D représente la dimension de la carte */
#define PT 3 /**< PT (pause time) represente le temps (en secondes) que le texte d'action soit affiche */

/**
  * \enum hex_t
  * \brief Type hexagone
*/
typedef enum {prairie = 1,foret,ville,lac,camp_mil,camp_ban,market,favella,montagne,frontiere,mer,wasteland} hex_t;

/**
  * \enum categ_hexa
  * \brief Catégorie hexagone
*/
typedef enum {other,nature,urbain,militaire} categ_hexa; // other : camp_ban + frontiere + wasteland

/**
	* \struct cell_t
	* \brief Structure pour un hexagone
*/
typedef struct {
  hex_t type;         /**< Type hexagone*/
  int encounter;      /**< Indicateur de rencontre sur cet hexagone */
  int quest_id;       /**< Identifiant quête */
	categ_hexa categ;   /**< Catégorie hexagone */
  int scavenged;      /**< Indicateur si le joueur a déjà fouillé cet hexagone */
}cell_t;

int coordonnees_valides(int l, int c); 		           		//world_generation.c
void clrscr(); 																		      //world_generation.c
int range(int a,int b); 													      //world_generation.c
int rng(int prob); 																      //world_generation.c
void init_border(cell_t map[D][D]);									    //world_generation.c
int bordercross(int i, int j, cell_t map[D][D]); 		    //world_generation.c
void topup(cell_t map[D][D]); 												  //world_generation.c
int spawntype(int l, int c, cell_t map[D][D]); 			    //world_generation.c
void nextgen(cell_t map[D][D]); 											  //world_generation.c
void portable_switch(int i, int j, cell_t map[D][D]);   //world_generation.c
void display_TEXT(int l, int c, cell_t map[D][D]); 	    //world_generation.c
void init_base(cell_t map[D][D]); 										  //world_generation.c
void count(const cell_t map[D][D]); 									  //world_generation.c
void display_grid(const cell_t map[D][D]); 					    //world_generation.c
void map_init(cell_t map[D][D]); 										    //world_generation.c

/*********************************************************************************/

/************************************* ITEMS *************************************/
/**
  * \enum type_t
  * \brief Type item
*/
typedef enum {armor,weapon,misc,food} type_t; /* types of items available */

/**
  * \enum equip_t
  * \brief Zone où un item est équipable
*/
typedef enum {none,hand,body,head} equip_t; 	/* where the player may wear equipment */

/**
	* \struct item_t
	* \brief Structure pour un item
*/
typedef struct {
	char name[20];       /**< Nom item */
	type_t type;         /**< Type item */

 	int attack[3]; 				 /**< Valeur d'attaque */
  int hitchance[3];      /**< A COMPLETER */

	float defense; 				 /**< Valeur de défense */
	equip_t equipable; 	 /**< Indicateur si le joueur peut s'équiper avec cet item et où */                        // indicates whether the player can equip himself with this item and where
	int pc_nature; 			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie nature */    // percentage chance of finding this item in a nature hexagon
	int pc_urban;  			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie urbain */    // percentage chance of finding this item in an urban hexagon
	int pc_military;		 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie militaire */ // percentage chance of finding this item in a military hexagon
	int index; 					 /**< Position de l'item dans l'inventaire du joueur (-1 si absent) */
} item_t;

item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military);
int creation_tab_item(item_t * Tab_Items, int * nb_items); //items.c
void display_item (item_t item); //items.c

/*********************************************************************************/

/************************************* COMBAT *************************************/

typedef struct { // structure to manage battlefield
	int posA;   // position of player
	int posB; // position of bot
	int coverA;
	int coverB;
	int distance; // distance between A and B;
}stat_t;

typedef struct {
  char name[10]; //
  int pv; // Points de vie
  item_t * weapon; 	/* Pointeur sur item dans les mains */
  item_t * armor; 	/* Pointeur sur item armure */
} npc_t;

/*********************************************************************************/

/************************************* PERSO *************************************/

#define INVENTORY_CAPACITY 10 /**< INVENTORY_CAPACITY représente le nombre maximum d'items que peut contenir l'inventaire du joueur (10 items dans la version 1.0) */

//typedef enum {normal,sprinter,metabolism,luck,scout} skill_t;

/**
	* \struct perso_t
	* \brief Structure pour un personnage
*/
typedef struct  {
  int pv;     /**< Points de vie */
  int pe;     /**< Points d'énergie */
  int pa;     /**< Points d'action */
	int posX;   /**< Position X sur la carte */
	int posY;   /**< Position Y sur la carte */
	int turns;  /**< Nombre de tours restants */

//  skill_t competence; /**< Compétence spéciale */

  item_t inventory[INVENTORY_CAPACITY];  /**< Inventaire */
  int nb_items_inventory;  /**< Nombre d'items dans l'inventaire */

  item_t * left_hand; 	/**< Pointeur sur item main gauche */
  item_t * right_hand; 	/**< Pointeur sur item main droite */
  item_t * body; 				/**< Pointeur sur item corps */
  item_t * head;				/**< Pointeur sur item tête */

} perso_t;

void init_player(perso_t * player); //perso.c
void display_player_characteristics(cell_t map[D][D], perso_t player); //perso.c

/**********************************************************************************/

/************************************* SCAVENGE **************************************/
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ); //scavenge.c
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available);       //scavenge.c
/************************************************************************************/

/************************************* MOVE **************************************/
int move_lose_pa (hex_t type_hexa); 						   //move.c
void look_around(int i, int j, cell_t map[D][D]);  //move.c
void move (perso_t * player, cell_t map[D][D]);		 //move.c
/*********************************************************************************/

/*********************************** INVENTORY ***********************************/
void check_the_map(perso_t player, cell_t map[D][D]);         //inventory.c
int item_in_inventory(perso_t player, char * nom_item);       //inventory.c
int too_much_of_the_same_item(perso_t player, item_t item);   //inventory.c
void display_inventory (perso_t player);                      //inventory.c
void delete_item_in_inventory(perso_t * player, item_t item); //inventory.c
int add_item_to_inventory(perso_t * player, item_t item);     //inventory.c
void manage_inventory(perso_t * player);                      //inventory.c
/*********************************************************************************/

/*********************************** EQUIPMENT ***********************************/
#define NOT_EQUIPPED 0 /**< NOT_EQUIPPED indique qu'un item n'est pas équipé */
#define LEFT_HAND 1    /**< LEFT_HAND indique qu'un item est équipé sur la main gauche du joueur */
#define RIGHT_HAND 2   /**< RIGHT_HAND indique qu'un item est équipé sur la main droite du joueur */
#define BODY 3         /**< BODY indique qu'un item est équipé sur le corps du joueur */
#define HEAD 4         /**< HEAD indique qu'un item est équipé sur la tête du joueur */

void display_equipment_player(perso_t player);              //equipment.c
int is_equipped(perso_t player, item_t item);               //equipment.c
void swap_equipment_player(perso_t * player, item_t item);  //equipment.c
void equip_player(perso_t * player);                        //equipment.c
void remove_equipment_player(perso_t * player);             //equipment.c
void manage_equipment(perso_t * player);                    //equipment.c
/**********************************************************************************/

/************************************* FISH  *******************************************/
void fish (perso_t * player, cell_t map[D][D]);   //fish.c
/***************************************************************************************/

/*********************************** EAT_OR_DRINK ***********************************/
void eat_or_drink (perso_t * player, item_t item);  //eat_or_drink.c
/************************************************************************************/

/*********************************** TURN ******************************************/
void next_turn(perso_t * player); //turn.c
void rest_and_heal(perso_t * player); //turn.c
/************************************************************************************/

/*********************************** BACKUP AND LOAD ***********************************/
void save (perso_t player, cell_t map[D][D]);               //backup_and_load.c
void save_inventory (perso_t player);			                  //backup_and_load.c
void save_info_player (perso_t player);		                  //backup_and_load.c
void save_equipment (perso_t player);			                  //backup_and_load.c
void save_map (cell_t map[D][D]);						                //backup_and_load.c

int load (perso_t * player, cell_t map[D][D]);              //backup_and_load.c
int load_inventory (perso_t * player);			                //backup_and_load.c
int load_info_player (perso_t * player);		                //backup_and_load.c
int load_equipment (perso_t * player);			                //backup_and_load.c
int load_map(cell_t map[D][D]);								              //backup_and_load.c

int backup_exists ();                                       //backup_and_load.c
int init_or_load_game (perso_t * player, cell_t map[D][D]); //backup_and_load.c
/***************************************************************************************/

/************************************* EXIT & HELP *************************************/
int exit_game();             //exit_help.c
void help(perso_t * player); //exit_help.c
/***************************************************************************************/


/************************************* QUETES *************************************/
/**
	* \struct quete_t
	* \brief Structure de suivi des quetes
*/
typedef struct{
  int soin;          /**< Indicateur pour savoir si le joueur a aider l'homme blessé : quete "soin" */
  int recherche;     /**< Indicateur pour savoir si le joueur actuellement dans la quete "recheche" */
}quete_t;


int quetes(perso_t * player, cell_t map[D][D]);             //quetes.c
int quete_montagne(perso_t * player);                       //quetes.c
int quete_frontiere(perso_t * player, quete_t * quete);     //quetes.c
int quete_bunker(perso_t * player);                         //quetes.c

npc_t * init_npc_quete(item_t * Tab_Items, int pers);                                                 //quete_soin.c
int ajout_item_blesse(perso_t * player, npc_t * homme, int item);                               //quete_soin.c
int ajout_pass_card(perso_t * player, item_t * pass_card);                                      //quete_soin.c
int menu_choix_ajout_item(perso_t * player, item_t * pass_card, npc_t * homme);                 //quete_soin.c
int recup_1item_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card);    //quete_soin.c
int recup_2items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card);   //quete_soin.c
int recup_3items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card);   //quete_soin.c
int quete_soin(perso_t * player, quete_t * quete);                                              //quete_soin.c
/***************************************************************************************/

/************************************* EXIT & HELP *************************************/
int exit_game();             //exit_help.c
void help(perso_t * player); //exit_help.c
/***************************************************************************************/
