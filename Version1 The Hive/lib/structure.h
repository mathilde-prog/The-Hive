/**
 * \file structure.h
 * \brief Toutes les fonctions, énumérations, structures, macros du projet
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/


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

/**********************************************************************************/


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
  int quest_id;       /**< Numéro de la quete associé à l'hexagone*/
  categ_hexa categ;   /**< Catégorie hexagone */
  int scavenged;      /**< Indicateur si le joueur a déjà fouillé cet hexagone */
}cell_t;

int coordonnees_valides(int l, int c); 		           		//world_generation.c
void init_border(cell_t map[D][D]);									    //world_generation.c
void quest_init(cell_t map[D][D], int quest_map[6][2]); //world_generation.c
int bordercross(int i, int j, cell_t map[D][D]); 		    //world_generation.c
void topup(cell_t map[D][D]); 												  //world_generation.c
int spawntype(int l, int c, cell_t map[D][D]); 			    //world_generation.c
void nextgen(cell_t map[D][D]); 											  //world_generation.c
void portable_switch(int i, int j, cell_t map[D][D]);   //world_generation.c
void display_TEXT(int l, int c, cell_t map[D][D]); 	    //world_generation.c
void init_base(cell_t map[D][D]); 										  //world_generation.c
void count(const cell_t map[D][D]); 									  //world_generation.c
void display_grid(const cell_t map[D][D]); 					    //world_generation.c
void map_init(cell_t map[D][D], int quest_map[6][2], perso_t player); 	//world_generation.c

/*********************************************************************************/





// suite perso
void display_player_characteristics(cell_t map[D][D], perso_t player); //perso.c

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


void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int cover, int scenario);
npc_t * init_npc(item_t * Tab_Items);
stat_t * init_field();
void show_field(stat_t field);
void turn_npc(npc_t * enemy, stat_t * field, perso_t * player);
int run_away(int position, int distance);
void combat_info(int print_type, perso_t player, npc_t enemy, stat_t field);
int combat(perso_t * player, npc_t * enemy, stat_t * field, item_t * Tab_Items, int nb_items_available);
void loot_enemy (item_t * Tab_Items, int nb_items_available, npc_t * enemy, perso_t * player);

/*********************************************************************************/

/************************************* SCAVENGE **************************************/
void generate_items(item_t * Tab_Items, int nb_items_available, perso_t * player, categ_hexa categ); //scavenge.c
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available);       //scavenge.c
/************************************************************************************/

/************************************* MOVE **************************************/
int move_lose_pa (hex_t type_hexa); 						   //move.c
void look_around(int i, int j, cell_t map[D][D]);  //move.c
void move (perso_t * player, cell_t map[D][D]);		 //move.c
void random_move(perso_t * player, cell_t map[D][D]); //move.c
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
void equip_player(perso_t * player);                        //equipement.c
int nb_equipement(perso_t player);                         //equipment.c
void remove_equipment_player(perso_t * player);             //equipment.c
void manage_equipment(perso_t * player);                    //equipment.c
/**********************************************************************************/

/************************************* FISH  *******************************************/
void fish (perso_t * player, cell_t map[D][D]);   //fish.c
/***************************************************************************************/

/*********************************** EAT_OR_DRINK ***********************************/
void gain_energie(perso_t * player, int val_e);  //eat_or_drink.c
void eat_or_drink (perso_t * player, item_t item);  //eat_or_drink.c
/************************************************************************************/

/*********************************** TURN ******************************************/
void next_turn(perso_t * player); //turn.c
void rest_and_heal(perso_t * player); //turn.c
/************************************************************************************/

/************************************* QUETES *************************************/
/**
	* \struct search_t
	* \brief Structure de suivi de la quete "recherche"
	* \details
        situation = -1 : quete encore non joué
        situation = 0 : quete en cours
        situation = 1 : quete déja joué/fini
        trouve = -1 : la recherche de l'item n'est pas encore active
        trouve = 0 : recherche de l'item est en cours
        trouve = 1 : l'item recherché est trouvé
*/
typedef struct{
    int situation;  /**< Indicateur pour savoir l'avancer du joueur dans la quete "recherche"*/
    item_t wanted;  /**< Item que le joueur doit trouver*/
    int trouve;     /**< Indicateur afin de savoir si l'item a été trouvé*/
    int bunkerX;
    int bunkerY;
}search_t;

