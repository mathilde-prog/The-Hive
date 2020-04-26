void combat(perso_t * player, npc_t * enemy, stat_t * field){
  int choise=9;
  clrscr();
  if(player->left_hand!=NULL && player->right_hand!=NULL){
    printf("Your HP: %d                               Enemy HP: %d\nWeapon in your left hand: %s                      Weapon in your right hand: %s\nEnemy weapon: %s\n\n                                Distance: %d                  \n",player->pv, enemy->pv, player->left_hand->name, player->right_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
    printf("Your choise: ");
  }else if(player->left_hand!=NULL && player->right_hand==NULL){
    printf("Your HP: %d                               Enemy HP: %d\nYour weapon: %s                      Enemy weapon: %s\n\n                              Distance: %d                  \n", player->pv, enemy->pv, player->left_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
    printf("Your choise: ");
  }else if(player->left_hand==NULL && player->right_hand!=NULL){
    printf("Your HP: %d                               Enemy HP: %d\nYour weapon: %s                      Enemy weapon: %s\n\n                              Distance: %d                  \n", player->pv, enemy->pv, player->right_hand->name, enemy->weapon->name, field->distance);
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with your weapon.\n5. Try to run away.\n");
    printf("Your choise: ");
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
    printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
    printf("Your choise: ");
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
        printf("You reached the battlefield border. You can't go any further. If you wany to run away hit corresponding key in the menu.\n");
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
  }
}


void combat(perso_t * player, npc_t * enemy, stat_t * field){
  int choise=9;
  printf("Your turn.\n");
  if(player->left_hand!=NULL && player->left_hand!=NULL){
    printf("Your HP: %d                               Enemy HP: %d\nWeapon in your left hand: %s                      Weapon in your right hand: %s\nEnemy weapon: %s\n\n                                Distance: %d                  \n",player->pv, enemy->pv, player->left_hand->name, player->right_hand->name, enemy->weapon->name, field->distance);
    while(player->pv>1 && enemy->pv>1){
      field->coverA=0;
      printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
      printf("Your choise: ");
      checkpoint:
      scanf("%d", &choise);
      switch(choise){
        case 1: field->posA+=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit closer to your enemy.\n"); break;
        case 2: field->posA-=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit away from your enemy.\n"); break;
        case 3: field->coverA=1; printf("You managed to get to cover.\n"); break;
        case 4: damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2); break;
        case 5: damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2); break;
        case 6: run_away(field->posA, field->distance); break;
        default: printf("You sure you didn't missclick? Try again: \n"); goto checkpoint; break;
      }
      turn_npc(enemy,field, player);
    }
  }else if(player->left_hand!=NULL && player->right_hand==NULL){
      printf("Your HP: %d                               Enemy HP: %d\nYour weapon: %s                      Enemy weapon: %s\n\n                              Distance: %d                  \n", player->pv, enemy->pv, player->left_hand->name, enemy->weapon->name, field->distance);
      while(player->pv>1 && enemy->pv>1){
        field->coverA=0;
        printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with a weapon in your left hand.\n5. Attack with a weapon in your right hand.\n5. Try to run away.\n");
        printf("Your choise: ");
        checkpoint_1:
        scanf("%d", &choise);
        switch(choise){
          case 1: field->posA+=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit closer to your enemy.\n"); break;
          case 2: field->posA-=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit away from your enemy.\n"); break;
          case 3: field->coverA=1; printf("You managed to get to cover.\n"); break;
          case 4: damage_calculator(player->left_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2); break;
          case 5: run_away(field->posA, field->distance); break;
          default: printf("You sure you didn't missclick? Try again: \n"); goto checkpoint_1; break;
        }
        turn_npc(enemy,field, player);
      }
    }else if(player->left_hand==NULL && player->right_hand!=NULL){
      printf("Your HP: %d                               Enemy HP: %d\nYour weapon: %s                      Enemy weapon: %s\n\n                              Distance: %d                  \n", player->pv, enemy->pv, player->right_hand->name, enemy->weapon->name, field->distance);
      while(player->pv>1 && enemy->pv>1){
        field->coverA=0;
        printf("1. Get closer.\n2. Move away.\n3. Get in cover.\n4. Attack with your weapon.\n5. Try to run away.\n");
        printf("Your choise: ");
        checkpoint_2:
        scanf("%d", &choise);
        switch(choise){
          case 1: field->posA+=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit closer to your enemy.\n"); break;
          case 2: field->posA-=1; field->distance=(field->posB - field->posA) -1; printf("You successfully moved 1 unit away from your enemy.\n"); break;
          case 3: field->coverA=1; printf("You managed to get to cover.\n"); break;
          case 4: damage_calculator(player->right_hand, enemy->armor, &enemy->pv, field->distance, field->coverB, 2); break;
          case 6: run_away(field->posA, field->distance); break;
          default: printf("You sure you didn't missclick? Try again: \n"); goto checkpoint_2; break;
        }
        turn_npc(enemy,field, player);
      }
    }else{
      printf("You dont seem to have a weapon, you better just run away pal.\n");
      exit(0);
    }
  }
