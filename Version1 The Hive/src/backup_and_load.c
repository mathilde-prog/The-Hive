#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file backup_and_load.c
 * \brief Sauvegarde et chargement d'une partie
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version 1.0
 * \date 2020
*/
void sauvegarder_progression(perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv){
  int rep;

  clrscr();
  save(player,map,quest_map,quete,sauv);
  printf("   \n   Votre progression a été sauvegardée !\n");
  printf("\n   Un choix s'offre à vous : \n");
  printf("   1. Continuer le jeu\n");
  printf("   2. Quitter le jeu\n");
  printf("\n   Votre réponse : ");
  do {
    scanf("%d",&rep);
    if(rep < 1 || rep > 2){
      printf("   Valeur incorrecte. Veuillez ressaisir : ");
    }
  } while (rep < 1 || rep > 2);

  clrscr();
  if(rep == 2){
    exit(1);
  }
}

/**
 * \fn int sauvegarde_existante(sauv_t sauv)
 * \brief Indique s'il existe une sauvegarde pour la partie choisie par l'utilisateur
 * \param sauv_t sauv
 * \return Un \a int : 1 si une sauvegarde existe. 0 sinon.
*/
int sauvegarde_existante(sauv_t sauv){
  switch(sauv.numPartie){
    case 1: return sauv.sauv1_existe;
    case 2: return sauv.sauv2_existe;
    case 3: return sauv.sauv3_existe;
    default: return 0;
  }
}

/**
 * \fn void affichage_parties(sauv_t sauv)
 * \brief Affiche les parties sauvegardées
 * \param sauv_t sauv
 * \return Rien
*/
void affichage_parties(sauv_t sauv){
  printf("\n   +-----+-----+-----+-----+-----+\n");
  printf("   |  1  |%20s   |\n",sauv.nomPartie1);
  printf("   +-----+-----+-----+-----+-----+\n\n");
  printf("   +-----+-----+-----+-----+-----+\n");
  printf("   |  2  |%20s   |\n",sauv.nomPartie2);
  printf("   +-----+-----+-----+-----+-----+\n\n");
  printf("   +-----+-----+-----+-----+-----+\n");
  printf("   |  3  |%20s   |\n",sauv.nomPartie3);
  printf("   +-----+-----+-----+-----+-----+\n\n");
}

/**
 * \fn void update_etat_sauvegarde(sauv_t * sauv)
 * \brief Met à jour l'état des sauvegardes (si elles existent et leurs noms)
 * \param sauv_t * sauv
 * \return Rien
*/
void update_etat_sauvegarde(sauv_t * sauv){
  FILE * sauv1, * sauv2, * sauv3;
  sauv1 = fopen("../sauv/sauv1.csv","r");
  sauv2 = fopen("../sauv/sauv2.csv","r");
  sauv3 = fopen("../sauv/sauv3.csv","r");

  if(sauv1){
    sauv->sauv1_existe = 1;
    fscanf(sauv1," %[^\n]",sauv->nomPartie1);
    fclose(sauv1);
  }
  else {
    sauv->sauv1_existe = 0;
    strcpy(sauv->nomPartie1,"Nouvelle partie");
  }

  if(sauv2){
    sauv->sauv2_existe = 1;
    fscanf(sauv2," %[^\n]",sauv->nomPartie2);
    fclose(sauv2);
  }
  else {
    sauv->sauv2_existe = 0;
    strcpy(sauv->nomPartie2,"Nouvelle partie");
  }

  if(sauv3){
    sauv->sauv3_existe = 1;
    fscanf(sauv3," %[^\n]",sauv->nomPartie3);
    fclose(sauv3);
  }
  else {
    sauv->sauv3_existe = 0;
    strcpy(sauv->nomPartie3,"Nouvelle partie");
  }
}

/**
 * \fn void effacer_partie(sauv_t sauv)
 * \brief Efface une partie
 * \param sauv_t sauv
 * \return Rien
*/
void effacer_partie(sauv_t sauv){
  int choix;

  if((!sauv.sauv1_existe) && (!sauv.sauv2_existe) && (!sauv.sauv3_existe)){
      printf("\n   Aucune partie à supprimer\n");
      sleep(1);
  }
  else {
    choix:
    clrscr();
    affichage_parties(sauv);
    printf("   Quelle partie souhaitez-vous effacer ?\n");
    printf("   Retour au menu: -1\n\n");
    printf("   Votre choix : ");
    do {
      scanf("%d",&choix);
      if((choix != -1) && (choix < 1 || choix > 3)){
        printf("   Valeur incorrecte. Veuillez ressaisir : ");
        sleep(1);
      }
    } while((choix != -1) && (choix < 1 || choix > 3));

    if(choix == 1){
      if(sauv.sauv1_existe){
        printf("   Partie %s effacée\n", sauv.nomPartie1);
        remove("../sauv/sauv1.csv");
        update_etat_sauvegarde(&sauv);
      }
      else {
        printf("   Pas de sauvegarde pour cette partie. Rien à effacer.\n");
        sleep(1);
        goto choix;
      }
    }
    else if(choix == 2){
      if(sauv.sauv2_existe){
        printf("   Partie %s effacée\n", sauv.nomPartie2);
        remove("../sauv/sauv2.csv");
        update_etat_sauvegarde(&sauv);
      }
      else {
        printf("   Pas de sauvegarde pour cette partie. Rien à effacer.\n");
        sleep(2);
        goto choix;
      }
    }
    else if(choix == 3){
      if(sauv.sauv3_existe){
        printf("   Partie %s effacée\n", sauv.nomPartie3);
        remove("../sauv/sauv3.csv");
        update_etat_sauvegarde(&sauv);
      }
      else {
        printf("   Pas de sauvegarde pour cette partie. Rien à effacer.\n");
        sleep(1);
        goto choix;
      }
    }

    if(choix != -1){
      sleep(1);
    }
  }
}

