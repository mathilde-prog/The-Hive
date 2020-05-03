#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file quete_recherche.c
 * \brief Fonctions utilisees dans la quete "recherche".
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/

void init_items_recherche(item_t * Tab_items_search, item_t * Tab_Items, int nb_items_urbain){
    int i, num, cpt;

    for(i=0, cpt=0; i<nb_items_urbain; i++){
        num = rand()%nb_items_urbain;
        /*Si l'item peut etre trover d'un hexagone de categorie urbain*/
        if(Tab_Items[num]->pc_urban != 0){
            Tab_items_search[cpt] = Tab_Items[num];
            cpt++;
        }
    }
}

int compte_items_urbain(item_t * Tab_Items, int nb_items_available){
    int i, cpt;

    for(i=0, cpt=0; i<nb_items_available; i++){
        if(Tab_Items[i]->pc_urban != 0)
            cpt++;
    }
    return cpt;
}


/**
 * \fn void quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete, quest_map[6][2], item_t * Tab_Items, int nb_items_available)
 * \brief Acc�s � la quete "recherche".
 * \details
    Le joueur doit aller � un endroit donn� pour trouver un item et le ramener.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \param quete_t * quete
 * \param quest_map[6][2];
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Retourne un \a int : 0 si le jeu continue et -1 si probl�me dans la quete.
*/
int quete_recherche(perso_t * player, cell_t map[D][D], quete_t * quete, quest_map[6][2], item_t * Tab_Items, int nb_items_available){
    int nb_items_urban, num, choix, conf;

    /*Si la quete n'est pas encore commenc�, ou que le joueur y a deja renonc�*/
    if(quete->recherche.trouve==-1){
        quete->recherche.situation=0;

        nb_items_urbain = compte_items_urbain(Tab_Items, nb_items_available); //Nombre d'item que l'on peut trouver dans les hexagones de categorie urbain
        /*Cr�ation d'un tableau contenant les items que l'on peux trouver dans un haxagon de categorie urbain*/
        item_t Tab_items_search = malloc(nb_items_urbain * sizeof(item_t));
        init_items_recherche(&Tab_items_search, Tab_Items, nb_items_urbain);

        /*Generation aleatoire de l'item � trouver*/
        num = rand()%nb_items_urbain;
        quete->recherche.wanted = Tab_items_search[num];

        /*Description de la situation*/
        printf("Vous croiser la chemin d'un homme qui para�t sympathique. Il vient � votre rencontre, vous commencez � discuter.\n");
        printf("Il vous explique qu'il connait tr�s bien cette map, et qu'il pourrait vous aider � vous mettre en s�curit� dans un lieu discret.\n");
        printf("Vous �tes tr�s int�ress� par l'aide qu'il vous propose, et il l'a tr�s bien compris. Il vous propose un march� :\n");
        printf("\"J'ai besoin de trouver l'item %s, si tu acceptes d'aller me chercher cet item et de me la ramener par la suite, je t'aiderais � te sortir d'ici.\"\n", quete->recherche.wanted.name);

        do{
            printf("Vous avez deux possibilites :\n");
            printf("1 - Accepter la requete de l'homme\n");
            printf("2 - Ne pas l'accepter\n");
            printf("Que choisissez vous ?\n");
            scanf("%d", &choix);

            if(choix<1 || choix>2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(choix<1 || choix>2);

        /*Le joueur souhaite trouver l'item*/
        if(choix){
            printf("L'homme est heureux de votre r�ponse, il vous donne plus de d�tails sur votre mission :\n");
            printf("\"Tu as le choix d'aller dans une ville, dans un marchet ou dans une favella pour trouver l'item %s. Une fois que tu as trouve l'item il faudra que tu revienne ici pour me le redonner. ", quete->recherche.wanted.name);
            printf("Bien entendu si ton inventaire est plein, tu devras �changer l'item que je te demande contre un en ta possession.\"\n");

            printf("A ce moment pr�sent ton inventaire contient %d items sur %d items possible.\n", player->nb_items_inventory, INVENTORY_CAPACITY);
            do{
                printf("Souhaitez-vous toujours trouver l'item demand� par l'homme ?\n");
                printf("1 - Oui\n");
                printf("2 - Non\n");
                printf("Votre choix : ");
                scanf("%d", &conf);

                if(conf<1 || conf>2)
                    printf("Valeur incorrecte. Veuillez resaissir.\n");
            }while(conf<1 || conf>2);

            /*Le joueur renonce � la requete*/
            if(conf==2){
                printf("Vous lui annoncez renoncer � cette requ�te, il es de�u mais vous laisse repartir explorer la map.\n");
                return 0;
            }
            /*Le joueur continue la requete*/
            else{
                printf("C'est parti, a vous de trouver l'item %s que l'homme vous demande !\n", quete->recherche.wanted.name);
                quete->recherche.trouve=0;
                return 0;
            }
        }
        /*Le joueur ne souhaite pas trouver l'item demand� par l'homme*/
        else{
            printf("Vous lui annoncez ne pas souhaitez honorer cette requ�te, il es de�u mais vous laisse repartir explorer la map.\n");
            return 0;
        }
        return (-1);
    }

    /*Si la quete est d�ja commenc� par le joueur, et qu'il est entrain de chercher l'item, il souhaite rechercher les items sur l'hexagone actuel*/
    else if(quete->recherche.trouve==0){
        /*Le joueur n'est pas sur un hexagone de categorie urbain*/
        if(map[player->posX][player->posY].categ != urbain){
            printf("Vous ne pourrez pas trouver l'item %s recherch� par l'homme ici, vous n'�tes ni en ville, ni au marchet et pas dans une favella.\n", quete->recherche.wanted.name);
            printf("Continuez votre route sur la map, afin d'aller dans un des lieux sit�s ci-dessus.\n");
            return 0;
        }
        /*Le joueur est sur un hexagone de categorie urbain*/
        else{
            printf("Vous �tes dans un lieu o� vous pouvez trouver l'item %s recherch� par l'homme !\n", quete->recherche.wanted.name);
            /*Recherche d'items et verification si item trouve par le joueur*/
            scavenge(map,&player,Tab_Items,nb_items_available);
            /*L'item a �t� trouv� par le joueur sur l'hexagone*/
            if(item_in_inventory(*player,quete->recherche.wanted.name) != -1){
                printf("F�licitations, vous avez trouv� l'item %s que l'homme vous a demande ! Il faut maintenant aller le retrouver pour lui donner.\n", quete->recherche.wanted.name);
                quete->recherche.trouve=1;
                return 0;
            }
            /*L'item n'a pas �t� trouv� par le joueur sur l'hexagone, ou ce dernier n'a pas souhaitez l'ajouter � son inventaire*/
            else{
                printf("Vous n'avez pas trouv� l'item recherch� %s, cela sera pour une prochaine fois dans un autre lieu.\n", quete->recherche.wanted.name);
                return 0;
            }
        }
        return (-1);
    }

    /*Le joueur a trouv� par le joueur, il doit maintenant le donner � l'homme*/
    else if(quete->recherche.trouve==1){
        /*Le joueur n'est pas sur le bon hexagone pour retrouver l'homme*/
        if(map[player->posX][player->posY] != map[quest_map[5][0]][quest_map[5][1]]){
            printf("Vous ne pourrez pas retrouver l'homme ici, vous n'�tes pas sur ce lieu de votre rencontre.\n");
            printf("Continuez votre route sur la map, afin de retouver l'homme.\n");
            return 0;
        }
        /*Le joueur n'est pas sur le bon hexagone pour retrouver l'homme*/
        else{
            printf("Vous �tes dans le lieu o� vous avez rencontr� l'homme !\n");
            printf("Il se tient face a vous avec un grand sourire. Vous lui donnez son item, il est au passage retir� de votre inventaire. Il vous remercie �norm�ment de lui avoi rendu ce service.\n");
            delete_item_in_inventory(player, quete->recherche.wanted);
            printf("Pour vous remercier, et comme il vous l'avez promis il vous indique le lieu o� vous pourrez vous r�fugier et ainsi vous mettre en s�curit�.\n");
            printf("Voil� les coordonn�es : X=%d, Y=%d\n", quete->recherche.bunkerX, quete->recherche.bunkerY);
            quete->recherche.situation=1;
            return 0;
        }
    }
    return (-1);
}
