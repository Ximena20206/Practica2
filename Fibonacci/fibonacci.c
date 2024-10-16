/*Integrantes del equipo:
	-Barajas Pacheco Harol Fabian
	-Moran Diaz Barriga Jorge
	-Rocha Arellano Ximena Yulian
	-Rosales Barraza Erick Efren

	17 de octubre de 2024
	Programa que realiza la busqueda en un arreglo por medio del método de 
	Fibonacci
	Lenguaje de programacion: gcc
	Paradigma de programación: Imperativo
	
	Programa que realiza la búsqueda del índice donde se encuentra el valor x en un arreglo de n elementos, tomado del archivo 10millones.txt
	Donde n=10000000
	El arreglo de valores debe estar previamente ordenado para cumplir con los rangos de índices
	Complejidad del algoritmo: O(log n)
	
	Compilacion: gcc fibonacci.c -o fibonacci
	Ejecucion ./fibonacci 10000000 10millones.txt 90128
*/
//LIBRERIAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tiempo.h"
//1 Minimo entre dos enteros
/*Parámetros:
	-x: entero
	-y:entero
Devuelve:
Por medio de un if in line devuelve el mayor entre dos números*/
int min (int x, int y){
	return (x<=y)?x:y;
}


//2 Busqueda por medio de fibonacci recursivo
/*La funcion nombredada 'fibonacciSearch' hace uso de las serie de Fibonacci para poder realizar la búsqueda de un número en un arreglo 

Parámetros:
	- *A: Referencia del arreglo
	- x: Valor a buscar
	- n: Tamaño del arreglo	

Observaciones:
	-El arreglo de valores debe estar ordenado
	-La complejidad del algoritmo es O(log n)
	- El ordenamiento es in-place, lo que significa que se realiza en el mismo arreglo sin requerir espacio adicional significativo.
Algoritmo:
1. Asigna los 3 primeros valores de serie de Fibonacci a 0, 1 y 1
2. Calcula el valor de la serie de Fibonacci en el indice i
3. Si el valor de la serie de Fibonacci en el indice i es menor que el valor a buscar, se calcula el valor de la serie de Fibonacci en el indice i + 1
4. Si el valor de la serie de Fibonacci en el indice i es mayor que el valor a buscar, se calcula el valor de la serie de Fibonacci en el indice i - 1
5. Si el valor de la serie de Fibonacci en el indice i es igual que el valor a buscar, se retorna el indice i
6. Si no se encuentra el valor, se retorna -1

Devuelve: 
	- El índice donde se encuentra el valor
*/
int fibonacciSearch(int *A, int x, int n){
	int fibMMm2=0;
	int fibMMm1=1;
	int fibM=fibMMm2+fibMMm1;
	int i;
	while (fibM<n){
		fibMMm2=fibMMm1;
		fibMMm1=fibM;
		fibM=fibMMm2+fibMMm1;
	}
	int offset=-1;//Variable para el índice de la x
	while(fibM>1){
		i=min (offset+fibMMm2, n-1);
	//Si el valor del arreglo es menor que el buscado
	if (A[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        /* Si el valor buscado es menor al que se encuentra en el indice i */
        else if (A[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        /* si se encuentra el valor, se retorna el indice */
        else
            return i;
     
	}      
	 /* Compara el ultimo elemento con la c */
    	if (fibMMm1 && A[offset + 1] == x)
        return offset + 1;
    	/*Se devuelve -1 si no se encontr{o el elemento x */
    	return -1;
}


int func (int *A, int x, int n){	
	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i; //Variables para loops
		
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento	
	uswtime(&utime0, &stime0, &wtime0);
		
	//Algoritmo	
	int r= fibonacciSearch(A,x, n);
	
	//Evaluar los tiempos de ejecución 
	uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
    return r;
}

//**PROGRAMA PRINCIPAL***
//se reciben 4 parámetros: ejecutable, tamaño del Arreglo, archivo de texto con los numeros, valor buscado
int main (int argc, char **argv){
	//----variables-----
	FILE *p;
	int n, i=0, x;
	n=atoi(argv[1]);
	char name[100];
	//Se asigna memoria al arreglo
	int A= (int)malloc (sizeof(int)*n);
	//-----------------
	if (argc!=4){
		exit (1);
		free(A);
	}
	strcpy(name, argv[2]);
	x=atoi(argv[3]);
	if (!(p=fopen(name, "r"))){
		printf ("No se pudo abrir el archivo");
		free(A);
		exit(1);
	}
	//Se almacenan los valores obtenidos del archivo de texto a un arreglo
	while (!feof(p)&&i<n){
		fscanf(p,"%d", &A[i]);
		i++;
		}
	fclose(p);

	//Se llama a la funcion de buscar por Fibonacci
	int indice= func (int *A, int x, int n);
	if (indice>=0){
	printf ("Se encontró el elemento en el indice %d", indice);
	}else printf ("El elemento quen buscas no está contenido en el arreglo");

    free(A);
	return 0;
}   