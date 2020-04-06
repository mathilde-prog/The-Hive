#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

void damage_calculator(){
  printf("X damage dealt!\n");
}


npc_t * init_npc(item_t * Tab_Items){
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
        enemy->weapon=&Tab_Items[5]; // BASEBALL BAT
      }else{
        enemy->weapon=&Tab_Items[3]; // KNIFE
      }
    }else if(rng(30)){ // 30% de chance que ce marodeur soit de classe "moyen"
      enemy->pv=80;
      if(rng(30)){
        enemy->weapon=&Tab_Items[0]; // PISTOL
      }else{
        enemy->weapon=&Tab_Items[5]; // BASEBALL BAT
        enemy->armor=&Tab_Items[6]; // BULLETPROOF WEST
      }
    }else{ // 5% de chance que cec marodeur soit de classe "lourd"
      enemy->pv=120;
      enemy->armor=&Tab_Items[6]; // VEST
      if(rng(5)){
        enemy->weapon=&Tab_Items[2]; // SHOTGUN;
      }else if(rng(40)){
        enemy->weapon=&Tab_Items[0]; // PISTOL
      }else{
        enemy->weapon=&Tab_Items[5]; // BASEBALL BAT
      }
    }
  }else{
    strcpy(enemy->name,"chien sauvage");
    enemy->pv=50;
    enemy->weapon=&Tab_Items[1];
  }
  return enemy;
}

void turn_npc(npc_t * enemy, stat_t * field){
	field->coverB=0;
  field->distance=field->posB-field->posA;
	if(enemy->weapon->name=="shotgun"){ // ===================== CHECK =====================
			if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB--;
        printf("Enemy is moving towards you!\n");
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(60) || field->posB > 7){
					field->posB++;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(); // TO CODE
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
          damage_calculator();
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
            damage_calculator();
          }
        }
			}else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB--;
          printf("Enemy is moving towards you!\n");
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
          damage_calculator();
        }
      }
		}else if(enemy->weapon->name=="pistol"){ //
      if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB--;
        printf("Enemy is moving towards you!\n");
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(80) || field->posB > 7){
					field->posB++;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(); // TO CODE
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB++;
          printf("Enemy is moving away from you!\n");
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
          damage_calculator();
        }
      }else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
          damage_calculator();
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
            damage_calculator();
          }
        }
			}
    }else{
      if(field->distance > 1){ // BEHAVIOUR OF NPC WHEN DISTANCE > 1
				field->posB--;
        printf("PEPEGAEnemy is moving towards you!\n");
			}else{
        if(enemy->pv > 50){
          damage_calculator();
        }else{
          if(rng(50)){
            field->coverB++;
          }else{
            damage_calculator();
          }
        }
      }
    }
	}

void main(){
  npc_t * enemy;
  stat_t field;
  stat_t * p_field;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available;
  creation_tab_item(Tab_Items, &nb_items_available);
  enemy=init_npc(Tab_Items);
  turn_npc(&enemy, &p_field);
  free(enemy);
}
