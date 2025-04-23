#include <iostream>
using namespace std;


struct Nodo{
    int valor;
    Nodo* siguiente;
};

class pila{
private:
    Nodo* cima;
public:
    pila() : cima(nullptr){}

    void push(int x){
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo -> valor = x;
        nuevoNodo -> siguiente = cima;
        cima = nuevoNodo;
    }

    int top(){
        if(cima == nullptr){
            cerr << "Error, pila vacia" << endl;
            return -1;
        }
        return cima -> valor;
    }

    void pop(){
        if(cima == nullptr){
            cerr << "Error, no se puede hacer pop en una pila vacia";
            return;
        }
        Nodo* temp = cima;
        cima = cima -> siguiente;
        delete temp;
    }

    bool esVacia(){
        return cima == nullptr;
    }

    void imprimir(){
        Nodo* actual = cima;
        while (actual != nullptr){
            cout << actual -> valor << " ";
            actual = actual -> siguiente;
        }
        cout << endl;
    }

    ~pila(){
        while(cima != nullptr){
            pop();
        }
    }
};


main(){
    return 0;   
}