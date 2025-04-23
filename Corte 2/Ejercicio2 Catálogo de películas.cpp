//encontrados.
//puntuacion.
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int** crear_matriz(int f, int c){
    int** m = new int*[f];
    for (int i = 0; i < f; i++){
        m[i] = new int [c];
        for (int j = 0; j < c; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

void destruit_matriz(int** m, int f){
    for (int i = 0; i < f; i++){
        delete[] m[i];
    }
    delete[] m;  // Liberar la memoria de la matriz
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

// Clase Cinema Pelicula , Puntuacion

//clase Cinema
class Cinema {
    private:
        int pelicula;
        float puntuacion;
    public:
        Cinema() {
            pelicula = -1; 
            puntuacion = -1.0; // Es float
        }
        Cinema(int pelicula, float puntuacion) {
            this -> pelicula = pelicula;
            this -> puntuacion = puntuacion;
        }
        
        //Getters y Setters
        int getPelicula() const { 
            return pelicula; 
        }

        float getPuntuacion() const { 
            return puntuacion; 
        }
    
    
        Cinema& operator=(const Cinema& f) {
            pelicula = f.pelicula;
            puntuacion = f.puntuacion;
            return *this;
        }
    
        string to_string() const {
            return "Pelicula: " + std::to_string(pelicula) + ", Puntuacion: " + std::to_string(puntuacion);
        }
    
        friend std::ostream& operator<<(std::ostream& os, const Cinema& s) {
            return os << s.to_string();
        }

        bool operator>(const Cinema& f) const {
            return puntuacion > f.puntuacion;
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

    // Método para dividir la lista en dos mitades Juan Felipe Poveda
    // y mezclar las dos mitades ordenadas
    void split(Nodo<T>*& cabeza, Nodo<T>*& medio) {
        if (cabeza == nullptr || cabeza->getSiguiente() == nullptr) {
            medio = nullptr; // Si la lista es vacía o de un solo nodo, no se divide
            return;
        }

        Nodo<T>* slow = cabeza; // avanza de a 1 nodo
        Nodo<T>* fast = cabeza->getSiguiente(); // avanza de a 2 nodos

        while (fast != nullptr && fast->getSiguiente() != nullptr) {
            slow = slow->getSiguiente(); // avanza de a 1 paso
            fast = fast->getSiguiente()->getSiguiente(); // avanza de a 2 pasos
        }

        medio = slow->getSiguiente(); // inicio de la segunda mitad
        slow->setSiguiente(nullptr); // Parte la lista en dos partes
    }
    // Método para mezclar dos listas ordenadas Juan Felipe Poveda
    // en una sola lista ordenada
    void merge(Nodo<T>* cabeza, Nodo<T>* medio) {
        if (cabeza == nullptr) {
            cabeza = medio;
            return;
        }

        if (medio == nullptr) {
            return;
        }

        Nodo<T>* temp = cabeza;
        while (temp->getSiguiente() != nullptr) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(medio);
    }
    
    // Método de ordenamiento por mezcla (Merge Sort) Juan Felipe Poveda
    void mergeSort(Nodo<T>* cabeza) {
        if (cabeza == nullptr || cabeza->getSiguiente() == nullptr) {
            return;
        }

        Nodo<T>* medio = nullptr;
        split(cabeza, medio); // Divide la lista en dos partes
        mergeSort(cabeza); // Me ordena la parte izquierda
        mergeSort(medio); // Me ordena la parte derecha
        merge(cabeza, medio); // Mezcla las dos partes ordenadas
    }

    void mergeSort() {
        mergeSort(cabeza);
    }
    
    void busquedaBinariaRango(float peliculaMinimo, float peliculaMaximo) {
        if (peliculaMinimo > peliculaMaximo || size == 0) {
            cout << "Rango invalido." << endl;
            return;
        }
    
        float inicio = 0, fin = size - 1;
        ListaEnlazada<T> encontrados;    
        while (inicio <= fin) {
            float medio  = inicio + (fin - inicio) / 2;
            Nodo<T>* nodoMedio = get(medio);
            float peliculaMedio  = nodoMedio->getValor().getPuntuacion();
    
            if (peliculaMedio  >= peliculaMinimo && peliculaMedio  <= peliculaMaximo) {
                float left = medio ;
                while (left >= 0 && get(left)->getValor().getPuntuacion() >= peliculaMinimo) {
                    encontrados.insertar(get(left)->getValor());
                    left--;
                }
    
                float right = medio  + 1;
                while (right < size && get(right)->getValor().getPuntuacion() <= peliculaMaximo) {
                    encontrados.insertar(get(right)->getValor());
                    right++;
                }
                break;
            }
    
            if (peliculaMedio  < peliculaMinimo) {
                inicio = medio  + 1;
            } else {
                fin = medio  - 1;
            }
        }
        cout << "_________________________________________" << endl;
        cout << endl;
        cout << "Peliculas encontradas en el rango de [" << peliculaMinimo << ", " << peliculaMaximo << "]:" << endl;
        //encontrados.bubbleSort();
        //encontrados.mergeSort();
        //encontrados.selectionSort();
        //encontrados.shellSort();
        //encontrados.insertionSort();
        encontrados.quickSort(0, encontrados.get_size() - 1, true);
        cout << "_________________________________________" << endl;
        encontrados.mostrar();
    }
};


// Clase PuntuacionPelicula
class PuntuacionPelicula {
private:
    ListaEnlazada<Cinema> puntuaciones;
    int* arreglo;
    int numPelicula;
    int numPuntuacion;
    int numCartelera; // Tamaño de la lista de peliculas

public:
    PuntuacionPelicula(int pelicula = 20, float puntuacion = 20, int Num_cartelera = 20): numPelicula(pelicula), numPuntuacion(puntuacion), numCartelera(Num_cartelera) {
        arreglo = crear_arreglo(numPuntuacion);
    }

    ~PuntuacionPelicula() {
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista() Juan Felipe Poveda 
    void init_lista() {
       Cinema* z;
       int pelicula;
       float puntuacion;

       for (int i = 0; i < numCartelera; i++){
        pelicula = rand() % numPelicula;
        puntuacion = (rand() % numPuntuacion) / 10.0;
        z = new Cinema(pelicula, puntuacion);
        puntuaciones.insertar(*z);
       }
       cout << "_________________________________________" << endl;
       cout << "Se han generado " << puntuaciones.get_size() << " reseñas de las peliculas." << endl;
       puntuaciones.mostrar();
       cout << "_________________________________________" << endl;
    }

    void ordenar() {
        //puntuaciones.mergeSort();
        //puntuaciones.bubbleSort();
        //puntuaciones.selectionSort();
        //puntuaciones.shellSort();
        //puntuaciones.insertionSort();
        puntuaciones.quickSort(0, puntuaciones.get_size() - 1, true);
    }

    void busquedaBinaria(int peliculaMinimo, int peliculaMaximo) {
        puntuaciones.busquedaBinariaRango(peliculaMinimo, peliculaMaximo);
    }

    // Mostrar la lista de productos
    void print() {
        puntuaciones.mostrar();
    }
};

int main() {
    ListaEnlazada<string> ListaEnlazada;

    srand(time(0));  // Inicialización del generador de números aleatorios Juan Felipe Poveda 
    int pelicula = 5;
    float puntuacion = 109.0;
    int opc = 1;
    int peliculaMinimo, peliculaMaximo;

    PuntuacionPelicula peliculaPun = PuntuacionPelicula(pelicula, puntuacion);
    peliculaPun.init_lista();
    cout<<endl;

    peliculaPun.ordenar();
    cout << "Lista ordenada por puntuaciones más baja a más alta: " << endl;
    peliculaPun.print();
    cout << endl;

    while (opc == 1) {
        cout << "\tBusqueda de productos" << endl;
        cout << "_________________________________________" << endl;
        cout << endl;

        cout << "Digite el minimo de puntuacion y maximo, en ese orden: " << endl;
        cin >> peliculaMinimo;
        cin >> peliculaMaximo;
        cout << "_________________________________________" << endl;
        cout << endl;
        
        peliculaPun.busquedaBinaria(peliculaMinimo, peliculaMaximo);
        cout << endl;
        cout << "_________________________________________" << endl;
        cout << endl;

        cout << "¿Realizar otra búsqueda? (1/Sí , 0/No): ";
        cin >> opc;
        cout << endl;
    }

    return 0;
}