#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int main(void) {

	char* fp = "clanovi.bin"; //16
	unsigned int STUDENTNumber = 0;

	kreiranje(fp, &STUDENTNumber); //10

	glavniIzbornik(fp, &STUDENTNumber);

	return 0;
}
