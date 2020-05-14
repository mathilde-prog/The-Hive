/**
 * \file commun.h
 * \brief Tous les prototypes de fonctions, énumérations, structures, macros appelés dans plusieurs fichiers du projet
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>

/*
 * FONCTIONS PRATIQUES (fonctions_pratiques.c)
 */
void entree_pour_continuer();
void clrscr();
int range(int a,int b);
int rng(int prob);

/*
 * ITEMS (items.c)
 */

/**
  * \enum type_t
  * \brief Type d'un item
*/
typedef enum {
	armor, 	/*!< Armure */
	weapon, /*!< Arme */
	misc, 	/*!< Objet divers */
	food 		/*!< Nourriture  */
} type_t;

/**
  * \enum equip_t
  * \brief Zone où un item est équipable
*/
typedef enum {
	none, /*!< Pas équipable */
	hand, /*!< Main */
	body, /*!< Corps */
	head /*!< Tête */
} equip_t;

/**
	* \struct item_t
	* \brief Structure pour un item
*/
typedef struct {
	char name[20];       /**< Nom item */
	type_t type;         /**< Type item */
 	int attack[3]; 			 /**< Valeurs d'attaque */
  int hitchance[3];    /**< Chances d'attaquer */
	float defense; 			 /**< Valeur de défense */
	equip_t equipable; 	 /**< Indicateur si le joueur peut s'équiper avec cet item et où */
	int pc_nature; 			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie nature */
	int pc_urban;  			 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie urbain */
	int pc_military;		 /**< Pourcentage de chance de trouver cet item dans un hexagone de catégorie militaire */
	int index; 					 /**< Position de l'item dans l'inventaire du joueur (-1 si absent) */
} item_t;

item_t * creer_item (char * chaine, type_t type, int attack0, int attack1, int attack2, int hitchance0, int hitchance1, int hitchance2, float defense, int equipable, int pc_nature, int pc_urban, int pc_military);
int creation_tab_item(item_t * Tab_Items, int * nb_items);
void display_item (item_t item);

/*
 * JOUEUR (perso.c) -- partie 1
 */

#define INVENTORY_CAPACITY 10 /**< INVENTORY_CAPACITY représente le nombre maximum d'items que peut contenir l'inventaire du joueur (10 items dans la version 1.0) */

/**
	* \struct perso_t
	* \brief Structure pour un personnage
*/
typedef struct  {
  int pv;     /**< Points de vie */
  int pa;     /**< Points d'action */
	int pe; 		/**< Points d'énergie */
	int posY;   /**< Position Y (ligne) sur la carte */
	int posX;   /**< Position X (colonne) sur la carte */
	int turns;  /**< Nombre de tours restants */
  item_t inventory[INVENTORY_CAPACITY];  /**< Inventaire */
  int nb_items_inventory;  /**< Nombre d'items dans l'inventaire */
  item_t * left_hand; 		 /**< Pointeur sur item porté à la main gauche */
  item_t * right_hand; 	   /**< Pointeur sur item porté à la main droite */
  item_t * body; 				   /**< Pointeur sur item porté le corps */
  item_t * head;				   /**< Pointeur sur item porté sur la tête */
} perso_t;


/*
 * CARTE (world_generation.c)
 */

#define ITEMS_MAX 5 /**< ITEMS_MAX représente le nombre maximum d'items générés sur un hexagone de la carte */
#define D 15 				/**< D représente la dimension de la carte */

/**
  * \enum hex_t
  * \brief Type d'un hexagone
*/
typedef enum {
	prairie = 1, 		/*!< Prairie */
	foret, 					/*!< Forêt */
	ville, 					/*!< Ville */
	lac, 						/*!< Lac */
	camp_mil,     	/*!< Camp militaire */
	camp_ban,     	/*!< Camp des bandits  */
	market,       	/*!< Marché */
	favela, 				/*!< Favela */
	montagne,       /*!< Montagne */
	frontiere,			/*!< Frontière */
	mer,						/*!< Mer */
	wasteland				/*!< Wasteland (terres abandonnées) */
} hex_t;

