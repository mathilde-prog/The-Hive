#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "structure.h"

/**
 * \file quetes.c
 * \brief Fonctionalite : Actionner quetes du jeu.
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/

//quete_t * quete = malloc(sizeof(quete_t));

/*Initialisation d'une structure quete_t*/
void init_quete(quete_t * quete){
    quete->soin = -1;
    quete->recherche.situation = -1;
    //quete->recherche.butX = ; A FAIRE
    //quete->recherche.butY = ; A FAIRE
    quete->bunker = -1;
    quete->montagne = -1;
    quete->frontiere = -1;
    quete->bandits = -1;
}


/**
 * \fn int quete(perso_t * player, cell_t map[D][D])
 * \brief Recupere le numero de la quete pour par la suite acceder a la quete correspondante.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quetes(perso_t * player, cell_t map[D][D], quest_map[6][2], quete_t * quete){
    int ok;

    switch (map[quest_map[0][0]][quest_map[0][1]].quest_id){
        map[quest_map[0][0]][quest_map[0][1]].quest_id
        case 1 : clrscr(); ok = quete_montagne(player, quete); clrscr(); break;
        case 2 : clrscr(); ok = quete_frontiere(player, quete); clrscr(); break;
        case 3 : clrscr(); ok = quete_bunker(player, quete); clrscr(); break;
   //     case 4 : clrscr(); ok = quete_bandits(player, quete); clrscr(); break;
        case 5 : clrscr(); ok = quete_soin(player, quete); clrscr(); break;
        case 6 : clrscr(); ok = quete_recherche(player, quete); clrscr(); break;
        default : printf("ERREUR : aucune quete ne correspond au quest_id donne : %d", map[player->posX][player->posY].quest_id); break;
    }
    return ok;
}

/**
 * \fn void quete_montagne(perso_t * player, quete_t * quete)
 * \brief Acces a la quete de la montagne.
 * \details
    Le joueur a le choix de franchir la montagne (finir le jeu) ou non.
    Si il a en sa possession l'equipement de montagne alors ses chances de s'echapper sont imporantes. Mais si il ne l'a pas il est tres risque pour lui de vouloir s'echapper.
    La chance est donne en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_montagne(perso_t * player, quete_t * quete){
    int choix, num_r, num_w, chance;

    quete->montagne=0;

    /*Description du lieu et de la situation*/
    printf("Vous vous trouvez face a la montagne ! De l'autre cote de celle-ci vous retrouverez votre liberte et la paix.\n");
    printf("La montagne est un endroit perilleux ! Il faut de l'energie, du courage, et materiel adapter a la montagne si on veut reussir a la franchir.\n");

    /*Recuperation des indices des items rope et walking_stick*/
    num_r = item_in_inventory(*player,"rope");
    num_w = item_in_inventory(*player,"walking stick");
    /*Si le joueur possede l'equipement complet*/
    if((num_r != -1) && (num_w != -1)){
        printf("Bonne nouvelle, vous etes en possession des bons equipements pour la montagne !\n");
        chance = 100;
    }
    else{
        /*Si le joueur possede uniquement la corde*/
        if(num_r != -1){
            printf("Vous ne possedez qu'une corde pour vous aider a escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
            chance = 45;
        }
        else{
            /*Si le joueur possede uniquement le baton de marche*/
            if(num_w !=-1){
                printf("Vous ne possedez que la baton de marche pour vous aider a escalader la montagne. Son franchissement serait dangereux pour votre vie.\n");
                chance = 45;
            }
            /*Si le joueur ne possede aucun equipement de montagne*/
            else{
                printf("Malheureusement vous n'avez aucun equipement pour la montagne... L'escalader serait presque mission impossible. Le risque de mourrir est important.\n");
                chance = 5;
            }
        }
    }
    printf("Beaucoup de personnes y ont laisse leur vie, en voulant defier ce monstre de roche.");

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
            printf("Vous avez les equipements adapter pour escalader ce gros rocher, vous arrivez a gravir la montagne sans soucis. Vous voila de l'autre cote !\n");
            quete->montagne=1;
            return exit_game();
        }
        /*Si sa chance de franchir la montagne est <100*/
        else{
            int sortie;

            /*Suppression des items  de son inventaire qu'il va utiliser*/
            if (num_r != -1)
                delete_item_in_inventory(player, player->inventory[num_r]);
            if (num_w != -1)
                delete_item_in_inventory(player, player->inventory[num_w]);
            sortie = rng(chance); //Fonction d�terminant si le joueur reussi a s'echapper ou non
            if(sortie == 1){
                printf("Felicitations, malgre la grande difficulte de l'ascension vous y etes arrives ! Vous voila de l'autre cote !\n");
                quete->montagne=1;
                return exit_game();
            }
            else{
                printf("C'est fini ! Malheureusement la difficulte de l'ascension ete trop importante !\n");
                printf("Vous n'avez pas reussi a sortir de la map. Vous venez de perdre de la vie !\n");
                quete->montagne=1;
                return 1;
            }
        }
    }
    else {
        printf("Vous etes prudent, continuez d'explorer la map et peut-etre trouverez-vous l'equipement parfait pour la gravir plus tard !\n");
        quete->montagne=1 //OU -1 ??
        return 0;
    }
    return (-1);
}



