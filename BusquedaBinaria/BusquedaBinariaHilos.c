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
Windows: gcc BusquedaBinariaHilos.c tiempo.c tiempo.h -o bbh
Linux:  gcc BusquedaBinariaHilos.c tiempo.c tiempo.h -o bbh

Ejecución:
windows: ./bbh n numeros10millones(Desordenados).txt x
linux: ./bbh n numeros10millones(Desordenados).txt x
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"
#define NUM_THREADS 2

typedef struct {
    int *arr;
    int left;
    int right;
    int target;
    int result;
} ThreadData;


/*
    En la siguiente función nombrada "binarySearchThread", se implementa la búsqueda binaria en un arreglo
    de manera concurrente mediante el uso de hilos (threads).

    Parámetros:
        - *arg: Apuntador a una estructura de tipo ThreadData que contiene:
            
    Observaciones:
        - El algoritmo divide el arreglo en dos partes, cada hilo busca en una de las mitades del arreglo.
        - La búsqueda binaria es eficiente con un tiempo de ejecución de O(log n).

    Algoritmo:
        - Se establece un ciclo que se ejecuta mientras left sea menor o igual a right.
        - Calculamos el índice del medio, middle = left + (right - left) / 2.
        - Si el elemento en la posición middle es el objetivo (target), se guarda el resultado y se termina el hilo.
        - Si el valor en middle es menor que el target, ajustamos left a middle + 1 para ignorar la mitad izquierda.
        - Si es mayor, ajustamos right a middle - 1 para ignorar la mitad derecha.
        - Si no se encuentra el target, se almacena -1 en result y se termina el hilo.

    Devuelve:
        - No retorna un valor, pero modifica el valor de result en la estructura ThreadData.
*/
void *binarySearchThread(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int left = data->left;
    int right = data->right;
    int target = data->target;
    int *arr = data->arr;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (arr[middle] == target) {
            data->result = middle;
            pthread_exit(NULL);
        }

        if (arr[middle] < target)
            left = middle + 1;
        else
            right = middle - 1;
    }

    data->result = -1;
    pthread_exit(NULL);
}


/*
    En la siguiente función nombrada "Hilos", se implementa el uso de hilos para realizar la búsqueda binaria
    de manera concurrente en un arreglo de números enteros. El arreglo se divide en dos partes, y cada hilo busca
    en una de las mitades.

    Parámetros:
        - *A: Referencia al arreglo de números enteros en el que se realizará la búsqueda.
        - x: Valor a buscar en el arreglo.
        - n: Tamaño del arreglo.

    Observaciones:
        - Se utilizan dos hilos para dividir la búsqueda binaria en dos mitades.
        - Esta técnica puede mejorar la eficiencia en sistemas multiprocesadores o multinúcleo.
        - La búsqueda es más eficiente cuando el arreglo está previamente ordenado.

    Algoritmo:
        - Se crean dos hilos que ejecutarán la función "binarySearchThread" de manera concurrente.
        - El arreglo se divide en dos mitades, y cada hilo se encarga de buscar en una mitad.
        - Cada hilo busca de manera independiente usando búsqueda binaria.
        - Una vez que ambos hilos terminan, se verifica cuál de los dos encontró el objetivo.
        - Si se encuentra el objetivo, se muestra su índice; si no, se indica que no está presente.

    Devuelve:
        - No retorna un valor, pero imprime en consola el índice donde se encontró el valor o indica que no está presente.
*/
void Hilos(int *A, int x, int n){

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Dividir el arreglo en dos mitades para los dos hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = A;
        thread_data[i].target = x;
        thread_data[i].result = -1;

        if (i == 0) {
            thread_data[i].left = 0;
            thread_data[i].right = n / 2 - 1;
        } else {
            thread_data[i].left = n / 2;
            thread_data[i].right = n - 1;
        }

        // Crear hilos para buscar en cada mitad
        pthread_create(&threads[i], NULL, binarySearchThread, &thread_data[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Verificar si algún hilo encontró el objetivo
    int result = -1;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (thread_data[i].result != -1) {
            result = thread_data[i].result;
            break;
        }
    }

    if (result != -1)
        printf("El elemento esta en el índice %d\n", result);
    else
        printf("El elemento no esta en el arreglo\n");
}

/*Funcion que ayuda a mostrar datos de ejecucion en SO linux. 
    Parámtros:
    - *A:arreglo de numeros
    - n tamano del arreglo
    - x: numero buscar en el arreglo
    
    Devuelve:
    -r: respuesta del algoritmo binarysearch
*/
void func(int *A, int n, int x){
    double utime0, stime0, wtime0, utime1, stime1, wtime1; //Variables para medición de tiempos
    int i, s; //Variables para loops

    //Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    //Algoritmo
    Hilos(A, x, n);

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

int main(int num_par, char  **par_cad) {
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
    //Hilos(A,x,n);
    func(A,n,x);

    free(A);
    return 0;
}
