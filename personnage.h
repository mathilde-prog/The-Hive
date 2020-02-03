
typedef enum {none,sprinter,metabolism,luck,scout} skill_t; /* possibilité compétence spéciale */

typedef enum {armor,weapon,misc,food} item_t; /* possibilité item */

typedef enum {inconnu,bandit,maraudeur,animal,paysan};

typedef struct obj_s{
  char nom[20];
  item_t type;
  int price; // valeur objet

  int attack; // valeur attaque
  int defense; // valeur défense
  int equipped; // indique si le joueur est équipé de cet objet
} obj_t;

typedef struct perso_s {
  int pv; // Points de vie
  int pe; // Points d'énergie
  int pa; // Points d'action
  int karma; // Karma
  int money; // Argent


  skill_t competence; // Compétence spéciale
  int nb_weapons;  // number of weapons : 0, 1 ou 2
  int armor; // armor ? 0 ou 1

} perso_t;

typedef struct npc_s{




} npc_t;
