#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //7 
#include <stdlib.h>
#include "Header.h"
#include <string.h>

//Obavezni koncepti
//4 upotreba camelCase
//6

void pocetniIzbornik();
void dodajStudenta(char* datoteka, unsigned int* brojStudenata);
void ispisiStudente(char* datoteka, unsigned int* brojStudenata);
void pronalazenjeStudenta(char* datoteka, unsigned int* brojStudenata);
void uredivanjeStudenta(char* datoteka, unsigned int* brojStudenata);
void sortiranjeImena(char* datoteka, unsigned int* brojStudenata);
void izlazFunkcija(void);



void kreiranje(char* datoteka, unsigned int* BrojStudenata) { //9

	FILE* fp = fopen(datoteka, "rb");

	if (fp == NULL) {

		perror("\nGreska"); //19

		fp = fopen(datoteka, "wb");

		if (fp == NULL) {

			perror("Greska");
			exit(EXIT_FAILURE);
		}
		else {

			fwrite(BrojStudenata, sizeof(unsigned int), 1, fp);
			fclose(fp);
			printf("Pravljenje Datoteke...\nDatoteka usijesno kreirana!\n");
		}
	}
	else {

		fread(BrojStudenata, sizeof(unsigned int), 1, fp);
		fclose(fp);
		printf("Datoteka postoji\n");
	}
}








void glavniIzbornik(char* datoteka, unsigned int* brojStudenata) {
	unsigned int izbor = -1;
	static int loop = 1; //5
	while (loop) {
		pocetniIzbornik();

		scanf("%u", &izbor);

		switch (izbor) {

		case 1:
			printf("\n\t\tDodaj studenta\n\n");
			dodajStudenta(datoteka, brojStudenata);
			break;

		case 2:
			printf("\n\t\tPregled svih studenata\n\n");
			ispisiStudente(datoteka, brojStudenata);
			break;

		case 3:
			printf("\n\t\tPretrazivanje studenata\n\n");
			pronalazenjeStudenta(datoteka, brojStudenata);
			break;

		case 4:
			printf("\n\t\tUredivanje studenata\n\n");
			uredivanjeStudenta(datoteka, brojStudenata);
			break;

		case 5:
			printf("\n\t\tBrisanje svih studenata\n\n");
			printf("Jeste li sigurni da zelite izbrisati sve studente(D/N)\n");
			char izbor[2] = { '\0' };
			scanf(" %s", izbor);
			if (!strcmp("D", izbor)) {

				remove(datoteka); //18
				printf("Svi studenti su izbrisani, pravljenje nove datoteke!");
				kreiranje(datoteka, brojStudenata);
			}
			break;

		case 6:
			printf("\n\t\Pregled svih studenata poredano abecedno po imenu (Z-A)\n\n");

			sortiranjeImena(datoteka, brojStudenata);

			break;
		case 0:
			printf("\nIzlaz...\n\n");
			izlazFunkcija();
			break;

		default:
			printf("Nevazeci unos, pokusajte ponovo!\n");
		}
	}
}






void pocetniIzbornik() { //8
	printf("BAZA PODATAKA ZA STUDENTSKI DOM\n");
	printf("Izaberite opciju\n");
	printf("[1] Dodaj studenta\n");
	printf("[2] Pregled svih studenata\n");
	printf("[3] Pretrazi studenta\n");
	printf("[4] Uredi studenta\n");
	printf("[5] Izbrisi sve studente\n");
	printf("[6] Pregled svih studenata poredano abecedno po imenu (Z-A):\n");
	printf("[0] Izlaz\n");
	printf("Odabir: ");
}

void dodajStudenta(char* datoteka, unsigned int* brojStudenata) {

	FILE* fp = NULL;

	fp = fopen(datoteka, "rb+");

	if (fp == NULL) {
		perror("Greska");
		exit(EXIT_FAILURE);
	}
	//datoteka otvorena
	else {
		STUDENT privremeniStudent = { 0 }; //10
		printf("Ime: \n");
		scanf(" %50[^\n]", privremeniStudent.Ime); //3
		printf("Prezime: \n");
		scanf(" %50[^\n]", privremeniStudent.Prezime);
		printf("Broj mobitela studenta:\n");
		scanf(" %30[^\n]", privremeniStudent.brojMobitela);
		printf("Broj sobe:\n");
		char privremeniBroj[10] = { '\0' }; //12
		scanf("%9s", privremeniBroj);
		strcpy(privremeniStudent.brojSobe, "");
		strcat(privremeniStudent.brojSobe, privremeniBroj);
		privremeniStudent.brojac = (*brojStudenata)++;

		fseek(fp, sizeof(unsigned int) + ((*brojStudenata - 1) * sizeof(STUDENT)), SEEK_SET);
		fwrite(&privremeniStudent, sizeof(STUDENT), 1, fp);
		rewind(fp);
		fwrite(brojStudenata, sizeof(unsigned int), 1, fp);
		fclose(fp);
	}
}


