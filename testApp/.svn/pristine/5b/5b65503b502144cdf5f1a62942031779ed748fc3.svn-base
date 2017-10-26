/*********************************************************************\
*                                                                     *
*   Autor : Dejan Martinov RA94/2013                                  *
*                                                                     *
*   Datum : 22.10.2017.                                               *
*                                                                     *
 *********************************************************************
*                                                                     *
* Zadatak : Napraviti modul koji predstavlja stek. Modul izvesti kao  *
*   dinamicku  biblioteku  (deljeni objekat). Napisati  program koji  *
*   ucitava sliku iz datoteke u formi matrice nula i jedinica. Zatim  *
*   napisati funkciju koja krece od  zadatog piksela i pronalazi sve  *
*   piksele iste vrednosti  koji su susedi  njegovim  istovrednosnim  *
*   susedima, itd. Uzeti u obzir da je na pretpostavljenom namenskom  *
*   procesoru maksimalna dubina poziva  funkcija  4. Deljeni objekat  *
*   koji  predstavlja  stek  dinamicki povezati tokom izvrsavanja. U  *
*   resenju se osloniti na strukturu reda iz modula.                  *
*                                                                     *
 *********************************************************************
*                                                                     *
* Resenje : Izradi resenja prethodilo je pisanje dinamicke biblioteke *
*  koja se sastoji iz  fajlova stack.h i stack.c i koja  se dinamicki *
*  uvezuje u toku izvrsavanja. Detaljan  opis  pojedinih funckija dat *
*  je u okviru stack.h zaglavlja. Sam program sastoji se iz tri fajla *
*  imageProcessing.h u kom se nalaze  definicije  funkcija kao i opis *
*  svih funkcija i struktura koje  su koriscene  u programu. Funckije *
*  pomocu kojih se realizuje pretraga i ispis su realizovane u okviru *
*  imageProcessing.c fajla, dok se  uvezivanje dinamicke biblioteke i *
*  poziv svih funkcija vrsi u mail.c  fajlu. Vecina koda je  pisana u *
*  skladu sa MISRA C standardom osim u slucajevima kada  su koriscene *
*  funkcije za rad sa stringovima, za rad sa datotekama i za ispis na *
*  ekran.
*                                                                     *
 *********************************************************************
*                                                                     *
*  Testiranje : Testiranje je obuhvatalo ucitavanje razlicitih slika. *
*    Testirani su  slucajevi kada se zbog strukture slike zauzima ceo *
*    stek, kada nema istovrednosnih suseda i razni slucajevi u kojima *
*    je povezano nekoli istovrednosnih piksela.                       *
 *********************************************************************/


#include "imageProcessing.h"


int_least32_t main(int argc, char* argv[])
{
	void* handle;
	char* error;
	char imeSlike[] = "slika100x100.txt";

	void (*initFunc)(stek*);
	void (*pushFunc)(stek*, koordinate);
	koordinate (*popFunc)(stek*);

	velicinaSlike_t dimenzije;
	koordinate pocetak;
	slika_t slika[MAX_VELICINA_SLIKE];
	stek istovrednosniPikseli;


	/* Uvezivanje dinamicke biblioteke i dobavljanje simbola */

	handle = dlopen("libstackModule.so", RTLD_LAZY);
	if(handle == NULL)
	{
		fputs(dlerror(), stderr);
		exit(1);
	}

	initFunc = dlsym(handle, "inicijalizacijaSteka");
	if((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}

	pushFunc = dlsym(handle, "push");
	if((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}

	popFunc = dlsym(handle, "pop");
	if((error = dlerror()) != NULL)
	{
		fputs(error, stderr);
		exit(1);
	}


	initFunc(&istovrednosniPikseli);

	dimenzije = ucitajSliku(imeSlike, slika);


	/* Postavljanje koordinate pocetno piksela za pretragu */

	pocetak.sirina = 0;
	pocetak.visina = 0;


	pronadjiPiksele(slika, dimenzije, pocetak, &istovrednosniPikseli, pushFunc);

	ispisiPiksele(pocetak, &istovrednosniPikseli, popFunc);


	dlclose(handle);

	return EXIT_SUCCESS;
}
