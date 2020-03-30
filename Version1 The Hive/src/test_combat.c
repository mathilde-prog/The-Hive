#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct stat_s{ // structure to manage battlefield
	int posA; // position of player
	int posB; // position of bot
	int coverA;
	int coverB;
	int distance; // distance between A and B;
}stat_t;

typedef struct npc_s {
  char name[10]; //
  int pv; // Points de vie
  item_t * weapon; 	/* Pointeur sur item dans les mains */
  item_t * armor; 	/* Pointeur sur item armure */
} npc_t;


npc_t * init_npc(){
  int i;
  npc_t * enemy;
  enemy = malloc(sizeof(npc_t));
  strcpy(enemy->name,"unknown enemy");;
  enemy->weapon=NULL;
  enemy->armor=NULL;
  enemy->pv=0;
  if(rng(80)){ // 70% de chance que le joueur tombe sur un maraudeur
    strcpy(enemy->name,"maraudeur");
    if(rng(65)){ // 65% de chance que ce marodeur soit de classe "leger"
      enemy->pv=40;
      enemy->armor=NULL;
      if(rng(70)){
        enemy->weapon=&bat;
      }else{
        enemy->weapon=&stick;
      }
    }else if(rng(30)){ // 30% de chance que ce marodeur soit de classe "moyen"
      enemy->pv=80;
      if(rng(30)){
        enemy->weapon=&pistol;
      }else{
        enemy->weapon=&bat;
        enemy->armor=&bulletproof_vest;
      }
    }else{ // 5% de chance que cec marodeur soit de classe "lourd"
      enemy->pv=120;
      enemy->armor=&bulletproof_vest;
      if(rng(5)){
        enemy->weapon=&shotgun;
      }else if(rng(40)){
        enemy->weapon=&pistol;
      }else{
        enemy->weapon=&bat;
      }
    }
  }else{
    strcpy(enemy->name,"chien sauvage");
    enemy->pv=50;
    enemy->weapon=&claws_n_teeth;
  }
  return enemy;
}

void turn_npc(npc_t enemy, stat_t field){
	field.coverB=0;
  field.distance=field.posB-field.posA;
	if(enemy.weapon=shotgun){ // ===================== CHECK =====================
			if(field.distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field.posB--;
        printf("Enemy is moving towards you!\n");
			}else if(field.distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(60) || field.posB > 7){
					field.posB++;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field.coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(&player,&enemy, field, 2); // TO CODE
				}
			}else if(field.distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy.pv > 50){
          damage_calculator(&player,&enemy, field, 2);
        }else{
          if(rng(50)){
            field.coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
            damage_calculator(&player, &enemy, field, 2);
          }
        }
			}else if(field.distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field.posB--;
          printf("Enemy is moving towards you!\n");
        }else if(rng(30)){
          field.coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
          damage_calculator(&player, &enemy, field, 2);
        }
      }
		}else if(enemy.weapon->pistol){ // ===================== CHECK ======================
      if(field.distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field.posB--;
        printf("Enemy is moving towards you!\n");
			}else if(field.distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(80) || field.posB > 7){
					field.posB++;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field.coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(&player,&enemy, field, 2); // TO CODE
				}
			}else if(field.distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field.posB++;
          printf("Enemy is moving away from you!\n");
        }else if(rng(30)){
          field.coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
          damage_calculator(&player, &enemy, field, 2);
        }
      }else if(field.distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy.pv > 50){
          damage_calculator(&player,&enemy, field, 2);
        }else{
          if(rng(50)){
            field.coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
            damage_calculator(&player, &enemy, field, 2);
          }
        }
			}
    }else{
      if(field.distance > 1){ // BEHAVIOUR OF NPC WHEN DISTANCE > 1
				field.posB--;
        printf("Enemy is moving towards you!\n");
			}else{
        if(enemy.pv > 50){
          damage_calculator(&player, &enemy, field, 2);
        }else{
          if(rng(50)){
            field.coverB++;
          }else{
            damage_calculator(&player, &enemy, field, 2);
          }
        }
      }
    }
	}
}
