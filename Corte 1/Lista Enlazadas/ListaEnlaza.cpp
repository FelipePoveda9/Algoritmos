#include <iostream>
using namespace std;

// Clase Nodo que representa un elemento de la lista enlazada
template<typename T>
class Nodo{
private: // Variables privadas de la clase
    T valor; // Variable para almacenar el valor del nodo
    Nodo <T>* siguiente; // Apuntador al nodo siguiente de la lista

public: // Constructor y métodos
    Nodo(T _valor) : valor(_valor), siguiente(nullptr){} // Constructor inicializa valor y puntero a siguiente como nulo

    void setSiguiente(Nodo<T>* _siguiente){ // Método para ajustar el apuntador al siguiente nodo
        this -> siguiente = _siguiente;
    }

    void setValor(T _valor){ // Método para establecer un nuevo valor en el nodo
        this -> valor = _valor;
    }

    T getValor(){ // Método que retorna el valor almacenado en el nodo
        return valor;
    }
    Nodo<T>* getSiguiente(){ // Método que retorna el apuntador al siguiente nodo
        return siguiente;
    }
};

// Clase Lista que representa una lista enlazada
template <typename T>
class Lista{
private: 
    Nodo<T>* cabeza; // Apuntador al primer nodo de la lista
public:
    // Constructor inicializa la lista como vacía
    Lista(): cabeza(nullptr){};
    
    // Destructor que libera la memoria de la lista
    ~Lista(){
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr){
            siguiente = actual -> getSiguiente(); // Guardamos la dirección del siguiente nodo
            delete actual; // Liberamos el nodo actual
            actual = siguiente; // Avanzamos al siguiente nodo
        }
    }
    
    // Método para insertar nodos al final de la lista
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
    }

    // Método para insertar un nodo en una posición específica
    void insertarPos(int posicion, T _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if (posicion == 0) { // Insertar en la primera posición
            nuevoNodo -> setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }
    
        Nodo<T>* actual = cabeza;
        int contador = 0;
    
        while (actual != nullptr && contador < (posicion - 1)) { // Recorremos la lista hasta la posición anterior
            actual = actual -> getSiguiente();
            contador++;
        }
    
        if (actual == nullptr) { // Si la posición no existe
            cout << "Posicion fuera de rango" << endl;
            delete nuevoNodo;
            return;
        } 
        nuevoNodo -> setSiguiente(actual -> getSiguiente()); // Insertamos el nodo en la posición
        actual -> setSiguiente(nuevoNodo);
    }

    // Método para buscar un valor en la lista y devolver su posición
    int buscar(T _valor) {
        Nodo<T>* actual = cabeza;
        int recorrer = 0;
        while (actual != nullptr) {
            if (actual -> getValor() == _valor) {
                return recorrer; // Si se encuentra, retornamos la posición
            }
            else{
                recorrer++;
                actual = actual -> getSiguiente();
            }
        }
        return -1; // Retornamos -1 si no se encuentra
    }

    // Método para eliminar un nodo por su valor
    bool eliminar(T _valor){
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while(actual){
            if(actual -> getValor() == _valor){
                if(anterior){
                    anterior -> setSiguiente(actual -> getSiguiente());
                }
                else{
                    cabeza = actual -> getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual -> getSiguiente();
        }
        return false;
    }

    // Método para mostrar la lista
    void mostrar(){
        Nodo<T>* actual = cabeza;
        while (actual != nullptr){
            cout << actual -> getValor() << "-->"; // Imprimimos el valor del nodo
            actual = actual -> getSiguiente(); // Avanzamos al siguiente nodo
        }
        cout << " NULL" << endl; // Indicamos el final de la lista
    }
    
    // Método para invertir la lista enlazada
    void invertir();
};

// Implementación del método para invertir la lista
template<typename T>
void Lista<T>::invertir(){
    Nodo<T>* previo = nullptr;
    Nodo<T>* actual = cabeza;
    Nodo<T>* siguiente = nullptr; 

    while (actual) // Recorremos la lista
    {
        siguiente = actual->getSiguiente(); // Guardamos el siguiente nodo
        actual->setSiguiente(previo); // Invertimos el enlace
        previo = actual; // Movemos previo a la posición actual
        actual = siguiente; // Avanzamos al siguiente nodo
    }
    cabeza = previo; // La nueva cabeza es el último nodo procesado
}

// Función principal para probar la lista enlazada
int main(){
    Lista<string> Lista;
    Lista.insertar("Carlos");
    Lista.insertar("Edwin");
    Lista.insertar("Daniela");
    Lista.insertar("Sofia");
    Lista.insertar("Cara");
    cout << "Lista original: " << endl;
    Lista.mostrar();

    Lista.insertarPos(0, "Añañai");
    cout << "Lista tras eliminar insertar en posicion: " << endl;
    Lista.mostrar();

    cout << "Busqueda de un elemento: " << endl;
    cout<< "Persona encontrada en la posicion: " << Lista.buscar("Carlos") <<endl;

    Lista.eliminar("Edwin");
    cout << "Lista tras eliminar un elemento: " << endl;
    Lista.mostrar();

    Lista.invertir();
    cout << "Lista invertida: " << endl;
    Lista.mostrar();
    return 0;
}
