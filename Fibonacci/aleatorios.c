//Barajas Pacheco Harol Fabian
//3CM4
//Paradigma de programacion: Imperativo
//Lenguaje de Programacion: C
//6 de octubre de 2024
/*Programa para generar los numeros aleatorios

Compilacion: gcc nonmbre.c -o i

Ejecución ./i n numeros.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(int argc,char *argv[]){
	FILE *p;
	int n,i;
	char nombreArchivo[100];
	if (argc!=3){
		exit (1);
	}
	n=atoi (argv[1]);
	strcpy(nombreArchivo,argv[2]);
	if (!(p=fopen(nombreArchivo, "w"))){
		printf ("No se pudo abrir el archivo\n");
		exit (1);
	}
	srand(time(NULL));
	for (int i = 0; i <= n; i++) {
        int numero = rand() % 1000; // Números aleatorios entre 0 y 999
        fprintf(p, "%d\n", numero);
    }

    fclose(p);
	return 0;
}
