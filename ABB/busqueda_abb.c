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

struct Node* newNode(int item)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* root, int x)
{
    struct Node* temp = newNode(x);
    if (root == NULL)
        return temp;

    struct Node *parent = NULL, *curr = root;
    while (curr != NULL) {
        parent = curr;
        if (curr->key > x)
            curr = curr->left;
        else if (curr->key < x)
            curr = curr->right;
        else
            return root;
    }
    if (parent->key > x)
        parent->left = temp;
    else
        parent->right = temp;
    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct Node* search(struct Node* root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

/*Funcion que ayuda a mostrar datos de ejecucion en SO linux. 
    Parámtros:
    - *A:arreglo de numeros
    - n tamano del arreglo
    - x: numero buscar en el arreglo
    
    Devuelve:
    -r: respuesta del algoritmo binarysearch
*/

char* func (struct Node* root, int key){
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i; //Variables para loops
		
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento	
	uswtime(&utime0, &stime0, &wtime0);
		
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

    //Algoritmo y salida
    return(search(root,key) != NULL ? "Si" : "No");
}

int main(int num_par, char **par_cad)
{
    //Variables
    FILE *p; //apuntador para direccion de archivo
    int *A,n, i=0;
    char* res;

    //verificar que el usuario ingrese 4 argumentos: archivo a ejecutar, n, fichero, x
    if(num_par!=4){
        exit(1);
    }

    // designamos tamaño del arreglo
    n=atoi(par_cad[1]);
    A =(int*)malloc(n*sizeof(int));
    
    //Lectura del archivo
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
    // Rellenamos el arbol
    struct Node* root = newNode(A[0]);
    for (i=0;i<n;i++){
        root = insert(root, A[i]);
    }

    //Ordenar el arbol de datos
    inorder(root);

    //Designamos la variable a buscar
    int x=atoi(par_cad[3]);
    func(root, x);
    fclose(p);

    //Ejecucion del algoritmo
    res = func(root, x);

    //Imprimimos el resultado
    printf("%s", res);

    free(A);

    return 0;
}
