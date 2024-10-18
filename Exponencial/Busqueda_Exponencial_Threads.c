/*
INTEGRANTES DEL EQUIPO:
- Barajas Pacheco Harol Fabian
- Morán Diaz Barriga Jorge
- Rocha Arellano Ximena Yulian
- Rosales Barraza Erick Efren

V 1.0 Octubre 2024

Este programa realiza una búsqueda exponencial seguida de una búsqueda binaria de un número x dentro de una lista de n números, provenientes de un archivo de texto.
El programa implementa hilos para paralelizar la búsqueda exponencial y la búsqueda binaria.

Compilación:
Windows: gcc busqueda_paralela.c tiempo.c -o bp -lpthread
Linux: gcc busqueda_paralela.c tiempo.c -o bp -lpthread

Ejecución:
windows: ./bp x n numeros10millones(Desordenados).txt
linux: ./bp x n numeros10millones(Desordenados).txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"

// Estructura para pasar datos entre los hilos
typedef struct {
    int *Nums;
    int x;
    int inicio;
    int fin;
    int pos;
} BusquedaData;

// Función para la búsqueda exponencial en un hilo
void *busqueda_exponencial(void *args) {
    BusquedaData *data = (BusquedaData *)args;
    int *Nums = data->Nums;
    int x = data->x;
    int size = data->fin; // 'fin' se utiliza como el tamaño del array
    int inicio = 0, fin = 0;

    for (int i = 1; i < size; i *= 2) {
        if (x > Nums[i]) {
            inicio = i;
        } else if (x < Nums[i]) {
            fin = i;
            break;
        } else {
            data->pos = i; // Si el número se encuentra
            return NULL;
        }
    }

    if (fin == 0) {
        fin = size - 1; // Si `fin` no fue actualizado, buscar hasta el final
    }

    data->inicio = inicio;
    data->fin = fin;
    return NULL;
}

// Función para la búsqueda binaria en un hilo
void *busqueda_binaria(void *args) {
    BusquedaData *data = (BusquedaData *)args;
    int *Nums = data->Nums;
    int x = data->x;
    int inicio = data->inicio;
    int fin = data->fin;
    int pos = -1;

    while (inicio <= fin && pos == -1) {
        int m = inicio + (fin - inicio) / 2;

        if (x < Nums[m]) {
            fin = m - 1;
        } else if (x > Nums[m]) {
            inicio = m + 1;
        } else {
            pos = m; // Número encontrado
        }
    }

    data->pos = pos;
    return NULL;
}

// Función principal que ejecuta la búsqueda y mide el tiempo de ejecución
int main(int argc, char *argv[]) {
    // Variables para el manejo de tiempo
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    // Verificar que se ingresen los parámetros correctos
    if (argc != 4) {
        printf("Uso: %s <n> <archivo> <numero_a_buscar>\n", argv[0]);
        return 1;
    }

    // Abrir el archivo con los números
    FILE *archivo = fopen(argv[2], "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Inicializar arreglo dinámico para los números
    int *Nums = NULL;
    int numero, size = 0, capacity = 10;
    Nums = (int *)malloc(capacity * sizeof(int));
    if (Nums == NULL) {
        printf("Error en la asignación de memoria\n");
        return 1;
    }

    // Leer los números del archivo
    while (fscanf(archivo, "%d", &numero) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            Nums = (int *)realloc(Nums, capacity * sizeof(int));
            if (Nums == NULL) {
                printf("Error en la asignación de memoria\n");
                return 1;
            }
        }
        Nums[size++] = numero;
    }

    fclose(archivo);

    // Asignar valores de entrada
    int n = atoi(argv[1]);  // Tamaño del arreglo
    int x = atoi(argv[3]);  // Número a buscar

    // Iniciar el conteo del tiempo
    uswtime(&utime0, &stime0, &wtime0);

    // Crear datos para las búsquedas y los hilos
    BusquedaData data = {Nums, x, 0, size - 1, -1};
    pthread_t hilo_exponencial, hilo_binario;

    // Crear y ejecutar el hilo para la búsqueda exponencial
    pthread_create(&hilo_exponencial, NULL, busqueda_exponencial, &data);
    pthread_join(hilo_exponencial, NULL); // Esperar a que el hilo termine

    // Si el número ya fue encontrado en la búsqueda exponencial
    if (data.pos == -1) {
        // Crear y ejecutar el hilo para la búsqueda binaria
        pthread_create(&hilo_binario, NULL, busqueda_binaria, &data);
        pthread_join(hilo_binario, NULL); // Esperar a que el hilo termine
    }

    // Parar el conteo del tiempo
    uswtime(&utime1, &stime1, &wtime1);

    // Mostrar resultados de la búsqueda
    if (data.pos != -1) {
        printf("El numero %d se encuentra en la posicion %d\n", x, data.pos);
    } else {
        printf("Numero no encontrado\n");
    }

    // Mostrar los tiempos de ejecución
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo en acciones de E/S)  %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

    // Liberar la memoria
    free(Nums);

    return 0;
}
