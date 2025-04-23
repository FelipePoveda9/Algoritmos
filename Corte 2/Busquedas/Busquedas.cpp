#include <iostream>

using namespace std;


// Función para realizar una búsqueda secuencial
int busquedaSecuencial(int arreglo[], int n, int valor) {
    // Recorrer el arreglo buscando el valor
    for (int i = 0; i < n; i++) {
        if (arreglo[i] == valor) {
            return i; // Retorna la posición donde se encontró el valor
        }
    }
    return -1; // Retorna -1 si no se encuentra el valor
}

int busquedaBinaria(int arreglo[], int n, int valor) {
    int bajo = 0;
    int alto = n - 1;
    while (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2;  // Calcula el índice medio

       if (arreglo[medio] == valor) {
            return medio;  // Retorna la posición donde se encontró el valor
        }        
      if (arreglo[medio] < valor) {
            bajo = medio + 1;
        }
      else {
            alto = medio - 1;
        }
    }    
    return -1;  // Retorna -1 si no se encuentra el valor
}


main(){
    int size = 5;
}
