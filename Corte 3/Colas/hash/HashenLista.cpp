#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Nodo para lista enlazada: 
struct Node {
    string data;
    Node* next;
    Node(const string& d, Node* n = nullptr) : data(d), next(n) {}
};

// Lista simplemente enlazada
class SimpleLinkedList {
private:
    Node* head;

public:
    SimpleLinkedList() : head(nullptr) {}

    bool contains(const string& x) const {
        Node* current = head;
        while (current) {
            if (current->data == x) return true;
            current = current->next;
        }
        return false;
    }
bool insert(const string& x) {
        if (contains(x)) return false;
        head = new Node(x, head);
        return true;
    }

    bool remove(const string& x) {
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if (current->data == x) {
                if (prev) prev->next = current->next;
                else head = current->next;
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void moveAllTo(vector<SimpleLinkedList>& newLists, int (*hashFunc)(const string&, int), int newSize) {
        Node* current = head;
        while (current) {
            int index = hashFunc(current->data, newSize);
            newLists[index].insert(current->data);
            current = current->next;
        }
    }
void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL";
    }

    ~SimpleLinkedList() {
        Node* current = head;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }
};
// Tabla Hash con encadenamiento separado
class HashTable {
private:
    vector<SimpleLinkedList> theLists;
    int currentSize;

    int stringHash(const string& key) const {
        unsigned int hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return static_cast<int>(hashVal);
    }

    int MYHASH(const string& key) const {
        return stringHash(key) % theLists.size();
    }

    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }
int nextPrime(int n) const {
        while (!isPrime(n)) ++n;
        return n;
    }

    static int staticHash(const string& key, int tableSize) {
        unsigned int hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % tableSize;
    }

    void rehash() {
        vector<SimpleLinkedList> oldLists = theLists;
        int newSize = nextPrime(2 * theLists.size());
        theLists = vector<SimpleLinkedList>(newSize);
        currentSize = 0;

        for (auto& list : oldLists) {
            list.moveAllTo(theLists, staticHash, newSize);
        }
    }
public:
    HashTable(int size = 7) : theLists(nextPrime(size)), currentSize(0) {}

    bool contains(const string& x) const {
        int index = MYHASH(x);
        return theLists[index].contains(x);
    }

    bool insert(const string& x) {
        int index = MYHASH(x);
        if (!theLists[index].insert(x)) return false;
        ++currentSize;

        if (currentSize > theLists.size())
            rehash();

        return true;
    }

    bool remove(const string& x) {
        int index = MYHASH(x);
        if (theLists[index].remove(x)) {
            --currentSize;
            return true;
        }
        return false;
    }

    void display() const {
        for (int i = 0; i < theLists.size(); ++i) {
            cout << "[" << i << "]: ";
            theLists[i].print();
            cout << endl;
        }
    }
};
// ---------------------------- MENÚ INTERACTIVO --------------------------------

int main() {
    HashTable ht(7);  // Tamaño pequeño para ver colisiones y rehash

    int option;
    string key;

    do {
        cout << "\n----- MENÚ -----\n";
        cout << "1. Insertar clave\n";
        cout << "2. Buscar clave\n";
        cout << "3. Eliminar clave\n";
        cout << "4. Mostrar tabla hash\n";
        cout << "5. Salir\n";
        cout << "Elija una opción: ";
        cin >> option;
        cin.ignore();  // Limpiar el buffer de entrada

        switch (option) {
            case 1:
                cout << "Ingrese la clave a insertar: ";
                getline(cin, key);
                if (ht.insert(key)) {
                    cout << "Clave '" << key << "' insertada con éxito.\n";
                } else {
                    cout << "La clave '" << key << "' ya existe.\n";
                }
                break;
case 2:
                cout << "Ingrese la clave a buscar: ";
                getline(cin, key);
                if (ht.contains(key)) {
                    cout << "La clave '" << key << "' está presente en la tabla.\n";
                } else {
                    cout << "La clave '" << key << "' no está presente.\n";
                }
                break;

            case 3:
                cout << "Ingrese la clave a eliminar: ";
                getline(cin, key);
                if (ht.remove(key)) {
                    cout << "Clave '" << key << "' eliminada con éxito.\n";
                } else {
                    cout << "La clave '" << key << "' no se pudo eliminar.\n";
                }
                break;
case 4:
                cout << "Tabla hash actual:\n";
                ht.display();
                break;

            case 5:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida, intente de nuevo.\n";
        }

    } while (option != 5);

    return 0;
}