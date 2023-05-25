#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include"header.h"


void ispisIzbornika() {
	printf("\nBAZA PODATAKA ZA STUDENTSKI DOM\n");
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
	fprintf(pokazivacDatoteke, c.ime);
	fprintf(pokazivacDatoteke, "\n");																										
	printf("\nUnesite prezime studenta: ");
	scanf("%s", c.prezime);
	fprintf(pokazivacDatoteke, c.prezime);
	fprintf(pokazivacDatoteke, "\n");

	printf("\nBroj sobe: ");
	scanf("%s", c.brojSobe);
	fprintf(pokazivacDatoteke, c.brojSobe);
	fprintf(pokazivacDatoteke, "\n");

	printf("\nDatum rodenja: ");
	scanf("%s", c.datumRodenja);
	fprintf(pokazivacDatoteke, c.datumRodenja);
	fprintf(pokazivacDatoteke, "\n");

	printf("\nSpol (M/Z): ");
	scanf("%s", c.spol);
	fprintf(pokazivacDatoteke, c.spol);
	fprintf(pokazivacDatoteke, "\n");

	printf("\nAdresa: ");
	scanf("%s", c.adresa);
	fprintf(pokazivacDatoteke, c.adresa);
	fprintf(pokazivacDatoteke, "\n");
		
	printf("\nKontakt: ");
	scanf("%s", c.kontakt);
	fprintf(pokazivacDatoteke, c.kontakt);
	fprintf(pokazivacDatoteke, "\n");
	fprintf(pokazivacDatoteke, "\n");

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

					
	static char citanjeDatoteke[5000];
	while (!feof(pokazivacDatoteke))
	{								
		fgets(citanjeDatoteke, 5000, pokazivacDatoteke);
		puts(citanjeDatoteke);		
	}								
	
	fclose(pokazivacDatoteke);		
}									
void pronadiStudenta() {			
										
	int trazenjePoBrojuSobe;		
	printf("Unesite broj sobe clana kojeg zelite pronaci: ");
	scanf("%d", &trazenjePoBrojuSobe);
									
	FILE* pokazivacDatoteke = fopen("studenti.txt", "r"); //16
	if (pokazivacDatoteke == NULL) {
									
		printf("Ne mogu otvoriti dadoteku\n");
		return;						
	}								
									
	STUDENT c;						
									
	int usporedivanjeSoba = 1;		
	int pronaden = 0;				
	if (trazenjePoBrojuSobe == c.brojSobe)
		usporedivanjeSoba = 0;		
									
									
	while (!feof(pokazivacDatoteke)) {
		if (usporedivanjeSoba == 0) {
			printf("Pronaden clan:\n");
			printf("Ime: %s\nPrezime: %s\nBroj sobe: %s\nDatum rodenja: %s\nSpol: %s\nAdresa: %s\nKontakt: %s\n", c.ime, c.prezime, c.brojSobe, c.datumRodenja, c.spol, c.adresa, c.kontakt);
			pronaden = 1;
			break;
		}
	}

	if (!pronaden) {
		printf("Nema studenta u domu s brojem sobe %d\n", trazenjePoBrojuSobe);
	}
	fclose(pokazivacDatoteke);
}
void popisSlobodnihSoba()
{

}
void uredivanjeStudenata()
{

}
void brisanjeStudenata() {
	char imeDat[] = "studenti.txt";
	char imeZaObrisat[20];

	printf("Unesite ime studenta kojega zelite izbrisati: ");
	scanf("%s", imeZaObrisat);

	FILE* fp = fopen(imeDat, "r+");
	if (fp == NULL) {
		printf("Ne moze se otvoriti datoteka %s\n", imeDat);
		return 1;
	}

	
	char tempFilename[] = "temp.txt";
	FILE* tempFp = fopen(tempFilename, "w");
	char line[100];
	while (fgets(line, 100, fp) != NULL) {
		char* token = strtok(line, ",");
		if (strcmp(token, imeZaObrisat) != 0) {
			fputs(line, tempFp);
		}
	}

	
	fclose(fp);
	fclose(tempFp);

	
	remove(imeDat);
	rename(tempFilename, imeDat);

	printf("Student %s je usijesno obrisan iz datoteke.\n", imeZaObrisat);
}