/**
 * \fn void save (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv)
 * \brief Sauvegarde les informations sur le joueur, son inventaire, son équipement ainsi que les informations sur la carte et les quêtes d'une partie
 * \param perso_t player
 * \param cell_t map[D][D]
 * \param int quest_map[6][2]
 * \param quete_t quete
 * \param sauv_t sauv
 * \return Rien
*/
void save (perso_t player, cell_t map[D][D], int quest_map[6][2], quete_t quete, sauv_t sauv){
  int l, c, i;
  FILE * fic;

  // Ouverture en écriture du fichier de sauvegarde correspondant au numéro de partie jouée
  switch(sauv.numPartie){
    case 1: fic = fopen("../sauv/sauv1.csv","w"); break;
    case 2: fic = fopen("../sauv/sauv2.csv","w"); break;
    case 3: fic = fopen("../sauv/sauv3.csv","w"); break;
    default: break;
  }

  // Ecriture nom de partie
  switch(sauv.numPartie){
    case 1: fprintf(fic,"%s\n\n\n",sauv.nomPartie1); break;
    case 2: fprintf(fic,"%s\n\n\n",sauv.nomPartie2); break;
    case 3: fprintf(fic,"%s\n\n\n",sauv.nomPartie3); break;
  }

  /*
   * Sauvegarde informations joueur
   */

   fprintf(fic,"\n\npv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n\n", player.pv, player.pe, player.pa, player.posX, player.posY, player.turns);

  /*
   * Sauvegarde inventaire
   */

  fprintf(fic,"%d\n",player.nb_items_inventory);
  for(i = 0; i < player.nb_items_inventory; i++){
    fprintf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%s\n",player.inventory[i].type, player.inventory[i].attack[0], player.inventory[i].attack[1],player.inventory[i].attack[2], player.inventory[i].hitchance[0], player.inventory[i].hitchance[1],player.inventory[i].hitchance[2],player.inventory[i].defense, player.inventory[i].equipable, player.inventory[i].pc_nature, player.inventory[i].pc_urban, player.inventory[i].pc_military, player.inventory[i].name);
  }

  /*
   * Sauvegarde équipement
   */

  (player.head != NULL) ? fprintf(fic, "\nhead;%d\n", player.head->index) : fprintf(fic, "\nhead;-1\n");
  (player.left_hand != NULL) ? fprintf(fic, "left hand;%d\n", player.left_hand->index) : fprintf(fic, "left hand;-1\n");
  (player.right_hand != NULL) ? fprintf(fic, "right hand;%d\n", player.right_hand->index) : fprintf(fic, "right hand;-1\n");
  (player.body != NULL) ? fprintf(fic, "body;%d\n\n", player.body->index) : fprintf(fic, "body;-1\n\n");

  /*
   * Sauvegarde carte
   */

  // type
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].type);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // categ
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].categ);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // encounter
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].encounter);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // quest_id
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic,"%2d;", map[l][c].quest_id);
    }
      fprintf(fic,"\n");
  }
  fprintf(fic,"\n\n");

  // scavenged
  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic, "%2d;", map[l][c].scavenged);
    }
    fprintf(fic,"\n");
  }

  fprintf(fic,"\n");

  /*
   * Sauvegarde quêtes
   */

   // Sauvegarde int quest_map[6][2]
   for(l = 0; l < 6; l++){
    for(c = 0; c < 2; c++){
      fprintf(fic,"%d;",quest_map[l][c]);
    }
    fprintf(fic,"\n");
  }

  // Sauvegarde quete_t quete
  fprintf(fic,"\n%d;%d;%d;%d;%d;%d;%d;%d;%d\n",quete.soin,quete.recherche.situation,quete.recherche.trouve,quete.recherche.bunkerX,quete.recherche.bunkerY,quete.bunker,quete.montagne,quete.frontiere,quete.bandits);
  fprintf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%s\n",quete.recherche.wanted.type, quete.recherche.wanted.attack[0], quete.recherche.wanted.attack[1],quete.recherche.wanted.attack[2], quete.recherche.wanted.hitchance[0], quete.recherche.wanted.hitchance[1],quete.recherche.wanted.hitchance[2],quete.recherche.wanted.defense, quete.recherche.wanted.equipable, quete.recherche.wanted.pc_nature, quete.recherche.wanted.pc_urban, quete.recherche.wanted.pc_military, quete.recherche.wanted.name);

  fclose(fic);
}

