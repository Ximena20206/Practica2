/*
INTEGRANTES DEL EQUIPO:
- Barajas Pacheco Harol Fabian
- Morán Diaz Barriga Jorge
- Rocha Arellano Ximena Yulian
- Rosales Barraza Erick Efren

V 1.0 Octubre 2024

Programa que realiza la búsqueda de un número x dentro de una lista de n numeros proveniente del archivo txt.
Donde

para (4)
x = A[i]
donde A = [322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0]
y n = [1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000]

Tiempo en busqueda: O(log n)

Compilación
Windows: gcc BusquedaBinaria.c tiempo.c tiempo.h -o bb
Linux:  gcc BusquedaBinaria.c tiempo.c tiempo.h -o bh

Ejecución:
windows: ./bh n numeros10millones(Desordenados).txt x
linux: ./bh n numeros10millones(Desordenados).txt x
*/
#include <stdio.h>
#include "tiempo.h"

/*
    En la siguiente función "binarySearch", se implementa la búsqueda binaria
    de manera iterativa para encontrar un valor objetivo en un arreglo ordenado.

    Parámetros:
        - *A: Arreglo de enteros donde se va a buscar el valor objetivo.
        - n: El tamaño del arreglo A.
        - x: El valor objetivo a buscar dentro del arreglo.

    Observaciones:
        - Utiliza la técnica de dividir y conquistar, dividiendo el rango de búsqueda
          a la mitad en cada iteración.
        - Es eficiente con un tiempo de complejidad O(log n), pero el arreglo debe estar
          previamente ordenado.

    Algoritmo:
        - Se inicializan dos punteros, left y right, para delimitar el rango de búsqueda.
        - En cada iteración, se calcula el índice medio y se compara el valor objetivo con
          el valor en la posición media.
        - Si el objetivo es igual al valor medio, se retorna el índice medio.
        - Si el objetivo es mayor, se ajusta left para ignorar la mitad izquierda.
        - Si el objetivo es menor, se ajusta right para ignorar la mitad derecha.
        - Si no se encuentra el valor, se retorna -1.

    Devuelve:
        - El índice donde se encuentra el valor objetivo, o -1 si no está presente.
*/
int binarySearch(int *A, int n, int x) {
    int left = 0;
    int right = n - 1;
    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;

        // Verifica si x está en el medio
        if (A[middle] == x) {
            return middle;
        }

        // Si el x es mayor, ignora la mitad izquierda
        if (A[middle] < x) {
            left = middle + 1;
        }
        // Si el x es menor, ignora la mitad derecha
        else {
            right = middle - 1;
        }
    }

    // Si no se encontró el elemento
    return -1;
}

void func(int *A, int n, int x){
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    int i, s; //Variables para loops

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    //Algoritmo
    binarySearch(A,n,x);

    //Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    //Damos datos a mostrar
    printf("\nPara n: %d x: %d", n, x);

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
    printf("-------------------------------------------------------------------");

}


int main(int num_par, int  **par_cad) {
    //Variables
    FILE *p; //apuntador para direccion de archivo
    int *A, n, i=0, x;

    //Verificar que el usuario ingrese 4 parámetros: archivo a ejecutar, n, fichero, x
    if(num_par!=4)
        exit(1);
    
    // designamos tamaño del arreglo
    n=atoi(par_cad[1]);
    A=(int*)malloc(n*sizeof(int));

    //Lectura del archivo
    if(!(p=fopen(par_cad[2],"r")))//verificamos que el archivo exista
    {
        printf("\nError al abrir el fichero");
        exit(1); // abandonamos el programa
    }
    while(!feof(p) && i<n)// llenar el arreglo mientras i < n y no haya fin de archivo
    {
        fscanf(p, "%d", &A[i]); //leemos los numeros y guardamos en el arreglo
        i++;
    }
    fclose(p);

    // Designamos la variable a buscar
    x=atoi(par_cad[3]);
    
    //*Algoritmo
    binarySearch(A,n,x);
    //func(A,n,x);

    return 0;
}