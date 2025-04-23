#include <iostream>
#include <ctime>  
#include <string>

using namespace std;

// Función para crear una matriz dinámica
int* crear_mat(int f) {
    int* m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[f];
            m[i] = 0;
    }
    return m;
}

// Función para destruir el arreglo
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir el arreglo
void print_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        cout << "{";
            cout << m[i] << "__";
        cout << "}";
        cout << endl;
    }
}


//clase Prestamo
class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo() {
        usuario=-1; 
        libro=-1;
        genero=-1;
    }
    Prestamo(int u, int l, int g){
        usuario=u;
        libro=l;
        genero=g;
    }
    
    //Setters y Getters
    int getUsuario() const { 
        return usuario; 
    }
    void setUsuario(int u) { 
        usuario = u; 
    }
    int getLibro() const { 
        return libro; 
    }
    void setLibro(int l) { 
        libro = l; 
    }

    int getGenero() const { 
        return genero; 
    }
    void setGenero(int g) { 
        genero = g; 
    }

    Prestamo& operator=(const Prestamo& f) {
        usuario = f.usuario;
        libro = f.libro;
        genero = f.genero;
        return *this;
    }

    string to_string() const {
        return std::to_string(usuario) + ", " + std::to_string(libro) + ", " + std::to_string(genero);
    }

    friend std::ostream& operator<<(std::ostream& os, const Prestamo& p) {
        return os << p.to_string();
    }
};

// Clase nodo con plantilla
template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}

    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setValor(T _valor) { this->valor = _valor; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// Clase lista enlazada con plantilla
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr) {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente()) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        size++;
    }

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

    bool eliminar(const T& _valor) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while (actual) {
            if (actual->getValor() == _valor) {
                if (anterior) {
                    anterior->setSiguiente(actual->getSiguiente());
                } else {
                    cabeza = actual->getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
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

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
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
};


// Clase Biblioteca
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int** matriz;
    int nu; // Número de usuarios
    int nl; // Número de libros
    int ng; // Número de géneros
    int np; // Número de préstamos
    int* librosPrestados;

public:
    Biblioteca(int u = 100, int l = 100, int g = 100, int p = 1000) : nu(u), nl(l), ng(g), np(p) {
        matriz = crear_mat(nl, ng);
    }

    ~Biblioteca() {
        destruir_mat(matriz, nl);
    }

    void init_lista() {
        Prestamo* t;
        int u, l, g;
        for (int i = 0; i < np; i++) {
            u = rand() % nu;
            l = rand() % nl;
            g = rand() % ng;
            t = new Prestamo(u, l, g);
            prestamos.insertar(*t);
        }
        cout << "Se han generado " << prestamos.get_size() << " préstamos." << endl;
        prestamos.mostrar();
    }
     void print(){
        prestamos.mostrar();
    }

    void arreglo_Prestados(){
        librosPrestados = new int[nl]();
        cout << "Arreglo de libros prestados: " << endl;
        for(int i = 0; i < nl; i++){
            cout << librosPrestados[i] << " , ";
        }
        cout << endl;
    }
    void llenar_arreglo() {
        Nodo<Prestamo>* ptr = prestamos.get(0);
        for (int i = 0; i < np; i++) {
            librosPrestados[ptr->getValor().getLibro()]++;
            ptr = ptr->getSiguiente();
        }
        cout << "Prestamos por libros: " << endl;
        print_mat(librosPrestados, nl);
    }

};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int u = 10;
    int l = 10;
    int g = 10;
    int p = 100;
    Biblioteca bib=Biblioteca(u, l, g, p);
    bib.init_lista();
    cout<<endl;
    bib.arreglo_Prestados();

    return 0;
}