/**
  * \enum categ_hexa
  * \brief Catégorie hexagone
*/
typedef enum {
	other, 		/*!< Autre : camp des bandits, frontière et wasteland */
	nature,		/*!< Nature : prairie, forêt, lac, montagne, mer */
	urbain, 	/*!< Urbain : ville, marché, favela */
	militaire /*!< Militaire : camp militaire */
} categ_hexa;

/**
	* \struct cell_t
	* \brief Structure pour un hexagone
*/
typedef struct {
  hex_t type;         /**< Type d'hexagone*/
  int encounter;      /**< Indicateur de combat sur cet hexagone */
  int quest_id;       /**< Identifiant quête associé à l'hexagone*/
  categ_hexa categ;   /**< Catégorie d'hexagone */
  int scavenged;      /**< Indicateur si le joueur a déjà fouillé l'hexagone */
}cell_t;

void afficher_type_categ_hexa(cell_t map[D][D], int l, int c);
void informations_map(cell_t map[D][D]);
int coordonnees_valides(int l, int c);
void quest_init(cell_t map[D][D], int quest_map[6][2]);
void display_TEXT(int l, int c, cell_t map[D][D]);
void map_init(cell_t map[D][D], int quest_map[6][2]);
void portable_switch(int i, int j, cell_t map[D][D]);

/*
 * JOUEUR (perso.c) -- partie 2
 */

void init_player(perso_t * player, cell_t map[D][D]);
void display_player_characteristics(cell_t map[D][D], perso_t player);

/*
 * COMBAT (combat.c)
 */

/**
	* \struct stat_t
	* \brief Structure pour un champ de bataille
*/
typedef struct {
	int posA;   	/**< Position joueur*/
	int posB;   	/**< Position l'ennemi */
	int coverA; 	/**< Couverture joueur */
	int coverB; 	/**< Couverture l'ennemi */
	int distance; /**< Distance entre le joueur et l'ennemi */
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

npc_t * init_npc(item_t * Tab_Items);
stat_t * init_field();
void combat(perso_t * player, npc_t * enemy, stat_t * field, cell_t map[D][D], item_t * Tab_Items, int nb_items_available);

/*
 * DEPLACEMENT JOUEUR (move.c)
 */

void move (perso_t * player, cell_t map[D][D]);
void random_move(perso_t * player, cell_t map[D][D]);

/*
 * INVENTAIRE (inventory.c)
 */
void eat_or_drink (perso_t * player, item_t item);
void check_the_map(perso_t player, cell_t map[D][D]);
int item_in_inventory(perso_t player, char * nom_item);
void display_inventory (perso_t player);
void delete_item_in_inventory(perso_t * player, item_t item);
int add_item_to_inventory(perso_t * player, item_t item);
void manage_inventory(perso_t * player);

/*
 * EQUIPEMENT (equipment.c)
 */

#define NOT_EQUIPPED 0 /**< NOT_EQUIPPED indique qu'un item n'est pas équipé */
#define LEFT_HAND 1    /**< LEFT_HAND indique qu'un item est équipé sur la main gauche du joueur */
#define RIGHT_HAND 2   /**< RIGHT_HAND indique qu'un item est équipé sur la main droite du joueur */
#define BODY 3         /**< BODY indique qu'un item est équipé sur le corps du joueur */
#define HEAD 4         /**< HEAD indique qu'un item est équipé sur la tête du joueur */

void display_equipment_player(perso_t player);
int is_equipped(perso_t player, item_t item);
int nb_equipement(perso_t player);
void manage_equipment(perso_t * player);

/*
 * PECHER (fish.c)
 */
void fish (perso_t * player, cell_t map[D][D]);

/*
 * TOUR DU JEU (turn.c)
 */
void next_turn(perso_t * player);
void rest_and_heal(perso_t * player);

/*
 * QUETES
 */

/**
	* \struct search_t
	* \brief Structure de suivi de la quête "recherche"
	* \details
        - situation = -1 : quête encore non jouée
        - situation = 0 : quête en cours
        - situation = 1 : quête déjà jouée/finie
        - trouve = -1 : la recherche de l'item n'est pas encore activée
        - trouve = 0 : la recherche de l'item est en cours
        - trouve = 1 : l'item recherché est trouvé
*/
typedef struct{
    int situation;  /**< Indicateur pour savoir l'avancée du joueur dans la quête "recherche"*/
    item_t wanted;  /**< Item que le joueur doit trouver*/
    int trouve;     /**< Indicateur afin de savoir si l'item a été trouvé*/
    int bunkerY; 		/**< Coordonnée Y (ligne) du bunker */
    int bunkerX; 		/**< Coordonnée X (colonne) du bunker */
}search_t;

/**
	* \struct quete_t
	* \brief Structure de suivi des quêtes
	* \details
      -  int = -1 : quête encore non jouée
      -  int = 0 : quête en cours
      -  int = 1 : quête déja jouée/finie
      -  soin = 2 : quête jouée le joueur a aide l'homme blesse
      -  soin = 3 : quête jouée le joueur a voulu aider l'homme blesse mais sans succes
*/
typedef struct{
  int soin;             /**< Indicateur pour savoir l'avancée du joueur dans la quête "soin", si le joueur a aidé l'homme blessé */
  search_t recherche;   /**< Indicateur de type search_t pour savoir l'avancée du joueur dans la quête "recheche" */
  int bunker;           /**< Indicateur pour savoir l'avancée du joueur dans la quête "bunker" */
  int montagne;         /**< Indicateur pour savoir l'avancée du joueur dans la quête "montagne" */
  int frontiere;        /**< Indicateur pour savoir l'avancée du joueur dans la quête "frontiere" */
  int bandits;          /**< Indicateur pour savoir l'avancée du joueur dans la quête "bandits" */
} quete_t;

// quetes.c
int exit_game();
void informations_quetes(cell_t map[D][D], int quest_map[6][2], quete_t quete);
void init_quete(quete_t * quete, int quest_map[6][2], item_t * Tab_Items, int nb_items_available);
int quetes(perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, item_t * Tab_Items, int nb_items_available);
int quete_montagne(perso_t * player, quete_t * quete);
int quete_frontiere(perso_t * player, quete_t * quete);
int quete_bunker(perso_t * player, quete_t * quete);
int quete_bandits(perso_t * player, quete_t * quete, item_t * Tab_Items, int nb_items_available, cell_t map[D][D]);

// quete_soin.c
int quete_soin(perso_t * player, quete_t * quete, item_t * Tab_Items);

// quete_search.c
int quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete);
void affichage_quete_search_en_cours(quete_t quete, cell_t map[D][D], perso_t player);
int compter_items_urbain(item_t * Tab_Items, int nb_items_available);
void init_Tab_Items_urbain(item_t * Tab_items_search, item_t * Tab_Items, int nb_items_urbain);