void ispisiStudente(char* datoteka, unsigned int* brojStudenata) {

	FILE* fpRead = NULL;
	fpRead = fopen(datoteka, "rb");

	if (fpRead == NULL) {

		perror("Greska");
		exit(EXIT_FAILURE);
	}
	//datoteka otvorena
	else {
		//polje STUDENT struktura
		STUDENT* sviStudenti = NULL;

		fread(brojStudenata, sizeof(unsigned int), 1, fpRead);

		if (*brojStudenata == 0) {

			printf("Nema unesenih studenata!\n");
			fclose(fpRead);
			return;
		}
		//ako ima studenata
		else {
			sviStudenti = (STUDENT*)calloc(*brojStudenata, sizeof(STUDENT)); //13

			if (sviStudenti == NULL) {

				perror("Greska");
				exit(EXIT_FAILURE);
			}
			//uspjesno zauzimanje memorije
			else {
				fread(sviStudenti, sizeof(STUDENT), *brojStudenata, fpRead);
				fclose(fpRead);

				unsigned int i;
				//prikaz studenata
				for (i = 0; i < *brojStudenata; i++)
				{
					
					printf("Ime: %s, ", (sviStudenti + i)->Ime);
					printf("Prezime: %s, ", (sviStudenti + i)->Prezime);
					printf("Broj mobitela: %s, ", (sviStudenti + i)->brojMobitela);
					printf("Broj sobe: %s\n", (sviStudenti + i)->brojSobe);

				}
				free(sviStudenti);
			}
		}
	}
}

void pronalazenjeStudenta(char* datoteka, unsigned int* brojStudenata) {
	FILE* fpSearch = NULL;
	fpSearch = fopen(datoteka, "rb");

	if (fpSearch == NULL) {

		perror("Greska");
		return;

	}
	//datoteka otvorena
	else {
		STUDENT* sviStudenti = NULL;

		fread(brojStudenata, sizeof(unsigned int), 1, fpSearch);

		if (*brojStudenata == 0) {

			printf("Nema unesenih studenata!\n");
			fclose(fpSearch);
			return;
		}
		//ima studenata
		else {
			sviStudenti = (STUDENT*)calloc(*brojStudenata, sizeof(STUDENT)); //14

			if (sviStudenti == NULL) {

				perror("Greska");
				exit(EXIT_FAILURE);
			}
			//uspjesno zauzeto
			else {
				fread(sviStudenti, sizeof(STUDENT), *brojStudenata, fpSearch);
				fclose(fpSearch);
				unsigned int search;
				unsigned int i;
				printf("Pretrazi pomocu imena[1] ili broja sobe[2]?\n");
				do {
					scanf("%u", &search);
					if (search != 1 && search != 2)
					{
						printf("Unesite [1] ili [2]!\n");
					}
				} while (search != 1 && search != 2);

				
				//Ime ili broj sobe
				switch (search) {
				case 1:

					printf("Unesite ime\n");
					char privremenoIme[51] = { '\0' };
					scanf(" %50[^\n]", privremenoIme);
					unsigned int statusIme = 0;
					unsigned int indeksIme = -1;

					//usporedivanje stringa
					for (i = 0; i < *brojStudenata; i++)
					{
						if (!strcmp((sviStudenti + i)->Ime, privremenoIme)) { //21
							statusIme = 1;
							indeksIme = i;
						}
					}

					if (statusIme)
					{
						printf("\nStudent pronaden!\n");

						printf("Ime: %s\n", (sviStudenti + indeksIme)->Ime);
						printf("Prezime: %s\n", (sviStudenti + indeksIme)->Prezime);
						printf("Broj mobitela: %s\n", (sviStudenti + indeksIme)->brojMobitela);
						printf("Broj sobe: %s\n\n", (sviStudenti + indeksIme)->brojSobe);
					}
					else
					{
						printf("Student nije u bazi podataka\n");
					}
					break;

				case 2:

					printf("Unesite broj sobe:\n");
					char privremeniBroj[14] = { '\0' };
					scanf("%14s", privremeniBroj);
					unsigned int statusBroj = 0;
					unsigned int indeksBroj = -1;

					//usporedivanje stringa
					for (i = 0; i < *brojStudenata; i++)
					{

						if (!strcmp((sviStudenti + i)->brojSobe, privremeniBroj)) {
							statusBroj = 1;
							indeksBroj = i;
						}
					}

					if (statusBroj)
					{
						printf("\nStudent pronaden\n");

						printf("Ime: %s\n", (sviStudenti + indeksBroj)->Ime);
						printf("Prezime: %s\n", (sviStudenti + indeksBroj)->Prezime);
						printf("Broj Mobitela: %s\n", (sviStudenti + indeksBroj)->brojMobitela);
						printf("Broj sobe: %s\n\n", (sviStudenti + indeksBroj)->brojSobe);
					}
					else
					{
						printf("Student nije u bazi podataka\n");
					}
					break;

				default: //11
					printf("Nevazeci unos, pokusajte ponovo!\n");
				}
			}
			free(sviStudenti); //15
		}
	}

}




