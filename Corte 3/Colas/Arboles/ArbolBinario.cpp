#include <iostream>
#include <string>

using namespace std;
// Clase genérica para un Árbol Binario de Búsqueda (BST)
template <typename T>
class BST {
private:
    // Estructura de cada nodo del árbol
    struct Node {
        T data;           // Valor almacenado en el nodo
        Node* left;       // Puntero al hijo izquierdo
        Node* right;      // Puntero al hijo derecho

        // Constructor para inicializar un nodo con un valor
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root; // Puntero a la raíz del árbol

    // Función recursiva para insertar un valor en el árbol
    Node* insert(Node* node, T value) {
        if (!node) return new Node(value); // Si el nodo es nulo, crea uno nuevo

        if (value < node->data) // Si el valor es menor, inserta en el subárbol izquierdo
            node->left = insert(node->left, value);
        else if (value > node->data) // Si el valor es mayor, inserta en el subárbol derecho
            node->right = insert(node->right, value);

        return node; // Retorna el nodo actualizado
    }

    // Encuentra el nodo con el valor mínimo en un subárbol
    Node* findMin(Node* node) {
        while (node && node->left) // Recorre hacia la izquierda hasta encontrar el nodo más pequeño
            node = node->left;
        return node;
    }

    // Función recursiva para eliminar un valor del árbol
    Node* remove(Node* node, T value) {
        if (!node) return nullptr; // Si el nodo es nulo, no hay nada que eliminar

        if (value < node->data) // Si el valor es menor, busca en el subárbol izquierdo
            node->left = remove(node->left, value);
        else if (value > node->data) // Si el valor es mayor, busca en el subárbol derecho
            node->right = remove(node->right, value);
        else {
            // Caso 1: Nodo sin hijos
            if (!node->left && !node->right) {
                delete node; // Libera la memoria del nodo
                return nullptr;
            }
            // Caso 2: Nodo con un solo hijo
            if (!node->left) { // Solo tiene hijo derecho
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) { // Solo tiene hijo izquierdo
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Caso 3: Nodo con dos hijos
            Node* successor = findMin(node->right); // Encuentra el sucesor (mínimo del subárbol derecho)
            T successorValue = successor->data; // Guarda el valor del sucesor
            node->right = remove(node->right, successorValue); // Elimina el sucesor
            node->data = successorValue; // Reemplaza el valor del nodo con el del sucesor
        }
        return node; // Retorna el nodo actualizado
    }

    // Función recursiva para buscar un valor en el árbol
    bool search(Node* node, T value) const {
        if (!node) return false; // Si el nodo es nulo, el valor no está en el árbol
        if (value < node->data) // Si el valor es menor, busca en el subárbol izquierdo
            return search(node->left, value);
        else if (value > node->data) // Si el valor es mayor, busca en el subárbol derecho
            return search(node->right, value);
        else
            return true; // Si el valor es igual, se encontró
            printInOrder(node);
    }
    


    // Función recursiva para imprimir el árbol en orden (izquierda, nodo, derecha)
    void printInOrder(Node* node) const {
        if (!node) return; // Si el nodo es nulo, no hace nada
        printInOrder(node->left); // Imprime el subárbol izquierdo
        std::cout << node->data << " "; // Imprime el valor del nodo
        printInOrder(node->right); // Imprime el subárbol derecho
    }

    // Función recursiva para imprimir el árbol en preorden (nodo, izquierda, derecha)
    void printPreOrder(Node* node) const {
        if (!node) return; // Si el nodo es nulo, no hace nada
        std::cout << node->data << " "; // Imprime el valor del nodo
        printPreOrder(node->left); // Imprime el subárbol izquierdo
        printPreOrder(node->right); // Imprime el subárbol derecho
    }

    // Función recursiva para imprimir el árbol en postorden (izquierda, derecha, nodo)
    void printPostOrder(Node* node) const {
        if (!node) return; // Si el nodo es nulo, no hace nada
        printPostOrder(node->left); // Imprime el subárbol izquierdo
        printPostOrder(node->right); // Imprime el subárbol derecho
        std::cout << node->data << " "; // Imprime el valor del nodo
    }

    // Función recursiva para liberar la memoria de los nodos
    void destroy(Node* node) {
        if (!node) return; // Si el nodo es nulo, no hace nada
        destroy(node->left); // Libera el subárbol izquierdo
        destroy(node->right); // Libera el subárbol derecho
        delete node; // Libera el nodo actual
    }

public:
    // Constructor: Inicializa el árbol vacío
    BST() : root(nullptr) {}

    // Destructor: Libera toda la memoria del árbol
    ~BST() {
        destroy(root);
    }

    // Inserta un valor en el árbol (si no está duplicado)
    void insert(T value) {
        if (!search(root, value)) { // Verifica si el valor ya existe
            root = insert(root, value); // Inserta el valor si no está duplicado
        } else {
            std::cout << "Valor duplicado no permitido: " << value << "\n";
        }
    }

    // Elimina un valor del árbol
    void remove(T value) {
        root = remove(root, value);
    }

    // Busca un valor en el árbol
    bool search(T value) const {
        return search(root, value);
    }

    // Imprime el árbol en orden
    void printInOrder() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    // Imprime el árbol en preorden
    void printPreOrder() const {
        printPreOrder(root);
        std::cout << std::endl;
    }

    // Imprime el árbol en postorden
    void printPostOrder() const {
        printPostOrder(root);
        std::cout << std::endl;
    }
};

// Función principal con un menú interactivo
int main() {
    BST<string> tree; // Crea un árbol binario de búsqueda de enteros
    int option;
    string value;

    do {
        // Muestra el menú de opciones
        std::cout << "\n------ MENÚ DE OPCIONES ------\n";
        std::cout << "1. Insertar valor\n";
        std::cout << "2. Buscar valor\n";
        std::cout << "3. Eliminar valor\n";
        std::cout << "4. Imprimir inorden\n";
        std::cout << "5. Imprimir preorden\n";
        std::cout << "6. Imprimir postorden\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch (option) {
            case 1: // Inserta un valor en el árbol
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> value;
                tree.insert(value);
                break;
            case 2: // Busca un valor en el árbol
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> value;
                if (tree.search(value))
                    std::cout << "Valor encontrado\n";
                else
                    std::cout << "Valor no encontrado\n";
                break;
            case 3: // Elimina un valor del árbol
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> value;
                tree.remove(value);
                break;
            case 4: // Imprime el árbol en orden
                std::cout << "Recorrido inorden: ";
                tree.printInOrder();
                break;
            case 5: // Imprime el árbol en preorden
                std::cout << "Recorrido preorden: ";
                tree.printPreOrder();
                break;
            case 6: // Imprime el árbol en postorden
                std::cout << "Recorrido postorden: ";
                tree.printPostOrder();
                break;
            case 0: // Sale del programa
                std::cout << "Saliendo del programa.\n";
                break;
            default: // Opción inválida
                std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (option != 0); // Repite hasta que el usuario elija salir

    return 0;
}