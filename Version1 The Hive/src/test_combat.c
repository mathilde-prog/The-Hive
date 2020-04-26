#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"

void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int cover, int scenario){ // welp, that's a damagae calculator
  float damage;
  float armor_mod;
  printf("Distance for calculations (not supposed to be affected) is: %d\n", distance);
  if(scenario==1){
    if(rng(weapon->hitchance[distance-1]-(15*cover))){
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


npc_t * init_npc(item_t * Tab_Items){ // everything ok
  npc_t * enemy;
  enemy = malloc(sizeof(npc_t));
  strcpy(enemy->name,"unknown enemy");;
  enemy->weapon=NULL;
  enemy->armor=NULL;
  enemy->pv=0;
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
  return enemy;
}

stat_t * init_field(){

  stat_t * field;
  field=malloc(sizeof(stat_t));
  field->posA=2;
  field->posB=6;
  field->coverA=0;
  field->coverB=0;
  field->distance=(field->posB - field->posA) -1;
  return field;
}


void show_field(stat_t * field){
  printf("======FIELD======\nPosA: %d\nPosB: %d\nDistance: %d\n==============\n",field->posA, field->posB, field->distance);
}

void turn_npc(npc_t * enemy, stat_t * field, perso_t * player){
	field->coverB=0;
  field->distance=field->posB-field->posA -1;
	if(strcmp(enemy->weapon->name,"shotgun") == 0){ // ===================== CHECK =====================
			if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("Enemy is moving towards you!\n");
        show_field(field);
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(60) && field->posB > 7){
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("Enemy is moving away from you!\n");
          show_field(field);
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
          show_field(field);
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1); // TO CODE
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
            show_field(field);
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
          }
        }
			}else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB-=1;
          field->distance=(field->posB - field->posA) -1;
          printf("Enemy is moving towards you!\n");
          show_field(field);
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
          show_field(field);
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }
		}else if(strcmp(enemy->weapon->name,"pistol") == 0){ //
      if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("Enemy is moving towards you!\n");
        show_field(field);
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(80) || field->posB < 7){
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("Enemy is moving away from you!\n");
          show_field(field);
				}else if(rng(30)){
					field->coverB=1;
          printf("Enemy decided to take cover.\n");
          show_field(field);
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("Enemy is moving away from you!\n");
          show_field(field);
        }else if(rng(30)){
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
          show_field(field);
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("Enemy decided to take cover.\n");
            show_field(field);
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
          }
        }
			}
    }else{ // for melee
      if(field->distance>1){
        if(rng(80)){
          field->posB-=1;
          field->distance=(field->posB - field->posA) -1;
          printf("Enemy is moving towards you!\n");
          show_field(field);
        }else{
          field->coverB=1;
          printf("Enemy decided to take cover.\n");
          show_field(field);
        }
      }else if(field->distance==1){
        damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
      }
  }
}

void run_away(int position, int distance){
  if(position!=1){
    if(rng(20*distance)){
      printf("You  managed to run away.\n");
      exit(0); // TO REPLACE
    }else{
      printf("You tried to run away but failed.\n");
    }
  }else{
    if(rng(40*distance)){
      printf("You  managed to run away.\n");
      exit(0); // TO REPLACE
    }else{
      printf("You tried to run away but failed.\n");
    }
  }
}

