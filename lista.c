/*
 * CT60A0210 Käytännön ohjelmointi -kurssin ohjelmien otsikkotiedot.
 * Tekijä: Camilla Piskonen
 * Päivämäärä: 12.3.16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: harkat, Essi Rautasalo
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

/*tietue listalle*/
struct alkio {

   char sNimi[31];
   struct alkio *pSeuraava;
};

typedef struct alkio lista;                                                     /*tätä käytetään viitatessa struct alkio*/


lista *lisays(lista *pA) {                                                      /*lisätään listalle yksi uusi nimi*/

  lista *ptr, *ptrUusi;                                                         /* *ptr avulla käydään listaa läpi, *ptrUusi avulla lisätään nimi listalle*/

  if ((ptrUusi=(lista*)malloc(sizeof(lista))) == NULL ) {                       /*jos asiat menee pieleen*/

      perror("Muistin varaus epäonnistui.\n");
      exit(1);

  }

  /*Alkion arvojen määrittäminen*/
  printf("Anna talletettava nimi: ");
  getchar();
  fgets(ptrUusi->sNimi, 31, stdin);                                             /*ptrUusi viittaa alkio-rakenteeseen jonne nimi tallennetaan*/
  ptrUusi->sNimi[strlen(ptrUusi->sNimi)-1]='\0';                                /*poistetaan ylimääräinen rivivaihtomerkki*/
  ptrUusi->pSeuraava = NULL;                                                    /*uudesta alkiosta seuraava laitetaan tyhjäksi, jotta jatkossa sinne voidaan lisätä uusi niimi*/

  /*Alkion lisääminen listan viimeiseksi*/
  if (pA == NULL) {

    pA = ptrUusi;                                                               /*jos listassa ei ole alkioita, niin voidaan uusi nimi laittaa suoraan ensimmäiseksi*/

  }

  else {

    ptr = pA;
    while (ptr->pSeuraava != NULL) {                                            /*siirrytään listalla niin pitkälle kunnes saavutetaan loppu*/

      ptr = ptr->pSeuraava;

      }

    ptr->pSeuraava = ptrUusi;                                                   /*viimeisen alkion seuraava alkio laitetaan viittaamaan uuteen nimeen*/

  }

  return pA;                                                                    /*palautetaan listan ensimmäinen alkio*/

}

lista *poisto(lista *pA) {                                                      /*poistaa yhden nimen*/

  int luku;                                                                     /*poistettavan nimen numero*/
  int i = 1;                                                                    /*askeltaja*/
  int x = 0;                                                                    /*listan pituus*/
  lista *ptr = pA;
  lista *tptr;                                                                  /*apuosoitin*/


  while (ptr != NULL ) {                                                        /*listan pituuden selvitys*/

    ptr = ptr->pSeuraava;
    x = x+1;

    }

  if (x == 0) {                                                                 /*jos lista tyhjä, keskeytetään*/

      return pA;

  }

  else {

      printf("Anna poistettava nimi: \n");
      scanf("%d", &luku);
	  ptr = pA;                                                                 /*alustetaan ptr takaisin alkuun*/

      if (luku > x) {                                                           /*jos listalla ei ole kyseistä nimeä*/

          printf("Listalla ei ole kyseistä alkiota.\n");
          return pA;
        }

        else if (i == luku) {                                                   /*jos poistettava on listan ensimmäinen*/
            free(pA);
            pA = ptr->pSeuraava;                                                /*alku laitetaan osoittamaan listan seuraavaan, ei tule listaan tyhjiä kohtia*/
            return pA;
        }

        else {                                                                  /*kun poistettava on jokin muu kuin ensimmäinen*/

            ptr = pA;

            while (i < luku-1) {                                                /*siirrytään poistettavaa edelliseen alkioon*/

                ptr = ptr->pSeuraava;
                i = i+1;

            }

            tptr = ptr->pSeuraava;                                              /*tptr osoittaa poistettavaan*/
            ptr->pSeuraava = ptr->pSeuraava->pSeuraava;                         /*ptr osoittaa poistettavaa seuraavaan, ei jää listaan tyhjiä kohtia*/
            free(tptr);                                                         /*vapautetaan muisti*/
            return pA;

        }

    }

}


void *tulostus(lista *pA) {                                                     /*listan tulostus*/

  lista *ptr = pA;
  int i = 1;                                                                    /*laskuri alkioiden numerointiin*/

  if (ptr == NULL) {                                                            /*jos lista on tyhjä*/
    printf("Lista on tyhjä!\n");
  }

  else {

    printf("ALKIO\tNIMI\n");                                                    /*muotoilu koska uolevi*/

    while (ptr != NULL) {

      printf("%d\t%s\n", i, ptr->sNimi);                                        /*apupointteri osoittaa kyseiseen listan alkioon*/
      i = i+1;                                                                  /*kasvatetaan laskuria*/
      ptr = ptr->pSeuraava;                                                     /*siirrytään seuraavaan alkioon*/

    }

  }

}


lista *tyhjennys(lista *pA) {                                                   /*tyhjennetään koko lista*/

  lista *ptr = pA;

  if (ptr == NULL) {                                                            /*jos se onkin jo tyhjä*/

    printf("Lista on tyhjä!\n");

  }

  else {

      while(ptr != NULL) {                                                      /*tyhjennetään alkio kerrallaan*/

          printf("Poistetaan %s.\n", pA->sNimi);                                /*printataan nimi koska uolevi*/
          pA = ptr->pSeuraava;                                                  /*laitetaan alku osoittamaan seuraavaan alkioon*/
          free(ptr);                                                            /*vapautetaan muisti*/
          ptr = pA;                                                             /*alustetaan pointteri taas alkuun*/

      }

  }

  return pA;

}


void main(void) {                                                               /*pääohjelma*/

  int valinta;
  lista *pAlku = NULL;                                                          /*alussa lista on tyhjä*/

  do {

    printf("Valitse toiminto valikosta:\n");                                    /*valikko*/
    printf("1) Lisää alkio listan loppuun\n");
    printf("2) Poista valittu alkio\n");
    printf("3) Tulosta listan tiedot\n");
    printf("4) Tyhjennä lista\n");
    printf("0) Lopeta\n");
    printf("Valintasi: ");
    scanf("%d", &valinta);

    switch (valinta) {

      case 1:                                                                   /*alkion lisäys*/
      pAlku = lisays(pAlku);
      break;

      case 2:                                                                   /*yksittäisen alkion poisto*/
      tulostus(pAlku);
      pAlku = poisto(pAlku);
      break;

      case 3:                                                                   /*listan tulostus*/
      tulostus(pAlku);
      break;

      case 4:                                                                   /*listan tyhjennys*/
      pAlku = tyhjennys(pAlku);
      break;

      case 0:                                                                   /*ohjelman lopetus*/

      if (pAlku == NULL) {                                                      /*jos lista on jo tyhjä*/
          printf("Kiitos ohjelman käytöstä!\n");
		  break;
      }

      else {                                                                    /*jos listalla on jotain*/
          printf("Kiitos ohjelman käytöstä!\n");
          pAlku = tyhjennys(pAlku);                                             /*tyhjennetään lista*/
          break;
      }

      default:                                                                  /*jos joku on tyhmä, älä syötä kirjaimia pls*/
      printf("Tuntematon valinta\n");
      break;
      }

  } while (valinta != 0);                                                       /*suoritetaan niin kauan kunnes käyttäjä haluaa lopettaa*/

}
