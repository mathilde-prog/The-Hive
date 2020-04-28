#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file quetes.c
 * \brief Fonctionalit� : Actionner qu�tes du jeu.
 * \author Mathilde Mottay, Ana�s Mottier, Cl�ment Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/


/**
 * \fn int quete(int quest_id)
 * \brief R�cup�re le num�ro de la quete pour par la suite acc�der � la quete correspondante.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quetes(perso_t * player, cell_t map[D][D]){
    int ok;

    /*Initialisation d'une structure quete_t*/
    quete_t * quete = malloc(sizeof(quete_t));
    quete->soin=-1;
    quete->recherche=-1;

    switch (map[player->posX][player->posY].quest_id){
        case 1 : clrscr(); ok = quete_montagne(player); clrscr(); break;
        case 2 : clrscr(); ok = quete_frontiere(player,quete); clrscr(); break;
        case 3 : clrscr(); ok = quete_bunker(player); clrscr(); break;
  //    case 4 : clrscr(); ok = quete_bandits(player); clrscr(); break;
        case 5 : clrscr(); ok = quete_soin(player,quete); clrscr(); break;
  //    case 6 : clrscr(); ok = quete_recherche(player,quete); clrscr(); break;
        default : printf("ERREUR : aucune quete ne correspond au quest_id donn� : %d", map[player->posX][player->posY].quest_id); break;
    }
    return ok;
}

