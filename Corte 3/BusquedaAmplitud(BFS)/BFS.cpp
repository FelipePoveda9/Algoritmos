#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <typename T> 
class Cola {
private: 
    struct NodoCola {
        T actual;
        NodoCola* sig;
    };
    
    NodoCola* frente;
    NodoCola* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}

    bool estaVacia() {
        return frente == nullptr;
    }

    void encolar(const T actual) {
        NodoCola* nuevo = new NodoCola{actual, nullptr};
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->sig = nuevo;
            final = nuevo;
        }
    }

    T desencolar() {
        if (estaVacia()) {
            return "";
        }
        NodoCola* temp = frente;
        T actual = temp->actual;
        frente = frente->sig;
        if (frente == nullptr) {
            final = nullptr;
        }
        delete temp;
        return actual;
    }

    T verFrente() {
        if (estaVacia()) {
            return "";
        }
        return frente->actual;
    }

    void mostrar() {
        if (estaVacia()) {
            cout << "Cola vacía";
            return;
        }
        NodoCola* actual = frente;
        while (actual != nullptr) {
            cout << actual->actual << " ";
            actual = actual->sig;
        }
    }

    bool contains(T elemento){
        NodoCola* current = frente;
        while(current){
            if(current->actual == elemento){
                return true;
            }
            current = current->sig;
        }
        return false;
    }

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

template <typename T>
class Grafo{
private: 
     map<T, vector<T>> lista_adyacencia;
public:
    Grafo(){
        lista_adyacencia["A"] = {"B","F", "D"};
        lista_adyacencia["B"] = {"E"};  
        lista_adyacencia["C"] = {"E", "F"};
        lista_adyacencia["D"] = {"A"};
        lista_adyacencia["E"] = {"B", "C"};
        lista_adyacencia["F"] = {"A", "C"};
    }
    void lista_adyacencia_string(){
        for (const auto& par : lista_adyacencia) 
        {
            cout << par.first << " -> ";
            for (const string& cercanos : par.second) 
            {
                cout << cercanos << ", ";
            }
            cout << endl;
        }
    }
    
    void BFS(string Nodo){
        Cola <string> cola;
        set <string> visitados;
        cola.encolar(Nodo);
        
        while(!cola.estaVacia()){
            string actual = cola.desencolar();
            visitados.insert(actual);
            cout <<actual << " , ";
            for(auto vecino : lista_adyacencia[actual]){
                if (visitados.find(vecino) == visitados.end() && !cola.contains(vecino)){
                    cola.encolar(vecino);
                }
            }
        }        
    }
};


int main(){
    Grafo <string> g;
    string inicial = "A";
    g.BFS(inicial);
}