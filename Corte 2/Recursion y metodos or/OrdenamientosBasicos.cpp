#include <iostream>
#include <vector>
using namespace std;

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        //arr[i] = rand() % 100;  // Inicializar con 0 (o cualquier otro valor que desees)
        arr[i] = 0;
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
    for (int i = 0; i < 4; i++){
        for (int j = i + 1; j < 5; j++){
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

void SelectSort(int arr[], int size){
    for (int i = 0; i < size - 1; i++){
        int minIndex = i;
        for (int j = 0; j < size; j++){
            if (arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        if (minIndex != i){
            int aux = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = aux;
            }
            print_arreglo(arr, size);
    }
}

void ShellSort(int arr[], int size){
int sizered = size / 2;
int aux, j, k;

    while(sizered > 0){
        for(int i = sizered; i < size; i++){
            j = i - sizered;
            while(j >= 0){
                k = j + sizered;
                if(arr[j] <= arr[k]){
                    j = -1;
                    } else{
                        aux = arr[j];
                        arr[j] = arr[k];
                        arr[k] = aux;
                    }
                    j = j - sizered;
                }  
            }
        sizered = sizered / 2;
        print_arreglo(arr, size);
    }
}

int partition(int* arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(int* arr, int low, int high){
    if(low < high){
        int pivotIndex = partition(arr,low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main(){
    int size = 5;
    int *arr = crear_arreglo(size);
    int high = size - 1;
    int low = 0;
    
    /*cout << "Insertar 1:" << endl;
    bubbleSort(arr, size);
    cout << "____________________________________________________";
    cout << endl;

    int *arr1 = crear_arreglo(size);

    cout << "Insertar 2:" << endl;
    InsertSort(arr1, size);
    cout << "____________________________________________________";
    cout << endl;

    int *arr2 = crear_arreglo(size);

    cout << "Insertar 3:" << endl;
    SelectSort(arr2, size);
    cout << "____________________________________________________";
    cout << endl;

    int *arr3 = crear_arreglo(size);

    cout << "Insertar 4:" << endl;
    ShellSort(arr3, size);
    cout << "____________________________________________________";
    cout << endl;*/

    int *arr4 = crear_arreglo(size);

    cout << "Insertar 5:" << endl;
    llenar_arreglo(arr4, size);
    print_arreglo(arr4,size);
    quickSort(arr4, low, high);
    print_arreglo(arr4, size);
    cout << "____________________________________________________"<< endl;
    cout << endl;    


    return 0;
}