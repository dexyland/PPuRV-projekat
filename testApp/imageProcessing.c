#include "imageProcessing.h"


velicinaSlike_t ucitajSliku(const char* imeDatoteke, slika_t slika[])
{
	FILE* fp;
	int_least8_t sirinaSlike = 0;
	int_least8_t visinaSlike = 0;
	int_least8_t sirinaIzmerena = 0;
	int_fast8_t brojac = 0;
	velicinaSlike_t velicinaUcitane;
	char linija[101];


	fp = fopen(imeDatoteke, "r");


	while((fgets(linija, (MAX_SIRINA_SLIKE + 2), fp) != NULL) && (visinaSlike < MAX_VISINA_SLIKE))
	{
		if(sirinaIzmerena == 0)
		{
			sirinaSlike = ((int_least8_t)strlen(linija)) - 1;
			sirinaIzmerena = 1;
		}


		for(brojac = 0; brojac < sirinaSlike; brojac++)
		{
			slika[(visinaSlike*sirinaSlike) + brojac].piksel = (int_least8_t)(linija[brojac] - '0');
		}

		visinaSlike++;
	}

	velicinaUcitane.sirina = sirinaSlike;
	velicinaUcitane.visina = visinaSlike;

	fclose(fp);

	return velicinaUcitane;
}


int_least8_t proveriDimenzije(int_least16_t pocetnaVisina, int_fast16_t offSetVisine, int_least16_t pocetnaSirina, int_fast16_t offSetSirine, velicinaSlike_t velicina)
{
	int_least8_t retVal = 1;

	/*
	 * Ukoliko je bar jedan od uslova ispunjen, odnosno  ako je  visina
	 * ili sirina trenutne tacke van opsega dimenzija 'slike', povratna
	 * vrednost funkcije ce biti  '0' sto  oznacava invalidnu  poziciju
	 * piksela.
	 */

	if((pocetnaVisina + offSetVisine) < 0)
	{
		retVal = 0;
	}


	if((pocetnaVisina + offSetVisine) > velicina.visina)
	{
		retVal = 0;
	}


	if((pocetnaSirina + offSetSirine) < 0)
	{
		retVal = 0;
	}


	if((pocetnaSirina + offSetSirine) > velicina.sirina)
	{
		retVal = 0;
	}


	return retVal;
}


void pronadjiPiksele(slika_t slika[], velicinaSlike_t velicinaSlike, koordinate pocetak, stek* sStek, void (*pushFunc)(stek*, koordinate))
{
	int_fast8_t brojacW = 0;
	int_fast8_t brojacH = 0;
	int_fast8_t brojac1 = 0;
	int_fast8_t brojac2 = 0;
	int_fast8_t kraj = 1;
	int_fast8_t vrednostZaPretragu;
	int_fast16_t brojUcitanih = 0;
	int_fast16_t prethodnoUcitanih = 0;
	int_fast16_t sirinaPretrage = 1;

	vrednostZaPretragu = slika[pocetak.visina*velicinaSlike.sirina + pocetak.sirina].piksel;
	slika[pocetak.visina*velicinaSlike.sirina + pocetak.sirina].ucitan = 1;


	/* Uslov za kraj pretrage je da se broj pronadjenih piksela ne promeni izmedju dve iteracije. */

	while(kraj != 0)
	{
		/* Prolaz kroz sliku po visini */
		for(brojacH = (-sirinaPretrage); brojacH < (sirinaPretrage + 1); brojacH++)
		{
			/* Prolaz kroz sliku po sirini */
			for(brojacW = (-sirinaPretrage); brojacW < (sirinaPretrage + 1); brojacW++)
			{
				/* Provera da li su dimenzije unutar opsega velicine slike */
				if(proveriDimenzije(pocetak.visina, brojacH, pocetak.sirina, brojacW, velicinaSlike))
				{
					int_fast16_t pozicija = (pocetak.visina + brojacH)*velicinaSlike.sirina + brojacW + pocetak.sirina;

					/* Provera da li trenutni piksel ima istu vrednost kao pocetni piksel odnosno da li je upisan na stek*/
					if(slika[pozicija].ucitan == 1)
					{
						/* Prolaz po visini oko trenutnog piksela */
						for(brojac1 = -1; brojac1 < 2; brojac1++)
						{
							/* Prolaz po sirini oko trenutnog piksela */
							for(brojac2 = -1; brojac2 < 2; brojac2++)
							{
								/* Provera da li su dimenzije unutar opsega velicine slike */
								if(proveriDimenzije(pocetak.visina + brojacH, brojac1, pocetak.sirina + brojacW, brojac2,velicinaSlike))
								{
									int_fast16_t tempPozicija = pozicija + (brojac1*(int_fast16_t)velicinaSlike.sirina) + brojac2;

									/* Provera da li je vrednost piksela iz okoline jednaka pocetnom i da li je isti upisan na stek */
									if((slika[tempPozicija].piksel == vrednostZaPretragu) && (slika[tempPozicija].ucitan != 1))
									{
										koordinate temp;
										temp.visina = pocetak.visina + brojacH + brojac1;
										temp.sirina = pocetak.sirina + brojacW + brojac2;


										pushFunc(sStek, temp);
										slika[tempPozicija].ucitan = 1;
										brojUcitanih++;
									}
								}
							}
						}
					}
				}
			}
		}

		if(prethodnoUcitanih == brojUcitanih)
		{
			kraj = 0;
		}

		sirinaPretrage++;
		prethodnoUcitanih = brojUcitanih;
	}
}


void ispisiPiksele(koordinate pocetak, stek* sStek, koordinate (*popFunc)(stek*))
{
	printf("Koordinate pocetnog piksela:\n");
	printf("(%"PRIuLEAST16",%"PRIuLEAST16")\n", pocetak.visina, pocetak.sirina);

	printf("\n");

	printf("Koordinate istovrednosnih piksela:\n");

	while(sStek->vrhSteka != -1)
	{
		koordinate tempPozicijaIspis = popFunc(sStek);

		printf("(%"PRIuLEAST16",%"PRIuLEAST16")\n",tempPozicijaIspis.visina, tempPozicijaIspis.sirina);
	}
}
