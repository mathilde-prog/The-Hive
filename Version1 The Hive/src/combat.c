#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

void damage_calculator(item_t * weapon, item_t * armor, int * hp, int distance , int cover, int scenario){ // welp, that's a damagae calculator
  float damage;
  float armor_mod;

  if(scenario==1){
    if(rng(weapon->hitchance[distance-1]-(15*cover))){
      if(armor==NULL){
        //printf("   Damage of the weapon is: %d\n", weapon->attack[distance-1]);
        damage=weapon->attack[distance-1];
      }else{
        //printf("   Damage of the weapon is: %d\n", weapon->attack[distance-1]);
        //printf("   Armor name is: %s", armor->name);
        //printf("   Armor def stat is: %f", armor->defense);
        armor_mod=armor->defense;
        damage=weapon->attack[distance-1]*(armor_mod);
      }

      //printf("   HP before affectation: %d\n", *hp);
      *(hp)=*(hp)-damage;
      //printf("   HP after affectation: %d\n", *hp);
      printf("   Enemy attacked you with %s and dealt %d damage!\n", weapon->name, (int)(damage));
    }else{
      printf("   Enemy tried to attack you but failed miserably.\n");
    }
  }else{
    if(rng(weapon->hitchance[distance-1])){
      if(armor==NULL){
        damage=weapon->attack[distance-1];
      }else{
        damage=weapon->attack[distance-1]*(armor->defense);
      }
      *(hp)=*(hp)-damage;
      printf("   You dealt %d damage to enemy!\n", (int)(damage));
    }else{
      printf("   You missed. What a dissapointment.\n");
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


void show_field(stat_t field){
  printf("\n   ======FIELD======\n   PosA: %d   PosB: %d   Distance: %d\n   ==============\n",field.posA, field.posB, field.distance);
}

void turn_npc(npc_t * enemy, stat_t * field, perso_t * player){
	field->coverB=0;
  field->distance=field->posB-field->posA -1;

	if(strcmp(enemy->weapon->name,"shotgun") == 0){ // ===================== CHECK =====================
			if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   Enemy is moving towards you!\n   The distance between you is now %d units.\n", field->distance);
        //show_field(*field);
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(60) && (field->posB < 6)){  //CHANGEMENT ICI, avant : if(rng(60) && (field->posB > 7)) ??? 2ème condition impossible, non ?
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   Enemy is moving away from you!\n   The distance between you is now %d units.\n", field->distance);
          //show_field(*field);
				}else if(rng(30)){
					field->coverB=1;
          printf("   Enemy decided to take cover.\n");
          //show_field(*field);
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1); // TO CODE
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("   Enemy decided to take cover.\n   The distance between you is now %d units.\n", field->distance);
            //show_field(*field);
          }else{
  					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
          }
        }
			}else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB-=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   Enemy is moving towards you!\n   The distance between you is now %d units.\n", field->distance);
          //show_field(*field);
        }else if(rng(30)){
          field->coverB=1;
          printf("   Enemy decided to take cover.\n");
          //show_field(*field);
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }
		}else if(strcmp(enemy->weapon->name,"pistol") == 0){ //
      if(field->distance > 3){ // BEHAVIOUR OF NPC WHEN DISTANCE > 3
				field->posB-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   Enemy is moving towards you!\n   The distance between you is now %d units.\n", field->distance);
        //show_field(*field);
			}else if(field->distance == 1){ // BEHAVIOUR OF NPC WHEN DISTANCE == 1
				if(rng(80) || (field->posB < 6)){   //CHANGEMENT ICI, avant : if(rng(60) && (field->posB > 7)) ??? 2ème condition impossible, non ?
					field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   Enemy is moving away from you!\n   The distance between you is now %d units.\n", field->distance);
        }else if(rng(30)){
					field->coverB=1;
          printf("   Enemy decided to take cover.\n");
          //show_field(*field);
				}else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
				}
			}else if(field->distance == 2){ // BEHAVIOUR OF NPC WHEN DISTANCE == 3
        if(rng(40)){
          field->posB+=1;
          field->distance=(field->posB - field->posA) -1;
          printf("   Enemy is moving away from you!\n   The distance between you is now %d units.\n", field->distance);
          //show_field(*field);
        }else if(rng(30)){
          field->coverB=1;
          printf("   Enemy decided to take cover.\n");
          //show_field(*field);
        }else{
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }
      }else if(field->distance == 3){ // BEHAVIOUR OF NPC WHEN DISTANCE == 2
				if(enemy->pv > 50){
					damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
        }else{
          if(rng(50)){
            field->coverB=1;
            printf("   Enemy decided to take cover.\n");
            //show_field(*field);
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
          printf("   Enemy is moving towards you!\n   The distance between you is now %d units.\n", field->distance);
          //show_field(*field);
        }else{
          field->coverB=1;
          printf("   Enemy decided to take cover.\n");
          //show_field(*field);
        }
      }else if(field->distance==1){
        damage_calculator(enemy->weapon, player->body, &player->pv, field->distance, field->coverA, 1);
      }
  }
}

