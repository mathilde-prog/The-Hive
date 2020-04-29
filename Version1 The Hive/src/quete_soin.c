#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file quete_soin.c
 * \brief Fonctions utilisees dans la quete "soin".
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/


/**
 * \fn npc_t * init_npc_quete(item_t * Tab_Items, int pers)
 * \brief Initialisation du personnage de l'homme bless�.
 * \details
    L'initialisation est differente en fonction du "metier" de l'homme : soldat, policier. Il n'aura pas la meme arme mais aura la meme armure.
 * \param item_t * Tab_Items
 * \param int pers
 * \return Un pointeur (npc_t) sur le npc cree
*/

npc_t * init_npc_quete(item_t * Tab_Items, int pers){
  npc_t * blesse;
  blesse = malloc(sizeof(npc_t));
  /*Soldat*/
  if(pers==0){
    strcpy(blesse->name,"soldat");;
    blesse->weapon=&Tab_Items[2]; // SHOTGUN
    blesse->armor=&Tab_Items[6]; // BULLETPROOF WEST
    blesse->pv=0;
  }
  /*Policier*/
  else{
    strcpy(blesse->name,"policier");;
    blesse->weapon=&Tab_Items[0]; // PISTOL
    blesse->armor=&Tab_Items[6]; // BULLETPROOF WEST
    blesse->pv=0;
  }

  return blesse;
}


