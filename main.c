#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int main(void) {

	char* fp = "clanovi.bin"; //16
	unsigned int brojStudenata = 0;

	kreiranje(fp, &brojStudenata); //10

	glavniIzbornik(fp, &brojStudenata);

	return 0;
}
