/*
INTEGRANTES DEL EQUIPO:
- Barajas Pacheco Harol Fabian
- Morán Diaz Barriga Jorge
- Rocha Arellano Ximena Yulian
- Rosales Barraza Erick Efren

V 1.0 Octubre 2024

Programa que realiza la búsqueda de un número x dentro de una lista de n numeros proveniente del archivo txt
con el algoritmo de busqueda de arbol ABB.
Donde

para (4)
n = A[i]
donde A = [322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0]
y n = [1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000]

Tiempo en busqueda: O(n)

Compilación
Windows: gcc busqueda_abb.c tiempo.c tiempo.h -o bAbb
Linux:  gcc busqueda_abb.c tiempo.c tiempo.h -o bAbb

Ejecución:
windows: ./bAbb n numeros10millones(Desordenados).txt x
linux: ./bAbb n numeros10millones(Desordenados).txt x
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"

/*
    En la siguiente función nombrada "busqueda_abb", se implementa un algoritmo de busqueda de arbol binario para buscar
    un número en cierta lista de n numeros

    Parámetros:
        - *A: Referencia de la lista de números enteros a buscar
        - n: Longitud de la lista
        - x: El número que se busca

    Algoritmo:
        - Se rellena el Arbol con el algorítmo de ordenamiento.
        - Se ordena el Arbol con la función InOrder, la cual define
        si la rama que se introdujo es mayor o menor y se va recorriendo
        el arbol hasta encontrar su lugar en este.
        - Se invoca la función search, que es el algoritmo de busqueda
        - Recorre el arbol dependiendo si es mayor o menor al valor de
        la rama en la que esté, si es mayor el número, recorre hacia la
        izquierda, sino, hacia la derecha, y si ya no hay valores se le
        asigna el valor nulo.
        -Al encotrar el valor, se retorna este mismo;

    Devuelve:
        - char*: Sí, si se encontró el número
        - No, si no se encontró
*/

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Estructura para pasar parámetros a los threads
struct ThreadArgs {
    struct Node* root;
    int key;
    int found;
};

// Función para crear un nuevo nodo del árbol
struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Función para insertar un nodo en el ABB
struct Node* insert(struct Node* root, int x) {
    if (root == NULL)
        return newNode(x);

    if (x < root->key)
        root->left = insert(root->left, x);
    else if (x > root->key)
        root->right = insert(root->right, x);

    return root;
}

// Recorrido InOrder del ABB (para depuración)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        inorder(root->right);
    }
}

// Función de búsqueda en el ABB (usada por cada thread)
void* search_thread(void* args) {
    struct ThreadArgs* searchArgs = (struct ThreadArgs*)args;
    struct Node* root = searchArgs->root;
    int key = searchArgs->key;

    while (root != NULL) {
        if (root->key == key) {
            searchArgs->found = 1;
            return NULL;
        }
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    searchArgs->found = 0;
    return NULL;
}

/*Funcion que ayuda a mostrar datos de ejecucion en SO linux. 
    Parámtros:
    - *A:arreglo de numeros
    - n tamano del arreglo
    - x: numero buscar en el arreglo
    
    Devuelve:
    -r: respuesta del algoritmo binarysearch
*/

int main(int num_par, char **par_cad) {
    // Variables
    FILE *p; // apuntador para direccion de archivo
    int *A, n, i = 0;
    int x;

    // Verificar que el usuario ingrese 4 argumentos: archivo a ejecutar, n, fichero, x
    if (num_par != 4) {
        exit(1);
    }

    // Designamos tamaño del arreglo
    n = atoi(par_cad[1]);
    A = (int*)malloc(n * sizeof(int));

    // Lectura del archivo
    if (!(p = fopen(par_cad[2], "r"))) {
        printf("\nError al abrir el fichero");
        exit(1); // abandonamos el programa
    }

    while (!feof(p) && i < n) {
        fscanf(p, "%d", &A[i]); // leemos los numeros y guardamos en el arreglo
        i++;
    }

    // Rellenamos el arbol
    struct Node* root = newNode(A[0]);
    for (i = 1; i < n; i++) {
        root = insert(root, A[i]);
    }

    // Ordenar el arbol de datos (opcional, solo para verificar el contenido)
    inorder(root);

    // Designamos la variable a buscar
    x = atoi(par_cad[3]);

    // Creamos 2 threads para buscar en las ramas izquierda y derecha
    pthread_t thread1, thread2;
    struct ThreadArgs args1 = { root->left, x, 0 };
    struct ThreadArgs args2 = { root->right, x, 0 };

    // Iniciar el conteo del tiempo
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    uswtime(&utime0, &stime0, &wtime0);

    // Ejecutar la búsqueda en dos threads (rama izquierda y derecha)
    pthread_create(&thread1, NULL, search_thread, (void*)&args1);
    pthread_create(&thread2, NULL, search_thread, (void*)&args2);

    // Esperar que los threads terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
    printf("sys (Tiempo en acciones de E/S)  %.10f s\n",  stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    //Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

    free(A);
    fclose(p);

    return 0;
}
