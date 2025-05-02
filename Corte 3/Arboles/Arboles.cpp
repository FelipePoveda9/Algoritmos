#include <iostream>
using namespace std;

// Estructura TreeNode para representar nodos de un árbol general
struct TreeNode {
    char element;                // Elemento que almacena el nodo (en este caso, un carácter)
    TreeNode* firstChild;        // Puntero al primer hijo del nodo
    TreeNode* nextSibling;       // Puntero al siguiente hermano del nodo

    // Constructor para inicializar un nodo con un valor y punteros nulos
    TreeNode(char val) : element(val), firstChild(nullptr), nextSibling(nullptr) {}
};

// Función para realizar un recorrido en preorden: visitar -> hijos -> hermanos
void preOrder(TreeNode* node) {
    if (node == nullptr) return; // Caso base: si el nodo es nulo, no hace nada

    cout << node->element << " "; // Imprime el elemento del nodo actual
    preOrder(node->firstChild);   // Llama recursivamente al primer hijo
    preOrder(node->nextSibling);  // Llama recursivamente al siguiente hermano
}

int main() {
    // Creación de nodos del árbol
    TreeNode* A = new TreeNode('A'); // Nodo raíz con elemento 'A'
    TreeNode* B = new TreeNode('B'); // Nodo con elemento 'B'
    TreeNode* C = new TreeNode('C'); // Nodo con elemento 'C'
    TreeNode* D = new TreeNode('D'); // Nodo con elemento 'D'
    TreeNode* E = new TreeNode('E'); // Nodo con elemento 'E'
    TreeNode* F = new TreeNode('F'); // Nodo con elemento 'F'
    TreeNode* G = new TreeNode('G'); // Nodo con elemento 'G'

    // Construcción de la estructura del árbol
    A->firstChild = B;             // El nodo 'A' tiene a 'B' como su primer hijo
    B->nextSibling = C;            // 'B' y 'C' son hermanos, hijos de 'A'

    B->firstChild = D;             // El nodo 'B' tiene a 'D' como su primer hijo
    D->nextSibling = E;            // 'D' y 'E' son hermanos, hijos de 'B'

    C->firstChild = F;             // El nodo 'C' tiene a 'F' como su primer hijo
    F->nextSibling = G;            // 'F' y 'G' son hermanos, hijos de 'C'

    // Recorrido del árbol en preorden
    cout << "Pre-order traversal: "; // Mensaje inicial para el recorrido
    preOrder(A);                     // Llama a la función de recorrido en preorden empezando desde 'A'
    cout << endl;                    // Salto de línea al final del recorrido

    return 0; // Fin del programa
}