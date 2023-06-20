#ifndef MYHEADER
#define MYHEADER

typedef struct student { //2 //3
	unsigned int brojac;
	char Ime[51];
	char Prezime[51];
	char brojSobe[14];
	char brojMobitela[31];
	struct student* nextNode;
}STUDENT;

void kreiranje(char* datoteka, unsigned int* pBrojStudenata);
void glavniIzbornik(char* datoteka, unsigned int* BrojStudenata);
void pocetniIzbornik();
void dodajStudenta(char* datoteka, unsigned int* brojStudenata);
void ispisiStudente(char* datoteka, unsigned int* brojStudenata);
void pronalazenjeStudenta(char* datoteka, unsigned int* brojStudenata);
void uredivanjeStudenta(char* datoteka, unsigned int* brojStudenata);
void sortiranjeImena(char* datoteka, unsigned int* brojStudenata);
void izlazFunkcija(void);

#endif
