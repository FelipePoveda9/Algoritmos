#include <iostream>
#include <vector>
using namespace std;

class Grafo {
public:
   Grafo(int numNodos) {
        this->numNodos = numNodos;
        AdyacenciaMatriz = new bool*[numNodos];
        for (int i = 0; i < numNodos; i++) {
        AdyacenciaMatriz[i] = new bool[numNodos];
        for (int j = 0; j < numNodos; j++) {
            AdyacenciaMatriz[i][j] = false;
        }
    }
   }
 
   void agregarAristas(int i, int j) {
        AdyacenciaMatriz[i][j] = true;
        AdyacenciaMatriz[j][i] = true;
   }

   void removerAristas(int i, int j) {
        AdyacenciaMatriz[i][j] = false;
        AdyacenciaMatriz[j][i] = false;
   }
 
    void printMatriz() {
        cout << "    ";
        for (int i = 1; i < numNodos; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 1; i < numNodos; i++) {
            cout << i << " : ";
            for (int j = 1; j < numNodos; j++) {
                cout << AdyacenciaMatriz[i][j] << " ";
            }
            cout << endl;
        }
    }
 
   ~Grafo() {
        for (int i = 0; i < numNodos; i++){

            delete[] AdyacenciaMatriz[i];
        }
        delete[] AdyacenciaMatriz;
   }

private:
   bool** AdyacenciaMatriz;
   int numNodos;
 };

int main() { 
    Grafo nodos(7);

    nodos.agregarAristas(1, 5);
    nodos.agregarAristas(1, 2);
    nodos.agregarAristas(2, 1);
    nodos.agregarAristas(2, 3);
    nodos.agregarAristas(2, 5);
    nodos.agregarAristas(3, 4);
    nodos.agregarAristas(3, 2);
    nodos.agregarAristas(4, 3);
    nodos.agregarAristas(4, 5);
    nodos.agregarAristas(4, 6);
    nodos.agregarAristas(5, 4);
    nodos.agregarAristas(5, 2);
    nodos.agregarAristas(5, 1);
    nodos.agregarAristas(6, 4);
  
    nodos.printMatriz();
}
