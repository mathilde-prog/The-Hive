/**
 * \file structure.h
 * \brief Toutes les fonctions, énumérations, structures, macros du projet
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

/********************************* FONCTIONS PRATIQUES ***********************************/
void entree_pour_continuer(); // fonctions_pratiques.c
void clrscr(); 								// fonctions_pratiques.c
int range(int a,int b);       // fonctions_pratiques.c
int rng(int prob);            // fonctions_pratiques.c
/*****************************************************************************************/

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
 	int attack[3]; 			 /**< Valeur d'attaque */
  int hitchance[3];    /**< Chance d'attaquer */
	float defense; 			 /**< Valeur de défense */
	equip_t equipable; 	 /**< Indicateur si le joueur peut s'équiper avec cet item et où */
	int pc_nature; 			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie nature */
	int pc_urban;  			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie urbain */
	int pc_military;		 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie militaire */
	int index; 					 /**< Position de l'item dans l'inventaire du joueur (-1 si absent) */
} item_t;

item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military); //items.c
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
  int pa;     /**< Points d'action */
	int pe; /**< Points d'énergie */
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



/**********************************************************************************/

/************************************* MAP *************************************/
#define ITEMS_MAX 5 /**< ITEMS_MAX représente le nombre maximum d'items générés sur un hexagone de la carte */
#define D 15 				/**< D représente la dimension de la carte */
#define PT 3 /**< PT (pause time) represente le temps (en secondes) que le texte d'action soit affiche */

/**
  * \enum hex_t
  * \brief Type hexagone
*/
typedef enum {prairie = 1,foret,ville,lac,camp_mil,camp_ban,market,favela,montagne,frontiere,mer,wasteland} hex_t;

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

void afficher_type_categ_hexa(cell_t map[D][D], int l, int c); //world_generation.c
void informations_map(cell_t map[D][D]); //world_generation.c
int coordonnees_valides(int l, int c); //world_generation.c
void quest_init(cell_t map[D][D], int quest_map[6][2]); //world_generation.c
void display_TEXT(int l, int c, cell_t map[D][D]); 	//world_generation.c
void map_init(cell_t map[D][D], int quest_map[6][2]); //world_generation.c
void portable_switch(int i, int j, cell_t map[D][D]); //world_generation.c
/*********************************************************************************/

// suite perso
void init_player(perso_t * player, cell_t map[D][D]); //perso.c
void display_player_characteristics(cell_t map[D][D], perso_t player); //perso.c

/************************************* COMBAT *************************************/
/**
	* \struct stat_t
	* \brief Structure pour gérer champ de bataille
*/
typedef struct {
	int posA;   	/**< Position du joueur*/
	int posB;   	/**< Position ennemi */
	int coverA; 	/**< Couverture joueur */
	int coverB; 	/**< Couverture ennemi */
	int distance; /**< Distance entre joueur et ennemi */
}stat_t;

/**
	* \struct npc_t
	* \brief Structure pour ennemi (NPC)
*/
typedef struct {
  char name[10]; 		/**< Nom ennemi */
  int pv; 					/**< Points de vie ennemi */
  item_t * weapon; 	/**< Pointeur sur arme */
  item_t * armor; 	/**< Pointeur sur armure */
} npc_t;

npc_t * init_npc(item_t * Tab_Items); //combat.c
stat_t * init_field(); //combat.c
void combat(perso_t * player, npc_t * enemy, stat_t * field, cell_t map[D][D], item_t * Tab_Items, int nb_items_available); //combat.c
/*********************************************************************************/

/************************************* MOVE **************************************/
void move (perso_t * player, cell_t map[D][D]);		 //move.c
void random_move(perso_t * player, cell_t map[D][D]); //move.c
/*********************************************************************************/

/*********************************** INVENTORY ***********************************/
void check_the_map(perso_t player, cell_t map[D][D]);         //inventory.c
int item_in_inventory(perso_t player, char * nom_item);       //inventory.c
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

void display_equipment_player(perso_t player);             //equipment.c
int is_equipped(perso_t player, item_t item);              //equipment.c
int nb_equipement(perso_t player);                         //equipment.c
void manage_equipment(perso_t * player);                   //equipment.c
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

