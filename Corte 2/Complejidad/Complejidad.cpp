// T(N) : Tiempo exacto de ejecución del programa, ver numero de iteraciones, si son fijos los tamaños salen precisas, sino, toca mirar la formula general
// O(N) : El grado mayor el grado mas complejo, el crecimiento maximo. 
#include <iostream>
using namespace std;

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // Inicializar con 0 (o cualquier otro valor que desees)
        //arr[i] = 0;
    }
    return arr;
}

void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
    }
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

void bubbleSort(int *arr, int size){
    int n = 5;
    for (int i = 0; i < n - 2; i++){
        for (int j = i + 1; j < n - 1; j++){
            if (arr[i] >= arr[j]){
                int aux = arr[i];
                arr[i] = arr[j];
                arr[j] = aux;
                print_arreglo(arr, size);
            }
        }
    }
}

void InsertSort(int arr[], int size){
    for (int i = 1; i < size; i++){
        int aux = arr[i];
        int k = i - 1;
        bool sw = false;
              
        while (k >= 0 && sw == false){
            if (aux < arr[k]){
                arr[k + 1] = arr[k];
                k = k - 1;
            }
            else{
                sw = true;
            }
        }
        arr[k + 1] = aux;
        print_arreglo(arr, size);
    } 
}



int main(){
    int size = 5;

    int *arr = crear_arreglo(size);
    cout << "Insertar 1:" << endl;
    bubbleSort(arr, size);
    cout << "____________________________________________________";
    cout << endl;


    int *arr1 = crear_arreglo(size);
    cout << "Insertar 2:" << endl;
    InsertSort(arr1, size);
    cout << "____________________________________________________";
    cout << endl;

    return 0;
}