/**
 * \fn int ajout_item_blesse(perso_t * player, npc_t * homme, int item)
 * \brief Ajouter un item appartenant a un npc a l'inventaire du joueur
 * \param perso_t * player
 * \param npc_t * homme
 * \param int item
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

int ajout_item_blesse(perso_t * player, npc_t * homme, int item){
    if(item == 0){ //Arme
        if(add_item_to_inventory(player,*homme->weapon))
            return 0;
        else{
            printf("L'item n'a pas ete ajoute a votre inventaire.\n");
            return 0;
        }
    }
    else {//Armure
        if(add_item_to_inventory(player,*homme->armor))
            return 0;
        else{
            printf("L'item n'a pas ete ajoute a votre inventaire.\n");
            return(0);
        }
    }
    return (-1);
}


/**
 * \fn int ajout_pass_card(perso_t * player, item_t * pass_card)
 * \brief Ajouter l'item pass_card a l'inventaire du joueur
 * \param perso_t * player
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

int ajout_pass_card(perso_t * player, item_t * pass_card){
    if(add_item_to_inventory(player,*pass_card)){
        return 0;
    }
    else{
        printf("L'item n'a pas ete ajoute a votre inventaire.\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn int menu_choix_ajout_item(perso_t * player, item_t * pass_card, npc_t * homme)
 * \brief Menu permettant au joueur de choisir quel item il souhaite ajoute a son inventaire;
 * \details
    Le joueur fait son choix et par la suite la fonction fait appel a une autre fonction (ajout_item_blesse, ajout_pass_card) qui ajoute l'item choisi
 * \param perso_t * player
 * \param item_t * pass_card
 * \param npc_t * homme
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

int menu_choix_ajout_item(perso_t * player, item_t * pass_card, npc_t * homme){
    int ajout;
    do{
            printf("Quel item souhaitez-vous ajouter ?\n");
            printf("0 - La carte plastique\n");
            printf("1 - %s\n", homme->weapon->name);
            printf("2 - %s\n", homme->armor->name);
            scanf("%d",&ajout);
            if(ajout < 0 || ajout > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(ajout < 0 || ajout > 2);

    switch(ajout){
        case 0 : return ajout_pass_card(player, pass_card);  //Pass card
        case 1 : return ajout_item_blesse(player, homme, 0); //Arme
        case 2 : return ajout_item_blesse(player, homme, 1); //Armure
        default : return (-1); break;
    }
    return (-1);
}



/**
 * \fn int recup_1item_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card)
 * \brief Deroulement de la quete "soin" quand le joueur souhaite voler des items du npc et qu'il n'en trouve qu'un seul sur l'homme : le pass card.
 * \details
    Le joueur fait son choix entre voler le pass_card l'ajouter a son inventaire ou non.
 * \param perso_t * player
 * \param int nb_items_vole
 * \param npc_t * homme
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

/*Le joueur trouve 1 item sur l'homme : le pass card*/
int recup_1item_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card){
    int ajout;

    printf("Vous n'avez trouve qu'un seul item sur ce pauvre homme. ");
    printf("Il s'agit d'une carte en plastique de la taille d'une carte bancaire. Elle possede un liseret noir sur toute la longueur.\n");

    /*Le joueur choisi si il l'ajoute ou non a son inventaire*/
    do{
        printf("Souhaitez-vous ajouter cette carte a votre inventaire ? (Oui = 1, Non = 0)\n");
        scanf("%d",&ajout);
        if(ajout < 0 || ajout > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(ajout < 0 || ajout > 1);

    /*Le joueur ajoute l'item pass card a son inventaire*/
    if(ajout){
        ajout_pass_card(player, pass_card);
        return 0;
    }
    /*Le joueur n'ajoute pas l'item pass_card a son inventaire*/
    else{
        printf("L'item reste ici, repartez explorer la map !\n");
        return 0;
    }
    return (-1);
}



/**
 * \fn int recup_2items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card)
 * \brief Deroulement de la quete "soin" quand le joueur souhaite voler des items du npc et qu'il en trouve 2 sur l'homme.
 * \details
    Le pass_card est obligatoirement trouve, le deuxieme item est soit l'arme ou l'armure du npc.
    Le joueur fait son choix entre voler 1 ou 2 item(s) et le/les ajouter a son inventaire ou ne rien voler.
 * \param perso_t * player
 * \param int nb_items_vole
 * \param npc_t * homme
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

/*Le joueur trouve 2 items sur l'homme : le pass_card et soit son armure ou son arme*/
int recup_2items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card){
    int item2, ajout, choix;
    char nom_item2[20];

    /*Description de la situation*/
    printf("Felicitation, vous avez trouve 2 items sur cet homme.\n");
    printf("Le premier item est une carte en plastique de la taille d'une carte bancaire. Elle possede un liseret noir sur toute la longueur.\n");

    /*Determination aleatoire du 2eme item trouve : armure ou arme*/
    item2 = rand()%2;
    switch(item2){
        case 0 :    printf("Le second est : %s\n", homme->weapon->name); //Arme
                    strcpy(nom_item2,homme->weapon->name);
                    break;
        case 1 :    printf("Le second est : %s\n", homme->armor->name); //Armure
                    strcpy(nom_item2,homme->armor->name);
                    break;
        default : printf("ERREUR : fonction rand() ne renvoit pas 0 ou 1.\n"); break;
    }

    /*Le joueur choisi s'il ajoute 1, 2 ou aucun item(s) a son inventaire*/
    do{
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Ajouter un item dans votre inventaire\n");
        printf("2 - Tout ajouter a votre inventaire\n");
        printf("3 - Rien recuperer\n");
        scanf("%d",&choix);
        if(choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Choix : ajouter 1 item*/
    if(choix == 1){
        /*Choix de l'item a ajouter*/
        do{
            printf("Quel item souhaitez-vous ajouter ?\n");
            printf("0 - La carte plastique\n");
            printf("1 - %s\n", nom_item2);
            scanf("%d",&ajout);
            if(ajout < 0 || ajout > 1)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(ajout < 0 || ajout > 1);

        /*Ajoute l'item choisi a son inventaire*/
        switch(ajout){
            case 0 : return ajout_pass_card(player, pass_card);
            case 1 : return ajout_item_blesse(player, homme, item2);
            default : return(-1);
        }
    }
    else{
        /*Choix : ajouter tous les items (ici 2)*/
        if(choix == 2){
            int h, p;
            p = ajout_pass_card(player, pass_card);
            h = ajout_item_blesse(player, homme, item2);

            /*Verification que les 2 items ont ete ajoute*/
            if((p==0) && (h==0))
                return 0;
            else{
                printf("ERREUR ");
                if(p!=0)
                    printf("dans la fonction ajout_pass_card() ");
                if(h!=0)
                    printf("dans la fonction ajout_item_blesse() ");
                printf("\n");
                return (-1);
            }
        }
        /*Le joueur ajoute aucun items a son inventaire*/
        else{
            printf("Les items restent ici, repartez explorer la map !\n");
            return 0;
        }
    }
    return (-1);
}



/**
 * \fn int recup_3items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card)
 * \brief Deroulement de la quete "soin" quand le joueur souhaite voler des items du npc et qu'il en trouve 3 sur l'homme.
 * \details
    Le joueur trouve le pass_card, l'arme et l'armure du npc blesse.
    Il a le choix entre voler 1, 2 ou 3 item(s) et le/les ajouter a son inventaire ou ne rien voler.
 * \param perso_t * player
 * \param int nb_items_vole
 * \param npc_t * homme
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

/*Le joueur trouve 3 items sur l'homme : le pass_card, son armure et son arme*/
int recup_3items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card){
    int choix;

    /*Description de la situation*/
    printf("Felicitations, vous avez trouve 3 items sur cet homme.\n");
    printf("Le premier item est une carte en plastique de la taille d'une carte bancaire. Elle possede un liseret noir sur toute la longueur.\n");
    printf("Le second est : %s ", homme->weapon->name); //Arme
    printf("et le dernier est : %s\n", homme->armor->name);  //Armure

    /*Le joueur choisi s'il ajoute 1, 2 ou aucun item(s) a son inventaire*/
    do{
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Ajouter 1 item dans votre inventaire\n");
        printf("2 - Ajouter 2 items dans votre inventaire\n");
        printf("3 - Tout ajoutera votre inventaire\n");
        printf("4 - Rien recuperer\n");
        scanf("%d",&choix);
        if(choix < 1 || choix > 4)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 4);

    /*Choix : ajouter 1 item*/
    if(choix == 1)
        return menu_choix_ajout_item(player, pass_card, homme);
    else{
        /*Choix : ajouter 2 items*/
        if(choix == 2){
            int i1, i2;
            /*Choix et ajout du premier item choisi*/
            printf("Item 1 :\n");
            i1 = menu_choix_ajout_item(player, pass_card, homme);
            /*Choix et ajout du premier item choisi*/
            printf("Item 2 :\n");
            i2 = menu_choix_ajout_item(player, pass_card, homme);

            /*V�rification que les 2 items ont ete ajoute*/
            if((i1==0) && (i2==0))
                return 0;
            else{
                printf("ERREUR fonction menu_choix_ajout_item()");
                return (-1);
            }
        }
        else{
            /*Choix : ajouter tout*/
            if(choix == 3){
                int p, i1, i2;
                p = ajout_pass_card(player, pass_card);
                i1 = ajout_item_blesse(player, homme, 0);
                i2 = ajout_item_blesse(player, homme, 1);

                /*V�rification que les 2 items ont ete ajoute*/
                if((p==0) && (i1==0) && (i2==0))
                    return 0;
                else{
                    printf("ERREUR ");
                    if(p!=0)
                        printf("dans la fonction ajout_pass_card() ");
                    if(i1!=0)
                        printf("dans la fonction ajout_item_blesse(0: arme) ");
                    if(i2!=0)
                        printf("dans la fonction ajout_item_blesse(1: armure) ");
                    printf("\n");
                    return (-1);
                }
            }
            /*Le joueur n'ajoute aucun item a son inventaire*/
            else{
                printf("Les items restent ici, repartez explorer la map !\n");
                return 0;
            }
        }

    }
     return (-1);
}


/**
 * \fn void quete_soin()
 * \brief Deroulement de la quete "soin" : rencontre d'un individu blesse.
 * \details
    Le joueur rencontre un individu blesse. Il a le choix entre l'ignorer, lui voler ses items ou l'aider.
    Cet individu est un homme de l'Etat, en charge de la protection des civiles (policier ou soldat).
    Pour pouvoir aider le blesse le joueur doit �tre en possession du medical_kit ou de nourriture.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue et -1 si probleme dans la quete.
*/

int quete_soin(perso_t * player, quete_t * quete){
    int pers, choix;

    quete->soin=0;
    srand(time(NULL));
    pers = rand()%2;

    /*Description de la situation*/
    printf("Vous rencontrez un homme sur votre chemin. Il semble ne pas etre dans son etat normal. Vous remarquez qu'il porte un uniforme de ");
    if (pers == 0)
        printf("soldat.\n");
    else
        printf("policier.\n");
    printf("Il est blesse et tres affaibli. ");

    /*Choix du joueur sur son action pour l'homme blesse*/
    do{
        printf("Que choisissez-vous de faire a son sujet ?\n");
        printf("1 - Vous l'ignorez, vous etes presse et ne souhaitez pas l'aider.\n");
        printf("2 - Vous lui voler les items qu'il poss�de, apres tout il n'en n'aura bientot plus besoin vu son etat.\n");
        printf("3 - Vous lui venez en aide. Vous aimeriez bien que quelqu'un fasse pareil pour vous dans sa situation.\n");

        scanf("%d", &choix);

        if (choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Si le joueur ignore l'homme blesse*/
    if (choix == 1){
         printf("Continuons a explorer la map !\n");
         quete->soin=1;
         return 0;
    }
    else {
        /*Creation de l'item pass_card*/
        item_t * pass_card = malloc(sizeof(item_t));
        pass_card = creer_item("pass card", misc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        /*Si le joueur decide de voler les items du blesse*/
        if (choix == 2){
            printf("A l'attaque ! Recuperez ce que vous pouvez sur lui.\n");

            int nb, nb_items_vole, ok;

            /*Creation du npc blesse*/
            npc_t * blesse;
            item_t * Tab_Items = malloc(20 * sizeof(item_t));
            creation_tab_item(Tab_Items, &nb);
            blesse = init_npc_quete(Tab_Items, pers);

            /*Recuperation des items de l'homme blesse*/
            nb_items_vole = (rand()%3)+1; //Donne le nombre d'items que le joueur a reussi a voler (+1 pour le pass card : obligatoirement trouve)
            switch(nb_items_vole){
                case 1 : ok = recup_1item_vole(player, nb_items_vole, blesse, pass_card); break;
                case 2 : ok = recup_2items_vole(player, nb_items_vole, blesse, pass_card); break;
                case 3 : ok = recup_3items_vole(player, nb_items_vole, blesse, pass_card); break;
                default : printf("ERREUR : nb_items_vole n'est pas compris entre 1 et 3.\n"); return (-1);
            }
            if(ok==0){
                printf("Vous en avez fini avec ce pauvre homme, repartez explorer la map !\n");
                quete->soin=1;
                return(0);
            }
            else
               return(-1);

        }
        /*Si le joueur vient en aide a l'homme blesse*/
        else{
            int cpt, i, choix, mk=-1;

            printf("Pour l'aidez au mieux, il faudrait que vous ayez dans votre inventaire : de la nourriture, de la boisson ou un kit medical.\n");
            printf("Regardez ce que vous avez en votre possession.\n");
            display_inventory(*player);

            int ind_items_soin[player->nb_items_inventory]; //Tableau ou se trouveras les indices des items de type food et du medical_kit dans l'inventaire
            /*Initialisation du tableau ind_items_soin*/
            for(i=0; i < ITEMS_MAX; i++)
                ind_items_soin[i] = -1;

            /*Recherche des items de type food dans l'inventaire du joueur*/
            for(i=0, cpt=0; i < player->nb_items_inventory; i++){
                if(player->inventory[i].type == food){
                    ind_items_soin[cpt] = i;
                    cpt++;
                }
            }

            /*Recherche du medical_kit dans l'inventaire du joueur*/
            if(item_in_inventory(*player,"medical kit") !=  -1){
                    mk = item_in_inventory(*player,"medical kit");
                    ind_items_soin[cpt] = mk;
            }

            /*Le joueur possede au moins 1 item utile a l'homme blesse*/
            if(cpt!=0){
                if(cpt>1){
                    printf("Vous avez des items en votre possession qui peuvent aider cet homme blesse ! Les voici : \n");
                    /*Affichage de la liste des items utiles*/
                    // VERSION ANAIS : for(i=0; !ind_items_soin; i++){
                    // OU PLUTOT
                    for(i = 0; i <= cpt; i++){
                        printf("N°%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
                    }
                    /*Choix du joueur sur l'aide a apporter a l'homme*/
                    do{
                        printf("Plusieurs choix sont disponibles :\n");
                        printf("0 - Changement d'avis, ne rien lui donner, ne pas l'aider\n");
                        printf("1 - Donner de la nourriture pour qu'il reprenne des forces\n");
                        if(mk!=-1){
                            printf("2 - Utiliser le medical kit pour lui soigner ses blessures\n");
                            printf("3 - Donner de la nourriture et utiliser le medical kit\n");
                        }
                        printf("Comment souhaitez-vous l'aider ?\n");
                        scanf("%d", &choix);

                        if(mk==-1){
                            if (choix < 0 || choix > 1){
                                while(choix < 0 || choix > 1){
                                    printf("Valeur incorrecte. Veuillez resaissir.\n");
                                    scanf("%d", &choix);
                                }
                            }
                        }
                        else{
                            if (choix < 0 || choix > 3)
                                printf("Valeur incorrecte. Veuillez resaissir.\n");
                        }
                    }while(choix < 0 || choix > 3);

                    /*Le joueur change d'avis, fin de la quete*/
                    if(choix==0){
                        printf("Votre choix de ne pas aider cet homme a ete bien enregiste. Vous pouvez repartir explorer la map!\n");
                        quete->soin=1;
                        return 0;
                    }
                    else{
                        /*Donnation de nourriture(s)*/
                        if((choix==1)||(choix==3)){
                            int food, ali1, ali2;
                            do{
                                printf("Vous pouvez lui donner :\n");
                                printf("1 - Un aliment\n");
                                printf("2 - Deux aliments\n");
                                printf("Quel est votre choix ? ");
                                scanf("%d", &food);

                                if(food < 1 || food > 2)
                                    printf("Valeur incorrecte. Veuillez resaissir.\n");
                            }while(food < 1 || food > 2);

                            /*Donation de 1 aliment*/
                            if(food==1){
                                /*Choix de l'aliment*/
                                do{
                                    printf("Il faut maintenant choisir quel aliment donner au ");
                                    if (pers == 0)
                                        printf("soldat.\n");
                                    else
                                        printf("policier.\n");
                                    /*Affichage des items de type food*/
                                    for(i=0; i<cpt; i++){   //i<cpt car ind_items_soin[cpt] = -1 ou indice medical_kit
                                        printf("N°%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
                                    }
                                    printf("Pour cela entrer le numero de l'aliment : ");
                                    scanf("%d", &ali1);

                                    if(ali1 < 0 || ali1 > i-1)
                                        printf("Valeur incorrecte. Veuillez resaissir.\n");
                                }while(ali1 < 0 || ali1 > i-1);

                                /*Suppresion de l'aliment choisi dans l'inventaire du joueur*/
                                delete_item_in_inventory(player, player->inventory[ind_items_soin[ali1]]);
                                printf("L'item %s a bien ete utilise pour aider l'homme, il va mieux grace a vous !\n", player->inventory[ind_items_soin[ali1]].name);

                            }
                            /*Donation de 2 aliments*/
                            else{
                                /*Choix des aliments*/
                                do{
                                    printf("Il faut maintenant choisir quels aliments donner au ");
                                    if (pers == 0)
                                        printf("soldat.\n");
                                    else
                                        printf("policier.\n");
                                    /*Affichage des items de type food*/
                                    for(i=0; i<cpt; i++){   //i<cpt car ind_items_soin[cpt] = -1 ou indice medical_kit
                                        printf("N°%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
                                    }
                                    printf("Pour cela entrer le numero du premier aliment : ");
                                    scanf("%d", &ali1);
                                    printf("\n");
                                    printf("Puis celui du deuxi�me : ");
                                    scanf("%d", &ali2);

                                    if(ali1 < 0 || ali1 > i-1)
                                        printf("Valeur incorrecte du premier aliment. Veuillez resaissir.\n");
                                    if(ali2 < 0 || ali2 > i-1)
                                        printf("Valeur incorrecte du deuxi�me aliment. Veuillez resaissir.\n");
                                }while((ali1 < 0 || ali1 > i-1) || (ali2 < 0 || ali2 > i-1));

                                /*Suppresion des aliments choisis dans l'inventaire du joueur*/
                                delete_item_in_inventory(player, player->inventory[ind_items_soin[ali1]]);
                                delete_item_in_inventory(player, player->inventory[ind_items_soin[ali2]]);
                                printf("Les items %s et %s ont bien ete utilises pour aider l'homme, il va beaucoup mieux grace a vous !\n", player->inventory[ind_items_soin[ali1]].name, player->inventory[ind_items_soin[ali2]].name);

                            }

                        }
                        /*Utilisation du medical kit*/
                        if(choix>1){
                            delete_item_in_inventory(player, player->inventory[mk]);
                            printf("Le medical kit a bien ete utilise pour soigner l'homme, il va beaucoup mieux grace a vous !\n");
                        }
                        printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte.\n");
                        /*Si le joueur a beaucoup aider l'homme : 2 aliments ou medical_kit ou les 2, des informations sur le nouvel item lui sont donn�es*/
                        if((choix==2) || (choix==3) || (food==2))
                            printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y refugier et donc sauver ta vie.\"\n");
                        add_item_to_inventory(player,*pass_card);
                        printf("Apres cette rencontre il est temps de retourner explorer la map.\n");
                        quete->soin=2;
                        return 0;
                    }

                }
                /*Le joueur ne possede qu'un seul item pouvant �tre utile a l'homme*/
                else{
                    printf("Vous etes en possession d'un seul item pouvant aider l'homme affaiblis.\n");
                    printf("Il s'agit de l'item %s.\n", player->inventory[ind_items_soin[0]].name);
                    do{
                        printf("Vous avez deux possibilites : \n");
                        printf("0 - Changement d'avis, ne rien utiliser, ne pas l'aider\n");
                        printf("1 - Utiliser l'item du dessus\n");

                        if(choix < 0 || choix > 1)
                            printf("Valeur incorrecte. Veuillez resaissir.\n");
                    }while(choix < 0 || choix > 1);

                    /*Le joueur change d'avis, fin de la quete*/
                    if(choix==0){
                        printf("Votre choix de ne pas aider cet homme a ete bien enregistre. Vous pouvez repartir explorer la map!\n");
                        return 0;
                    }
                    /*Le joueur donne le seul item utile en sa possession*/
                    else{
                        /*Suppresion des aliments choisis dans l'inventaire du joueur*/
                        delete_item_in_inventory(player,player->inventory[ind_items_soin[0]]);
                        printf("L'item %s a bien ete utilise pour aider l'homme, il va mieux grace a vous !\n", player->inventory[ind_items_soin[0]].name);

                        printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte.\n");
                        /*Si le seul item utile est le medical_kit des informations sur le nouvel item sont donn�es au joueur*/
                        if(mk!=-1)
                            printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y refugier et donc sauver ta vie.\"\n");
                        add_item_to_inventory(player,*pass_card);
                        printf("Apres cette rencontre il est temps de retourner explorer la map.\n");
                        quete->soin=2;
                        return 0;
                    }
                }
            }
            /*Le joueur ne possede aucun item utile, il ne peut pas l'aider*/
            else{
                printf("Desole mais vous ne possedez aucun item pouvant venir en aide a cet homme...\n");
                quete->soin=3;
                return 0;
            }
            return (-1);
        }
    }
}
