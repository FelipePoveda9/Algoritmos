#include <iostream>
#include <string>

using namespace std;

// -------------------- Nodo para Map --------------------

template <typename K, typename V>
struct RegistroNotas {
    K key;
    V value;
    RegistroNotas* next;

    RegistroNotas(K k, V v) : key(k), value(v), next(nullptr) {}
};

// -------------------- Clase Map --------------------

template <typename K, typename V>
class Map {
private:
    RegistroNotas<K, V>* head;

    RegistroNotas<K, V>* findNode(K key) const {
        RegistroNotas<K, V>* current = head;
        while (current) {
            if (current->key == key)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    Map() : head(nullptr) {}

    ~Map() {
        RegistroNotas<K, V>* current = head;
        while (current) {
            RegistroNotas<K, V>* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(K key, V value) {
        RegistroNotas<K, V>* node = findNode(key);
        if (node) {
            node->value = value; // actualizar
        } else {
            RegistroNotas<K, V>* newNode = new RegistroNotas<K, V>(key, value);
            newNode->next = head;
            head = newNode;
        }
    }

    bool get(K key, V& value) const {
        RegistroNotas<K, V>* node = findNode(key);
        if (node) {
            value = node->value;
            return true;
        }
        return false;
    }

    void remove(K key, V& value) {
        RegistroNotas<K, V>* node = findNode(key);
        RegistroNotas<K, V>* current = head;
        RegistroNotas<K, V>* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void print() const {
        RegistroNotas<K, V>* current = head;
        cout << "-------------------------" << endl;
        if (current != nullptr) {
            while (current) {
                cout << " " << current->key << " → " << current->value << "\n";
                current = current->next;
            }
        } else if (current == nullptr) {
            cout << "No hay notas registradas." << endl;
        }
        cout << "-------------------------" << endl;
    }

    void printMenu() {
        cout << "Opciones:" << endl;
        cout << "1. Insertar nota" << endl;
        cout << "2. Buscar nota" << endl;
        cout << "3. Actualizar nota" << endl;
        cout << "4. Eliminar nota" << endl;
        cout << "5. Mostrar notas"<< endl;
        cout << "6. Salir" << endl;


    }

    void run() {
        int escoger;
        string key, value;

        do {
            printMenu();
            cout << "\nElija una opción: ";
            cin >> escoger;

            switch (escoger) {
                case 1:
                    cout << "\nNombre del Estudiante: " << endl;
                    cin >> key;
                    cout << "\nNota: " << endl;
                    cin >> value;
                    insert(key, value);
                    break;
                case 2:
                    cout << "\nNombre: " << endl;
                    cin >> key;
                    if (get(key, value)) {
                        cout << "\nNota de " << key << ": " << value << endl;
                    } else {
                        cout << key << " no está en el registro." << endl;
                    }
                    break;
                case 3:
                    cout << "\nNombre: " << endl;
                    cin >> key;
                    if (get(key, value)) {
                        cout << "\nNota de " << key << ": " << value << endl;
                    } else {
                        cout << key << " no está en el registro." << endl;
                    }
                    cout << "\nNota a actualizar: " << endl;
                    cin >> value;
                    insert(key, value);
                    break;
                case 4:
                    cout << "\nNombre: " << endl;
                    cin >> key;
                    remove(key, value);
                    break;
                case 5:
                    print();
                    break;
                case 6:
                    cout << "\nSaliendo..." << endl;
                    break;
                default:
                    cout << "\nOpción invalida, intente de nuevo." << endl;
            }
        } while (escoger != 6);
    }
};

// -------------------- Main con ejemplo de agenda --------------------

int main() {
    Map<string, string> agenda;

    agenda.run();

    return 0;
}

