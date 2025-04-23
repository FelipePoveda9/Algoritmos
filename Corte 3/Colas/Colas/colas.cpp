#include <iostream>
using namespace std;

// Definición del nodo
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Clase Cola con lista enlazada
class Cola {
private:
    Nodo* frente;
    Nodo* final;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    // Enqueue: agrega un elemento a la cola
    void Enqueue(int valor) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        cout << "Elemento " << valor << " agregado." << endl;
    }

    void EnqueueMultiple() {
        int n;
        cout << "¿Cuántos personas hay en espera?: \n";
        cin >> n;
        for (int i = 0; i < n; i++) {
            int valor;
            cout << "Persona (" << i + 1 << ")" << ": \n";
            cout << "Tiempo de espera persona (" << i + 1 <<"): \n" ;
            cin >> valor;
            Enqueue(valor);
            cout << endl;

        }
        int a;
        for (int i = 0; i < n; i++) {
            a = n - i;
            cout << "Persona (" << i + 1 << ") atendida, tiempo de espera nuevo (" << a << ")\n";
        }
    }

    
     // Dequeue: elimina el elemento del frente
     void Dequeue() {
        if (estaVacia()) {
            cout << "Cola vacía. No se puede hacer Dequeue." << endl;
            return;
        }
        Nodo* temp = frente;
        cout << "Elemento " << temp->dato << " eliminado con Dequeue." << endl;
        frente = frente->siguiente;
        delete temp;

        if (frente == nullptr) {
            final = nullptr;
        }
    }



    // Obtener el valor del frente
    int obtenerFrente() {
        if (!estaVacia()) {
            return frente->dato;
        }
        cout << "Cola vacía. No hay frente." << endl;
        return -1;
    }

    // Mostrar todos los elementos
    void mostrarCola() {
        if (estaVacia()) {
            cout << "Cola vacía." << endl;
            return;
        }

        Nodo* actual = frente;
        cout << "Contenido de la cola:\n";
        while (actual != nullptr) {
            cout << actual->dato << endl <<"";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    ~Cola() {
        while (!estaVacia()) {
            Dequeue();
        }
    }
};

// Función main para probar
int main() {
    Cola miCola;
    miCola.EnqueueMultiple();
    cout << endl;


    return 0;
}