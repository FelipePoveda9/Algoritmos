#include <iostream>
#include <string>

using namespace std;


// Implementación de Cola personalizada
class Cola {
private: 
    struct NodoCola {
        string placa;
        NodoCola* sig;
    };
    
    NodoCola* frente;
    NodoCola* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}

    bool estaVacia() {
        return frente == nullptr;
    }

    void encolar(const string placa) {
        NodoCola* nuevo = new NodoCola{placa, nullptr};
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->sig = nuevo;
            final = nuevo;
        }
    }

    string desencolar() {
        if (estaVacia()) {
            return "";
        }
        NodoCola* temp = frente;
        string placa = temp->placa;
        frente = frente->sig;
        if (frente == nullptr) {
            final = nullptr;
        }
        delete temp;
        return placa;
    }

    string verFrente() {
        if (estaVacia()) {
            return "";
        }
        return frente->placa;
    }

    void mostrar() {
        if (estaVacia()) {
            cout << "Cola vacía";
            return;
        }
        NodoCola* actual = frente;
        while (actual != nullptr) {
            cout << actual->placa << " ";
            actual = actual->sig;
        }
    }

    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

// Implementación de Pila personalizada
class Pila {
private:
    struct NodoPila {
        string placa;
        NodoPila* sig;
    };
    
    NodoPila* cima;

public:
    Pila() : cima(nullptr) {}

    bool estaVacia() {
        return cima == nullptr;
    }

    void push(const string placa) {
        NodoPila* nuevo = new NodoPila{placa, cima};
        cima = nuevo;
    }

    string pop() {
        if (estaVacia()) {
            return "";
        }
        NodoPila* temp = cima;
        string placa = temp->placa;
        cima = cima->sig;
        delete temp;
        return placa;
    }

    string top() {
        if (estaVacia()) {
            return "";
        }
        return cima->placa;
    }

    void mostrar() {
        if (estaVacia()) {
            cout << "Pila vacía";
            return;
        }
        NodoPila* actual = cima;
        while (actual != nullptr) {
            cout << actual->placa << " ";
            actual = actual->sig;
        }
    }

    ~Pila() {
        while (!estaVacia()) {
            pop();
        }
    }
};

// Estructura para representar un vehículo
struct Vehiculo {
    string placa;
    Vehiculo* sig;
};

// Estructura para representar una zona
struct Zona {
    string nombre;
    int capacidad;
    int ocupados;
    Vehiculo* vehiculos;
    Cola colaEspera;
    Pila pilaDeshacer;
    Zona* sig;
};

// Estructura para representar un parqueadero
struct Parqueadero {
    string nombre;
    Parqueadero* sig;
    Zona* zonas;
};

// Estructura para representar una ciudad
struct Ciudad {
    string nombre;
    Ciudad* sig;
    Parqueadero* parqueaderos;
};

// Prototipos de funciones
void agregarCiudad(Ciudad*& cabeza, const string nombre); // Paso direccion de  de memoria
void agregarParqueadero(Ciudad* cabeza, const string nombreCiudad, const string nombreParqueadero); // Paso el puntero cabeza de la ciudad
void agregarZona(Ciudad* cabeza, const string nombreCiudad, const string nombreParqueadero, const string nombreZona, int capacidad);
Ciudad* buscarCiudad(Ciudad* cabeza, const string nombre);
Parqueadero* buscarParqueadero(Parqueadero* cabeza, const string nombre);
Zona* buscarZona(Zona* cabeza, const string nombre);
void registrarVehiculo(Zona* zona, const string placa);
void deshacerUltimo(Zona* zona);
void atenderCola(Zona* zona);
void agregarCiudadConParqueaderos(Ciudad*& cabeza);
void agregarZonasAParqueadero(Ciudad* ciudades, Parqueadero* parqueadero, const string nombreCiudad);
void liberarMemoria(Ciudad*& cabeza);
void mostrarTodo(Ciudad* cabeza);
void mostrarMenu();


void agregarCiudad(Ciudad*& cabeza, const string nombre) {
    Ciudad* nuevaCiudad = new Ciudad;
    nuevaCiudad->nombre = nombre;
    nuevaCiudad->sig = nullptr;
    nuevaCiudad->parqueaderos = nullptr;

    if (!cabeza) {
        cabeza = nuevaCiudad;
    } else {
        Ciudad* actual = cabeza;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nuevaCiudad;
    }
    cout << "Ciudad '" << nombre << "' agregada correctamente." << endl;
}

