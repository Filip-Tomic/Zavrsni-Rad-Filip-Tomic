#ifndef HEADER_H
#define HEADER_H

typedef struct student {
	int id;
	char ime[20];
	char prezime[20];
	int brojSobe;
	char datumRodenja[20];
	char spol[2];
	char adresa[100];
	char kontakt[100];
}STUDENT;

void ispisIzbornika();
void dodajStudenta();
void ispisiStudente();
void pronadiStudenta();
void popisSlobodnihSoba();
void uredivanjeStudenata();
void brisanjeStudenata();
#endif
