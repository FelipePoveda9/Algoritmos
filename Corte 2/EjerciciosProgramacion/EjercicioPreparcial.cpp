#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int** crear_matriz(int f, int c){
    int** m = new int*[f];
    for (int i = 0; i < f; i++){
        m[i] = new int [c];
        for (int j = 0; j < c; j++){
            m[i][j];
        }
    }
    return m;
}

void destruit_matriz(int** m, int f){
    for (int i = 0; i < f; i++){
        delete[] m[i];
    }

}

void print_matriz(int** m, int f, int c){
    for (int i = 0; i < f; i++){
        for (int j = 0; j < c; j++){
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int* crear_arreglo(int n){
    int* arr = new int [n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++){
        arr[i] = 0;  // Inicializar con 0 (o cualquier otro valor que desees)
    }
    return arr;
}

// Función para destruir el arreglo
void destruir_arreglo(int* arr) {
    delete[] arr;  // Liberar la memoria del arreglo dinámico
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// Función para llenar el arreglo con valores
void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
    }
}

// Clase HillHotels Evaluadores, puntuacion

//clase HillHotels
class HillHotels {
    private:
        int grupo;
        int evaluador;
        float puntuacion;
    public:
        HillHotels() {
            grupo = -1; 
            puntuacion = -1;
            evaluador = -1;
        }
        HillHotels(int grupo, float puntuacion, int evaluador) {
            this -> grupo = grupo;
            this -> puntuacion = puntuacion;
            this -> evaluador = evaluador;
        }
        
        //Getters y Setters
        int getProducto() const { 
            return grupo; 
        }
    
        float getPuntuacion() const { 
            return puntuacion; 
        }

        int getevaluador() const { 
            return evaluador; 
        }

    
        HillHotels& operator=(const HillHotels& f) {
            grupo = f.grupo;
            puntuacion = f.puntuacion;
            evaluador = f.evaluador;
            return *this;
        }
    
        string to_string() const {
            return "Evaluador: " + std:: to_string(evaluador) + ", Grupo: " + std::to_string(grupo) + ", Puntaje: " + std::to_string(puntuacion);
        }
    
        friend std::ostream& operator<<(std::ostream& os, const HillHotels& s) {
            return os << s.to_string();
        }

        bool operator>(const HillHotels& f) const {
            return puntuacion > f.puntuacion;
        }

        bool operator<(const HillHotels& f) const {
            return puntuacion < f.puntuacion;
        }
    
    };


// Clase nodo con plantilla Juan Felipe Poveda 
template <typename T>
class Nodo{
    private:
        T valor;
        Nodo<T>* siguiente;
    public:
        // constructor 
        Nodo(T _valor) : valor(_valor), siguiente(nullptr){}

        // Metodo setter para ajustar siguiente
        void setSiguiente(Nodo<T>* _siguiente){
            this -> siguiente = _siguiente;
        }

        // Metodo setter para ajustar valor
        void setValor(T _valor){
            this -> valor = _valor;
        }

        // Metodo getter para valor
        T getValor(){
            return valor;
        }

        // Metodo getter paar siguiente
        Nodo<T>* getSiguiente(){
            return siguiente;
        }
};

//poner aquí su código de listas con los comentarios realizados en las clases
//Juan Felipe Poveda 
template <typename T>
class ListaEnlazada{
private: 
    Nodo<T>* cabeza; // Apuntador al primer nodo de la lista
    int size;
public:
    // Constructor inicializa la lista como vacía
    ListaEnlazada(): cabeza(nullptr), size(0) {};
    
    // Destructor que libera la memoria de la lista
    ~ListaEnlazada(){
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr){
            siguiente = actual -> getSiguiente(); // Guardamos la dirección del siguiente nodo
            delete actual; // Liberamos el nodo actual
            actual = siguiente; // Avanzamos al siguiente nodo
        }
    }
    
    // Método para insertar nodos al final de la lista Juan Felipe Poveda 
    void insertar(T _valor){
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr){ // Si la lista está vacía, el nuevo nodo es la cabeza
            cabeza = nuevoNodo;
        }else{
            Nodo<T>* actual = cabeza;
            while(actual -> getSiguiente()){ // Recorremos hasta el último nodo
                actual = actual -> getSiguiente();
            }
            actual -> setSiguiente(nuevoNodo); // Se enlaza el nuevo nodo al final
        }
        size ++;
    }

    // Método para insertar un nodo en una posición específica Juan Felipe Poveda 
    void insertarEnPosicion(int posicion, const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);

        if (posicion == 0) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }

        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        if (actual == nullptr) {
            std::cout << "Posición inválida" << std::endl;
            delete nuevoNodo;
            return;
        }

        nuevoNodo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevoNodo);
    }
    
    Nodo<T>* buscarPorValor(const T& _valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    int get_size() const { return size; }

    // Método para mostrar la lista Juan Felipe Poveda 
    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl; // Indicamos el final de lista
    }

    Nodo<T>* get(int i) const {
        if (i >= 0 && i < size) {
            int j = 0;
            Nodo<T>* actual = cabeza;
            while (j < i) {
                actual = actual->getSiguiente();
                j++;
            }
            return actual;
        }
        return nullptr;
    }
    
    void swap(int px, int py) {
        if (px == py) return; // Si son la misma posición, no hay nada que intercambiar
    
        Nodo<T>* prevX = nullptr, *nodoX = cabeza;
        Nodo<T>* prevY = nullptr, *nodoY = cabeza;
    
        // Buscar nodoX y su nodo anterior
        for (int i = 0; nodoX != nullptr && i < px; i++) {
            prevX = nodoX;
            nodoX = nodoX->getSiguiente();
        }
    
        // Buscar nodoY y su nodo anterior
        for (int i = 0; nodoY != nullptr && i < py; i++) {
            prevY = nodoY;
            nodoY = nodoY->getSiguiente();
        }
    
        // Si no encontramos uno de los nodos, no intercambiar
        if (nodoX == nullptr || nodoY == nullptr) return;
    
        // Si nodoX no es la cabeza, conectamos su anterior a nodoY
        if (prevX != nullptr)
            prevX->setSiguiente(nodoY);
        else // Si nodoX era la cabeza, ahora nodoY será la cabeza
            cabeza = nodoY;
    
        // Si nodoY no es la cabeza, conectamos su anterior a nodoX
        if (prevY != nullptr)
            prevY->setSiguiente(nodoX);
        else // Si nodoY era la cabeza, ahora nodoX será la cabeza
            cabeza = nodoX;
    
        // Intercambiamos los punteros siguientes de nodoX y nodoY
        Nodo<T>* temp = nodoX->getSiguiente();
        nodoX->setSiguiente(nodoY->getSiguiente());
        nodoY->setSiguiente(temp);
    }

    void bubbleSort(){
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                Nodo<T>* nodoA = get(j);
                Nodo<T>* nodoB = get(j + 1);
                if (nodoA->getValor().getPuntuacion() > nodoB->getValor().getPuntuacion()) {
                    swap(j, j + 1);
                }
            }
        }
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            Nodo<T>* minNode = get(i);
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                Nodo<T>* actual = get(j);
                if (actual->getValor().getPuntuacion() < minNode->getValor().getPuntuacion()) {
                    minNode = actual;
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(i, minIndex);
            }
        }
    }

    void shellSort() {
        int sizered = size / 2;

        while (sizered > 0) {
            for (int i = sizered; i < size; i++) {
                int j = i - sizered;
                while (j >= 0) {
                    int k = j + sizered;
                    if (get(j)->getValor().getPuntuacion() <= get(k)->getValor().getPuntuacion()) {
                        j = -1;
                    } else {
                        swap(j, k);
                    }
                    j = j - sizered;
                }
            }
            sizered = sizered / 2;
        }
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            Nodo<T>* actual = get(i);
            int j = i - 1;
            while (j >= 0 && get(j)->getValor().getPuntuacion() > actual->getValor().getPuntuacion()) {
                swap(j, j + 1);
                j--;
            }
            get(j + 1)->setValor(actual->getValor());
        }
    }

    int partition(int low, int high, bool ascendente) {
        Nodo<T>* pivot = get(high); // Elegimos el último elemento como pivote
        int cambio = low - 1; // Índice del elemento más pequeño

        for (int comparar = low; comparar < high; comparar++) {
            if (get(comparar)->getValor().getPuntuacion() < pivot->getValor().getPuntuacion()) {
                cambio++;
                swap(comparar, cambio); // Intercambiamos elementos
            }
        }
        swap(cambio + 1, high); // Colocamos el pivote en su posición correcta
        return cambio + 1;
    }

    void quickSort(int low, int high, bool ascendente) {
        if (low < high) {
            int pivotIndex = partition(low, high, ascendente);
            quickSort(low, pivotIndex - 1, ascendente);
            quickSort(pivotIndex + 1, high, ascendente);
        }
    }
};