void agregarParqueadero(Ciudad* cabeza, const string nombreCiudad, const string nombreParqueadero) {
    Ciudad* ciudad = buscarCiudad(cabeza, nombreCiudad);
    if (!ciudad) {
        cout << "Ciudad no encontrada." << endl;
        return;
    }

    Parqueadero* nuevoParqueadero = new Parqueadero;
    nuevoParqueadero->nombre = nombreParqueadero;
    nuevoParqueadero->sig = nullptr;
    nuevoParqueadero->zonas = nullptr;

    if (!ciudad->parqueaderos) {
        ciudad->parqueaderos = nuevoParqueadero;
    } else {
        Parqueadero* actual = ciudad->parqueaderos;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nuevoParqueadero;
    }
    cout << "Parqueadero '" << nombreParqueadero << "' agregado a '" << nombreCiudad << "' correctamente." << endl;
}

void agregarZona(Ciudad* cabeza, const string nombreCiudad, const string nombreParqueadero, const string nombreZona, int capacidad) {
    Ciudad* ciudad = buscarCiudad(cabeza, nombreCiudad);
    if (!ciudad) {
        cout << "Ciudad no encontrada." << endl;
        return;
    }

    Parqueadero* parqueadero = buscarParqueadero(ciudad->parqueaderos, nombreParqueadero);
    if (!parqueadero) {
        cout << "Parqueadero no encontrado." << endl;
        return;
    }

    Zona* nuevaZona = new Zona;
    nuevaZona->nombre = nombreZona;
    nuevaZona->capacidad = capacidad;
    nuevaZona->ocupados = 0;
    nuevaZona->vehiculos = nullptr;
    nuevaZona->sig = nullptr;

    if (!parqueadero->zonas) {
        parqueadero->zonas = nuevaZona;
    } else {
        Zona* actual = parqueadero->zonas;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nuevaZona;
    }
    cout << "Zona '" << nombreZona << "' con capacidad " << capacidad << " agregada a '" << nombreParqueadero << "' correctamente." << endl;
}

Ciudad* buscarCiudad(Ciudad* cabeza, const string nombre) {
    Ciudad* actual = cabeza;
    while (actual) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}

Parqueadero* buscarParqueadero(Parqueadero* cabeza, const string nombre) {
    Parqueadero* actual = cabeza;
    while (actual) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}