/*
 * SCAVENGE (items.c)
 */
void scavenge(cell_t map[D][D], perso_t * player, item_t * Tab_Items, int nb_items_available, quete_t quete);

/*
 * SAUVEGARDE ET CHARGEMENT (backup_and_load.c)
 */

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

void sauvegarder_progression(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv);
int sauvegarde_existante(sauv_t sauv);
void affichage_parties(sauv_t sauv);
void update_etat_sauvegarde(sauv_t * sauv);
void effacer_partie(sauv_t sauv);
void save (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv);
void load (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, sauv_t sauv);
/*******************************************************************************************/

/*
 * DEMO (demo.c)
 */
void demo_afficher_items(perso_t * player, item_t * Tab_Items, int nb_items_available);


/*
 * INTERFACE GRAPHIQUE
 */ 

#define N 13
void init_map_essai(int mapint[N][N]);
void map_correspondance(cell_t map_cell[D][D], int mapaff[N][N], int position_x, int position_y);
void relation_hexa_char(char*mapchar[], int mapint[][N]);
void affichage_case_centrale(SDL_Renderer *renderer);
void affichage_map(SDL_Renderer *renderer, char *map[], int maptest[N][N], cell_t map1[D][D], perso_t player);
int interface();

void affichage_personnage(SDL_Renderer *renderer, char *img_perso, int x, int y);
int combat_bis(TTF_Font *police/*, stat_t * combat_stats, npc_t * npc*/);
void affichage_help();

int monscanf(char * c);
int testscanf();