/**
 * \fn void quete_frontiere(perso_t * player, quete_t * quete)
 * \brief Acces a la quete "fronti�re".
 * \details
    Le joueur trouve la sortie de la frontiere, il a le choix de la franchir (finir le jeu) ou non.
    Si il a jouer la quete "soin" et qu'il a aide l'homme bless� alors ses chances de la franchir sont imporantes. Mais si il ne l'a pas fait,ses chances sont moins importantes.
    La chance est donne en un nombre entier entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/

int quete_frontiere(perso_t * player, quete_t * quete){
    int choix, chance, sortie;

    quete->frontiere=0;

    /*Description du lieu et de la situation*/
    printf("Vous vous a la frontiere ! De l'autre cote de celle-ci vous retrouverez votre liberte et la paix.\n");
    printf("La frontiere est pleine de soldats ! Il faut reussir a passer a travers les controles.\n");

    /*Choix du joueur : franchir ou non la frontiere*/
    do{
        printf("Deux choix s'offrent a vous :\n");
        printf("0 - Vous ne tentez pas le franchissement de la frontiere\n");
        printf("1 - Vous essayer de passer le frontiere\n");
        printf("Que choisissez-vous ? ");
        scanf("%d", &choix);

        if(choix < 0 || choix > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 0 || choix > 1);

    /*Le joueur tente le franchissement de la fronti�re*/
    if(choix == 1){
        /*Si le joueur a aide l'homme blesse (quete "soin")*/
        if(quete->soin == 1){
            printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et aider lors de votre exploration et qui vous avez donner la carte !\n");
            printf("Il vous apercoit egalement et viens a votre rencontre. Il vous remercie une nouvelle fois.\n");
            printf("Au fil de la discussion ce dernier comprend pourquoi vous etes ici. Il decide de vous aider a passer la frontiere.\n");
            printf("Il part voir ses collegues, apres quelques minutes a attendre il vous fait signe de le rejoindre.\n");
            printf("Vous passez la fronti�re grace a cet homme plein de bonte. Ca y est vous etes libre !\n");
            quete->frontiere=1;
            return exit_game();
        }
        else{
            /*Si le joueur a voulu aider l'homme blesse (quete "soin") mais sans succes*/
            if(quete->soin == 3){
                printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et tente d'aider lors de votre exploration mais vous n'aviez pas les bons items en votre possession.\n");
                printf("Il vous apercoit egalement et viens a votre rencontre. Il vous remercie d'avoir voulu essayer de l'aider.\n");
                printf("Au fil de la discussion ce dernier comprend pourquoi vous etes ici. Il vous informe qu'il va voir ce qu'il peut faire pour vous aider a passer la frontiere.\n");
                printf("Rien n'est gagner malheureusement, vous attendez son retour...\n");
                chance = 65;
            }
            else{
                int pass;

                /*Recuperation de l'indice du pass_card dans l'inventaire*/
                pass = item_in_inventory(*player,"pass card");

                /*Si le joueur possede le pass_card*/
                if(pass !=-1){
                    printf("Vous vous rappelez soudainement que vous etes en possession du pass (carte plastique).\n");
                    printf("Il pourrait peut-etre vous permettre de franchir la frontiere. Vous decidez de le montrer a un des soldats presents.\n");
                    chance = 50;
                }
                else
                    chance = 15;
            }
            /*Determination de la reussite de franchissement de la frontiere ou non par le calcul de la fonction rng*/
            sortie = rng(chance);
            quete->frontiere=1;
            switch(sortie){
                case 0 :    printf("Vous n'avez pas reussi a franchir la frontiere malheureusement...\n");
                            printf("Retourner explorer la map pour trouver une autre maniere d'en sortir.\n");
                            return 0;
                case 1 :    printf("Felicitations, vous avez reussi a franchir la frontiere ! Vous voila de l'autre cote !\n");
                            return exit_game();
                default :   printf("ERREUR : sortie est different de 0 et 1\n");
                            return (-1);
            }
        }
    }
    /*Le joueur ne souhaite pas tentez le franchissement de la frontiere*/
    else{
        printf("Vous ne souhaitez pas franchir pas la frontiere. Continuez d'explorer la map.\n");
        quete->frontiere=1; //OU -1 ???
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_bunker(perso_t * player, quete_t * quete)
 * \brief Accès à la quete du bunker.
 * \details
    Si le joueur possede le pass_card il aura le choix de rentrer dans le bunker ou non.
    Sinon il fait demi-tour.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si problème dans la quete.
*/

int quete_bunker(perso_t * player, quete_t * quete){
    int choix, num;

    quete->bunker=0;

    /*Description de l'univers, du lieu*/
    printf("Vous venez d'arriver sur un lieu tres etrange... Une enorme porte se dresse devant vous ! \n");
    printf("Elle est en metal, sans ouverture, camouflee par une verdure sauvages, un petit boitie electronique se trouve sur la droite. \n");
    printf("Elle est tellement lourde qu'il est impossible pour vous de l'ouvrir ne serait ce que d'un millimetre.\n");
    /*Recuperation du num�ro de l'item pass_card dans l'inventaire*/
    num = item_in_inventory(*player,"pass card");

    /*Si le joueur a le pass_card dans son inventaire*/
    if (num != -1){
        do{
            printf("Ce boitier est peut-etre un moyen d'entrer dans ce lieu ressemblant a un bunker... Souhaitez-vous y entrer ?");
            printf(" 1 - Oui\n 2 - Non\n");
            scanf("%d", &choix);
            if (choix < 1 || choix > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(choix < 1 || choix > 2);
        /*Le joueur souhaite entrer dans le bunker*/
        if (choix == 1){
            /*Suppression de l'item pass_card de son inventaire*/
            delete_item_in_inventory(player, player->inventory[num]);
            printf("Vous avez besoin d'un pass, heureusement vous en possede un ! Vous venez d'entrer a l'interieur du bunker !\n");
            printf("Ca y est vous etes sauves ! Vous etes en securite et venez de trouver l'une des sorties ! ");
            quete->bunker=1;
            return exit_game(); //1 si quitte la map, 0 si continue.
        }
        /*Le joueur decide de ne pas entrer dans le bunjer*/
        else {
           printf("On continue notre jeu ! Allons explorer la map.\n");
           quete->bunker=1;
           return 0;
        }
    }
    /* Si le joueur n'a pas le pass_card dans son inventaire*/
    else{
        printf("Vous ne pouvez rien faire ici malheureusement. Il faut retourner sur vos pas.\n");
        quete->bunker=1; //OU -1 ???
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_bandits(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "bandits".
 * \details
    Le joueur combat contre un npc aléatoire. Il en sort vivant, blesse ou mort.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si problème dans la quete.
*/

int quete_bandits(perso_t * player, quete_t * quete){
    int choix, ajout, combat;

    quete->bandits=0;

    /*Description de l'univers, du lieu*/
    printf("Vous venez d'arriver sur un lieu assez effrayant... Les lieux ont l'air occupes de maniere sauvage. Vous entendez beaucoup de voix au loin. \n");
    printf("Vous n'etes pas tres rassure. Le lieu n'est pas du tout accueillant ! Au fur et a mesure que vous vous en approche vous voyez des armes, des objets volés...\n");
    printf("Le lieu n'est pas occupé que par un individu mais par une vingtaine de bandits, les voix se rapprochent de plus en plus.\n");

    do{
        printf("Plusieurs possibilités s'offrent à vous :\n");
        printf("1 - Partir au plus vite, vous avez peur\n");
        printf("2 - Attendre le retour des bandits\n");
        printf("3 - Voler des items au plus vite\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Le joueur décide de quitter le camp de bandits*/
    if(choix == 1){
        printf("Vous quittez les lieux au pas de course.\n");
        quete->bandits=1;
        return 0;
    }
    else{
        /*Le joueur décide de d'attendre le retour des bandits*/
        if(choix == 2){
            printf("Les bandits se rapprochent, vous les appercevez. Ils sont plus nombreux que vous ne le pensiez.\n");
            printf("Ca y est ils vous ont vu, ils viennent directement vers vous ! Ils n'apprecient pas votre presence et vous le font comprendre.\n");
            do{
                printf("La rencontre est sur le point de degenerer, que faites-vous ?\n");
                printf("1 - Partir\n");
                printf("2 - Rester et combattr\n");
                scanf("%d", &combat);
                if (combat < 1 || combat > 2)
                    printf("Valeur incorrecte. Veuillez resaissir.\n");
            }while(combat < 1 || combat > 2);


        }
    }
}




/**
 * \fn void quete_recherche(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "recherche".
 * \details
    Le joueur doit aller à un endroit donné pour trouver un item et le ramener.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si problème dans la quete.
*/

int quete_recherche(perso_t * player, quete_t * quete){

    quete->recherche.situation=0;

}