Zona* buscarZona(Zona* cabeza, const string nombre) {
    Zona* actual = cabeza;
    while (actual) {
        if (actual->nombre == nombre) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}

void registrarVehiculo(Zona* zona, const string placa) {
    if (zona->ocupados < zona->capacidad) {
        Vehiculo* nuevoVehiculo = new Vehiculo;
        nuevoVehiculo->placa = placa;
        nuevoVehiculo->sig = zona->vehiculos;
        zona->vehiculos = nuevoVehiculo;
        
        zona->pilaDeshacer.push(placa);
        zona->ocupados++;
        
        cout << "Vehículo '" << placa << "' registrado en zona '" << zona->nombre << "'." << endl;
    } else {
        zona->colaEspera.encolar(placa);
        cout << "Zona llena. Vehículo '" << placa << "' agregado a la cola de espera." << endl;
    }
}

void deshacerUltimo(Zona* zona) {
    if (zona->pilaDeshacer.estaVacia()) {
        cout << "No hay registros para deshacer en esta zona." << endl;
        return;
    }

    string placa = zona->pilaDeshacer.pop();

    Vehiculo* actual = zona->vehiculos;
    Vehiculo* anterior = nullptr;
    bool encontrado = false;

    while (actual && !encontrado) {
        if (actual->placa == placa) {
            encontrado = true;
            if (anterior) {
                anterior->sig = actual->sig;
            } else {
                zona->vehiculos = actual->sig;
            }
            delete actual;
            zona->ocupados--;
            cout << "Registro del vehículo '" << placa << "' deshecho correctamente." << endl;
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }

    if (!encontrado) {
        cout << "Vehículo no encontrado en la lista de estacionados." << endl;
    }
}

void atenderCola(Zona* zona) {
    if (zona->colaEspera.estaVacia()) {
        cout << "No hay vehículos en la cola de espera de esta zona." << endl;
        return;
    }

    string placa = zona->colaEspera.verFrente();

    if (zona->ocupados < zona->capacidad) {
        zona->colaEspera.desencolar();
        registrarVehiculo(zona, placa);
    } else {
        cout << "No hay espacio disponible. Vehículo '" << placa << "' sigue en espera." << endl;
    }
}

void agregarCiudadConParqueaderos(Ciudad*& cabeza) {
    string nombreCiudad;
    cout << "\nIngrese el nombre de la ciudad: ";
    getline(cin, nombreCiudad);
    agregarCiudad(cabeza, nombreCiudad);
    
    Ciudad* ciudad = buscarCiudad(cabeza, nombreCiudad);
    if (!ciudad) {
        cout << "Error al agregar la ciudad." << endl;
        return;
    }

    int numParqueaderos;
    cout << "¿Cuántos parqueaderos tiene la ciudad " << nombreCiudad << "? ";
    cin >> numParqueaderos;
    cin.ignore();

    for (int i = 0; i < numParqueaderos; i++) {
        string nombreParqueadero;
        cout << "\nNombre del parqueadero " << (i + 1) << ": ";
        getline(cin, nombreParqueadero);
        
        agregarParqueadero(ciudad, nombreCiudad, nombreParqueadero);
        Parqueadero* parqueadero = buscarParqueadero(ciudad->parqueaderos, nombreParqueadero);
        
        if (parqueadero) {
            agregarZonasAParqueadero(cabeza, parqueadero, nombreCiudad);
        } else {
            cout << "Error al agregar el parqueadero." << endl;
        }
    }
}

void agregarZonasAParqueadero(Ciudad* ciudades, Parqueadero* parqueadero, const string nombreCiudad) {
    int numZonas;
    cout << "¿Cuántas zonas tiene el parqueadero " << parqueadero->nombre << "? ";
    cin >> numZonas;
    cin.ignore();

    Ciudad* ciudad = buscarCiudad(ciudades, nombreCiudad);
    if (!ciudad) {
        cout << "Error: Ciudad no encontrada" << endl;
        return;
    }

    for (int i = 0; i < numZonas; i++) {
        string nombreZona;
        int capacidad;
        
        cout << "\nNombre de la zona " << (i + 1) << ": ";
        getline(cin, nombreZona);
        
        cout << "Capacidad de la zona " << nombreZona << ": ";
        cin >> capacidad;
        cin.ignore();
        
        agregarZona(ciudades, nombreCiudad, parqueadero->nombre, nombreZona, capacidad);
    }
}

void mostrarTodo(Ciudad* cabeza) {
    if (!cabeza) {
        cout << "\nNo hay ciudades registradas en el sistema.\n" << endl;
        return;
    }

    cout << "\n=== ESTRUCTURA COMPLETA DEL SISTEMA ===\n";
    Ciudad* ciudadActual = cabeza;
    while (ciudadActual) {
        cout << "\nCiudad: " << ciudadActual->nombre << endl;
        
        Parqueadero* parqueaderoActual = ciudadActual->parqueaderos;
        if (!parqueaderoActual) {
            cout << "  No tiene parqueaderos registrados." << endl;
        } else {
            while (parqueaderoActual) {
                cout << "  Parqueadero: " << parqueaderoActual->nombre << endl;
                
                Zona* zonaActual = parqueaderoActual->zonas;
                if (!zonaActual) {
                    cout << "    No tiene zonas registradas." << endl;
                } else {
                    while (zonaActual) {
                        cout << "    Zona: " << zonaActual->nombre 
                             << " (Ocupación: " << zonaActual->ocupados << "/" << zonaActual->capacidad << ")" << endl;
                        
                        Vehiculo* vehiculoActual = zonaActual->vehiculos;
                        if (!vehiculoActual) {
                            cout << "      No hay vehículos estacionados." << endl;
                        } else {
                            cout << "      Vehículos estacionados: ";
                            while (vehiculoActual) {
                                cout << vehiculoActual->placa << " ";
                                vehiculoActual = vehiculoActual->sig;
                            }
                            cout << endl;
                        }
                        
                        if (zonaActual->colaEspera.estaVacia()) {
                            cout << "      No hay vehículos en espera." << endl;
                        } else {
                            cout << "      Vehículos en espera: ";
                            zonaActual->colaEspera.mostrar();
                            cout << endl;
                        }
                        
                        if (zonaActual->pilaDeshacer.estaVacia()) {
                            cout << "      No hay registros para deshacer." << endl;
                        } else {
                            cout << "      Último registro: " << zonaActual->pilaDeshacer.top() << endl;
                        }
                        zonaActual = zonaActual->sig;
                        if (zonaActual) cout << endl;
                    }
                }
                parqueaderoActual = parqueaderoActual->sig;
                if (parqueaderoActual) cout << endl;
            }
        }
        ciudadActual = ciudadActual->sig;
        if (ciudadActual) cout << endl;
    }
    cout << "\n=== FIN DEL REPORTE ===\n" << endl;
}

void liberarMemoria(Ciudad*& cabeza) {
    while (cabeza) {
        Ciudad* ciudadActual = cabeza;
        cabeza = cabeza->sig;
        Parqueadero* parqueaderoActual = ciudadActual->parqueaderos;
        while (parqueaderoActual) {
            Parqueadero* parqueaderoTemp = parqueaderoActual;
            parqueaderoActual = parqueaderoActual->sig;
            
            Zona* zonaActual = parqueaderoTemp->zonas;
            while (zonaActual) {
                Zona* zonaTemp = zonaActual;
                zonaActual = zonaActual->sig;
                
                Vehiculo* vehiculoActual = zonaTemp->vehiculos;
                while (vehiculoActual) {
                    Vehiculo* vehiculoTemp = vehiculoActual;
                    vehiculoActual = vehiculoActual->sig;
                    delete vehiculoTemp;
                }
                delete zonaTemp;
            }
            delete parqueaderoTemp;
        }
        delete ciudadActual;
    }
}

void mostrarMenu() {
    cout << "\n=== SISTEMA DE GESTIÓN DE PARQUEADEROS ===" << endl;
    cout << "1. Agregar ciudad con sus parqueaderos y zonas" << endl;
    cout << "2. Registrar vehículo" << endl;
    cout << "3. Mostrar estructura completa" << endl;
    cout << "4. Deshacer último registro" << endl;
    cout << "5. Atender vehículo de la cola" << endl;
    cout << "6. Salir del sistema" << endl;
    cout << "Seleccione una opción (1-6): ";
}

int main() {
    Ciudad* ciudades = nullptr;
    int opcion;
    string nombreCiudad, nombreParqueadero, nombreZona, placa;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                agregarCiudadConParqueaderos(ciudades);
                break;
                
            case 2: {
                cout << "Ciudad: ";
                getline(cin, nombreCiudad);
                cout << "Parqueadero: ";
                getline(cin, nombreParqueadero);
                cout << "Zona: ";
                getline(cin, nombreZona);
                cout << "Placa del vehículo: ";
                getline(cin, placa);
                
                Ciudad* ciudad = buscarCiudad(ciudades, nombreCiudad);
                if (ciudad) {
                    Parqueadero* parqueadero = buscarParqueadero(ciudad->parqueaderos, nombreParqueadero);
                    if (parqueadero) {
                        Zona* zona = buscarZona(parqueadero->zonas, nombreZona);
                        if (zona) {
                            registrarVehiculo(zona, placa);
                        } else {
                            cout << "Zona no encontrada." << endl;
                        }
                    } else {
                        cout << "Parqueadero no encontrado." << endl;
                    }
                } else {
                    cout << "Ciudad no encontrada." << endl;
                }
                break;
            }
                
            case 3:
                mostrarTodo(ciudades);
                break;
                
            case 4: {
                cout << "Ciudad: ";
                getline(cin, nombreCiudad);
                cout << "Parqueadero: ";
                getline(cin, nombreParqueadero);
                cout << "Zona: ";
                getline(cin, nombreZona);
                
                Ciudad* ciudad = buscarCiudad(ciudades, nombreCiudad);
                if (ciudad) {
                    Parqueadero* parqueadero = buscarParqueadero(ciudad->parqueaderos, nombreParqueadero);
                    if (parqueadero) {
                        Zona* zona = buscarZona(parqueadero->zonas, nombreZona);
                        if (zona) {
                            deshacerUltimo(zona);
                        } else {
                            cout << "Zona no encontrada." << endl;
                        }
                    } else {
                        cout << "Parqueadero no encontrado." << endl;
                    }
                } else {
                    cout << "Ciudad no encontrada." << endl;
                }
                break;
            }
                
            case 5: {
                cout << "Ciudad: ";
                getline(cin, nombreCiudad);
                cout << "Parqueadero: ";
                getline(cin, nombreParqueadero);
                cout << "Zona: ";
                getline(cin, nombreZona);
                
                Ciudad* ciudad = buscarCiudad(ciudades, nombreCiudad);
                if (ciudad) {
                    Parqueadero* parqueadero = buscarParqueadero(ciudad->parqueaderos, nombreParqueadero);
                    if (parqueadero) {
                        Zona* zona = buscarZona(parqueadero->zonas, nombreZona);
                        if (zona) {
                            atenderCola(zona);
                        } else {
                            cout << "Zona no encontrada." << endl;
                        }
                    } else {
                        cout << "Parqueadero no encontrado." << endl;
                    }
                } else {
                    cout << "Ciudad no encontrada." << endl;
                }
                break;
            }
                
            case 6:
                cout << "Saliendo del sistema..." << endl;
                break;
                
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);

    liberarMemoria(ciudades);
    return 0;
}