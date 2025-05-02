/*Sondeo cuadrático: es una técnica para resolver colisiones en una tabla hash sin usar listas enlazadas. En lugar de buscar la siguiente casilla de forma lineal como en el sondeo lineal, el sondeo cuadrático busca en posiciones más separadas usando una fórmula basada en potencias cuadradas.

Ventajas
Reduce el agrupamiento primario (bloques continuos de elementos), un problema común en el sondeo lineal.
Mejor rendimiento que el sondeo lineal en tablas con muchos elementos.

Desventajas
Puede ser más complicado encontrar una posición libre si la tabla está muy llena.

Puede producir agrupamiento secundario (diferentes claves que siguen el mismo patrón de sondeo).

Puede no recorrer toda la tabla si el tamaño no es primo, por lo que es importante que la tabla tenga un tamaño primo.

Limitaciones del Sondeo Cuadrático
No garantiza recorrer toda la tabla
Si el tamaño de la tabla no es primo, puede pasar que el algoritmo nunca encuentre una posición vacía aunque la haya (¡queda atrapado en un ciclo!).

Agrupamiento secundario
Aunque reduce el agrupamiento primario (bloques consecutivos de datos como en sondeo lineal), aún puede haber colisiones repetidas para diferentes claves si generan el mismo índice inicial.

Mayor complejidad para eliminación
No es tan directo eliminar elementos, porque dejar una casilla vacía puede interrumpir búsquedas futuras.
→ Se necesita usar marcadores especiales (como "borrado") para mantener el orden de sondeo.

Se vuelve lento si la tabla está muy llena
Si el factor de carga es alto (por ejemplo, más del 50%), el número de intentos puede aumentar bastante para encontrar una posición libre.

Problemas con expansión (rehashing)
Cuando se hace rehash, se deben recalcular todos los índices con la nueva función, y si hay errores de diseño, se pierde rendimiento.

*/


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

    // Encuentra el siguiente primo mayor o igual que n
    int nextPrime(int n) const {
        while (!isPrime(n)) ++n;
        return n;
    }

    // Rehashing para expandir la tabla
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

    // Insertar clave con SONDEO CUADRÁTICO
    bool insert(const string& key) {
        int hashIndex = hashFunc(key);
        int i = 0;
        int index;

        do {
            index = (hashIndex + i * i) % tableSize;
            if (table[index] == key) return false; // Ya existe
            if (table[index].empty()) {
                table[index] = key;
                currentSize++;

                if (currentSize > tableSize / 2) {
                    rehash();
                }

                return true;
            }
            i++;
        } while (i < tableSize);

        return false; // No encontró lugar (muy improbable si se rehashea a tiempo)
    }

    // Buscar clave
    bool contains(const string& key) const {
        int hashIndex = hashFunc(key);
        int i = 0;
        int index;

        do {
            index = (hashIndex + i * i) % tableSize;
            if (table[index] == key) return true;
            if (table[index].empty()) return false;
            i++;
        } while (i < tableSize);

        return false;
    }

    // Eliminar clave
    bool remove(const string& key) {
        int hashIndex = hashFunc(key);
        int i = 0;
        int index;

        do {
            index = (hashIndex + i * i) % tableSize;
            if (table[index] == key) {
                table[index] = "";  // Marcar como vacía
                currentSize--;
                return true;
            }
            if (table[index].empty()) return false;
            i++;
        } while (i < tableSize);

        return false;
    }

    // Mostrar tabla
    void display() const {
        cout << "\nTabla Hash (Sondeo Cuadrático):\n";
        for (int i = 0; i < tableSize; ++i) {
            cout << "[" << i << "]: ";
            if (table[i].empty())
                cout << "vacío";
            else
                cout << table[i];
            cout << endl;
        }
    }
};

// ---------------------- MENÚ INTERACTIVO ----------------------

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