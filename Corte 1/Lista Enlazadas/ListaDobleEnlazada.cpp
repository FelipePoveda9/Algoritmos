#include <iostream> 
using namespace std;

// ======================== CLASE NODO =========================
// Definir clase Nodo con plantilla para lista doblemente enlazada
template <typename T>
class Nodo {
private:
    T valor;               // Almacena el valor del nodo
    Nodo<T>* siguiente;    // Puntero al siguiente nodo en la lista
    Nodo<T>* anterior;     // Puntero al nodo anterior en la lista

public:
    // Constructor: inicializa el valor y los punteros a nullptr
    Nodo(T _valor) : valor(_valor), siguiente(nullptr), anterior(nullptr) {}

    // Métodos setter para actualizar los punteros siguiente y anterior
    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setAnterior(Nodo<T>* _anterior) { this->anterior = _anterior; }

    // Métodos getter para obtener los valores del nodo
    T getValor() { return valor; }
    Nodo<T>* getSiguiente() { return siguiente; }
    Nodo<T>* getAnterior() { return anterior; }
};

// ======================== CLASE LISTA DOBLE ENLAZADA =========================
template <typename T>
class ListaDobleEnlazada {
private:
    Nodo<T>* cabeza;   // Apuntador al primer nodo de la lista
    Nodo<T>* cola;     // Apuntador al último nodo de la lista (para optimización)

public:
    // Constructor: inicializa la lista como vacía
    ListaDobleEnlazada() : cabeza(nullptr), cola(nullptr) {}

    // Destructor: libera la memoria de todos los nodos al eliminar la lista
    ~ListaDobleEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while (actual != nullptr) {
            siguiente = actual->getSiguiente(); // Guarda referencia al siguiente nodo
            delete actual; // Elimina el nodo actual
            actual = siguiente; // Avanza al siguiente nodo
        }
    }

    // ======================== MÉTODO INSERTAR AL FINAL =========================
    // Inserta un nuevo nodo al final de la lista
    void insertar(T _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if (cabeza == nullptr) {
            // Si la lista está vacía, el nuevo nodo es tanto la cabeza como la cola
            cabeza = cola = nuevoNodo;
        } else {
            // Se enlaza el nuevo nodo con la cola actual y se actualiza la cola
            cola->setSiguiente(nuevoNodo);
            nuevoNodo->setAnterior(cola);
            cola = nuevoNodo;
        }
    }

    // ======================== MÉTODO INSERTAR EN POSICIÓN =========================
    // Inserta un nuevo nodo en una posición específica de la lista
    void insertarEnPosicion(int posicion, T _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        
        if (posicion == 0) {
            // Inserta en la primera posición (cabeza)
            nuevoNodo->setSiguiente(cabeza);
            if (cabeza != nullptr) cabeza->setAnterior(nuevoNodo);
            cabeza = nuevoNodo;
            if (cola == nullptr) cola = nuevoNodo;  // Si la lista estaba vacía
            return;
        }

        // Recorre la lista hasta la posición deseada
        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        // Si la posición no es válida, se descarta el nodo nuevo
        if (actual == nullptr) {
            cout << "Posición inválida" << endl;
            delete nuevoNodo;
            return;
        }

        // Inserta el nodo en la posición indicada
        nuevoNodo->setSiguiente(actual->getSiguiente());
        if (actual->getSiguiente() != nullptr) {
            actual->getSiguiente()->setAnterior(nuevoNodo);
        }
        actual->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(actual);
    }

    // ======================== MÉTODO ELIMINAR NODO POR VALOR =========================
    // Elimina el primer nodo que contenga el valor especificado
    bool eliminar(T _valor) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                // Si el nodo a eliminar no es el primero
                if (actual->getAnterior() != nullptr) {
                    actual->getAnterior()->setSiguiente(actual->getSiguiente());
                } else {
                    // Si es el primer nodo, se actualiza la cabeza
                    cabeza = actual->getSiguiente();
                }
                // Si el nodo a eliminar no es el último
                if (actual->getSiguiente() != nullptr) {
                    actual->getSiguiente()->setAnterior(actual->getAnterior());
                } else {
                    // Si es el último nodo, se actualiza la cola
                    cola = actual->getAnterior();
                }
                delete actual;
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    // ======================== MÉTODO BUSCAR POR VALOR =========================
    // Busca un nodo con un valor específico y devuelve su puntero
    Nodo<T>* buscarPorValor(T _valor) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    // ======================== MÉTODO MOSTRAR LISTA =========================
    // Imprime la lista en orden desde la cabeza hasta la cola
    void mostrar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->getValor() << " <--> ";
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
    }

    // ======================== MÉTODO MOSTRAR LISTA EN REVERSA =========================
    // Imprime la lista en orden inverso (desde la cola hasta la cabeza)
    void mostrarReversa() {
        Nodo<T>* actual = cola;
        while (actual != nullptr) {
            cout << actual->getValor() << " <--> ";
            actual = actual->getAnterior();
        }
        cout << "nullptr" << endl;
    }
};

// ======================== FUNCIÓN PRINCIPAL =========================
int main() {
    ListaDobleEnlazada<int> lista;

    // Insertar elementos en la lista
    lista.insertar(1);
    lista.insertar(2);
    lista.insertar(3);
    lista.insertar(4);
    lista.insertar(5);

    cout << "Lista original (de cabeza a cola): " << endl;
    lista.mostrar();

    // Eliminar un elemento por valor
    lista.eliminar(3);
    cout << "Lista tras eliminar 3 (de cabeza a cola): " << endl;
    lista.mostrar();

    // Insertar en posición específica
    lista.insertarEnPosicion(2, 6);
    cout << "Lista tras inserciones (de cabeza a cola): " << endl;
    lista.mostrar();
    
    lista.insertarEnPosicion(0, 3);
    cout << "Lista tras inserciones (de cabeza a cola): " << endl;
    lista.mostrar();

    // Mostrar la lista en orden inverso
    cout << "Lista en orden inverso (de cola a cabeza): " << endl;
    lista.mostrarReversa();

    // Buscar un valor en la lista
    Nodo<int>* encontrado = lista.buscarPorValor(4);
    if (encontrado != nullptr) {
        cout << "Valor encontrado: " << encontrado->getValor() << endl;
    } else {
        cout << "Valor NO encontrado!" << endl;
    }

    return 0;
}