/************************************* QUETES *************************************/
/**
	* \struct search_t
	* \brief Structure de suivi de la quête "recherche"
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
    int bunkerX; 		/**< Coordonnée X du bunker */
    int bunkerY; 		/**< Coordonnée Y du bunker */
}search_t;

/**
	* \struct quete_t
	* \brief Structure de suivi des quetes
	* \details
        int = -1 : quete encore non joué
        int = 0 : quete en cours
        int = 1 : quete déja joué/fini
        soin = 2 : quete joue le joueur a aide l'homme blesse
        soin = 3 : quete joue le joueur a voulu aider l'homme blesse mais sans succes
*/
typedef struct{
  int soin;             /**< Indicateur pour savoir l'avancer du joueur dans la quete "soin" : si le joueur a aider l'homme blessé : quete "soin" */
  search_t recherche;   /**< Indicateur de type search_t pour savoir l'avancer du joueur dans la quete "recheche" */
  int bunker;           /**< Indicateur pour savoir l'avancée du joueur dans la quete "bunker" */
  int montagne;         /**< Indicateur pour savoir l'avancée du joueur dans la quete "montagne" */
  int frontiere;        /**< Indicateur pour savoir l'avancée du joueur dans la quete "frontiere" */
  int bandits;          /**< Indicateur pour savoir l'avancée du joueur dans la quete "bandits" */
}quete_t;

int exit_game(); // quetes.c
void informations_quetes(cell_t map[D][D], int quest_map[6][2], quete_t quete); //quetes.c
void init_quete(quete_t * quete, int quest_map[6][2], item_t * Tab_Items, int nb_items_available); //quetes.c
int quetes(perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, item_t * Tab_Items, int nb_items_available);   //quetes.c
int quete_montagne(perso_t * player, quete_t * quete);  //quetes.c
int quete_frontiere(perso_t * player, quete_t * quete); //quetes.c
int quete_bunker(perso_t * player, quete_t * quete); //quetes.c
int quete_bandits(perso_t * player, quete_t * quete, item_t * Tab_Items, int nb_items_available, cell_t map[D][D]);  //quetes.c
int quete_soin(perso_t * player, quete_t * quete, item_t * Tab_Items); //quete_soin.c
int quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete); //quete_search.c
void affichage_quete_search_en_cours(quete_t quete, cell_t map[D][D], perso_t player); //quete_search.c
int compter_items_urbain(item_t * Tab_Items, int nb_items_available); //quete_search.c
void init_Tab_Items_urbain(item_t * Tab_items_search, item_t * Tab_Items, int nb_items_urbain); //quete_search.c
/***************************************************************************************/

/************************************* SCAVENGE **************************************/
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available, quete_t quete); //scavenge.c
/************************************************************************************/

/************************************* BACKUP_AND_LOAD *************************************/
/**
	* \struct sauv_t
	* \brief Structure pour sauvegarder les parties
*/
typedef struct{
  int numPartie;  		 /**< Numéro de la partie jouée */
  int sauv1_existe; 	 /**< Indicateur si sauvegarde 1 existe */
  int sauv2_existe; 	 /**< Indicateur si sauvegarde 2 existe */
  int sauv3_existe; 	 /**< Indicateur si sauvegarde 3 existe */
  char nomPartie1[21]; /**< Nom de la partie 1 */
  char nomPartie2[21]; /**< Nom de la partie 2 */
  char nomPartie3[21]; /**< Nom de la partie 3 */
} sauv_t;

void sauvegarder_progression(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv); //backup_and_load.c
int sauvegarde_existante(sauv_t sauv);      //backup_and_load.c
void affichage_parties(sauv_t sauv);        //backup_and_load.c
void update_etat_sauvegarde(sauv_t * sauv); //backup_and_load.c
void effacer_partie(sauv_t sauv);           //backup_and_load.c
void save (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv);      //backup_and_load.c
void load (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, sauv_t sauv);  //backup_and_load.c
/*******************************************************************************************/

/************************************* DEMO *************************************/
void demo_afficher_items(perso_t * player, item_t * Tab_Items, int nb_items_available);
/********************************************************************************/
