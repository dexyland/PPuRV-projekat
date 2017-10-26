#ifndef STACK_MODULE
#define STACK_MODULE
#define VELICINA_STEKA (10000)
#include <inttypes.h>
#include <assert.h>


/*
 *
 *  @ Struktura koja se koristi prilikom cuvanja podataka o lokaciji odredjenog 'piksela'. Polja visina odnosno
 *    sirina odredjuju poziciju 'piksela' po visini odnosno sirini unutar 'slike'.
 *
 */

typedef struct S_element
{
	uint_least16_t visina;
	uint_least16_t sirina;
}koordinate;


/*
 *
 *  @ Struktura pomocu koje je realizovan stek. Prvo  polje, polje  'elementi', predstavlja  stek. Tip podataka, koji
 *    se u ovom programu postavljaju na stek, je goreopisana struktura  'koordinate'. Stoga je i svaka lokacija steka
 *    tipa strukture 'koordinate'. Drugo polje, polje 'vrhSteka', nam ukazuje na poziciju poslednje upisanog podataka
 *    na stek. Velicina steka je ogranicena na 9999 iz razloga  sto je maksimalna  velicina ulazne 'slike' 100x100, a
 *    postoji mogucnost da je potrebno uneti  podatke o poziciji svih  preostalih 9999 'piksela'  ukoliko  svih 10000
 *    'piksela' imaju istu vrednost.
 *
 */

typedef struct S_stek
{
	koordinate elementi[VELICINA_STEKA];
	int_fast16_t vrhSteka;
}stek;


/*
 *
 *  @ Funckija 'inicijalizacijaSteka' se koristi za  postavljanje steka u pocetno stanje  odnosno za postavljanje vrednosti
 *    polja 'vrhSteka' na -1. Ta vrednost ujedno oznacava i da je stek prazan. Parametar funkcije je pokazivac na stek koji
 *    je potrebno inicijalizovati.
 *
 */

void inicijalizacijaSteka(stek* const sStek);


/*
 *
 *  @ Funkcija 'push' se koristi za postavljanje novog elementa na vrh steka. Prvi parametar funkcije je pokazivac na stek
 *    na koji se postavlja podatak. Drugi parametar funkcije je podatak koji se postavlja na stek.
 *
 */

void push(stek* const sStek, const koordinate element);


/*
 *
 *  @ Funkcija 'pop' se koristi za 'skidanje' podatka sa vrha steka. Parametar funkcije je pokazivac na stek sa koga se cita,
 *    a ujedno i skida podatak. Povratna vrednost funkcije je tipa strukture koordinate.
 *
 */

koordinate pop(stek* const sStek);


#endif
