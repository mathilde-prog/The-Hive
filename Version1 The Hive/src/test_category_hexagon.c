#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define D 15 // dimensions of the map

typedef enum {prairie = 1, foret, ville, lac, camp_mil, camp_ban, market, favella, montagne, frontiere, mer, wasteland} hex_t;
typedef enum {other, nature, urbain, militaire} categ_hexa;

/* category_hexagon: returns the category of a hexagon. The map and hexagon coordinates are passed in parameters.*/
categ_hexa category_hexagon (int map[D][D], int x, int y){
  hex_t hexagone = map[x][y];
  categ_hexa categ;

  switch(hexagone){
      case prairie   : categ = nature;    break;     //prairie
      case foret     : categ = nature;    break;     //foret
      case ville     : categ = urbain;    break;     //ville
      case lac       : categ = nature;    break;     //lac
      case camp_mil  : categ = militaire; break;     //camp mil
      case camp_ban  : categ = other;     break;     //camp_ban
      case market    : categ = urbain;    break;     //market
      case favella   : categ = urbain;    break;     //favella
      case montagne  : categ = nature;    break;     //montagne
      case frontiere : categ = other;     break;     //frontiere
      case mer       : categ = nature;    break;     //mer
      case wasteland : categ = other;    break;     //wasteland
      default : return 4; break;
  }

  return categ;
}

int main(){
    categ_hexa categ; //Categorie hexagone : nature, urbain...
    int map[D][D];
    int x, y;

    x = y = 1;
    for (int i=0; i<13; i++){
        printf("Type hexagone : ");
        switch(i){
            case 1 : printf("prairie"); break;
            case 2 : printf("foret"); break;
            case 3 : printf("ville"); break;
            case 4 : printf("lac"); break;
            case 5 : printf("camp_mil"); break;
            case 6 : printf("camp_band"); break;
            case 7 : printf("market"); break;
            case 8 : printf("favella"); break;
            case 9 : printf("montagne"); break;
            case 10 : printf("frontière"); break;
            case 11 : printf("mer"); break;
            case 12 : printf("wasteland"); break;
            default : printf("type hexagone inconnue"); break;
        }
        map[x][y] = i;
        categ = category_hexagon(map, x, y);
        printf(" -> Categ : ");
        switch (categ){
            case 0 : printf("other\n"); break;
            case 1 : printf("nature\n"); break;
            case 2 : printf("urbain\n"); break;
            case 3 : printf("militaire\n"); break;
            default : printf("aucune catégorie trouvée\n");
        }
        //Si catégorie = nature
        if ((categ==1)&&((i==1)||(i==2)||(i==4)||(i==9)||(i==11))){
            printf ("OK : categ nature\n");
        }
        else{
            //Si categorie = urbain
            if ((categ==2)&&((i==3)||(i==7)||(i==8))){
                printf ("OK : categ urbain\n");
            }
            else{
                //Si categorie = other
                if ((categ==0)&&((i==6)||(i==10)||(i==12))){
                    printf ("OK : categ other\n");
                }
                else{
                    //Si categorie = militaire
                    if ((categ==3)&&(i==5)){
                        printf ("OK : categ militaire\n");
                    }
                    else{
                        //Si la categorie est inconnue
                        if (categ==4){
                            printf("OK : categ inconnue\n");
                        }
                    }
                }
            }
        }
    }
    return 0;
}
