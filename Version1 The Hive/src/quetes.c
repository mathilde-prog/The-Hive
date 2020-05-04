#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

/**
 * \file quetes.c
 * \brief Fonctionalité : Actionner les quetes du jeu.
 * \author Mathilde Mottay, Anais Mottier, Clement Mainguy, Moustapha Tsamarayev
 * \version
 * \date 2020
*/

/**
 * \fn void init_quete(quete_t * quete)
 * \brief Initialisation d'une variable de type quete_t
 * \param quete_t * quete
 * \return Rien
*/
/*Initialisation d'une structure quete_t*/
void init_quete(quete_t * quete, int quest_map[6][2]){
    quete->soin = -1;
    quete->bunker = -1;
    quete->montagne = -1;
    quete->frontiere = -1;
    quete->bandits = -1;

    /*Initialisation de la structure recherche*/
    quete->recherche.situation = -1;
    quete->recherche.trouve = -1;
  //quete->recherche.wanted = NULL:
    quete->recherche.bunkerX = quest_map[2][0];
    quete->recherche.bunkerY = quest_map[2][1];
}


/**
 * \fn int quete(perso_t * player, cell_t map[D][D], quest_map[6][2], quete_t * quete, item_t * Tab_Items, int nb_items_available)
 * \brief Recupere le numero de la quete pour par la suite acceder a la quete correspondante.
 * \param perso_t * player
 * \param cell_t map[D][D]
 * \param quest_map[6][2]
 * \param quete_t * quete
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/
int quetes(perso_t * player, cell_t map[D][D], int quest_map[6][2], quete_t * quete, item_t * Tab_Items, int nb_items_available){
    int ok=10; //initialisé par un chiffre pour être sur du résultat par la suite

    switch(map[player->posX][player->posY].quest_id){
        case 1 :    if(quete->montagne != 1)
                        clrscr(); ok = quete_montagne(player, quete); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        case 2 :    if(quete->frontiere != 1)
                        clrscr(); ok = quete_frontiere(player, quete); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        case 3 :    if(quete->bunker != 1)
                        clrscr(); ok = quete_bunker(player, quete); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        case 4 :    if(quete->bandits != 1)
                        clrscr(); ok = quete_bandits(player, quete, Tab_Items, nb_items_available); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        case 5 :    if(quete->soin < 1)
                        clrscr(); ok = quete_soin(player, quete, Tab_Items); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        case 6 :    if(quete->recherche.situation != 1)
                        clrscr(); ok = quete_recherche(player, map, quete, quest_map, Tab_Items, nb_items_available); clrscr(); break;
                    else
                        printf("Vous avez déjà joué cette quête.\n"); break;

        default : printf("Aucune quête sur l'hexagone.\n"); return 0;
    }
    if(ok == -1)
        printf("ERREUR : avec la fonction quete ayant l'id_quest n°%d\n", map[player->posX][player->posY].quest_id);
    return ok;
}


/**
 * \fn void quete_montagne(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "montagne".
 * \details
    Le joueur a le choix de franchir la montagne (finir le jeu) ou non.
    Si il a en sa possession l'équipement de montagne alors ses chances de s'échapper sont importantes. Mais si il ne l'a pas il est très risqué pour lui de vouloir s'échapper.
    La chance est donné par un nombre entier compris entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/
int quete_montagne(perso_t * player, quete_t * quete){
    int choix, num_r, num_w, chance;

    quete->montagne=0;

    /*Description du lieu et de la situation*/
    printf("Vous vous trouvez face a la montagne ! De l'autre coté de celle-ci vous retrouverez votre liberté et la paix.\n");
    printf("La montagne est un endroit périlleux ! Il faut de l'énergie, du courage, et matériel adapter a la montagne si on veut reussir a la franchir.\n");
    printf("Beaucoup de personnes y ont laissé la vie, en voulant défier ce monstre de roche.\n");

    /*Le joueur choisi si il franchit ou pas la montagne*/
    do{
        printf("Allez-vous tenter son ascension ?\n");
        printf("1 - Oui\n");
        printf("2 - Non\n");
        scanf("%d", &choix);
        if (choix < 1 || choix > 2)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 2);

    /*Le joueur tente l'ascension de la montagne*/
    if(choix==1){
        /*Recuperation des indices des items rope et walking_stick*/
        num_r = item_in_inventory(*player,"rope");
        num_w = item_in_inventory(*player,"walking stick");

        /*Si le joueur possede l'equipement complet*/
        if((num_r != -1) && (num_w != -1)){
            printf("Bonne nouvelle, vous êtes en possession des bons équipements (corde et baton de marche) pour gravir la montagne !\n");
            chance = 100;
        }
        /*Si le joueur possede uniquement la corde*/
        else if(num_r != -1){
            printf("Vous ne possédez qu'une corde pour vous aider à escalader la montagne, le baton de marche n'est pas dans votre inventaire.\n");
            printf("Son franchissement sera dangereux pour votre vie.\n");
            chance = 45;
        }
        /*Si le joueur possede uniquement le baton de marche*/
        else if(num_w !=-1){
            printf("Vous ne possédez que le baton de marche pour vous aider à escalader la montagne, vous n'avez pas de corde. Son franchissement sera dangereux pour votre vie.\n");
            chance = 45;
        }
        /*Si le joueur ne possede aucun equipement de montagne*/
        else{
            printf("Malheureusement vous n'avez aucun équipement pour la montagne, ni corde, ni baton de marche... L'escaladé sera presque mission impossible. Le risque de mourrir est important.\n");
            chance = 5;
        }

        /*Le joueur confirme si il franchit ou pas la montagne*/
        do{
            printf("Voulez-vous vraiment tenter l'ascension ?\n");
            printf("1 - Oui\n");
            printf("2 - Non\n");
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
                printf("Vous avez les équipements adapter pour escalader ce gros rocher, vous arrivez à gravir la montagne sans soucis. Vous voilà de l'autre coté !\n");
                quete->montagne=1;
                return exit_game();
            }
            /*Si sa chance de franchir la montagne est <100*/
            else{
                int sortie, conf;

                printf("Les choses se compliquent, la monté est très compliqué. Vous êtes à bout de forces, d'énergie, vous perdez l'équilibre à plusieurs reprises.\n");
                /*Le joueur confirme si il franchit ou pas la montagne*/
                do{
                    printf("Voulez-vous réellement continuer l'ascension ?\n");
                    printf("1 - Oui\n");
                    printf("2 - Non\n");
                    scanf("%d", &conf);
                    if (conf < 1 || conf > 2)
                        printf("Valeur incorrecte. Veuillez resaissir.\n");
                }while(conf < 1 || conf > 2);

                /*Le joueur renonce a faire l'ascension de la montagne*/
                if(conf==2){
                    printf("La descente se passe bien. Vous voilà revenus sur terre. Il faut repartir explorer la map maintenant.\n");
                    return 0;
                }
                /*Le joueur souhaite continuer l'ascension*/
                else {
                    printf("Vous prenez de très gros risques mais c'est parti !\n");

                    /*Suppression des items  de son inventaire qu'il va utiliser*/
                    if (num_r != -1)
                        delete_item_in_inventory(player, player->inventory[num_r]);
                    if (num_w != -1)
                        delete_item_in_inventory(player, player->inventory[num_w]);
                    sortie = rng(chance); //Fonction d�terminant si le joueur reussi a s'echapper ou non
                    if(sortie == 1){
                        printf("Félicitations, malgré la grande difficulté de l'ascension vous y êtes arrivés ! Vous voilà de l'autre coté !\n");
                        quete->montagne=1;
                        return exit_game();
                    }
                    else {
                        printf("C'est fini ! Malheureusement la difficulté de l'ascension était trop importante !\n");
                        printf("Vous n'avez pas réussi à sortir de la map. Vous venez de perdre de la vie !\n");
                        quete->montagne=1;
                        return 1;
                    }
                }
            }
        }
    }
    /*Le joueur ne tente pas l'ascension de la montagne*/
    else if(choix==2){
        printf("Vous êtes prudent, continuez d'explorer la map et peut-être trouverez-vous l'équipement parfait pour la gravir plus tard !\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_frontiere(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "frontière".
 * \details
    Le joueur trouve la sortie de la frontière, il a le choix de la franchir (finir le jeu) ou non.
    Si il a joué la quete "soin" et qu'il a aide l'homme blessé alors ses chances de la franchir sont importantes. Mais si il ne l'a pas fait, ses chances le sont moins.
    La chance est donné par un nombre entier compris entre 0 et 100.
 * \param perso_t * player
 * \param quete_t * quete
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si probleme dans la quete.
*/
int quete_frontiere(perso_t * player, quete_t * quete){
    int choix, chance, sortie, conf;

    quete->frontiere=0;

    /*Description du lieu et de la situation*/
    printf("Vous voilà à la frontière ! De l'autre coté de celle-ci vous retrouverez votre liberté et la paix.\n");
    printf("La frontière est pleine de soldats ! Il faut réussir à passer à travers les contrôles.\n");

    /*Choix du joueur : franchir ou non la frontiere*/
    do{
        printf("Deux choix s'offrent à vous :\n");
        printf("0 - Vous ne tentez pas le franchissement de la frontière\n");
        printf("1 - Vous essayer de passer le frontière\n");
        printf("Que choisissez-vous ? ");
        scanf("%d", &choix);

        if(choix < 0 || choix > 1)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 0 || choix > 1);

    /*Le joueur tente le franchissement de la frontiere*/
    if(choix == 1){
        /*Si le joueur a aide l'homme blesse (quete "soin")*/
        if(quete->soin == 2){
            printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et aider lors de votre exploration et qui vous avez donner la carte !\n");
            printf("Il vous apercoit également et viens à votre rencontre. Il vous remercie une nouvelle fois.\n");
            printf("Au fil de la discussion ce dernier comprend pourquoi vous êtes ici. Il décide de vous aider à passer la frontière.\n");
            printf("Il part voir ses collègues, après quelques minutes à attendre il vous fait signe de le rejoindre.\n");
            printf("Vous passez la frontière grâce à cet homme plein de bonté. Ca y est vous êtes libre !\n");
            quete->frontiere=1;
            return exit_game();
        }
        /*Si le joueur a voulu aider l'homme blesse (quete "soin") mais sans succes*/
        else if(quete->soin == 3){
            printf("Surprise ! Vous voyez l'homme que vous avez rencontrer et tenté d'aider lors de votre exploration mais vous n'aviez pas les bons items en votre possession.\n");
            printf("Il vous apercoit également et viens à votre rencontre. Il vous remercie d'avoir voulu essayer de l'aider.\n");
            printf("Au fil de la discussion ce dernier comprend pourquoi vous êtes ici. Il vous informe qu'il va voir ce qu'il peut faire pour vous aider à passer la frontière.\n");
            printf("Rien n'est gagné malheureusement, vous attendez son retour...\n");
            chance = 70;
        }
        /*Si le joueur ne connait pas un soldat*/
        else{
            int pass;

            /*Récupération de l'indice du pass_card dans l'inventaire*/
            pass = item_in_inventory(*player,"pass card");

            /*Si le joueur possede le pass_card*/
            if(pass != -1){
                printf("Vous vous rappelez soudainement que vous êtes en possession du pass (carte plastique).\n");
                printf("Il pourrait peut-être vous permettre de franchir la frontière, mais sans certitude.\n");
                chance = 50;
            }
            /*Si le joueur n'apsa le pass_card*/
            else{
                printf("Les chances de réussir à franchir la frontière sont vraiment faibles. Vous ne pouvez bénéficier d'aucune aide de la part d'un soldat.\n");
                printf("Vous n'en connaissez aucun et donc vous ne pouvez pas être aidé avec un piston.\n");
                chance = 15;
            }
        }
        /*Le joueur confirme ou non son souhait de franchir la frontiere*/
        do{
            printf("Au vu des circonstances, voulez-vous toujours franchir la frontière ?\n");
            printf("1 - Oui\n");
            printf("2 - Non\n");
            scanf("%d", &conf);
            if (conf < 1 || conf > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(conf < 1 || conf > 2);

        /*Le joueur a confirme sa volonté de franchir la frontière*/
        if(conf){
            /*Determination de la reussite de franchissement de la frontiere ou non par le calcul de la fonction rng*/
            sortie = rng(chance);
            quete->frontiere=1;
            switch(sortie){
                case 0 :    printf("Vous n'avez pas réussi à franchir la frontière malheureusement...\n");
                            printf("Retourner explorer la map pour trouver une autre manière d'en sortir.\n");
                            return 0;
                case 1 :    printf("Félicitations, vous avez réussi à franchir la frontière ! Vous voilà de l'autre coté !\n");
                            quete->frontière=1;
                            return exit_game();
                default :   printf("ERREUR : sortie est différent de 0 et 1\n");
                            return (-1);
            }
        }
        /*Le joueur change d'avis, il ne souhaite plus passer la frontière*/
        else{
            printf("La prudence est une bonne qualité dans cette aventure. La situation sera peut-être plus avantageuse une prochiane fois.\n");
            printf("Continuez à explorer la map !\n");
            return 0;
        }
    }
    /*Le joueur ne souhaite pas tentez le franchissement de la frontiere*/
    else{
        printf("Vous ne souhaitez pas franchir pas la frontiere. Continuez d'explorer la map.\n");
        return 0;
    }
    return (-1);
}


/**
 * \fn void quete_bunker(perso_t * player, quete_t * quete)
 * \brief Accès à la quete "bunker".
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
    printf("Vous venez d'arriver sur un lieu très étrange... Une énorme porte se dresse devant vous ! \n");
    printf("Elle est en métal, sans ouverture, camouflée par une verdure sauvages. Sur la droite vous voyez un petit boitier électronique avec une fente.\n");
    printf("La porte est tellement lourde qu'il est impossible pour vous de l'ouvrir ne serait ce que d'un millimètre.\n");

    /*Recuperation du numero de l'item pass_card dans l'inventaire*/
    num = item_in_inventory(*player,"pass card");

    /*Si le joueur a le pass_card dans son inventaire*/
    if (num != -1){
        do{
            printf("Ce boitier est peut-être un moyen d'entrer dans ce lieu ressemblant à un bunker... Souhaitez-vous y entrer ?");
            printf(" 1 - Oui\n");
            printf("2 - Non\n");
            scanf("%d", &choix);
            if (choix < 1 || choix > 2)
                printf("Valeur incorrecte. Veuillez resaissir.\n");
        }while(choix < 1 || choix > 2);
        /*Le joueur souhaite entrer dans le bunker*/
        if (choix == 1){
            /*Suppression de l'item pass_card de son inventaire*/
            delete_item_in_inventory(player, player->inventory[num]);
            printf("Vous avez besoin d'un pass, heureusement vous en possédez un ! Vous entrez à l'intérieur du bunker !\n");
            printf("Ca y est vous êtes sauvé ! Vous êtes en sécurité et venez de trouver l'une des sorties ! ");
            quete->bunker=1;
            return exit_game(); //1 si quitte la map, 0 si continue.
        }
        /*Le joueur decide de ne pas entrer dans le bunker*/
        else {
           printf("Continuez votre exploration de la map.\n");
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


/**
 * \fn void quete_bandits(perso_t * player, quete_t * quete, item_t * Tab_Items, int nb_items_available)
 * \brief Accès à la quete "bandits".
 * \details
    Le joueur combat contre un npc aléatoire. Il en sort vivant, blesse ou mort.
 * \param perso_t * player
 * \param quete_t * quete
 * \param item_t * Tab_Items
 * \param int nb_items_available
 * \return Retourne un \a int : 0 si le jeu continue, 1 si le jeu est fini et -1 si problème dans la quete.
*/
int quete_bandits(perso_t * player, quete_t * quete, item_t * Tab_Items, int nb_items_available){
    int choix, combat, chance, voler=0, ind_lh, ind_rh;

    quete->bandits=0;

    /*Description de l'univers, du lieu*/
    printf("Vous venez d'arriver sur un lieu assez effrayant... Les lieux ont l'air occupés de manière sauvage. Vous entendez beaucoup de voix au loin. \n");
    printf("Vous n'êtes pas très rassuré. Le lieu n'est pas du tout accueillant ! Au fur et a mesure que vous vous en approche vous voyez des armes, des objets volés...\n");
    printf("Le lieu n'est pas occupé que par un individu mais par une vingtaine de bandits, les voix se rapprochent de plus en plus.\n");

    do{
        printf("Plusieurs possibilités s'offrent à vous :\n");
        printf("1 - Partir au plus vite, vous avez peur\n");
        printf("2 - Attendre le retour des bandits\n");
        printf("3 - Voler des items au plus vite\n");
        printf("Que faites vous ? ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 3)
            printf("Valeur incorrecte. Veuillez resaissir.\n");
    }while(choix < 1 || choix > 3);

    /*Le joueur décide de quitter le camp de bandits*/
    if(choix == 1){
        printf("Vous quittez les lieux aux pas de course. Vous êtes maintenant loin d'eux, continuez à explorer la map !\n");
        quete->bandits=1;
        return 0;
    }
    else{
        jump: //jump afin que quand le joueur choisi l'option "voler items" il rencontre les bandits de la meme facon que si il les avait attendu

        /*Le joueur décide de d'attendre le retour des bandits, ou le joueur vient de voler des items*/
        if(choix==2 || voler==1){
            int equip;

            printf("Les bandits se rapprochent, vous les appercevez. Ils sont plus nombreux que vous ne le pensiez.\n");
            printf("Ca y est ils vous ont vu, ils viennent directement vers vous ! Ils n'apprécient pas votre présence et vous le font comprendre.\n");

            /*Choix de voir l'équipement ou non*/
            do{
                printf("Souhaitez-vous voir votre équipement afin de savoir avec quoi vous pouvez vous défendre ? (1 - Oui | 2 - Non)\n");
                scanf("%d", &equip);

                if(equip<1 || equip>2)
                    printf("Valeur incorrecte. Veuillez resaissir.\n");
            }while(equip<1 || equip>2);

            /*Affichage de l'équipement du joueur*/
            if(equip==1)
                display_equipment_player(*player);

            /*Choix du joueur de partir ou combattre*/
            do{
                printf("La rencontre est sur le point de dégénérer, que faites-vous ?\n");
                printf("0 - Partir\n");
                printf("1 - Rester et combattre\n");
                scanf("%d", &combat);
                if (combat < 0 || combat > 1)
                    printf("Valeur incorrecte. Veuillez resaissir.\n");
            }while(combat < 0 || combat > 1);

            /*Le joueur décide de ne pas combattre et s'enfui*/
            if(combat==0){
                int fuir;

                /*Détermination de la chance : plus il a d'équipement, plus il est lourd donc plus il court lentement, donc plus la chance est faible*/
                switch(nb_equipement(*player)){
                    case 0 : chance = 75; break;
                    case 1 : chance = 65; break;
                    case 2 : chance = 55; break;
                    case 3 : chance = 50; break;
                    case 4 : chance = 40; break;
                    default : printf("ERREUR : nb_equipement ne renvoit pas un nombre entre 0 et 4\n"); return (-1);
                }
                fuir = rng(chance);
                /*Le joueur reussi a s'enfuir*/
                if(fuir){
                    printf("Vous fuyez le camps et ses occupants plus vite qu'un éclair, ils n'ont pas eu le temps de vous rattraper !\n");
                    printf("Vous avez échappe de justesse à la mort. Continuez à explorer la map.\n");
                    quete->bandits=1;
                    return 0;
                }
                /*Le joueur ne reussi pas a s'enfuir*/
                else{
                    printf("Vous fuyez le camps et ses occupants plus vite qu'un éclair, mais malheureusement ils ont réussi à vous rattraper !\n");
                    printf("Ils s'acharnent sur vous et vous tuent\n");
                    quete->bandits=1;
                    return 1;
                }
            }
            /*Le joueur reste et combat les bandits*/
            else{
                int vaincre;

                printf("Le courage est en vous, mais il risque d'être une arme faible face à ces individus très dangereux qui n'ont peur de rien, ni de personnes !\n");
                printf("Le combat est rude, vous vous prenez des coups sur l'ensemble du corps, mais vous arrivez à blesser et mettre à terre certains de vos adversaires.\n");

                /*Détermination de la chance : plus il a d'équipement et plus il a de la chance de combattre les bandits*/
                switch(nb_equipement(*player)){
                    case 0 : chance = 1; break;
                    case 1 : chance = 10; break;
                    case 2 : chance = 20; break;
                    case 3 : chance = 30; break;
                    case 4 : chance = 40; break;
                    default : printf("ERREUR : nb_equipement ne renvoit pas un nombre entre 0 et 4\n"); return (-1);
                }
                vaincre = rng(chance);
                /*Si le joueur arrive a vaincre les bandits*/
                if(vaincre){
                    printf("Au fur et à mesure le nombre de bandits diminue. Mais les coups continues même si vous en esquivez la plus part.\n");

                    /*Si 2 ou 3 equipements*/
                    if(chance==20 || chance==30)
                        printf("Vous arrivez à resister grâce aux quelques équipements que vous portez sur vous. ");
                    /*Si 4 équipements*/
                    else if(chance==40)
                        printf("Vous multipliez vos forces grâce à vos 4 équipements, résister à la troupe de bandits est plus simple. ");
                    /*Si aucun equipement*/
                    else
                        printf("Votre mental est inatteignable et vous donne une force presque irréelle permet de résister aux bandits. ");

                    printf("Apràs de longues minutes, il ne reste plus qu'un bandit en état de vous défier !");
                    /*Si il est equipe d'une arme a feu*/


                    /*
                     * MODIFICATIONS ICI A MONTRER A ANAIS!
                     */

                    ind_lh = (player->left_hand != NULL) ? player->left_hand->index : -1;
                    ind_rh = (player->right_hand != NULL) ? player->right_hand->index : -1;

                    if((ind_lh != -1) && (ind_rh != -1)){
                      if((!strcmp(player->inventory[ind_lh].name,"shotgun")) || (!strcmp(player->inventory[ind_lh].name,"pistol")) || (!strcmp(player->inventory[ind_rh].name,"shotgun")) || (!strcmp(player->inventory[ind_rh].name,"pistol"))){
                        printf("Vos forces sont tres faibles, il ne vous reste plus qu'une solution pour en finir avec lui... Vous lui tirer dessus, c'est gagne !\n");
                      }
                    }
                    else if (ind_lh != -1){
                      if((!strcmp(player->inventory[ind_lh].name,"shotgun")) || (!strcmp(player->inventory[ind_lh].name,"pistol"))){
                        printf("Vos forces sont tres faibles, il ne vous reste plus qu'une solution pour en finir avec lui... Vous lui tirer dessus, c'est gagne !\n");
                      }
                    }
                    else if (ind_rh != -1){
                      if((!strcmp(player->inventory[ind_rh].name,"shotgun")) || (!strcmp(player->inventory[ind_rh].name,"pistol"))){
                        printf("Vos forces sont tres faibles, il ne vous reste plus qu'une solution pour en finir avec lui... Vous lui tirer dessus, c'est gagne !\n");
                      }
                    }
                    else {
                      printf("Vous utilisez les dernières forces qui vous reste pour le vaincre. C'est gagne !\n");
                    }

                    printf("Vous avez réussi à combattre les bandits sur leur propre camp, mais vous avez échappe de justesse à la mort !\n");
                    printf("Il faut maintenant repartir explorer la map.\n");
                    quete->bandits=1;
                    return 0;
                }
                /*Si le joueur n'arrive pas a vaincre les bandits*/
                else{
                    printf("Au fur et à mesure le nombre de bandits diminue mais vos forces aussi... ");

                    if(chance==1)
                        printf("Vous n'avez aucun équipement sur vous, malheureusement la bataille est perdu d'avance.\n");
                    else
                        (chance>=2) ? (printf("Malgré les %d équipements sur vous, ", nb_equipement(player))) : (printf("Le seul équipement sur vous n'est pas suffisant, "));
                    printf("les bandits sont trop forts. Vous comprenez que c'est la fin pour vous, ils ne vous laisseront pas vivre ni repartir ! C'est fini !\n");
                    quete->bandits=1;
                    return 1;
                }
            }
        }
        /*Le joueur décide de voler des items*/
        else{
            int nb_items, num, i;

            printf("Vous partez à la recherche d'items à voler dans le camp de bandits !\n");
            voler=1;
            item_t items_camp_bandits[ITEMS_MAX]; //Tableau ou se trouveras les items trouvé dans le camp de bandits
            /*Initialisation du tableau items_camp_bandits*/

            /*
             * PROBLEME INITIALISATION AVEC NULL !
             */
             /*
            for(i=0; i < ITEMS_MAX; i++)
                items_camp_bandits[i] = NULL;
            */
            /*Génération des items trouvés*/
            for(i=0, nb_items=0; i<ITEMS_MAX; i++){
                num = rand()%nb_items_available;
                /*Le joueur peut trouver les items suivant : pistol, shotgun, knife, baseball bat ou helmet*/
                if((!strcmp(Tab_Items[num].name,"pistol")) || (!strcmp(Tab_Items[num].name,"shotgun")) || (!strcmp(Tab_Items[num].name,"knife")) || (!strcmp(Tab_Items[num].name,"baseball bat")) || (!strcmp(Tab_Items[num].name,"helmet"))){
                    items_camp_bandits[nb_items] = Tab_Items[num];
                    nb_items++;
                }
            }
            /*Le joueur n'a trouvé aucun item*/
            if(nb_items==0){
                printf("Vous ne trouvez aucun item chez les bandits malheureusement...\n");
            }
            /*Le joueur trouve au moins 1 item*/
            else{
                int ajout;

                printf("Vous avez trouvé %d item(s) chez les bandits !\n", nb_items);
                (nb_items>1) ? (printf("Pour chaque item trouvé, vous devez faire prendre une décision.\n")) : (printf("Vous devez prendre une décision pour cet item.\n"));

                /*Pour chaque item trouve sur le camp*/
                for(i=0; i<nb_items; i++){
                    /*Choix du joueur pour chaque item : ajouter à l'inventaire ou non*/
                    do{
                        if(nb_items==1)
                            printf("Item trouvé : %s. ", items_camp_bandits[i]->name)
                        else
                            printf("Item n°%d : %s. ", i+1, items_camp_bandits[i]->name);
                        printf("Vous avez le choix entre :\n");
                        printf("1 - Ajouter l'item a l'inventaire\n");
                        printf("2 - Ne pas l'ajouter\n");
                        printf("Votre choix : ");
                        scanf("%d", &ajout);

                        if(ajout<1 || ajout>2)
                            printf("Valeur incorrecte. Veuillez resaissir.\n");
                    }while(ajout<1 || ajout>2);

                    /*Ajouter l'item à l'inventaire*/
                    if(ajout){
                        if(add_item_to_inventory(player,items_camp_bandits[i])==0)
                            printf("L'item %s n'a pas été ajoute à votre inventaire.\n", items_camp_bandits[i]->name);
                    }
                    /*Pas d'ajout à l'inventaire*/
                    else
                        printf("Votre choix de ne pas ajouter l'item %s à bien été pris en compte.\n", items_camp_bandits[i]->name);
                }
                printf("Vous avez récupère tous les items possibles sur le camp de bandits.\n");
            }
            goto jump; //Arrivé des bandits sur le camps
        }
    }
    return(-1);
}
