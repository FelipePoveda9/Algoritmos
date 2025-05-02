#include <iostream>
#include <string>
using namespace std;

int hash_1(const string& key, int tableSize) {
    int hashValue = 0;
    for (char ch : key) {
        hashValue += ch; // Sumar el valor ASCII de cada carácter
    }
    return hashValue % tableSize; // Devolver el índice en la tabla de hash
}

int Hash_2(const string &key, int tableSize) {
    // Protección por si la clave tiene menos de 3 caracteres
    char c1 = (key.length() > 0) ? key[0] : 0;
    char c2 = (key.length() > 1) ? key[1] : 0;
    char c3 = (key.length() > 2) ? key[2] : 0;

    return (c1 + 27 * c2 + 729 * c3) % tableSize;
}

unsigned int hash_3(const string &key, int tableSize) {
    unsigned int hashValue = 0;

    for (char ch : key) {
        hashValue = 37 * hashValue + ch;
    }

    return hashValue % tableSize;
}

int main() {
    string key;
    string key2;
    string key3;
    int tableSize = 10007;

    cout << "Ingrese una clave hash 1: ";
    getline(cin, key2);
    cout << "Ingrese una clave hash 2: ";
    getline(cin, key);
    cout << "Ingrese una clave hash 3: ";
    getline(cin, key3);


    // Usamos la función renombrada
    int index2 = hash_1(key2, tableSize);
    int index = Hash_2(key, tableSize);
    unsigned int index3 = hash_3(key3, tableSize);
    cout << "El índice para la clave '" << key2 << "' es: " << index2 << endl;
    cout << "El índice para la clave '" << key << "' es: " << index << endl;
    cout << "El índice para la clave '" << key3 << "' es: " << index3 << endl;
    return 0;
}
