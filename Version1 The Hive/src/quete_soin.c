#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file quete_soin.c
 * \brief Fonctions utilis�es dans la quete "soin".
 * \author Mathilde Mottay, Ana�s Mottier, Cl�ment Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/


/**
 * \fn npc_t * init_npc_quete(item_t * Tab_Items, int pers)
 * \brief Initialisation du personnage de l'homme bless�.
 * \details
    L'initialisation est diff�rente en fonction du "m�tier" de l'homme : soldat, policier. Il n'aura pas la m�me arme mais aura la m�me armure.
 * \param item_t * Tab_Items
 * \param int pers
 * \return Un pointeur (npc_t) sur le npc cr��
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
 * \brief Ajouter un item appartenant � un npc � l'inventaire du joueur
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
            printf("L'item n'a pas �t� ajout� � votre inventaire.\n");
            return 0;
        }
    }
    else {//Armure
        if(add_item_to_inventory(player,*homme->armor))
            return 0;
        else{
            printf("L'item n'a pas �t� ajout� � votre inventaire.\n");
            return(0);
        }
    }
    return (-1);
}


/**
 * \fn int ajout_pass_card(perso_t * player, item_t * pass_card)
 * \brief Ajouter l'item pass_card � l'inventaire du joueur
 * \param perso_t * player
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

int ajout_pass_card(perso_t * player, item_t * pass_card){
    if(add_item_to_inventory(player,*pass_card)){
        return 0;
    }
    else{
        printf("L'item n'a pas �t� ajout� � votre inventaire.\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn int menu_choix_ajout_item(perso_t * player, item_t * pass_card, npc_t * homme)
 * \brief Menu permettant au joueur de choisir quel item il souhaite ajout� � son inventaire;
 * \details
    Le joueur fait son choix et par la suite la fonction fait appel � une autre fonction (ajout_item_blesse, ajout_pass_card) qui ajoute l'item choisi
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
        case 0 : return ajout_pass_card(player, pass_card); break;  //Pass card
        case 1 : return ajout_item_blesse(player, homme, 0); break; //Arme
        case 2 : return ajout_item_blesse(player, homme, 1); break; //Armure
        default : return (-1); break;
    }
    return (-1);
}



/**
 * \fn int recup_1item_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card)
 * \brief Deroulement de la quete "soin" quand le joueur souhaite voler des items du npc et qu'il n'en trouve qu'un seul sur l'homme : le pass_card.
 * \details
    Le joueur fait son choix entre voler le pass_card l'ajouter � son inventaire ou non.
 * \param perso_t * player
 * \param int nb_items_vole
 * \param npc_t * homme
 * \param item_t * pass_card
 * \return Retourne un \a int : 0 si le jeu continue, -1 si probleme lors de la quete.
*/