/**
	* \struct quete_t
	* \brief Structure de suivi des quetes
	* \details
        int = -1 : quete encore non joué
        int = 0 : quete en cours
        int = 1 : quete déjà joué/fini
        soin = 2 : quete joué le joueur a aide l'homme blessé
        soin = 3 : quete joué le joueur a voulu aider l'homme blessé mais sans succès
*/
typedef struct{
  int soin;             /**< Indicateur pour savoir l'avancer du joueur dans la quete "soin" : si le joueur a aider l'homme blessé : quete "soin" */
  search_t recherche;   /**< Indicateur de type search_t pour savoir l'avancer du joueur dans la quete "recheche" */
  int bunker;           /**< Indicateur pour savoir l'avancer du joueur dans la quete "bunker" */
  int montagne;         /**< Indicateur pour savoir l'avancer du joueur dans la quete "montagne" */
  int frontiere;        /**< Indicateur pour savoir l'avancer du joueur dans la quete "frontiere" */
  int bandits;          /**< Indicateur pour savoir l'avancer du joueur dans la quete "bandits" */
}quete_t;

void init_quete(quete_t * quete, int quest_map[6][2]);                                                                              //quetes.c
int quetes(perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, item_t * Tab_Items, int nb_items_available);   //quetes.c
int quete_montagne(perso_t * player, quete_t * quete);                                                                              //quetes.c
int quete_frontiere(perso_t * player, quete_t * quete);                                                                             //quetes.c
int quete_bunker(perso_t * player, quete_t * quete);                                                                                //quetes.c
int quete_bandits(perso_t * player, quete_t * quete, item_t * Tab_Items, int nb_items_available);                                   //quetes.c

int quete_soin(perso_t * player, quete_t * quete, item_t * Tab_Items);                                          //quete_soin.c
npc_t * init_npc_quete(item_t * Tab_Items, int pers);                                                           //quete_soin.c
int recup_items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card, quete_t * quete);   //quete_soin.c
int aider_homme_blesse(perso_t * player, item_t * pass_card, quete_t * quete, int pers);                        //quete_soin.c

int quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete, quest_map[6][2], item_t * Tab_Items, int nb_items_available);  //quete_search.c
int compter_items_urbain(item_t * Tab_Items, int nb_items_available);                                                                   //quete_search.c
void init_Tab_Items_urbain(item_t * Tab_Items_urbain, item_t * Tab_Items, int nb_items_urbain);                                         //quete_search.c
/***************************************************************************************/

/************************************* BACKUP_AND_LOAD *************************************/
/**
	* \struct sauv_t
	* \brief Structure pour sauvegarder les parties
*/
typedef struct{
  int numPartie;  /**< Numéro de la partie jouée */

  int sauv1_existe; /**< Indicateur si sauvegarde 1 existe */
  int sauv2_existe; /**< Indicateur si sauvegarde 2 existe */
  int sauv3_existe; /**< Indicateur si sauvegarde 3 existe */

  char nomPartie1[21]; /**< Nom de la partie 1 */
  char nomPartie2[21]; /**< Nom de la partie 2 */
  char nomPartie3[21]; /**< Nom de la partie 3 */
} sauv_t;

int sauvegarde_existante(sauv_t sauv);      //backup_and_load.c
void affichage_parties(sauv_t sauv);        //backup_and_load.c
void update_etat_sauvegarde(sauv_t * sauv); //backup_and_load.c
void effacer_partie(sauv_t sauv);           //backup_and_load.c
void save (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv);      //backup_and_load.c
void load (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, sauv_t sauv);  //backup_and_load.c
/*******************************************************************************************/

/********************************* FONCTIONS PRATIQUES ***********************************/
void entree_pour_continuer(); // fonctions_pratiques.c
void clrscr(); //fonctions_pratiques.c
int range(int a,int b); //fonctions_pratiques.c
int rng(int prob); //fonctions_pratiques.c
/*****************************************************************************************/