void combat_info(int print_type, perso_t * player, npc_t * enemy, stat_t * field){
  if(print_type==1){
    printf("Your HP : %d                                                      %d : Enemy HP\nLeft hand: %s\nRight hand: %s\nEnemy weapon: %s\n\n                                Distance: %d                  \n",player->pv, enemy->pv, player->left_hand->name, player->right_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
    printf("Your choise: ");
  }else if(print_type==2){
    printf("Your HP : %d                                                      %d : Enemy HP\nLeft hand: %s\nRight hand: %s\nEnemy weapon: %s\n\n                                Distance: %d                  \n",player->pv, enemy->pv, player->left_hand->name, player->right_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with your weapon.\n5. Try to run away.\n");
    printf("Your choise: ");
  }else if(print_type==3){
    printf("Your HP : %d                                                      %d : Enemy HP\nLeft hand: %s\nRight hand: %s\nEnemy weapon: %s\n\n                                Distance: %d                  \n",player->pv, enemy->pv, player->left_hand->name, player->right_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with your weapon.\n5. Try to run away.\n");
    printf("Your choise: ");
  }
}

void combat(perso_t * player, npc_t * enemy, stat_t * field){
  int choise=9;
  int print_type;
  clrscr();
  if(player->left_hand!=NULL && player->right_hand!=NULL){
    print_type=1;
  }else if(player->left_hand!=NULL && player->right_hand==NULL){
    print_type=2;
  }else if(player->left_hand==NULL && player->right_hand!=NULL){
    print_type=3;
  }else{
    printf("You dont seem to have a weapon, you better just run away pal.\n1. Try to run away.\nYour choise (do you really have one?):");
    scanf("%d", &choise);
    do{
      printf("Come on, you can do it. Try again (press 1): ");
      scanf("%d", &choise);
    }while(choise!=1);
    exit(0);
  }
  while(player->pv>1 && enemy->pv>1){
    field->coverA=0;
    checkpoint:
    clrscr();
    combat_info(print_type, player, enemy, field);
    scanf("%d", &choise);
    if(choise==1){
      if((field->posA+1)<field->posB){
        field->posA+=1;
        field->distance=(field->posB - field->posA) -1;
        clrscr();
        printf("You successfully moved 1 unit closer to your enemy.\n");
        sleep(PT);
      }else{
        clrscr();
        printf("You cant get closer to your enemy, unless you have the ability to pass through matter. Try something else mate.\n");
        sleep(PT);
        goto checkpoint;
      }
    }else if(choise==2){
      if(field->posA-1>0){
        field->posA-=1;
        field->distance=(field->posB - field->posA) -1;
        clrscr();
        printf("You successfully moved 1 unit away from your enemy.\n");
        sleep(PT);
      }else{
        clrscr();
        printf("You reached the battlefield border. You can't go any further. If you want to run away hit corresponding key in the menu.\n");
        sleep(PT);
        goto checkpoint;
      }
    }else if(choise==3){
      clrscr();
      field->coverA=1; printf("You managed to get some cover.\n");
      sleep(PT);
    }else if(choise==4){
      if(player->left_hand!=NULL){
        clrscr();
        damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
        sleep(PT);
      }else if(player->left_hand==NULL && player->right_hand!=NULL){
        clrscr();
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
        sleep(PT);
      }
    }else if(choise==5){
      if(player->left_hand!=NULL && player->left_hand!=NULL){
        clrscr();
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
        sleep(PT);
      }else{
        run_away(field->posA, field->distance);
      }
    }else{
      clrscr();
      printf("Unknown command. Try again.\n");
      sleep(PT);
    }
    clrscr();
    printf("Enemy turn:\n");
    sleep(2);
    turn_npc(enemy,field, player);
    sleep(PT);
  }
}

void main(){
  srand(time(NULL));
  perso_t player;
  npc_t * enemy;
  stat_t * field;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available;
  creation_tab_item(Tab_Items, &nb_items_available);
  field=init_field();
  enemy=init_npc(Tab_Items);
  player.body=NULL;
  player.pv=100;
  player.left_hand=&Tab_Items[0];
  player.right_hand=&Tab_Items[0];
  player.head=NULL;
  printf("======== SOME INFO ============\nEnemy hp: %d\nEnemy weapon: %s\nEnemy armor: %s\n=============================\n",enemy->pv, enemy->weapon->name, enemy->armor->name);
  combat(&player, enemy, field);
  free(enemy);
  free(field);
}
