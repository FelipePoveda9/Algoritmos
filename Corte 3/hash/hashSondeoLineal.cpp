#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
private:
    vector<string> table;
    int currentSize;
    int tableSize;

    // Función hash polinómica
    int hashFunc(const string& key) const {
        unsigned int hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % tableSize;
    }

    // Verifica si un número es primo
    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }

    // Retorna el siguiente número primo >= n
    int nextPrime(int n) const {
        while (!isPrime(n)) ++n;
        return n;
    }

    // Rehashing: redimensionar y reinsertar
    void rehash() {
        vector<string> oldTable = table;
        tableSize = nextPrime(2 * tableSize);
        table = vector<string>(tableSize, "");
        currentSize = 0;

        for (const auto& key : oldTable) {
            if (!key.empty()) {
                insert(key);
            }
        }
    }

public:
    HashTable(int size = 11) {
        tableSize = nextPrime(size);
        table.resize(tableSize, "");
        currentSize = 0;
    }

    // Insertar clave con sondeo lineal
    bool insert(const string& key) {
        int index = hashFunc(key);
        int startIndex = index;

        while (!table[index].empty()) {
            if (table[index] == key) return false; // Ya existe
            index = (index + 1) % tableSize;
            if (index == startIndex) return false; // Tabla llena
        }

        table[index] = key;
        currentSize++;

        if (currentSize > tableSize / 2) {
            rehash();  // Expandir si está medio llena
        }

        return true;
    }

    // Buscar clave
    bool contains(const string& key) const {
        int index = hashFunc(key);
        int startIndex = index;

        while (!table[index].empty()) {
            if (table[index] == key) return true;
            index = (index + 1) % tableSize;
            if (index == startIndex) break;
        }

        return false;
    }

    // Eliminar clave
    bool remove(const string& key) {
        int index = hashFunc(key);
        int startIndex = index;

        while (!table[index].empty()) {
            if (table[index] == key) {
                table[index] = "";  // Marcar como vacía
                currentSize--;
                return true;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex) break;
        }

        return false;
    }

    // Mostrar la tabla
    void display() const {
        cout << "\nTabla Hash (Sondeo Lineal):\n";
        for (int i = 0; i < tableSize; ++i) {
            cout << "[" << i << "] ";
            if (table[i].empty())
                cout << "vacío";
            else
                cout << table[i];
            cout << endl;
        }
    }
};

// ---------------- Menú interactivo ----------------

int main() {
    HashTable hashTable;

    int opcion;
    string clave;

    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Insertar clave\n";
        cout << "2. Buscar clave\n";
        cout << "3. Eliminar clave\n";
        cout << "4. Mostrar tabla\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese la clave a insertar: ";
                getline(cin, clave);
                if (hashTable.insert(clave))
                    cout << "Clave insertada correctamente.\n";
                else
                    cout << "La clave ya existe o la tabla está llena.\n";
                break;

            case 2:
                cout << "Ingrese la clave a buscar: ";
                getline(cin, clave);
                if (hashTable.contains(clave))
                    cout << "La clave está presente en la tabla.\n";
                else
                    cout << "La clave no se encontró.\n";
                break;

            case 3:
                cout << "Ingrese la clave a eliminar: ";
                getline(cin, clave);
                if (hashTable.remove(clave))
                    cout << "Clave eliminada correctamente.\n";
                else
                    cout << "La clave no estaba en la tabla.\n";
                break;

            case 4:
                hashTable.display();
                break;

            case 5:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 5);

    return 0;
}