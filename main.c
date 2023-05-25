#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include"header.h"
//Koristenje obveznih koncepata
//koristenje camelCase
//10.
//8.
//16.
//6.
//4.

int main() {
	int izbor; 
	do {
		ispisIzbornika(); //8
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			ispisiStudente();
			break;
		case 2:
			ispisiStudente();
			break;
		case 3:
			pronadiStudenta();
			break;
		case 4:
			pronadiStudenta();
			break;
		case 5:
			popisSlobodnihSoba();
			break;
		case 6:
			dodajStudenta();
			break;
		case 7:
			uredivanjeStudenata();
			break;
		case 8: 
			brisanjeStudenata();
			break;
		default:
			printf("Neispravan izbor\n");
			break;
		}


	} while (1);

	return 0;
}