void uredivanjeStudenta(char* datoteka, unsigned int* brojStudenata) {

	FILE* fpEdit = NULL;
	fpEdit = fopen(datoteka, "rb");

	if (fpEdit == NULL) {

		perror("Greska");
		return;

	}
	//datoteka otvorena
	else {
		STUDENT* sviStudenti = NULL;

		fread(brojStudenata, sizeof(unsigned int), 1, fpEdit);

		if (*brojStudenata == 0) {

			printf("Nema unesenih studenata!\n");
			fclose(fpEdit);
			return;
		}
		//ima studenata
		else {
			sviStudenti = (STUDENT*)calloc(*brojStudenata, sizeof(STUDENT));

			if (sviStudenti == NULL) {
				perror("Greska");
				exit(EXIT_FAILURE);
			}
			//uspjesno zauzimanje memorije
			else {
				STUDENT privremeniStudent = { 0 };
				fread(sviStudenti, sizeof(STUDENT), *brojStudenata, fpEdit);

				unsigned int i;

				printf("Unesite ime studenta:\n");
				char privremenoIme[51] = { '\0' };
				scanf(" %50[^\n]", privremenoIme);
				unsigned int statusIme = 0;
				unsigned int indeksIme = -1;

				//usporedivanje stringa
				for (i = 0; i < *brojStudenata; i++)
				{
					if (!strcmp((sviStudenti + i)->Ime, privremenoIme)) {
						statusIme = 1;
						indeksIme = i;
					}
				}

				if (statusIme == 1) {
					printf("\nStudent pronaden\n");

					printf("Ime: %s\n", (sviStudenti + indeksIme)->Ime);
					printf("Prezime: %s\n", (sviStudenti + indeksIme)->Prezime);
					printf("Broj mobitela: %s\n", (sviStudenti + indeksIme)->brojMobitela);
					printf("Broj sobe: %s\n\n", (sviStudenti + indeksIme)->brojSobe);
					fclose(fpEdit);
					fpEdit = fopen(datoteka, "rb+");
					printf("Novo ime: \n");
					scanf(" %50[^\n]", privremeniStudent.Ime);
					printf("Novo prezime: \n");
					scanf(" %50[^\n]", privremeniStudent.Prezime);
					printf("Novi broj mobitela: \n");
					scanf(" %50[^\n]", privremeniStudent.brojMobitela);
					printf("Novi broj sobe: \n");
					char privremeniBroj[10] = { '\0' };
					scanf("%9s", privremeniBroj);
					strcpy(privremeniStudent.brojSobe, "");
					strcat(privremeniStudent.brojSobe, privremeniBroj);
					privremeniStudent.brojac = indeksIme;

					fseek(fpEdit, sizeof(unsigned int) + ((indeksIme) * sizeof(STUDENT)), SEEK_SET); //17
					fwrite(&privremeniStudent, sizeof(STUDENT), 1, fpEdit);
					rewind(fpEdit);
					fwrite(brojStudenata, sizeof(unsigned int), 1, fpEdit);
					fclose(fpEdit);
				}
				else {
					printf("Student nije u bazi podataka\n");
				}
				free(sviStudenti);
			}
		}
	}
	fclose(fpEdit);
}

