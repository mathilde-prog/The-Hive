#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file quetes.c
 * \brief Fonctionalité : Actionner quêtes du jeu.
 * \author Mathilde Mottay, Anaïs Mottier, Clément Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/


/**
 * \fn int quete(int quest_id)
 * \brief Récupère le numéro de la quete pour par la suite accéder à la quete correspondante.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quetes(perso_t * player, cell_t map[D][D]){
    int ok;

    /*Initialisation d'une structure quete_t*/
    quete_t * quete;
    quete->soin=-1;
    quete->recherche=-1;

    switch (map[player->posX][player->posY].quest_id){
        case 1 : clrscr(); ok = quete_montagne(&player); clrscr(); break;
        case 2 : clrscr(); ok = quete_frontiere(&player, &quete); clrscr(); break;
        case 3 : clrscr(); ok = quete_bunker(&player); clrscr(); break;
        case 4 : clrscr(); ok = quete_bandits(&player); clrscr(); break;
        case 5 : clrscr(); ok = quete_soin(&player, &quete); clrscr(); break;
        case 6 : clrscr(); ok = quete_recherche(&player, &quete); clrscr(); break;
        default : printf("ERREUR : aucune quete ne correspond au quest_id donné : %d", map[player->posX][player->posY].quest_id); break;
    }
    return ok;
}

/**
 * \fn void quete_montagne(perso_t * player)
 * \brief Accès à la quete de la montagne.
 * \details
    Le joueur a le choix de franchir la montagne (finir le jeu) ou non.
    Si il a en sa possession l'équipement de montagne alors ses chances de séchapper sont imporantes. Mais si il ne l'a pas il est très risqué pour lui de vouloir s'échapper.
    La chance est donné en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_montagne(perso_t * player){
    int choix, num_r, num_w, chance;

    /*Description du lieu et de la situation*/
    printf("Vous vous trouvez face à la montagne ! De l'autre coté de celle-ci vous retrouverez votre liberté et la paix.\n");
    printf("La montagne est un endroit périlleux ! Il faut de l'énergie, du courage, et matériel adapter à la montagne si on veut réussir à la franchir.\n");

    /*Récupération des indices des items rope et walking_stick*/
    num_r = item_in_inventory(*player,"rope");
    num_w = item_in_inventory(*player,"walking_stick");
    /*Si le joueur possède l'équipement complet*/
    if((num_r != -1) && (num_w != -1)){
        printf("Bonne nouvelle, vous etes en possession des bons équipements pour la montagne !\n");
        chance = 100;
    }
    else{
        /*Si le joueur possède uniquement la corde*/
        if(num_r != -1){
            printf("Vous ne possédez qu'une corde pour vous aider à escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
            chance = 45;
        }
        else{
            /*Si le joueur possède uniquement le baton de marche*/
            if(num_w !=-1){
                printf("Vous ne possédez que la baton de marche pour vous aider à escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
                chance = 45;
            }
            /*Si le joueur ne possède aucun équipement de montagne*/
            else{
                printf("Malheureusement vous n'avez aucun équipement pour la montagne... L'escalader serait presque mission impossible. Le risque de mourrir est important.\n");
                chance = 5;
            }
        }
    }
    printf("Beaucoup de personnes y ont laissé leur vie, en voulant défier ce monstre de roche.");

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
            delete_item_in_inventory(&player, player->inventory[num_r]);
            delete_item_in_inventory(&player, player->inventory[num_w]);
            printf("Vous avez les équipements adapter pour escalader ce gros rocher, vous arrivez à gravir la montagne sans soucis. Vous voilà de l'autre coté !\n");
            return exit_game();
        }
        /*Si sa chance de franchir la montagne est de 5 ou 1*/
        else{
            int sortie;

            /*Suppression des items  de son inventaire qu'il va utiliser*/
            if (num_r != -1)
                delete_item_in_inventory(&player, player->inventory[num_r]);
            if (num_w != -1)
                delete_item_in_inventory(&player, player->inventory[num_w]);
            sortie = rng(chance); //Fonction déterminant si le joueur réussi a s'échapper ou non
            if(sortie == 1){
                printf("Félicitations, malgré la grande difficulté de l'ascension vous y êtes arrivés ! Vous voilà de l'autre coté !\n");
                return exit_game();
            }
            else{
                printf("C'est fini ! Malheureusement la difficulté de l'ascension été trop importante !\n");
                printf("Vous n'avez pas réussi a sortir de la map. Vous venez de perdre de la vie !\n");
                return 1;
            }
        }
    }
    else {
        printf("Vous êtes prudent, continuez d'explorer la map et peut-être trouverez-vous l'équipement parfait pour la gravir plus tard !\n");
        return 0;
    }
    return (-1);
}