/*Le joueur trouve 1 item sur l'homme : le pass_card*/
int recup_1item_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card){
    int ajout;

    printf("Vous n'avez trouv� qu'un seul item sur ce pauvre homme. ");
    printf("Il s'agit d'une carte en plastique de la taille d'une carte bancaire. Elle poss�de un liseret noir sur toute la longueur.\n");

    /*Le joueur choisi si il l'ajoute ou non � son inventaire*/
    do{
        printf("Souhaitez-vous ajouter cette carte � votre inventaire ? (Oui = 1, Non = 0)\n");
        scanf("%d",&ajout);
        if(ajout < 0 || ajout > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(ajout < 0 || ajout > 1);

    /*Le joueur ajoute l'item pass_card � son inventaire*/
    if(ajout){
        ajout_pass_card(player, pass_card);
        return 0;
    }
    /*Le joueur n'ajoute pas l'item pass_card � son inventaire*/
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
    Le pass_card est obligatoirement trouv�, le deuxi�me item est soit l'arme ou l'armure du npc.
    Le joueur fait son choix entre voler 1 ou 2 item(s) et le/les ajouter � son inventaire ou ne rien voler.
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
    printf("F�licitation, vous avez trouv� 2 items sur cet homme.\n");
    printf("Le premier item est une carte en plastique de la taille d'une carte bancaire. Elle poss�de un liseret noir sur toute la longueur.\n");

    /*D�termination al�atoire du 2�me item trouv� : armure ou arme*/
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

    /*Le joueur choisi s'il ajoute 1, 2 ou aucun item(s) � son inventaire*/
    do{
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Ajouter un item dans votre inventaire\n");
        printf("2 - Tout ajouter � votre inventaire\n");
        printf("3 - Rien r�cup�r�\n");
        scanf("%d",&choix);
        if(choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Choix : ajouter 1 item*/
    if(choix == 1){
        /*Choix de l'item � ajouter*/
        do{
            printf("Quel item souhaitez-vous ajouter ?\n");
            printf("0 - La carte plastique\n");
            printf("1 - %s\n", nom_item2);
            scanf("%d",&ajout);
            if(ajout < 0 || ajout > 1)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(ajout < 0 || ajout > 1);

        /*Ajoute l'item choisi � son inventaire*/
        switch(ajout){
            case 0 : return ajout_pass_card(player, pass_card); break;
            case 1 : return ajout_item_blesse(player, homme, item2); break;
            default : return(-1); break;
        }
    }
    else{
        /*Choix : ajouter tous les items (ici 2)*/
        if(choix == 2){
            int h, p;
            p = ajout_pass_card(player, pass_card);
            h = ajout_item_blesse(player,homme,item2);

            /*V�rification que les 2 items ont �t� ajout�*/
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
        /*Le joueur ajoute aucun items � son inventaire*/
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
    Il a le choix entre voler 1, 2 ou 3 item(s) et le/les ajouter � son inventaire ou ne rien voler.
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
    printf("F�licitation, vous avez trouv� 3 items sur cet homme.\n");
    printf("Le premier item est une carte en plastique de la taille d'une carte bancaire. Elle poss�de un liseret noir sur toute la longueur.\n");
    printf("Le second est : %s ", homme->weapon->name); //Arme
    printf("et le dernier est : %s\n", homme->armor->name);  //Armure

    /*Le joueur choisi s'il ajoute 1, 2 ou aucun item(s) � son inventaire*/
    do{
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Ajouter 1 item dans votre inventaire\n");
        printf("2 - Ajouter 2 items dans votre inventaire\n");
        printf("3 - Tout ajouter � votre inventaire\n");
        printf("4 - Rien r�cup�r�\n");
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

            /*V�rification que les 2 items ont �t� ajout�*/
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

                /*V�rification que les 2 items ont �t� ajout�*/
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
            /*Le joueur n'ajoute aucun item � son inventaire*/
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
 * \brief Deroulement de la quete "soin" : rencontre d'un individu bless�.
 * \details
    Le joueur rencontre un individu bless�. Il a le choix entre l'ignorer, lui voler ses items ou l'aider.
    Cet individu est un homme de l'Etat, en charge de la protection des civiles (policier ou soldat).
    Pour pouvoir aider le bl�ss� le joueur doit �tre en possession du medical_kit ou de nourriture.
 * \param perso_t * player
 * \return Retourne un \a int : 0 si le jeu continue et -1 si probleme dans la quete.
*/

int quete_soin(perso_t * player, quete_t * quete){
    int pers, choix;

    srand(time(NULL));
    pers = rand()%2;

    /*Description de la situation*/
    printf("Vous rencontrez un homme sur votre chemin. Il semble ne pas �tre dans son �tat normal. Vous remarquez qu'il porte un uniforme de ");
    if (pers == 0)
        printf("soldat.\n");
    else
        printf("policier.\n");
    printf("Il est bless� et tr�s affaibli. ");

    /*Choix du joueur sur son action pour l'homme bless�*/
    do{
        printf("Que choisissez-vous de faire � son sujet ?\n");
        printf("1 - Vous l'ignorez, vous �tes pr�ss� et ne souhaitez pas l'aider.\n");
        printf("2 - Vous lui voler les items qu'il poss�de, apr�s tout il n'en n'aura bient�t plus besoin vu son �tat.\n");
        printf("3 - Vous lui venez en aide. Vous aimeriez bien que quelqu'un fasse pareil pour vous dans sa situation.\n");

        scanf("%d", &choix);

        if (choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Si le joueur ignore l'homme bl�ss�*/
    if (choix == 1){
         printf("Continuons a explorer la map !\n");
         return 0;
    }
    else {
        /*Cr�ation de l'item pass_card*/
        item_t * pass_card = malloc(sizeof(item_t));
        pass_card = creer_item("pass_card", misc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        /*Si le joueur d�cide de voler les items du bless�*/
        if (choix == 2){
            printf("A l'attaque ! R�cup�rez ce que vous pouvez sur lui.\n");

            int nb, nb_items_vole, ok;

            /*Cr�ation du npc blesse*/
            npc_t * blesse;
            item_t * Tab_Items = malloc(20 * sizeof(item_t));
            creation_tab_item(Tab_Items, &nb);
            blesse = init_npc_quete(Tab_Items, pers);

            /*R�cup�ration des items de l'homme bless�*/
            nb_items_vole = (rand()%3)+1; //Donne le nombre d'items que le joueur a r�ussi a voler (+1 pour le pass_card : obligatoirement trouv�)
            switch(nb_items_vole){
                case 1 : ok = recup_1item_vole(player, nb_items_vole, blesse, pass_card); break;
                case 2 : ok = recup_2items_vole(player, nb_items_vole, blesse, pass_card); break;
                case 3 : ok = recup_3items_vole(player, nb_items_vole, blesse, pass_card); break;
                default : printf("ERREUR : nb_items_vole n'est pas compris entre 1 et 3.\n"); return (-1);
            }
            if(ok==0){
                printf("Vous en avez fini avec ce pauvre homme, repartez explorer la map !\n");
                return(0);
            }
            else
               return(-1);

        }
        /*Si le joueur vient en aide � l'homme bl�ss�*/
        else{
            int cpt, i, choix, mk=-1;

            printf("Pour l'aidez au mieux, il faudrait que vous ayez dans votre inventaire : de la nourriture, de la boisson ou un kit medical.\n");
            printf("Regardez ce que vous avez en votre possession.\n");
            display_inventory(*player);

            int ind_items_soin[player->nb_items_inventory]; //Tableau o� se trouveras les indices des items de type food et du medical_kit dans l'inventaire
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

            /*Recherche du m�dical_kit dans l'inventaire du joueur*/
            if(item_in_inventory(*player,"medical_kit") !=  -1){
                    mk = item_in_inventory(*player,"medical_kit");
                    ind_items_soin[cpt] = mk;
            }

            /*Le joueur poss�de au moins 1 item utile � l'homme bless�*/
            if(cpt!=0){
                if(cpt>1){
                    printf("Vous avez des items en votre possession qui peuvent aider cet homme bless� ! Les voici : \n");
                    /*Affichage de la liste des items utiles*/
                    // VERSION ANAIS : for(i=0; !ind_items_soin; i++){
                    // OU PLUTOT
                    for(i = 0; i < cpt; i++){
                        printf("N�%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
                    }
                    /*Choix du joueur sur l'aide a apporter � l'homme*/
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
                        printf("Votre choix de ne pas aider cet homme a �t� bien enregistr�. Vous pouvez repartir explorer la map!\n");
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
                                        printf("N�%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
                                    }
                                    printf("Pour cela entrer le numero de l'aliment : ");
                                    scanf("%d", &ali1);

                                    if(ali1 < 0 || ali1 > i-1)
                                        printf("Valeur incorrecte. Veuillez resaissir.\n");
                                }while(ali1 < 0 || ali1 > i-1);

                                /*Suppresion de l'aliment choisi dans l'inventaire du joueur*/
                                delete_item_in_inventory(player, player->inventory[ind_items_soin[ali1]]);
                                printf("L'item %s a bien �t� utilis� pour aider l'homme, il va mieux grace � vous !\n", player->inventory[ind_items_soin[ali1]].name);

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
                                        printf("N�%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
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
                                printf("Les items %s et %s ont bien �t� utilis�s pour aider l'homme, il va beaucoup mieux grace � vous !\n", player->inventory[ind_items_soin[ali1]].name, player->inventory[ind_items_soin[ali2]].name);

                            }

                        }
                        /*Utilisation du medical kit*/
                        if(choix>1){
                            delete_item_in_inventory(player, player->inventory[mk]);
                            printf("Le m�dical kit a bien �t� utilis� pour soigner l'homme, il va beaucoup mieux grace � vous !\n");
                        }
                        printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte.\n");
                        /*Si le joueur a beaucoup aider l'homme : 2 aliments ou medical_kit ou les 2, des informations sur le nouvel item lui sont donn�es*/
                        if((choix==2) || (choix==3) || (food==2))
                            printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y r�fugier et donc sauver ta vie.\"\n");
                        add_item_to_inventory(player,*pass_card);
                        printf("Apr�s cette rencontre il est temps de retourner explorer la map.\n");
                        quete->soin=1;
                        return 0;
                    }

                }
                /*Le joueur ne poss�de qu'un seul item pouvant �tre utile � l'homme*/
                else{
                    printf("Vous �tes en possession d'un seul item pouvant aider l'homme affaiblis.\n");
                    printf("Il s'agit de l'item %s.\n", player->inventory[ind_items_soin[0]].name);
                    do{
                        printf("Vous avez deux possibilit�s : \n");
                        printf("0 - Changement d'avis, ne rien utiliser, ne pas l'aider\n");
                        printf("1 - Utiliser l'item du dessus\n");

                        if(choix < 0 || choix > 1)
                            printf("Valeur incorrecte. Veuillez resaissir.\n");
                    }while(choix < 0 || choix > 1);

                    /*Le joueur change d'avis, fin de la quete*/
                    if(choix==0){
                        printf("Votre choix de ne pas aider cet homme a �t� bien enregistr�. Vous pouvez repartir explorer la map!\n");
                        return 0;
                    }
                    /*Le joueur donne le seul item utile en sa possession*/
                    else{
                        /*Suppresion des aliments choisis dans l'inventaire du joueur*/
                        delete_item_in_inventory(player,player->inventory[ind_items_soin[0]]);
                        printf("L'item %s a bien �t� utilis� pour aider l'homme, il va mieux grace � vous !\n", player->inventory[ind_items_soin[0]].name);

                        printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte.\n");
                        /*Si le seul item utile est le medical_kit des informations sur le nouvel item sont donn�es au joueur*/
                        if(mk!=-1)
                            printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y r�fugier et donc sauver ta vie.\"\n");
                        add_item_to_inventory(player,*pass_card);
                        printf("Apr�s cette rencontre il est temps de retourner explorer la map.\n");
                        quete->soin=1;
                        return 0;
                    }
                }
            }
            /*Le joueur ne poss�de aucun item utile, il ne peut pas l'aider*/
            else{
                printf("D�sol� mais vous ne possedez aucun item pouvant venir en aide a cet homme...\n");
                quete->soin=0;
                return 0;
            }
            return (-1);
        }
    }
}
