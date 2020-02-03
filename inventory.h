/* Enumerations and structures for the inventory */

typedef enum {armor,weapon,misc,food} type_t; /* types of items available */

typedef struct item_s{
	char name[20];
	type_t type;
 	int attack; 	// value of attack
	int defense; 	// value of defense
	int equipped; 	// indicates whether the player is equipped with this item.
} item_t;