/**
 * \fn void quete_frontiere(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "frontière".
 * \details
    Le joueur trouvé la sortie de la frontière, il a le choix de la franchir (finir le jeu) ou non.
    Si il a jouer la quete "soin" et qu'il a aidé l'homme blessé alors ses chances de la franchir sont imporantes. Mais si il ne l'a pas fait,ses chances sont moins importantes.
    La chance est donné en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_frontiere(perso_t * player, quete_t * quete){
    int choix, chance, sortie;

    /*Description du lieu et de la situation*/
    printf("Vous vous à la frontière ! De l'autre coté de celle-ci vous retrouverez votre liberté et la paix.\n");
    printf("La frontière est pleine de soldats ! Il faut réussir a passer à travers les contrôles.\n");

    /*Choix du joueur : franchir ou non la frontière*/
    do{
        printf("Deux choix s'offrent à vous :\n");
        printf("0 - Vous ne tentez pas le franchissement de la frontière\n");
        printf("1 - Vous essayer de passer le frontière\n");
        printf("Que choisissez-vous ? ");
        scanf("%d", &choix);

        if(choix < 0 || choix > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 0 || choix > 1);

    /*Le joueur tente le franchissement de la frontière*/
    if(choix == 1){
        /*Si le joueur a aidé l'homme blesse (quete "soin")*/
        if(quete->soin == 1){
            printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et aider lors de votre exploration et qui vous avez donner la carte !\n");
            printf("Il vous aperçoit également et viens à votre rencontre. Il vous remercie une nouvelle fois.\n");
            printf("Au fil de la discussion ce dernier comprend pourquoi vous êtes ici. Il décide de vous aider à passer la frontière.\n");
            printf("Il part voir ses collègues, après quelques minutes à attendre il vous fait signe de le rejoindre.\n");
            printf("Vous passez la frontière grâce a cet homme plein de bonté. Ca y est vous etes libre !\n");
            return exit_game();
        }
        else{
            /*Si le joueur voulu aider l'homme blesse (quete "soin") mais sans succes*/
            if(quete->soin == 0){
                printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et tenté d'aider lors de votre exploration mais vous n'aviez pas les bons items en votre possession.\n");
                printf("Il vous aperçoit également et viens à votre rencontre. Il vous remercie d'avoir voulu essayer de l'aider.\n");
                printf("Au fil de la discussion ce dernier comprend pourquoi vous êtes ici. Il vous informe qu'il va voir ce qu'il peut faire pour vous aider à passer la frontière.\n");
                printf("Rien n'est gagner malheureusement, vous attendez son retour...\n");
                chance = 65;
            }
            else{
                int pass;

                /*Récupération de l'indice du pass_card dans l'inventaire*/
                pass = item_in_inventory(*player,"pass_card");

                /*Si le joueur possède le pass_card*/
                if(pass !=-1){
                    printf("Vous vous rappelez soudainement que vous êtes en possession du pass (carte plastique).\n");
                    printf("Il pourrait peut-etre vous permettre de franchir la frontière. Vous décidez de le montrer à un des soldats présents.\n");
                    chance = 50;
                }
                else
                    chance = 15;
            }
            /*Détermination de la réussite de franchissement de la frontière ou non par le calcul de la fonction rng*/
            sortie = rng(chance);
            switch(sortie){
                case 0 :    printf("Vous n'avez pas réussi a franchir la frontière malheureusement...\n");
                            printf("Retourner explorer la map pour trouver une autre manière d'en sortir.\n");
                            return 0;
                case 1 :    printf("Félicitations, vous avez réussi a franchir la frontière ! Vous voilà de l'autre coté !\n");
                            return exit_game();
                default :   printf("ERREUR : sortie est different de 0 et 1\n");
                            return (-1);
            }
        }
    }
    /*Le joueur ne souhaite pas tentez le franchissement de la frontière*/
    else{
        printf("Vous ne souhaitez pas franchir pas la frontière. Continuez d'explorer la map.\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_bunker(perso_t * player)
 * \brief Accès à la quete du bunker.
 * \details
    Si le joueur possède le pass_card il aura le choix de rentrer dans le bunker ou non.
    Sinon il fait demi-tour.
 * \param perso_t * player
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_bunker(perso_t * player){
    int choix, num;

    /*Description de l'univers, du lieu*/
    printf("Vous venez d'arriver sur un lieu très étrange... Une énorme porte se dresse devant vous ! \n");
    printf("Elle est en métal, sans ouverture, camouflée par une verdure sauvages, un petit boitié éléctronique se trouve sur la droite. \n");
    printf("Elle est tellement lourde qu'il est impossible pour vous de l'ouvrir ne serait ce que d'un millimètre.\n");
    /*Récupération du numéro de l'item pass_card dans l'inventaire*/
    num = item_in_inventory(*player,"pass_card");

    /*Si le joueur à le pass_card dans son inventaire*/
    if (num != -1){
        do{
            printf("Ce boitier est peut-etre un moyen d'entrer dans ce lieu ressemblant à un bunker... Souhaitez-vous y entrer ?");
            printf(" 1 - Oui\n 2 - Non\n");
            scanf("%d", &choix);
            if (choix < 1 || choix > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(choix < 1 || choix > 2);
        /*Le joueur souhaite entrer dans le bunker*/
        if (choix == 1){
            /*Suppression de l'item pass_card de son inventaire*/
            delete_item_in_inventory(&player, player->inventory[num]);
            printf("Vous avez besoin d'un pass, heureusement vous en possédé un ! Vous venez d'entrer à l'interieur du bunker !\n");
            printf("Ca y est vous êtes sauvés ! Vous êtes en sécurité et venez de trouver l'une des sorties ! ");
            return exit_game(); //1 si quitte la map, 0 si continue.
        }
        /*Le joueur décide de ne pas entrer dans le bunjer*/
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