/**
 * \fn void quete_montagne(perso_t * player)
 * \brief Acc�s � la quete de la montagne.
 * \details
    Le joueur a le choix de franchir la montagne (finir le jeu) ou non.
    Si il a en sa possession l'�quipement de montagne alors ses chances de s�chapper sont imporantes. Mais si il ne l'a pas il est tr�s risqu� pour lui de vouloir s'�chapper.
    La chance est donn� en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_montagne(perso_t * player){
    int choix, num_r, num_w, chance;

    /*Description du lieu et de la situation*/
    printf("Vous vous trouvez face � la montagne ! De l'autre cot� de celle-ci vous retrouverez votre libert� et la paix.\n");
    printf("La montagne est un endroit p�rilleux ! Il faut de l'�nergie, du courage, et mat�riel adapter � la montagne si on veut r�ussir � la franchir.\n");

    /*R�cup�ration des indices des items rope et walking_stick*/
    num_r = item_in_inventory(*player,"rope");
    num_w = item_in_inventory(*player,"walking_stick");
    /*Si le joueur poss�de l'�quipement complet*/
    if((num_r != -1) && (num_w != -1)){
        printf("Bonne nouvelle, vous etes en possession des bons �quipements pour la montagne !\n");
        chance = 100;
    }
    else{
        /*Si le joueur poss�de uniquement la corde*/
        if(num_r != -1){
            printf("Vous ne poss�dez qu'une corde pour vous aider � escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
            chance = 45;
        }
        else{
            /*Si le joueur poss�de uniquement le baton de marche*/
            if(num_w !=-1){
                printf("Vous ne poss�dez que la baton de marche pour vous aider � escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
                chance = 45;
            }
            /*Si le joueur ne poss�de aucun �quipement de montagne*/
            else{
                printf("Malheureusement vous n'avez aucun �quipement pour la montagne... L'escalader serait presque mission impossible. Le risque de mourrir est important.\n");
                chance = 5;
            }
        }
    }
    printf("Beaucoup de personnes y ont laiss� leur vie, en voulant d�fier ce monstre de roche.");

    /*Le joueur choisi si il franchit ou pas la montagne*/
    do{
        printf("Allez-vous tenter son ascension ?\n 1 - Oui\n 2 - Non\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 2)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 2);
    /*Choix d'escalader la montagne*/
    if (choix == 1){
        printf("Allons franchir cette montagne !\n");
        /*Si sa chance de gravir la montagne est de 10*/
        if (chance == 100){
            /*Suppression des items  de son inventaire qu'il va utiliser*/
            delete_item_in_inventory(player, player->inventory[num_r]);
            delete_item_in_inventory(player, player->inventory[num_w]);
            printf("Vous avez les �quipements adapter pour escalader ce gros rocher, vous arrivez � gravir la montagne sans soucis. Vous voil� de l'autre cot� !\n");
            return exit_game();
        }
        /*Si sa chance de franchir la montagne est de 5 ou 1*/
        else{
            int sortie;

            /*Suppression des items  de son inventaire qu'il va utiliser*/
            if (num_r != -1)
                delete_item_in_inventory(player, player->inventory[num_r]);
            if (num_w != -1)
                delete_item_in_inventory(player, player->inventory[num_w]);
            sortie = rng(chance); //Fonction d�terminant si le joueur r�ussi a s'�chapper ou non
            if(sortie == 1){
                printf("F�licitations, malgr� la grande difficult� de l'ascension vous y �tes arriv�s ! Vous voil� de l'autre cot� !\n");
                return exit_game();
            }
            else{
                printf("C'est fini ! Malheureusement la difficult� de l'ascension �t� trop importante !\n");
                printf("Vous n'avez pas r�ussi a sortir de la map. Vous venez de perdre de la vie !\n");
                return 1;
            }
        }
    }
    else {
        printf("Vous �tes prudent, continuez d'explorer la map et peut-�tre trouverez-vous l'�quipement parfait pour la gravir plus tard !\n");
        return 0;
    }
    return (-1);
}



/**
 * \fn void quete_frontiere(perso_t * player, quete_t * quete)
 * \brief Acc�s � la quete "fronti�re".
 * \details
    Le joueur trouv� la sortie de la fronti�re, il a le choix de la franchir (finir le jeu) ou non.
    Si il a jouer la quete "soin" et qu'il a aid� l'homme bless� alors ses chances de la franchir sont imporantes. Mais si il ne l'a pas fait,ses chances sont moins importantes.
    La chance est donn� en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_frontiere(perso_t * player, quete_t * quete){
    int choix, chance, sortie;

    /*Description du lieu et de la situation*/
    printf("Vous vous � la fronti�re ! De l'autre cot� de celle-ci vous retrouverez votre libert� et la paix.\n");
    printf("La fronti�re est pleine de soldats ! Il faut r�ussir a passer � travers les contr�les.\n");

    /*Choix du joueur : franchir ou non la fronti�re*/
    do{
        printf("Deux choix s'offrent � vous :\n");
        printf("0 - Vous ne tentez pas le franchissement de la fronti�re\n");
        printf("1 - Vous essayer de passer le fronti�re\n");
        printf("Que choisissez-vous ? ");
        scanf("%d", &choix);

        if(choix < 0 || choix > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 0 || choix > 1);

    /*Le joueur tente le franchissement de la fronti�re*/
    if(choix == 1){
        /*Si le joueur a aid� l'homme blesse (quete "soin")*/
        if(quete->soin == 1){
            printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et aider lors de votre exploration et qui vous avez donner la carte !\n");
            printf("Il vous aper�oit �galement et viens � votre rencontre. Il vous remercie une nouvelle fois.\n");
            printf("Au fil de la discussion ce dernier comprend pourquoi vous �tes ici. Il d�cide de vous aider � passer la fronti�re.\n");
            printf("Il part voir ses coll�gues, apr�s quelques minutes � attendre il vous fait signe de le rejoindre.\n");
            printf("Vous passez la fronti�re gr�ce a cet homme plein de bont�. Ca y est vous etes libre !\n");
            return exit_game();
        }
        else{
            /*Si le joueur voulu aider l'homme blesse (quete "soin") mais sans succes*/
            if(quete->soin == 0){
                printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et tent� d'aider lors de votre exploration mais vous n'aviez pas les bons items en votre possession.\n");
                printf("Il vous aper�oit �galement et viens � votre rencontre. Il vous remercie d'avoir voulu essayer de l'aider.\n");
                printf("Au fil de la discussion ce dernier comprend pourquoi vous �tes ici. Il vous informe qu'il va voir ce qu'il peut faire pour vous aider � passer la fronti�re.\n");
                printf("Rien n'est gagner malheureusement, vous attendez son retour...\n");
                chance = 65;
            }
            else{
                int pass;

                /*R�cup�ration de l'indice du pass_card dans l'inventaire*/
                pass = item_in_inventory(*player,"pass_card");

                /*Si le joueur poss�de le pass_card*/
                if(pass !=-1){
                    printf("Vous vous rappelez soudainement que vous �tes en possession du pass (carte plastique).\n");
                    printf("Il pourrait peut-etre vous permettre de franchir la fronti�re. Vous d�cidez de le montrer � un des soldats pr�sents.\n");
                    chance = 50;
                }
                else
                    chance = 15;
            }
            /*D�termination de la r�ussite de franchissement de la fronti�re ou non par le calcul de la fonction rng*/
            sortie = rng(chance);
            switch(sortie){
                case 0 :    printf("Vous n'avez pas r�ussi a franchir la fronti�re malheureusement...\n");
                            printf("Retourner explorer la map pour trouver une autre mani�re d'en sortir.\n");
                            return 0;
                case 1 :    printf("F�licitations, vous avez r�ussi a franchir la fronti�re ! Vous voil� de l'autre cot� !\n");
                            return exit_game();
                default :   printf("ERREUR : sortie est different de 0 et 1\n");
                            return (-1);
            }
        }
    }
    /*Le joueur ne souhaite pas tentez le franchissement de la fronti�re*/
    else{
        printf("Vous ne souhaitez pas franchir pas la fronti�re. Continuez d'explorer la map.\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_bunker(perso_t * player)
 * \brief Acc�s � la quete du bunker.
 * \details
    Si le joueur poss�de le pass_card il aura le choix de rentrer dans le bunker ou non.
    Sinon il fait demi-tour.
 * \param perso_t * player
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_bunker(perso_t * player){
    int choix, num;

    /*Description de l'univers, du lieu*/
    printf("Vous venez d'arriver sur un lieu tr�s �trange... Une �norme porte se dresse devant vous ! \n");
    printf("Elle est en m�tal, sans ouverture, camoufl�e par une verdure sauvages, un petit boiti� �l�ctronique se trouve sur la droite. \n");
    printf("Elle est tellement lourde qu'il est impossible pour vous de l'ouvrir ne serait ce que d'un millim�tre.\n");
    /*R�cup�ration du num�ro de l'item pass_card dans l'inventaire*/
    num = item_in_inventory(*player,"pass_card");

    /*Si le joueur � le pass_card dans son inventaire*/
    if (num != -1){
        do{
            printf("Ce boitier est peut-etre un moyen d'entrer dans ce lieu ressemblant � un bunker... Souhaitez-vous y entrer ?");
            printf(" 1 - Oui\n 2 - Non\n");
            scanf("%d", &choix);
            if (choix < 1 || choix > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(choix < 1 || choix > 2);
        /*Le joueur souhaite entrer dans le bunker*/
        if (choix == 1){
            /*Suppression de l'item pass_card de son inventaire*/
            delete_item_in_inventory(player, player->inventory[num]);
            printf("Vous avez besoin d'un pass, heureusement vous en poss�d� un ! Vous venez d'entrer � l'interieur du bunker !\n");
            printf("Ca y est vous �tes sauv�s ! Vous �tes en s�curit� et venez de trouver l'une des sorties ! ");
            return exit_game(); //1 si quitte la map, 0 si continue.
        }
        /*Le joueur d�cide de ne pas entrer dans le bunjer*/
        else {
           printf("On continue notre jeu ! Allons explorer la map.\n");
           return 0;
        }
    }
    /* Si le joueur n'a pas le pass_card dans son inventaire*/
    else{
        printf("Vous ne pouvez rien faire ici malheureusement. Il faut retourner sur vos pas.\n");
        return 0;
    }
    return (-1);
}
