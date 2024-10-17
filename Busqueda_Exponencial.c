/*
INTEGRANTES DEL EQUIPO:
- Barajas Pacheco Harol Fabian
- Morán Diaz Barriga Jorge
- Rocha Arellano Ximena Yulian
- Rosales Barraza Erick Efren

V 1.0 Octubre 2024

Programa que realiza una búsqueda exponencial seguida de una búsqueda binaria de un número x dentro de una lista de n números provenientes de un archivo txt.
Donde:

para (4)
x = A[i]
donde A = [322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0]
y n = [1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000]

Tiempo en búsqueda: O(log n)

Compilación:
Windows: gcc busqueda_exponencial.c tiempo.c tiempo.h -o be
Linux: gcc busqueda_exponencial.c tiempo.c tiempo.h -o be

Ejecución:
windows: ./be x n numeros10millones(Desordenados).txt
linux: ./be x n numeros10millones(Desordenados).txt
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

/*
    La siguiente función realiza una búsqueda exponencial para encontrar un rango y luego una búsqueda binaria
    dentro de ese rango en un arreglo de enteros A de tamaño N para encontrar el valor x.

    Parámetros:
        - *A: Arreglo de enteros
        - N: Tamaño del arreglo
        - x: Número a buscar

    Algoritmo:
        - Si el número x está en la primera posición, se retorna la posición 0
        - Se realiza una búsqueda exponencial para determinar un rango donde puede estar el número
        - Luego, dentro de ese rango, se realiza una búsqueda binaria para encontrar el número

    Devuelve:
        - int: La posición del número en el arreglo, o -1 si no se encuentra
*/

int search_exponential_binary(int *A, int N, int x) {
    int inicio = 0, fin = 0, m = 0, pos = -1;

    // Caso especial: si el número está en la primera posición
    if (x == A[0]) {
        return 0;
    }

    // Búsqueda exponencial para encontrar el rango
    for (int i = 1; i < (2 * N) && i < N; i *= 2) {
        if (x > A[i]) {
            inicio = i;
        } else if (x < A[i]) {
            fin = i;
            break;
        } else {
            return i;  // Número encontrado en la búsqueda exponencial
        }
    }

    // Si fin no fue actualizado, buscar hasta el final
    if (fin == 0) {
        fin = N - 1;
    }

    // Búsqueda binaria en el rango determinado por la búsqueda exponencial
    while (inicio <= fin && pos == -1) {
        m = inicio + (fin - inicio) / 2;

        if (x < A[m]) {
            fin = m - 1;
        } else if (x > A[m]) {
            inicio = m + 1;
        } else {
            pos = m;  // Número encontrado
        }
    }

    return pos;  // Retorna la posición o -1 si no se encuentra
}

/*
    Función principal que ejecuta la búsqueda exponencial y binaria, midiendo el tiempo de ejecución del algoritmo.
*/

int func(int *A, int n, int x) {
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medir tiempos
    int pos;

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Algoritmo de búsqueda exponencial y binaria
    pos = search_exponential_binary(A, n, x);

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo en acciones de E/S)  %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    // Mostrar los tiempos en formato exponencial
    printf("\n");
    printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
    printf("sys (Tiempo en acciones de E/S)  %.10e s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    return pos;
}

int main(int argc, char *argv[]) {
    // Variables
    FILE *archivo;
    int *A, n, i = 0, x, pos;
    int capacity = 10000000; // Tamaño máximo del arreglo

    // Verificar que el usuario ingrese los parámetros correctos
    if (argc != 4) {
        printf("Uso: %s <n> <archivo> <numero_a_buscar>\n", argv[0]);
        return 1;
    }

    // Designamos tamaño del arreglo
    n = atoi(argv[1]);
    A = (int *)malloc(n * sizeof(int));

    // Lectura del archivo
    archivo = fopen(argv[2], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", argv[2]);
        return 1;
    }

    // Leer los números del archivo
    while (!feof(archivo) && i < n) {
        fscanf(archivo, "%d", &A[i]);
        i++;
    }
    fclose(archivo);

    // Asignamos el número a buscar
    x = atoi(argv[3]);

    // Aplicamos el algoritmo
    pos = func(A, n, x);

    // Imprimimos el resultado de la búsqueda
    if (pos != -1) {
        printf("El numero %d se encuentra en la posicion %d\n", x, pos);
    } else {
        printf("Numero no encontrado\n");
    }

    // Liberar memoria
    free(A);

    return 0;
}
