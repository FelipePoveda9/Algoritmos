#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class RutasGrafo{
public:
    RutasGrafo() {
        createMap();
    }

    void createMap(){
        origen["Bogota"] = vector<string>{"Medellin", "Bucaramanga"};
        origen["Cali"] = vector<string>{"Cartagena", "Medellin"};
        origen["Medellin"] = vector<string>{"Cali", "Bogota"};
    }

    void mostrarDestinosDesdeCiudad(string ciudad) {
        if (origen.find(ciudad) != origen.end()) {
            cout << "Desde " << ciudad << " se puede ir a: " << endl;
            for (const string& destino : origen[ciudad]) {
                cout << "->" << destino << " " << endl;
            }
            cout << endl;

        } else {
            cout << "No se encontraron destinos para " << ciudad << endl;
        }
    }

    void mostrarOrigenesHaciaCiudad(string ciudad) {
        cout << "Ciudades que tienen a " << ciudad << " como destino: ";
        bool encontrado = false;
        for (const auto& par : origen) {
            for (const string& destino : par.second) {
                if (destino == ciudad) {
                    cout << par.first << " ";
                    encontrado = true;
                    break;
                }
            }
        }
        if (!encontrado) {
            cout << "No se encontraron orígenes hacia " << ciudad << endl;
        }
        cout << endl;
    }

    void menu() {
        int opcion = 0;
        string ciudad;
        do {
            cout << "\n------Menu------" << endl;
            cout << "\n1. Destinos desde una ciudad";
            cout << "\n2. Mostrar origenes hacia una ciudad";
            cout << "\n3. Salir";
            cout << "\nSelecciona una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    cout << "Ingrese el nombre de la ciudad: ";
                    cin >> ciudad;
                    mostrarDestinosDesdeCiudad(ciudad);
                    break;
                case 2:
                    cout << "Ingrese el nombre de la ciudad de destino: ";
                    cin >> ciudad;
                    mostrarOrigenesHaciaCiudad(ciudad);
                    break;
                case 3: 
                    cout << "Saliendo del programa.\n";
                    break;
            }
        } while (opcion != 3);
    }
    
private:
    map<string, vector<string>> origen;
};

int main() {
    RutasGrafo grafo;
    grafo.menu();
    return 0;
}
