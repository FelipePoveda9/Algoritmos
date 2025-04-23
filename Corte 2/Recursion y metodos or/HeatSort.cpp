#include <iostream>
#include <vector>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

// Espacio de nombres hpsort_util con la función sift_down
namespace hpsort_util {
    template<class T>
    void sift_down(std::vector<T> &ra, const int l, const int r) {
        // Realiza la operación sift-down en el elemento ra[l] para mantener la estructura del montículo.
        // l y r determinan el rango "izquierdo" y "derecho" del sift-down.
        
        int j, jold;
        T a;
        a = ra[l];
        jold = l;
        j = 2*l + 1;
        
        while (j <= r) {
            if (j < r && ra[j] < ra[j+1]) j++; // Comparar con el mejor de los hijos.
            if (a >= ra[j]) break;            // Encontró el nivel de 'a'. Termina el sift-down.
            ra[jold] = ra[j];                 // De lo contrario, desciende 'a' y continúa.
            jold = j;
            j = 2*j + 1;
        }
        
        ra[jold] = a; // Coloca 'a' en su posición.
    }
}

// Función de heapsort
template<class T>
void hpsort(std::vector<T> &ra) {
    // Ordena un arreglo ra[0..n-1] en orden numérico ascendente usando el algoritmo Heapsort.
    // El arreglo ra es reemplazado en la salida por su reordenación.
    
    int i, n = ra.size();
    
    // Fase de creación del montículo
    for (i = n/2 - 1; i >= 0; i--) {
        // El índice i, que aquí determina el rango "izquierdo" del sift-down, es decir,
        // el elemento a bajar, decrece de n/2-1 a 0 durante la fase de "contratación" (creación del heap).
        hpsort_util::sift_down(ra, i, n - 1);
    }
    
    // Fase de selección del heap
    for (i = n - 1; i > 0; i--) {
        // Aquí el rango "derecho" del sift-down se decrece de n-2 a 0 durante la fase de
        // "retiro y promoción" (selección del heap).
        std::swap(ra[0], ra[i]);    // Libera un espacio al final del arreglo y retira
        hpsort_util::sift_down(ra, 0, i - 1); // la raíz del heap en ese espacio.
    }
}

// Función para mostrar el arreglo
template <class T>
void mostrarArreglo(const std::vector<T> &arr) {
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Función principal con ejemplo de uso
int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Inicializa la semilla para números aleatorios
    
    int N = 300; // Tamaño del arreglo
    std::vector<int> arr(N);

    // Llenar el arreglo con números aleatorios entre 1 y 1000
    for (int i = 0; i < N; i++) {
        arr[i] = std::rand() % 1000 + 1;
    }

    // Mostrar el arreglo antes de ordenar
    std::cout << "Arreglo original: " << std::endl;
    mostrarArreglo(arr);

    // Ordenar el arreglo usando heapsort
    hpsort(arr);

    // Mostrar el arreglo después de ordenar
    std::cout << "Arreglo ordenado: " << std::endl;
    mostrarArreglo(arr);

    return 0;
}