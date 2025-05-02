#include <iostream>

using namespace std;
 
int hash_1(const string& key, int tableSize) {
    int hashValue = 0;
    for (char ch : key) {
        hashValue += ch; // Sumar el valor ASCII de cada carácter
    }
    return hashValue % tableSize; // Devolver el índice en la tabla de hash
}

int main() {
    string key = "Hola"; // Clave a hashear
    int tableSize = 10; // Tamaño de la tabla de hash

    int index = hash_1(key, tableSize);
    cout << "Indice para la clave '" << key << "' es: " << index << endl;
    return 0;
}