/*
 * CT60A0210 Käytännön ohjelmointi -kurssin ohjelmien otsikkotiedot.
 * Tekijä: Camilla Piskonen
 * Päivämäärä: 12.3.16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Pera Juvonen, harkat, http://en.cppreference.com/w/c/string/byte/strtok
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>
 #include <ctype.h>

 struct ajoneuvo {

    char *autoMerkki;
    int vuosiMalli;
    struct ajoneuvo *seuraava;

};

typedef struct ajoneuvo *ajoneuvoOsoitin;



int varaaMuistia(ajoneuvoOsoitin *pA, char *merkki, int vuosi) {

    struct ajoneuvo *ptrUusi = NULL;
    struct ajoneuvo *ptr = NULL;

    if ((ptrUusi=(struct ajoneuvo*)malloc(sizeof(struct ajoneuvo))) == NULL ) {

        return 1;

    }

    else {

        ptrUusi->autoMerkki = malloc(sizeof(*merkki));
        strcpy(ptrUusi->autoMerkki, merkki);
        ptrUusi->vuosiMalli = vuosi;
        ptrUusi->seuraava = NULL;


        if (*pA == NULL) {

            *pA = ptrUusi;

        }

        else {

            ptr = *pA;

            while ( ptr->seuraava != NULL) {

                ptr = ptr->seuraava;


            }

            ptr->seuraava = ptrUusi;

        }

        return 0;

    }

}



void tulostaAjoneuvot(ajoneuvoOsoitin pA) {

    struct ajoneuvo *ptr = pA;

    if (ptr == NULL) {

      printf("Lista on tyhjä!\n");

    }

    else {

      printf("AUTO\tVUOSI\n");
      while (ptr != NULL) {

          printf("%s\t%d\n", ptr->autoMerkki, ptr->vuosiMalli);
          ptr = ptr->seuraava;

      }

    }

}


void vapautaMuisti(ajoneuvoOsoitin pA) {

    struct ajoneuvo *ptr = pA;

    if (ptr == NULL) {

      printf("Lista on tyhjä!\n");

    }

    else {

        while(ptr != NULL) {

            pA = ptr->seuraava;
            free(ptr);
            ptr = pA;

        }

    }

}
int main(int argc, char* argv[]) {

    ajoneuvoOsoitin pA = NULL;
    int vuosi;
    int z;
    char *merkki, *token;
    const char x[2] = " ";
    char puskuri[40];
    FILE *tiedosto;
    int n;

    if (argc == 1) {

        printf("Et antanut syötettä!\n");
        exit(1);

    }

    else {

        tiedosto = fopen(argv[1], "r");

        if (tiedosto == NULL) {

            printf("Tiedoston avaus epäonnistui!\n");
            exit(1);

        }

        else {

            while (fgets(puskuri, 41, tiedosto) != NULL) {

                n = 0;

                token = strtok(puskuri, x);
                while(token) {

                        if (n == 0) {

                            merkki = token;
                        }

                        else if (n == 1) {

                            vuosi = atoi(token);

                        }

                        n = n+1;
                        token = strtok(NULL, " ");

                }

                z = varaaMuistia(&pA, merkki, vuosi);

                if ( z == 1 ) {

                    printf("Muistin varaus epäonnistui.\n");
                    exit(0);
                }

                else if (z == 0) {

                    continue;

                }

            }

        }

        tulostaAjoneuvot(pA);
        vapautaMuisti(pA);

    }

    fflush(tiedosto);
    fclose(tiedosto);
    return 0;

}
