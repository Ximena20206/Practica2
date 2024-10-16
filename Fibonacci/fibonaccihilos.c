#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
//#include "tiempo.h"
// Se hce uso de una estructura para poder partir las operaciones y definir el inicio y final de los segmentos de cada hilo
/*
Compilacion: gcc fibonacci.c -o fibonacci
Ejecucion:*/
typedef struct {
    int *A;        // Arreglo a buscar
    int x;         // Valor a buscar
    int inicio;     // Índice inicial del segmento
    int fin;       // Índice final del segmento
    int res;    // Resultado de la búsqueda
} Parametros;
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
		
	//Algoritmo	de fibonacci
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
/*Función que se ejecuta en hilos
Recibe como parámetro un puntero a un Parametros
Almacena el resultado en el atributo res del Parametros
llamando a la función func para contabilizar el tiempo en el que se ejecuta el hilo*/
void* threadedFibonacciSearch(void* params) {
    Parametros* p = (Parametros*)params;
    p->res = func(p->A, p->x, p->inicio - p->fin + 1);
    return NULL;
}
//**PROGRAMA PRINCIPAL***
//se reciben 4 parámetros: ejecutable, tamaño del Arreglo, archivo de texto con los numeros, valor buscado
int main(int argc, char **argv) {
    //----variables-----
	FILE *p;
	int n, i=0, x;
	n=atoi(argv[1]);
	char name[100];
	//Se asigna memoria al arreglo
	int *A= (int*)malloc (sizeof(int)*n);
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

    // Crear hilos
    int numThreads = 3; // Cantidad de hilos
    pthread_t threads[numThreads]; // Arreglo de identificadores de hilos
    Parametros Parametros[numThreads]; // Arreglo de parámetros de hilos

    int tam = n / numThreads; // Tamaños de los segmentos
    //Crea y ejecuta los hilos a partir de los parámetros asignados en la estructura Parametros
    for (int i = 0; i < numThreads; i++) {
        Parametros[i].A = A;
        Parametros[i].x = x;
        Parametros[i].inicio = i * tam;
        Parametros[i].fin = (i == numThreads - 1) ? (n - 1) : ((i + 1) * tam - 1);//Si es el último segmento, el final es el n-1, de lo contrario, el final es el (i+1)*tam-1
        Parametros[i].res = -1;

        pthread_create(&threads[i], NULL, threadedFibonacciSearch, &Parametros[i]);//se crea el hilo y se llama a la funciÃ³n
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        if (Parametros[i].res != -1) {
            printf("Se encontró el elemento en el índice %d\n", Parametros[i].res);
            break;
        }
    }

    free(A);
    return 0;
}
