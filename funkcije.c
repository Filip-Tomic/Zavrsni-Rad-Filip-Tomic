#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include"header.h"


void ispisIzbornika() {
	printf("BAZA PODATAKA ZA STUDENTSKI DOM\n");
	printf("Unesite radnju\n");
	printf("1. Pregled svih studenata (abecedno)\n");
	printf("2. Pregled svih studenata (po broju sobe)\n");
	printf("3. Pronadi studenta po imenu\n");
	printf("4. Pronadi studenta po broju sobe (1-50)\n");
	printf("5. Popis slobodnih soba\n");
	printf("6. Dodavanje novih studenata\n");
	printf("7. Uredivanje postojecih studenata\n");
	printf("8. Brisanje studenata\n");

}


void dodajStudenta() {
	FILE* pokazivacDatoteke = fopen("studenti.txt", "a"); //16
	if (pokazivacDatoteke == NULL) {
		printf("Ne mogu otvoriti dadoteku\n");
		return;
	}
	STUDENT c;
	printf("\nUnesite ime studenta: ");
	scanf("%s", c.ime);
	printf("\nUnesite prezime studenta: ");
	scanf("%s", c.prezime);
	printf("\nBroj sobe: ");
	scanf("%d", &c.brojSobe);
	printf("\nDatum rodenja: ");
	scanf("%s", c.datumRodenja);
	printf("\nSpol (M/Z): ");
	scanf("%s", c.spol);
	printf("\nAdresa: ");
	scanf("%s", c.adresa);
	printf("\nKontakt: ");
	scanf("%s", c.kontakt);
	srand((unsigned)time(NULL));
	fwrite(&c, sizeof(c), 1, pokazivacDatoteke);

	fclose(pokazivacDatoteke);
	printf("Student uspijesno dodan\n");
}


void ispisiStudente() {
	FILE* pokazivacDatoteke = fopen("studenti.txt", "r"); //16
	if (pokazivacDatoteke == NULL) {
		printf("Ne mogu otvoriti dadoteku\n");
		return;
	}
	STUDENT c;

	int brojClanova = 0;
	while (fread(&c, sizeof(c), 1, pokazivacDatoteke)) {
		printf("\nIme:%s\nPrezime:%s\nBroj sobe:%d\nDatum rodenja:%s\nSpol:%s\nAdresa:%s\nKontakt:%s\n",c.ime, c.prezime, c.brojSobe, c.datumRodenja,c.spol, c.adresa, c.kontakt);
		brojClanova++;
		
	}
	printf("\nUkupno clanova: %d\n", brojClanova);
	fclose(pokazivacDatoteke);
}
void pronadiStudenta() {

	char trazenjeIme[20];
	printf("Unesite ime clana kojeg zelite pronaci: ");
	scanf("%s", &trazenjeIme);

	FILE* pokazivacDatoteke = fopen("studenti.txt", "r"); //16
	if (pokazivacDatoteke == NULL) {

		printf("Ne mogu otvoriti dadoteku\n");
		return;
	}
	
	STUDENT c;
	int usporedivanjeStringova = strcmp(c.ime, trazenjeIme);
	int pronaden = 0;
	while (fread(&c, sizeof(c), 1, pokazivacDatoteke)) {
		if (usporedivanjeStringova == 0) {
			printf("Pronaden clan:\n");
			printf("Ime: %s\nPrezime: %s\nBroj sobe: %d\nDatum rodenja: %s\nSpol: %s\nAdresa: %s\nKontakt: %s\n", c.ime,c.prezime, c.brojSobe, c.datumRodenja, c.spol, c.adresa, c.kontakt);
			pronaden = 1;
			break;
		}
	}

	if (!pronaden) {
		printf("Nema studenta u domu s imenom %s\n", trazenjeIme);
	}
	fclose(pokazivacDatoteke);
}
void popisSlobodnihSoba()
{

}
void uredivanjeStudenata()
{

}
void brisanjeStudenata()
{

}
