#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int scenario){ // welp, that's a damagae calculator
  float damage;
  float armor_mod;
  printf("Distance is: %d\n", distance);
  if(scenario==1){
    if(rng(weapon->hitchance[distance-1])){
      if(armor==NULL){
        printf("Damage of the weapon is: %d\n", weapon->attack[distance-1]);
        damage=weapon->attack[distance-1];
      }else{
        printf("Damage of the weapon is: %d\n", weapon->attack[distance-1]);
        printf("Armor name is: %s", armor->name);
        printf("Armor def stat is: %f", armor->defense);
        armor_mod=armor->defense;
        damage=weapon->attack[distance-1]*armor_mod;
      }
      printf("HP before affectation: %d\n", *hp);
      *(hp)=*(hp)-damage;
      printf("HP after affectation: %d\n", *hp);
      printf("Enemy attacked you with %s and dealt %f damage!\n", weapon->name, damage);
    }else{
      printf("Enemy tried to attack you but failed miserably.\n");
    }
  }else{
    if(rng(weapon->hitchance[distance-1])){
      if(armor==NULL){
        damage=weapon->attack[distance-1];
      }else{
        damage=weapon->attack[distance-1]*(armor->defense);
      }
      *(hp)=*(hp)-damage;
      printf("You dealt %f damage to enemy!\n", damage);
    }else{
      printf("You missed. What a dissapointment.\n");
    }
  }
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

stat_t * init_field(){

  stat_t * field=malloc(sizeof(stat_t));
  field->posA=4;
  field->posB=6;
  field->coverA=0;
  field->coverB=0;
  field->distance=field->posB - field->posA;
  return field;
}

void turn_npc(npc_t * enemy, stat_t * field, perso_t * player){
	field->coverB=0;
  field->distance=field->posB-field->posA;
  printf("Distance at the start of the turn: %d\n", field->distance);
	if(strcmp(enemy->weapon->name,"shotgun")){ // ===================== CHECK =====================
			if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=field->posB - field->posA;
        printf("Enemy is moving towards you!\n");
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(60) || field->posB > 7){
					field->posB+=1;
          field->distance=field->posB - field->posA;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1); // TO CODE
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
          }
        }
			}else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB-=1;
          field->distance=field->posB - field->posA;
          printf("Enemy is moving towards you!\n");
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
        }
      }
		}else if(strcmp(enemy->weapon->name,"pistol")){ //
      if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=field->posB - field->posA;
        printf("Enemy is moving towards you!\n");
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(80) || field->posB > 7){
					field->posB+=1;
          field->distance=field->posB - field->posA;
          printf("Enemy is moving away from you!\n");
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB+=1;
          field->distance=field->posB - field->posA;
          printf("Enemy is moving away from you!\n");
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
        }
      }else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
          }
        }
			}
    }else{
      if(field->distance > 1){ // BEHAVIOUR OF NPC WHEN DISTANCE > 1
				field->posB-=1;
        field->distance=field->posB - field->posA;
        printf("Enemy is moving towards you!\n");
			}else{
        if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
        }else{
          if(rng(50)){
            printf("Enemy decided to take cover.\n");
            field->coverB=1;
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, 1);
          }
        }
      }
    }
    printf("Distance at the end of the turn: %d\n", field->distance);
	}

void main(){
  perso_t player;
  player.body=NULL;
  npc_t * enemy;
  stat_t * field;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available;
  for(int i=0; i<50; i++){
    creation_tab_item(Tab_Items, &nb_items_available);
    field=init_field();
    printf("======FIELD======\nPosA: %d\nPosB: %d\nDistance: %d\n==============\n",field->posA, field->posB, field->distance);
    enemy=init_npc(Tab_Items);
    player.pv=100;
    printf("Enemy is armed with %s.\n", enemy->weapon->name);
    turn_npc(&enemy, &field, &player);
    free(enemy);
    free(field);
  }
}
