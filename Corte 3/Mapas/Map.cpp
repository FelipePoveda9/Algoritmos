#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    // Crea dos mapas: uno de int a string y otro de string a int
    map<int, string> myMap;
    map<string, int> myMap2;
    set<int> mySet;
    // Inserta elementtos en los mapas
    myMap[1] = "Uno";
    myMap[2] = "Dos";
    myMap[3] = "Tres";
    
    myMap2["Uno"] = 1;
    myMap2["Dos"] = 2;
    myMap2["Tres"] = 3;

    mySet.insert(20);
    mySet.insert(12);        
    mySet.insert(3);

    // Acceso a los elementos del mapa
    cout << "Elemento 1: " << myMap[1] << endl;
    cout << "Elemento 2: " << myMap[2] << endl;
    cout << "Elemento 3: " << myMap[3] << endl;
    cout << "Elemento 4: " << myMap2["Uno"] << endl; 
    cout << "Elemento 5: " << myMap2["Dos"] << endl;
    cout << "Elemento 6: " << myMap2["Tres"] << endl;
    cout << "Elemento 7: " << mySet.count(20) << endl; 
    cout << "Elemento 8: " << mySet.count(0) << endl; 
    cout << "Elemento 9: " << mySet.size() << endl; 
    cout << "Elemento 10: " << mySet.empty() << endl;
    
    // Iterate through the map
    cout << "\nContenido del mapa 1 enumerado:" << endl;
    for (const auto& pair : myMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "\nContenido del mapa 2 enumerado:" << endl;
    for (const auto& pair : myMap2) {
        cout << pair.first << ": " << pair.second << endl;
    }

    for(auto& elem : mySet){
        cout << elem << " ";
    }
    return 0;
}