/**
 * \fn void load (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, sauv_t sauv)
 * \brief Charge les informations sur le joueur, son inventaire, son équipement ainsi que les informations sur la carte et les quêtes d'une partie
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \param int quest_map[6][2]
 * \param quete_t * quete
 * \param sauv_t sauv
 * \return Rien
*/
void load (perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, sauv_t sauv){
  int l, c, ind_rh, ind_lh, ind_head, ind_body, i = 0;
  FILE * fic;
  char nomPartie[21];

  // Ouverture en lecture du fichier de sauvegarde correspondant au numéro de partie jouée
  switch(sauv.numPartie){
    case 1: fic = fopen("../sauv/sauv1.csv","r"); break;
    case 2: fic = fopen("../sauv/sauv2.csv","r"); break;
    case 3: fic = fopen("../sauv/sauv3.csv","r"); break;
    default: break;
  }

  if(fic){

    fscanf(fic," %[^\n]\n\n\n",nomPartie);
    printf("\n   >>> Chargement Partie %s\n",nomPartie); sleep(1);

    /*
     * Chargement informations joueur
     */

    fscanf(fic,"pv;%d\npe;%d\npa;%d\nposX;%d\nposY;%d\nturns;%d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->turns);

    /*
     * Chargement inventaire
     */

    fscanf(fic,"%d\n",&player->nb_items_inventory);
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[i].type, &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense, &player->inventory[i].equipable, &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
    while(i < player->nb_items_inventory){
      player->inventory[i].index = i;
      i++;
      fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]", &player->inventory[i].type, &player->inventory[i].attack[0], &player->inventory[i].attack[1],&player->inventory[i].attack[2], &player->inventory[i].hitchance[0], &player->inventory[i].hitchance[1],&player->inventory[i].hitchance[2],&player->inventory[i].defense, &player->inventory[i].equipable, &player->inventory[i].pc_nature, &player->inventory[i].pc_urban, &player->inventory[i].pc_military, player->inventory[i].name);
    }

    /*
     * Chargement équipement
     */

    fscanf(fic,"head;%d\nleft hand;%d\nright hand;%d\nbody;%d\n", &ind_head, &ind_lh, &ind_rh, &ind_body);
    (ind_head != -1) ? (player->head = &player->inventory[ind_head]) : (player->head = NULL);
    (ind_lh != -1) ? (player->left_hand = &player->inventory[ind_lh]) : (player->left_hand = NULL);
    (ind_rh != -1) ? (player->right_hand = &player->inventory[ind_rh]) : (player->right_hand = NULL);
    (ind_body != -1) ? (player->body = &player->inventory[ind_body]) : (player->body = NULL);

    /*
     * Chargement map
     */

    // type
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].type);
      }
    }

    // categ
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].categ);
      }
    }

    // encounter
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].encounter);
      }
    }

    // quest_id
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].quest_id);
      }
    }

    // scavenged
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d;",&map[l][c].scavenged);
      }
    }

    /*
     * Chargement quêtes
     */

    // Chargement int quest_map[6][2]
    for(l = 0; l < 6; l++){
      for(c = 0; c < 2; c++){
        fscanf(fic,"%d;",&quest_map[l][c]);
      }
    }

    // Chargement quete_t quete
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%d;%d",&quete->soin,&quete->recherche.situation,&quete->recherche.trouve,&quete->recherche.bunkerX,&quete->recherche.bunkerY,&quete->bunker,&quete->montagne,&quete->frontiere,&quete->bandits);
    fscanf(fic,"%d;%d;%d;%d;%d;%d;%d;%f;%d;%d;%d;%d;%[^\n]",&quete->recherche.wanted.type,&quete->recherche.wanted.attack[0],&quete->recherche.wanted.attack[1],&quete->recherche.wanted.attack[2],&quete->recherche.wanted.hitchance[0],&quete->recherche.wanted.hitchance[1],&quete->recherche.wanted.hitchance[2],&quete->recherche.wanted.defense,&quete->recherche.wanted.equipable,&quete->recherche.wanted.pc_nature,&quete->recherche.wanted.pc_urban,&quete->recherche.wanted.pc_military,quete->recherche.wanted.name);


    fclose(fic);
  }
  else {
    printf("   Erreur lors du chargement des données sauvegardées.\n");
  }
}
