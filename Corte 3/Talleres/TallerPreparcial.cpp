#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <queue> 
#include <vector>

using namespace std;

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class HistorialNavegacion {
public:
    bool atras() {
        if (!pila_atras.empty()) {
            pila_adelante.push(pagina_actual);
            pagina_actual = pila_atras.top();
            pila_atras.pop();
            return true;
        }
        return false;
    }

    bool adelante() {
        if (!pila_adelante.empty()) {
            pila_atras.push(pagina_actual);
            pagina_actual = pila_adelante.top();
            pila_adelante.pop();
            return true;
        }
        return false;
    }

    void visitar(const string& url) {
        if (!pagina_actual.empty())
            pila_atras.push(pagina_actual);
        pagina_actual = url;
        while (!pila_adelante.empty()) pila_adelante.pop();
    }


    void mostrarPaginaActual() const {
        cout << "Página actual: " << (pagina_actual.empty() ? "Ninguna" : pagina_actual) << endl;
    }

private:
    stack<string> pila_atras;
    stack<string> pila_adelante;
    string pagina_actual;
};

struct Paciente {
    string nombre;
    int prioridad;
    int ordenLlegada;

    Paciente(string _nombre, int _prioridad, int _ordenLlegada) {
        nombre = _nombre;
        prioridad = _prioridad;
        ordenLlegada = _ordenLlegada;
    }
};

struct ComparadorPaciente {
    bool operator()(const Paciente& a, const Paciente& b) const {
        if (a.prioridad != b.prioridad) {
            return a.prioridad > b.prioridad;
        }
        return a.ordenLlegada > b.ordenLlegada;
    }
};


class SalaUrgencias {
public:
    void agregarPaciente(const string& nombre, int prioridad) {
        Paciente nuevo(nombre, prioridad, ordenLlegada++);
        cola_prioridad.push(nuevo);
        cout << "Paciente agregado: " << nombre << " (Prioridad " << prioridad << ")\n";
    }

    bool atenderPaciente() {
        if (cola_prioridad.empty()) {
            cout << "No hay pacientes por atender.\n";
            return false;
        } else {
            Paciente paciente = cola_prioridad.top();
            cola_prioridad.pop();
            cout << "Atendiendo a: " << paciente.nombre << " (Prioridad " << paciente.prioridad << ")\n";
            return true;
        }
    }

    void mostrarColaActual() const {
        if (cola_prioridad.empty()) {
            cout << "No hay pacientes en la cola.\n";
            return;
        }

        auto copiaCola = cola_prioridad;

        cout << "Pacientes en la cola (en orden de prioridad):\n";
        cout << "[";
        while (!copiaCola.empty()) {
            Paciente p = copiaCola.top();
            copiaCola.pop();
            cout << " - " << p.nombre << " (Prioridad " << p.prioridad << ")";
        }
        cout << "]";
    }
private:
    int ordenLlegada = 0;
    priority_queue<Paciente, vector<Paciente>, ComparadorPaciente> cola_prioridad;
};

void Menu() {
    HistorialNavegacion Historial;
    int opcion = 0;
    string pagina;

    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Visitar nueva página\n";
        cout << "2. Ir atrás\n";
        cout << "3. Ir adelante\n";
        cout << "4. Mostrar página actual\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese URL: ";
                getline(cin, pagina);
                Historial.visitar(pagina);
                cout << "Pagina visitada con éxito.\n";
                break;

            case 2:
                if (Historial.atras())
                    cout << "Volviste a la pagina anterior.\n";
                else
                    cout << "No hay paginas atras.\n";
                break;

            
            case 3:
                if (Historial.adelante())
                    cout << "Avanzaste a la siguiente pagina.\n";
                else
                    cout << "No hay paginas adelante.\n";
                break;

            case 4:
                Historial.mostrarPaginaActual();
                break;

            case 5:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 5);
}

void MenuUrgencias() {
    SalaUrgencias urgencias;
    int opcion;
    string nombre;
    int prioridad;

    do {
        cout << "\n--- MENÚ SALA DE URGENCIAS ---\n";
        cout << "1. Agregar paciente\n";
        cout << "2. Atender paciente\n";
        cout << "3. Mostrar cola\n"; 
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nombre del paciente: ";
                getline(cin, nombre);
                cout << "Prioridad (1-5): ";
                cin >> prioridad;
                cin.ignore();
                urgencias.agregarPaciente(nombre, prioridad);
                break;
            case 2:
                urgencias.atenderPaciente();
                break;
            case 3:
                urgencias.mostrarColaActual();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
                break;
        }
    } while (opcion != 4);
}


int main() {
    Menu();
    MenuUrgencias();
    return 0;
}
