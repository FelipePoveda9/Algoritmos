/*Función perfectHash:

El hashing perfecto es una técnica donde se diseña una función hash que no produce colisiones para un conjunto específico de claves conocidas.
Una función hash perfecta asigna cada clave a una posición única y distinta en la tabla hash.


Para este ejemplo, se utiliza una función hash perfecta para un conjunto específico de claves conocidas.

Se asigna un índice único a cada clave.

Métodos insert, contains y remove:

Estos métodos ahora usan perfectHash para encontrar el índice de la clave.

Ya no se usan técnicas como sondeo cuadrático, ya que la tabla tiene una asignación perfecta sin colisiones.

Tamaño de la tabla:

En este ejemplo, se ha fijado un tamaño de tabla igual al número de claves conocidas. 
Esto garantiza que no haya colisiones con las claves definidas.

Si se añaden más claves, se necesitaría una estrategia diferente para manejar colisiones, ya que el hashing perfecto solo funciona para un conjunto conocido de claves.

Hashing Perfecto Directo es la mejor opción cuando las claves son conocidas y no cambian, porque garantiza que no haya colisiones.

Si las claves son dinámicas, se pueden usar tablas hash secundarias para gestionar colisiones.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
private:
    vector<string> table;
    int tableSize;

    // Función hash perfecta (suposición: claves fijas)
    int perfectHash(const string& key) const {
        if (key == "pera") return 0;
        else if (key == "manzana") return 1;
        else if (key == "banano") return 2;
        else if (key == "uva") return 3;
        else if (key == "ciruela") return 4;
        else return -1; // No válida
    }

public:
    HashTable(int size = 5) {
        tableSize = size;
        table.resize(tableSize, "");
    }

    // Insertar clave con Hashing Perfecto
    bool insert(const string& key) {
        int index = perfectHash(key);
        if (index == -1) return false; // Clave no válida
        if (!table[index].empty()) return false; // Colisión

        table[index] = key;
        return true;
    }

    // Buscar clave con Hashing Perfecto
    bool contains(const string& key) const {
        int index = perfectHash(key);
        if (index == -1) return false; // Clave no válida
        return table[index] == key;
    }

    // Eliminar clave con Hashing Perfecto
    bool remove(const string& key) {
        int index = perfectHash(key);
        if (index == -1) return false; // Clave no válida
        if (table[index] != key) return false; // No se encuentra

        table[index] = "";
        return true;
    }

    // Mostrar tabla
    void display() const {
        cout << "\nTabla Hash (Hashing Perfecto):\n";
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
                    cout << "La clave ya existe o es inválida.\n";
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