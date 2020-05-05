#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

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
    L'initialisation est différente en fonction du "metier" de l'homme : soldat, policier. Il n'aura pas la même arme mais aura la même armure.
 * \param item_t * Tab_Items
 * \param int pers
 * \return Un pointeur (npc_t) sur le npc créé
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
 * \fn int recup_items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card, quete_t * quete)
 * \brief Récupération des items voler sur l'homme blessé par le joueur.
 * \details
    Génération des items volés + décision du joueur de les récupérer ou non dans son inventaire
 * \param perso_t * player
 * \param int nb_items_vole
 * \param npc_t* homme
 * \param item_t * pass_card
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue et -1 si probleme dans la quete.
*/
int recup_items_vole(perso_t * player, int nb_items_vole, npc_t* homme, item_t * pass_card, quete_t * quete){
    int i, item2, ajout, recup;

    item_t items_vole_blesse[nb_items_vole]; //Tableau ou se trouveras les items trouvé sur l'homme blesse
    /*Initialisation du tableau items_vole_blesse*/
    for(i=0; i<nb_items_vole; i++){
        if(i==0) //Le premier item volé est obligatoirement le pass card
            items_vole_blesse[i] = *pass_card;
        /*Génération aléatoire du 2 item volé, si le joueur vole 2 items*/
        else if(nb_items_vole == 2){
            item2 = rand()%2;
            switch(item2){
                case 0 : items_vole_blesse[i] = *homme->weapon; break; //Arme
                case 1 : items_vole_blesse[i] = *homme->armor; break;  //Armure
                default : printf("ERREUR : fonction rand() ne renvoit pas 0 ou 1.\n"); break;
            }
        }
        /*Si le joueur vole 3 items, il recupère l'arme puis l'armure*/
        else if(i==1)
            items_vole_blesse[i] = *homme->weapon;
        else
            items_vole_blesse[i] = *homme->armor;
    }

    /*Si le joueur a trouvé plus d'un item*/
    if(nb_items_vole>1){
        printf("Félicitations, vous avez trouvé %d items sur cet homme.\n", nb_items_vole);

        /*Affichage des items trouvés*/
        for(i=0; i<nb_items_vole; i++){
            if(i==0)
                printf("Item n°%d : une carte en plastique de la taille d'une carte bancaire. Elle possède un liseret noir sur toute la longueur.\n", i+1);
            else{
                printf("Item n°%d : %s\n", i+1, items_vole_blesse[i].name);
            }
        }

        /*Le joueur choisi s'il ajoute aucun item ou au moins 1 à son inventaire*/
        do{
            printf("Que souhaitez-vous faire ?\n");
            printf("1 - Ajouter au moins un item à votre inventaire\n");
            printf("2 - Rien ajouter\n");
            scanf("%d",&recup);
            if(recup < 1 || recup > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(recup < 1 || recup > 2);

        /*Choix : ajouter au moins 1 item*/
        if(recup==1){
            printf("Pour chaque item trouvé, vous devez faire prendre une décision.\n");

            /*Pour chaque item trouve sur l'homme blessé*/
            for(i=0; i<nb_items_vole; i++){
                /*Choix du joueur pour chaque item : ajouter à l'inventaire ou non*/
                do{
                    if(i==0)
                        printf("Item n°%d : carte plastique. ", i+1);
                    else
                        printf("Item n°%d : %s. ", i+1, items_vole_blesse[i].name);
                    printf("Vous avez le choix entre :\n");
                    printf("1 - Ajouter l'item a l'inventaire\n");
                    printf("2 - Ne pas l'ajouter\n");
                    printf("Votre choix : ");
                    scanf("%d", &ajout);

                    if(ajout<1 || ajout>2)
                        printf("Valeur incorrecte. Veuillez resaissir.\n");
                }while(ajout<1 || ajout>2);

                /*Ajouter l'item à l'inventaire*/
                if(ajout==1){
                    if(add_item_to_inventory(player, items_vole_blesse[i]) == 0)
                        printf("L'item %s n'a pas été ajouté à votre inventaire.\n", items_vole_blesse[i].name);
                }
                /*Pas d'ajout à l'inventaire*/
                else if(ajout==2)
                    printf("Votre choix de ne pas ajouter l'item %s a bien été pris en compte.\n", items_vole_blesse[i].name);
            }
            printf("Vous en avez fini avec ce pauvre homme, repartez explorer la map !\n");
            quete->soin=1;
            return 0;
        }
        /*Choix : rien ajouter à l'inventaire*/
        else if(recup==2){
            printf("Les items restent ici, repartez explorer la map !\n");
            quete->soin=1;
            return 0;
        }
    }
    /*Si le joueur a trouvé qu'un item*/
    else if(nb_items_vole==1){
        printf("Vous n'avez trouvé qu'un seul item sur ce pauvre homme. ");
        printf("Il s'agit d'une carte en plastique de la taille d'une carte bancaire. Elle possède un liseret noir sur toute la longueur.\n");

        /*Choix du joueur pour chaque item : ajouter à l'inventaire ou non*/
        do{
            printf("Vous avez le choix entre :\n");
            printf("1 - Ajouter l'item a l'inventaire\n");
            printf("2 - Ne pas l'ajouter\n");
            printf("Votre choix : ");
            scanf("%d", &ajout);

            if(ajout<1 || ajout>2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(ajout<1 || ajout>2);

        /*Ajouter l'item à l'inventaire*/
        if(ajout==1){
            if(add_item_to_inventory(player, items_vole_blesse[0]) == 0)
                printf("La carte en plastique n'a pas été ajouté à votre inventaire.\n");
        }
        /*Pas d'ajout à l'inventaire*/
        else{
            printf("Votre choix de ne pas ajouter la carte en plastique a bien été pris en compte.\n");
        }
        printf("Vous en avez fini avec ce pauvre homme, repartez explorer la map !\n");
        quete->soin=1;
        return 0;
    }
    return(-1);
}


/**
 * \fn int aider_homme_blesse(perso_t * player, item_t * pass_card, quete_t * quete, int pers)
 * \brief Fonction où se déroule la partie aide de la quete "soin".
 * \details
    Le joueur peut aider l'homme de différentes façons, il choisit comment il souhaite le faire ou non.
 * \param perso_t * player
 * \param item_t * pass_card
 * \param quete_t * quete
 * \param int pers
 * \return Retourne un \a int : 0 si le jeu continue et -1 si problème dans la quete.
*/
int aider_homme_blesse(perso_t * player, item_t * pass_card, quete_t * quete, int pers){
    int cpt, i, choix, mk=-1;

    int ind_items_soin[player->nb_items_inventory]; //Tableau ou se trouveras les indices des items de type food et du medical_kit dans l'inventaire
    /*Initialisation du tableau ind_items_soin*/
    for(i=0; i < player->nb_items_inventory; i++)
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
        /*Plus de 1 item utile dans l'inventaire*/
        if(cpt>1){
            printf("Vous avez des items en votre possession qui peuvent aider cet homme blesse ! Les voici : \n");
            /*Affichage de la liste des items utiles*/
            for(i = 0; i <= cpt; i++){
                printf("N°%d - %s\n", i, player->inventory[ind_items_soin[i]].name);
            }
            /*Choix du joueur sur l'aide a apporter a l'homme*/
            do{
                printf("Plusieurs choix sont disponibles :\n");
                printf("0 - Changement d'avis, ne rien lui donner, ne pas l'aider\n");
                printf("1 - Donner de la nourriture pour qu'il reprenne des forces\n");
                if(mk!=-1){   //Si le joueur n'a pas le medical kit
                    printf("2 - Utiliser le medical kit pour lui soigner ses blessures\n");
                    printf("3 - Donner de la nourriture et utiliser le medical kit\n");
                }
                printf("Comment souhaitez-vous l'aider ?\n");
                scanf("%d", &choix);

                /*Si le joueur n'a pas le medical kit*/
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
                printf("Votre choix de ne pas aider cet homme a bien été enregisté. Vous pouvez repartir explorer la map !\n");
                return 0;
            }
            else{
                /*Donnation de nourriture(s)*/
                if((choix==1)||(choix==3)){
                    int food, ali, j;

                    /*Choix du nombre d'aliment à donner*/
                    do{
                        printf("Vous pouvez lui donner :\n");
                        printf("1 - Un aliment\n");
                        printf("2 - Deux aliments\n");
                        printf("Quel est votre choix ? ");
                        scanf("%d", &food);

                        if(food < 1 || food > 2)
                            printf("Valeur incorrecte. Veuillez resaissir.\n");
                    }while(food < 1 || food > 2);

                    printf("Il faut maintenant choisir quoi donner au ");
                    if (pers == 0)
                        printf("soldat.\n");
                    else
                        printf("policier.\n");

                    /*Donation d'aliments*/
                    for(i=0; i<food; i++){
                        /*Choix de l'aliment*/
                        do{
                            printf("Voici la liste des aliments dont vous êtes en possession :\n");
                            /*Affichage des items de type food*/
                            for(j=0; j<cpt; j++){   //j<cpt car ind_items_soin[cpt] = -1 ou indice medical_kit
                                printf("N°%d - %s\n", j, player->inventory[ind_items_soin[j]].name);
                            }
                            printf("Entrer le numéro de l'aliment ");
                            if(food == 2)
                                printf("%d", i+1);
                            printf(" à donner : ");
                            scanf("%d", &ali);

                            if(ali < 0 || ali > cpt-1)
                                printf("Valeur incorrecte. Veuillez resaissir.\n");
                        }while(ali < 0 || ali > cpt-1);

                        /*Suppresion de l'aliment choisi dans l'inventaire du joueur*/
                        printf("L'item %s a bien été utilisé pour aider l'homme.\n", player->inventory[ind_items_soin[ali]].name);
                        delete_item_in_inventory(player, player->inventory[ind_items_soin[ali]]);
                    }
                }
                /*Utilisation du medical kit*/
                if(choix>1){
                    delete_item_in_inventory(player, player->inventory[mk]);
                    printf("Le medical kit a bien été utilisé pour soigner l'homme.\n");
                }
                printf("Il va beaucoup mieux grâce à vous !");
                printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte. . Elle est en plastique avec un liseret noir sur la longueur et fait la taille d'un carte bancaire.\n");
                /*Si le joueur a beaucoup aider l'homme : 2 aliments ou medical_kit ou les 2, des informations sur le nouvel item lui sont donn�es*/
                if((choix==2) || (choix==3) || (food==2))
                    printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y refugier et donc sauver ta vie.\"\n");
                add_item_to_inventory(player,*pass_card); //Ajout du pass card à l'inventaire du joueur
                printf("Apres cette rencontre il est temps de retourner explorer la map.\n");
                quete->soin=2;
                return 0;
            }

        }
        /*Le joueur ne possede qu'un seul item pouvant etre utile a l'homme*/
        else if(cpt==1){
            printf("Vous êtes en possession d'un seul item pouvant aider l'homme affaiblis.\n");
            printf("Il s'agit de l'item %s. ", player->inventory[ind_items_soin[0]].name);
            /*Explications des bien fait de l'item*/
            if(mk!=-1) //Si l'item est le medical kit
                printf("Grâce à cela l'homme pourrait soigner ses blessures et repartir au combat.\n");
            else
                printf("Grâce à cela l'homme pourrait reprendre un peu de force pour allez trouver un lieu ou se soigner.\n");

            /*Le joueur choisi d'utiliser l'item ou non*/
            do{
                printf("Vous avez deux possibilites : \n");
                printf("1 - Changement d'avis, ne rien utiliser, ne pas l'aider\n");
                printf("2 - Utiliser l'item du dessus\n");
                printf("Laquelle choisissez-vous ? ");
                scanf("%d", &choix);

                if(choix < 1 || choix > 2)
                    printf("Valeur incorrecte. Veuillez resaissir.\n");
            }while(choix < 1 || choix > 2);

            /*Le joueur change d'avis, fin de la quete*/
            if(choix==1){
                printf("Votre choix de ne pas aider cet homme a bien été enregistré. Repartez explorer la map!\n");
                return 0;
            }
            /*Le joueur donne le seul item utile en sa possession*/
            else if(choix==2){
                /*Suppresion l'item dans l'inventaire du joueur*/
                printf("L'item %s a bien été utilisé pour aider l'homme, il va mieux grâce à vous !\n", player->inventory[ind_items_soin[0]].name);
                delete_item_in_inventory(player,player->inventory[ind_items_soin[0]]);

                printf("Pour vous remercier de votre bienveillance l'homme vous donne une carte. Elle est en plastique avec un liseret noir sur la longueur et fait la taille d'un carte bancaire.\n");
                /*Si le seul item utile est le medical_kit des informations sur le nouvel item sont données au joueur*/
                if(mk!=-1)
                    printf("\"Prends ceci, cela te sera utile, tu pourras acceder au bunker pour t'y refugier et donc sauver ta vie.\"\n");
                add_item_to_inventory(player,*pass_card); //Ajout du pass crad à l'inventaire du joueur
                printf("Apres cette rencontre il est temps de retourner explorer la map.\n");
                quete->soin=2;
                return 0;
            }
        }
    }
    /*Le joueur ne possède aucun item utile, il ne peut pas aider l'homme*/
    else if(cpt == 0){
        printf("Désolé mais vous ne possedez aucun item pouvant venir en aide a cet homme...\n");
        quete->soin=3;
        return 0;
    }
    return(-1);
}


/**
 * \fn void quete_soin(perso_t * player, quete_t * quete, item_t * Tab_Items)
 * \brief Deroulement de la quete "soin" : rencontre d'un individu blesse.
 * \details
    Le joueur rencontre un individu blesse. Il a le choix entre l'ignorer, lui voler ses items ou l'aider.
    Cet individu est un homme de l'Etat, en charge de la protection des civiles (policier ou soldat).
    Pour pouvoir aider le blesse le joueur doit être en possession du medical kit ou de nourriture.
 * \param perso_t * player
 * \param quete_t * quete
 * \param item_t * Tab_Items
 * \return Retourne un \a int : 0 si le jeu continue et -1 si probleme dans la quete.
*/
int quete_soin(perso_t * player, quete_t * quete, item_t * Tab_Items){
    int pers, choix, conf, ok;

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
        printf("2 - Vous lui voler les items qu'il possede, apres tout il n'en n'aura bientot plus besoin vu son etat.\n");
        printf("3 - Vous lui venez en aide. Vous aimeriez bien que quelqu'un fasse pareil pour vous dans sa situation.\n");

        scanf("%d", &choix);

        if (choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Si le joueur ignore l'homme blesse*/
    if (choix == 1){
         printf("Continuons a explorer la map !\n");
         return 0;
    }
    else{
        /*Creation de l'item pass_card*/
        item_t * pass_card = malloc(sizeof(item_t));
        pass_card = creer_item("pass card", misc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        /*Si le joueur decide de voler les items du blesse*/
        if (choix == 2){
            int nb_items_vole;

            printf("A l'attaque ! Recuperez ce que vous pouvez sur lui.\n");
            printf("Vous vous approchez de l'homme pour commencer à le dépouiller, celui-ci vous supplis de ne pas le faire.\n");
            printf("Il vous dit que ses équipements son les dernières choses qui lui reste pour survivre. Il pourrat peut-etre en récupérer une somme afin de payer des soins.\n");

            /*Le joueur confirme ou non son choix de dépouiller l'homme blessé*/
            do{
                printf("Face à cette situation vous avez deux possibilités :\n");
                printf("1 - Voler tout de même les items de l'homme même si il ne pourra pas survivre\n");
                printf("2 - Renoncer aux items pour lui laisser une chance de s'en sortir\n");
                printf("Votre choix : ");
                scanf("%d", &conf);

                if(conf<1 || conf>2)
                    printf("Valeur incorrecte. Veuillez ressaisir.\n");
            }while(conf<1 || conf>2);

            /*Le joueur confirme vouloir voler les items de l'homme affaiblis*/
            if(conf==1){
                /*Creation du npc blesse*/
                npc_t * blesse;
                blesse = init_npc_quete(Tab_Items, pers);

                /*Nombre d'items volé à l'homme blesse*/
                nb_items_vole = (rand()%3)+1; //Donne le nombre d'items que le joueur a reussi a voler (+1 pour le pass card : obligatoirement trouve)
                ok = recup_items_vole(player, nb_items_vole, blesse, pass_card,quete);
                if(ok!=0){
                    printf("ERREUR : fonction recup_items_vole()\n");
                    return(-1);
                }
                else
                    return ok;
            }
            /*Le joueur renonce a voler les items du npc blesse*/
            else if(conf==2){
                printf("Vous avez choisi de laisser une chance à l'homme de vivre en ne récupérant pas ses items. Il faut maintenant allez explorer la map.\n");
                return 0;
            }
        }
        /*Si le joueur vient en aide a l'homme blesse*/
        else if(choix==3){
            printf("Pour l'aidez au mieux, il faudrait que vous ayez dans votre inventaire : de la nourriture, de la boisson ou un kit medical.\n");
            printf("Regardez ce que vous avez en votre possession.\n");
            display_inventory(*player); //Affichage de l'inventaire

            /*Le joueur a le choix de confirmer ou non vouloir aider le npc*/
            do{
                printf("A la vue de votre inventaire, et des items que vous possédez souhaitez-vous toujours aidé l'homme ?\n");
                printf("1 - Oui\n");
                printf("2 - Non\n");
                printf("Quelle est votre réponse ? ");
                scanf("%d", &conf);

                if(conf<1 || conf>2)
                    printf("Valeur incorrecte. Veuillez ressaisir.\n");
            }while(conf<1 || conf>2);

            /*Le joueur a confirmé vouloir aider l'homme*/
            if(conf==1){
                ok = aider_homme_blesse(player, pass_card, quete, pers);
                if(ok!=0){
                    printf("ERREUR : fonction aider_homme_blesse()\n");
                    return(-1);
                }
                else
                    return ok;
            }
            /*Le joueur ne confirme pas son choix initiale, il n'aide pas l'homme*/
            else if(conf==2){
                printf("Votre choix de renoncer à aider cet homme a bien été enregistré. Repartez explorer la map!\n");
                return 0;
            }
        }
    }
    return (-1);
}