// Clase Grupo
class Grupo {
private:
    ListaEnlazada<HillHotels> puntuacion;
    int* arreglo;
    int numGrupo;
    int numPuntuaciones;
    int numEvaluador;
    int numT;

public:
    Grupo(int grupo = 6, float puntuacion = 20, int evaluador = 4, int numTotalLista = 0): numGrupo(grupo), numPuntuaciones(puntuacion), numEvaluador(evaluador), numT(numTotalLista) {
        arreglo = crear_arreglo(numPuntuaciones);
    }

    ~Grupo() {
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista() Juan Felipe Poveda 
    void init_lista() {
       HillHotels* z;
       int grupo;
       float puntuaciones;
       int evaluador;
       int numT;

       for (int i = 0; i < 4; i++){
        cout << "Ingrese el número de Evaluadores: " << endl;
        cin >> numT;
        for (int i = 0; i < numT; i++){
            for (int i = 0; i <= 3; i++){
                evaluador = i;
            }
            grupo = rand() % numGrupo;
            puntuaciones = (rand() % numPuntuaciones) / 10.0;
            z = new HillHotels(grupo, puntuaciones, evaluador);
            puntuacion.insertar(*z);
           }
           
           cout << "Se han generado " << puntuacion.get_size() << " productos en el inventario." << endl;
       }
       puntuacion.mostrar();
    }

    void ordenar() {
        puntuacion.insertionSort();
    }

    void print() {
        puntuacion.mostrar();
    }
};

int main() {
    ListaEnlazada<string> ListaEnlazada;

    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual Juan Felipe Poveda 
    int grupo = 6;
    float puntuaciones = 100.0;
    int evaluador = 4;

    Grupo grup = Grupo(grupo, puntuaciones, evaluador);
    grup.init_lista();
    cout<<endl;

    grup.ordenar();
    cout << "Lista ordenada por puntuacion mayor a menor: " << endl;
    grup.print();

    return 0;
}