int run_away(int position, int distance){
  if(position!=1){
    if(rng(20*distance)){
      printf("   You  managed to run away.\n\n");
      return 1; // TO REPLACE
    }else{
      printf("   You tried to run away but failed.\n");
    }
  }else{
    if(rng(40*distance)){
      printf("   You  managed to run away.\n\n");
      return 1; // TO REPLACE
    }else{
      printf("   You tried to run away but failed.\n");
    }
  }
  return 0;
}

void combat_info(int print_type, perso_t player, npc_t enemy, stat_t field){
  printf("\n   ========================== INFO COMBAT ==========================\n");
  printf("    Your HP : %3d                    Enemy HP : %3d\n",player.pv,enemy.pv);
  (player.left_hand != NULL)  ? printf("    Left hand : %-20s",player.left_hand->name)   : printf("    Left hand : none               ");
  (enemy.weapon != NULL)      ? printf(" Enemy weapon : %-20s\n",enemy.weapon->name)     : printf(" Enemy weapon : none\n");
  (player.right_hand != NULL) ? printf("    Right hand : %-20s",player.right_hand->name) : printf("    Right hand : none               ");
  (enemy.armor != NULL)       ? printf(" Enemy armor : %s\n\n",enemy.armor->name)        : printf(" Enemy armor : none\n\n");
  printf("    Distance: %d\n",field.distance);
  printf("   ==================================================================\n");

  printf("\033[34;01m\n   Menu combat\033[00m\n");
  if(print_type==1){
    printf("   1. Get closer\n   2. Move away\n   3. Get in cover\n   4. Attack with a weapon in your left hand\n   5. Attack with a weapon in your right hand\n   6. Try to run away\n");
  }else if((print_type==2) || (print_type==3)){
    printf("   1. Get closer\n   2. Move away\n   3. Get in cover\n   4. Attack with your weapon\n   5. Try to run away\n");
  }

  printf("\n   Your choise: ");
}

void combat(perso_t * player, npc_t * enemy, stat_t * field){
  int choise, choise_max;
  int print_type;

  if(player->left_hand!=NULL && player->right_hand!=NULL){  // une arme dans chaque main
    print_type=1;
  }else if(player->left_hand!=NULL && player->right_hand==NULL){ // une arme à la main gauche
    print_type=2;
  }else if(player->left_hand==NULL && player->right_hand!=NULL){ // une arme à la main droite
    print_type=3;
  }else{
    printf("   You dont seem to have a weapon, you better just run away pal.\n1. Try to run away.\nYour choise (do you really have one?):");
    do{
      scanf("%d", &choise);
      printf("   Come on, you can do it. Try again (press 1): ");
    }while(choise!=1);
    return;
  }

  choise_max = (print_type == 1) ? 6 : 5; // Nombre de choix proposés dans le menu suivant print_type

  while(player->pv>1 && enemy->pv>1){ // Le joueur ne peut pas mourir au combat ?

    field->coverA=0;
    checkpoint:
    clrscr();
    combat_info(print_type,*player,*enemy,*field);

    // Choix par l'utilisateur (+ vérification)
    do {
      scanf("%d",&choise);
      if((choise < 1) || (choise > choise_max)){
        printf("   Unknown command. Try again : ");
      }
    } while((choise < 1) || (choise > choise_max));

    clrscr();
    printf("\n   \033[1;32mYour turn :\033[00m\n");

    /*
     * GET CLOSER
     */

    if(choise==1){
      if((field->posA+1) < (field->posB-1)){
        field->posA+=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   You successfully moved 1 unit closer to your enemy.");
      }else{
        printf("   You cant get closer to your enemy, unless you have the ability to pass through matter. Try something else mate.\n\n");
        entree_pour_continuer();
        goto checkpoint;
      }
    }

    /*
     * MOVE AWAY
     */
    else if(choise==2){
      if(field->posA-1>0){
        field->posA-=1;
        field->distance=(field->posB - field->posA) -1;
        printf("   You successfully moved 1 unit away from your enemy.\n");
      }else{
        printf("   You reached the battlefield border. You can't go any further. If you want to run away hit corresponding key in the menu.\n");
        entree_pour_continuer();
        goto checkpoint;
      }

    /*
     * GET IN COVER
     */
    }else if(choise==3){
      field->coverA=1; printf("   You managed to get some cover.\n");
    }

    /*
     * print_type 1 = ATTACK WITH A WEAPON IN YOUR LEFT HAND
     * print_type 2 ET 3 = ATTACK WITH YOUR WEAPON
     */
    else if(choise==4){
      if(print_type == 1){
        damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else if(print_type == 2){
        damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else if(print_type == 3){
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
    }

    /*
     * print_type 1 : ATTACK WITH A WEAPON IN YOUR RIGHT HAND
     * print_type 2 ou 3 : TRY TO RUN AWAY
     */
    else if(choise==5){
      if(print_type == 1){
        damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2);
      }
      else {
        if(run_away(field->posA, field->distance)){
          entree_pour_continuer();
          return;
        }
      }
    }

    /*
     * TRY TO RUN AWAY (seulement pour print_type == 1)
     */
    else if(choise==6){
      if(run_away(field->posA, field->distance)){
        entree_pour_continuer();
        return;
      }
    }

    printf("\n\n   \033[1;32mEnnemy turn :\033[00m\n");
    turn_npc(enemy,field, player);
    printf("\n");
    entree_pour_continuer();
  }



}
