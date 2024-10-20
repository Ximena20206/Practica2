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

Tiempo en busqueda: O(n)

Compilación
Windows: gcc busqueda_lineal.c tiempo.c tiempo.h -o bl
Linux:  gcc busqueda_lineal.c tiempo.c tiempo.h -o bl

Ejecución:
windows: ./bl n numeros10millones(Desordenados).txt x
linux: ./bl n numeros10millones(Desordenados).txt x
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"

/*
    En la siguiente función nombrada "busqueda_lineal", se implementa un algoritmo de busqueda lineal para buscar
    un número en cierta lista de n numeros

    Parámetros:
        - *A: Referencia de la lista de números enteros a buscar
        - n: Longitud de la lista
        - x: El número que se busca

    Algoritmo:
        - Se recorren todos los elementos de la lista con el iterador i
        - Si el elemento actual es igual a x, se retorna la posicion en la que se encuentra
        - De lo contrario, se retorna -1

    Devuelve:
        - int: Posicion del número en la lista
        - -1: No se encuentra el número
    
*/

#define NUM_THREADS 4 // Número de hilos

// definicion de los datos del thread
typedef struct {
    int *arr;
    int start;
    int end;
    int x;
    int thread_id;
    int result;
} ThreadData;

pthread_mutex_t lock;
//se inicializa el mutex
int global_result = -1;

void* thread_search(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    
    for (int i = data->start; i < data->end; i++) {
        if (data->arr[i] == data->x) {
            pthread_mutex_lock(&lock);
            if (global_result == -1) { // Si aún no se ha encontrado el valor
                global_result = i; // Guardamos el índice del valor encontrado
            }
            pthread_mutex_unlock(&lock);
            return NULL; // Finalizamos la búsqueda para este hilo
        }
    }
    
    return NULL; // Si no encontró nada
}

/*Funcion que ayuda a mostrar datos de ejecucion en SO linux. 
    Parámtros:
    - *A:arreglo de numeros
    - n tamano del arreglo
    - x: numero buscar en el arreglo
    
    Devuelve:
    -r: respuesta del algoritmo binarysearch
*/

int func(int *A, int n, int x) {
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    int i, s; 
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Inicializamos el mutex
    pthread_mutex_init(&lock, NULL);

    // Dividimos el arreglo en partes iguales para cada hilo
    int part_size = n / NUM_THREADS;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = A;
        thread_data[i].start = i * part_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * part_size;
        thread_data[i].x = x;
        thread_data[i].result = -1;
        thread_data[i].thread_id = i;

        // Crear un hilo que realice la búsqueda
        pthread_create(&threads[i], NULL, thread_search, (void*) &thread_data[i]);
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    // Mostrar los tiempos en formato exponencial
    printf("\n");
    printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    pthread_mutex_destroy(&lock); // Destruimos el mutex

    return global_result; // Retornamos el resultado global
}

int main(int num_par, char **par_cad) {
    FILE *p;
    int *A, n, i = 0, x, s;

    // Verificar que el usuario ingrese 4 parámetros
    if (num_par != 4)
        exit(1);

    n = atoi(par_cad[1]);
    A = (int *)malloc(n * sizeof(int));

    // Lectura del archivo
    if (!(p = fopen(par_cad[2], "r"))) {
        printf("\nError al abrir el fichero");
        exit(1);
    }
    while (!feof(p) && i < n) {
        fscanf(p, "%d", &A[i]);
        i++;
    }
    fclose(p);

    // Designamos la variable a buscar
    x = atoi(par_cad[3]);

    // Aplicamos algoritmo
    s = func(A, n, x);

    // Imprimimos el valor del número buscado
    printf("Posición: %d\n", s);

    free(A);

    return 0;
}