void sortiranjeImena(char* datoteka, unsigned int* brojStudenata) { //20
	FILE* fpEdit = NULL;
	fpEdit = fopen(datoteka, "rb");

	if (fpEdit == NULL) {

		perror("Greska");
		return;

	}
	//datoteka otvorena
	else {
		STUDENT* sviStudenti = NULL;

		fread(brojStudenata, sizeof(unsigned int), 1, fpEdit);

		if (*brojStudenata == 0) {

			printf("Nema unesenih studenata!\n");
			fclose(fpEdit);
			return;
		}

		else {
			sviStudenti = (STUDENT*)calloc(*brojStudenata, sizeof(STUDENT));
			STUDENT temp;
			char prvoSlovo, prvoSlovoPom;
			int min;
			if (sviStudenti == NULL) {
				perror("Greska");
				exit(EXIT_FAILURE);
			}

			else {
				fread(sviStudenti, sizeof(STUDENT), *brojStudenata, fpEdit);

				for (int i = 0; i < *brojStudenata - 1; i++)
				{
					min = i;
					prvoSlovo = (sviStudenti + i)->Ime[0] >= 'A' && (sviStudenti + i)->Ime[0] <= 'Z' ? (sviStudenti + i)->Ime[0] : (sviStudenti + i)->Ime[0] - 32;
					for (int j = i + 1; j < *brojStudenata; j++)
					{
						prvoSlovoPom = (sviStudenti + j)->Ime[0] >= 'A' && (sviStudenti + j)->Ime[0] <= 'Z' ? (sviStudenti + j)->Ime[0] : (sviStudenti + j)->Ime[0] - 32;
						if (prvoSlovo < prvoSlovoPom)
						{
							min = j;
							prvoSlovo = (sviStudenti + j)->Ime[0] >= 'A' && (sviStudenti + j)->Ime[0] <= 'Z' ? (sviStudenti + j)->Ime[0] : (sviStudenti + j)->Ime[0] - 32;
						}
					}
					//zamjena Imena
					strcpy(temp.Ime, (sviStudenti + i)->Ime);
					strcpy((sviStudenti + i)->Ime, (sviStudenti + min)->Ime);
					strcpy((sviStudenti + min)->Ime, temp.Ime);
					//zamjena prezimena
					strcpy(temp.Prezime, (sviStudenti + i)->Prezime);
					strcpy((sviStudenti + i)->Prezime, (sviStudenti + min)->Prezime);
					strcpy((sviStudenti + min)->Prezime, temp.Prezime);
					//zamjena broja sobe
					strcpy(temp.brojSobe, (sviStudenti + i)->brojSobe);
					strcpy((sviStudenti + i)->brojSobe, (sviStudenti + min)->brojSobe);
					strcpy((sviStudenti + min)->brojSobe, temp.brojSobe);
					//zamjena broj mobitela
					strcpy(temp.brojMobitela, (sviStudenti + i)->brojMobitela);
					strcpy((sviStudenti + i)->brojMobitela, (sviStudenti + min)->brojMobitela);
					strcpy((sviStudenti + min)->brojMobitela, temp.brojMobitela);
				}

				//ispis na ekran
				for (int i = 0; i < *brojStudenata; i++)
				{
				

					printf("Ime: %s ", (sviStudenti + i)->Ime);
					printf("Prezime: %s ", (sviStudenti + i)->Prezime);
					printf("Broj mobitela: %s ", (sviStudenti + i)->brojMobitela);
					printf("Broj sobe: %s\n", (sviStudenti + i)->brojSobe);
				}
				free(sviStudenti);
			}
		}
	}
}





void izlazFunkcija(void) {

	printf("Jeste li sigurni da zelite izaci?(D/N)\n");
	char izbor[2] = { '\0' }; //1
	scanf(" %s", izbor);
	if (!strcmp("D", izbor)) {
		exit(EXIT_FAILURE);
	}
	return;
}

