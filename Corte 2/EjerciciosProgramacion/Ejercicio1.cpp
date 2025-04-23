#include <iostream>
#include <ctime>  // Para srand(time(0))
#include <string>

using namespace std;


/*código para la matriz*/

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


/*código para el arreglo*/

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
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

//clase Libro
class Libro {
    private:
        int titulo;
        int categoria;
        int puntuacion;
    public:
        Libro() {
            titulo = -1; 
            categoria = -1;
            puntuacion = -1;
        }
        Libro(int t, int c, int p) {
            titulo = t;
            categoria = c;
            puntuacion = p;
        }
        
        //Getters y Setters
        int getTitulo() const { 
            return titulo; 
        }
        void setTitulo(int t) { 
            titulo = t; 
        }
        int getCategoria() const { 
            return categoria; 
        }
        void setCategoria(int c) { 
            categoria = c; 
        }
    
        int getPuntuacion() const { 
            return puntuacion; 
        }
        void setPuntuacion(int p) { 
            puntuacion = p; 
        }
    
        Libro& operator=(const Libro& f) {
            titulo = f.titulo;
            categoria = f.categoria;
            puntuacion = f.puntuacion;
            return *this;
        }
    
        string to_string() const {
            return std::to_string(titulo) + ", " + std::to_string(categoria) + ", " + std::to_string(puntuacion);
        }
    
        friend std::ostream& operator<<(std::ostream& os, const Libro& s) {
            return os << s.to_string();
        }

        bool operator>(const Libro& f) const {
            return puntuacion > f.puntuacion;
        }

        bool operator<(const Libro& f) const {
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
    
    /*void swap(int px, int py){
        if(px == py){
            return;
        }
        Nodo<T>* nodoX = get(px);
        Nodo<T>* nodoY = get(py);
        T temp = nodoX -> getValor();
        nodoX -> setValor(nodoY -> getValor());
        nodoY -> setValor(temp);
    }*/
    
    void bubbleSort(){
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        T aux;
        while (actual != nullptr){
            siguiente = actual -> getSiguiente();
            while (siguiente != nullptr){
                if(actual -> getValor().getPuntuacion() < siguiente -> getValor().getPuntuacion()){
                    aux = actual -> getValor();
                    actual -> setValor(siguiente -> getValor());
                    siguiente -> setValor(aux);
                }
                siguiente = siguiente -> getSiguiente();
            }
            actual = actual -> getSiguiente();
        }
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
};


// Clase Biblioteca
class Biblioteca {
private:
    ListaEnlazada<Libro> puntuacion;
    int* arreglo;
    int nt;
    int nc;
    int np;
    int ns;

public:
    Biblioteca(int t = 20, int c = 20, int p = 20, int s = 200): nt(t), nc(c), np(p), ns(s) {
        arreglo = crear_arreglo(np);
    }

    ~Biblioteca() {
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista() Juan Felipe Poveda 
    void init_lista() {
       Libro* z;
       int t , c, p;
       for (int i = 0; i < ns; i++){
        t = rand() % nt;
        c = rand() % nc;
        p = rand() % np;
        z = new Libro(t, c, p);
        puntuacion.insertar(*z);
       }
       cout << "Se han generado " << puntuacion.get_size() << " categorias de libro." << endl;
       puntuacion.mostrar();
    }

    void ordenar() {
        puntuacion.bubbleSort();
    }

    void print() {
        puntuacion.mostrar();
    }
};

int main() {
    ListaEnlazada<string> ListaEnlazada;

    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual Juan Felipe Poveda 
    int t = 10;
    int c = 10;
    int p = 10;
    int s = 20;
    Biblioteca bib = Biblioteca(t, c, p, s);
    bib.init_lista();
    cout<<endl;

    bib.ordenar();
    cout << "Lista ordenada por puntuacion mas alta a la mas baja: " << endl;
    bib.print();

    return 0;
}