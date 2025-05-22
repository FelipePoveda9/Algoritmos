#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <ctime>
#include <limits>
#include <string>

using namespace std;

//PARTE 1: Red Social
const int NUMERO_DE_PERSONAS = 1000;

class RedSocial {
private:
    bool matriz_adyacencia[NUMERO_DE_PERSONAS][NUMERO_DE_PERSONAS];
    vector<vector<int>> reacciones_por_persona;
    map<int, string> persona_a_ciudad;

    int generar_aleatorio(int minimo, int maximo) {
        return minimo + (rand() % (maximo - minimo + 1));
    }

    void generar_conexiones() {
        for (int i = 0; i < NUMERO_DE_PERSONAS; ++i)
            for (int j = 0; j < NUMERO_DE_PERSONAS; ++j)
                matriz_adyacencia[i][j] = false;

        for (int persona = 0; persona < NUMERO_DE_PERSONAS; ++persona) {
            int cantidad_de_conexiones = generar_aleatorio(1, 30);
            while (cantidad_de_conexiones > 0) {
                int conexion = generar_aleatorio(0, NUMERO_DE_PERSONAS - 1);
                if (conexion != persona && !matriz_adyacencia[persona][conexion]) {
                    matriz_adyacencia[persona][conexion] = true;
                    matriz_adyacencia[conexion][persona] = true;
                    cantidad_de_conexiones--;
                }
            }
        }
    }

    void generar_reacciones() {
        reacciones_por_persona.resize(NUMERO_DE_PERSONAS);
        for (int persona = 0; persona < NUMERO_DE_PERSONAS; ++persona) {
            int cantidad_de_mensajes = generar_aleatorio(1, 500);
            for (int m = 0; m < cantidad_de_mensajes; ++m) {
                int cantidad_de_reacciones = generar_aleatorio(1, 50);
                for (int r = 0; r < cantidad_de_reacciones; ++r) {
                    int valor_reaccion = generar_aleatorio(-5, 5);
                    reacciones_por_persona[persona].push_back(valor_reaccion);
                }
            }
        }
    }

public:
    RedSocial() {
        srand(time(0));
        generar_conexiones();
        generar_reacciones();
    }

    vector<int> top_influencers(int top_n = 5) {
        vector<pair<int, int>> conexiones_por_persona;
        for (int i = 0; i < NUMERO_DE_PERSONAS; ++i) {
            int conexiones = 0;
            for (int j = 0; j < NUMERO_DE_PERSONAS; ++j) {
                if (matriz_adyacencia[i][j]) conexiones++;
            }
            conexiones_por_persona.push_back({i, conexiones});
        }
        sort(conexiones_por_persona.begin(), conexiones_por_persona.end(), 
             [](auto& a, auto& b) { return a.second > b.second; });
        
        vector<int> top_ids;
        for (int i = 0; i < min(top_n, (int)conexiones_por_persona.size()); ++i) {
            top_ids.push_back(conexiones_por_persona[i].first);
        }
        return top_ids;
    }

    void asignar_ciudades_aleatorias(const vector<string>& ciudades) {
        for (int i = 0; i < NUMERO_DE_PERSONAS; ++i) {
            int idx_ciudad = rand() % ciudades.size();
            persona_a_ciudad[i] = ciudades[idx_ciudad];
        }
    }

    string obtener_ciudad(int id_persona) {
        return persona_a_ciudad[id_persona];
    }
};

//PARTE 2: Red Logística
struct Ruta {
    int costo;
    bool es_duplicada;

    Ruta(int costo = 0, bool es_duplicada = false) {
        this->costo = costo;
        this->es_duplicada = es_duplicada;
    }
};

class RedLogistica {
private:
    int presupuesto_maximo;
    int ciudad_inicial_id;

    vector<string> ciudades = {
        "Bogota", "Cali", "Chia", "Cajica", "Sopo",
        "Tabio", "Medellin", "Fusagasugá", "Cartagena", "Barranquilla"
    };

    map<string, int> ciudad_a_id;
    map<int, string> id_a_ciudad;

    vector<vector<Ruta>> matriz_de_adyacencia;

public:
    RedLogistica(int presupuesto_maximo, const string& ciudad_inicial) {
        this->presupuesto_maximo = presupuesto_maximo;
        inicializar_ciudades();
        ciudad_inicial_id = ciudad_a_id[ciudad_inicial];
        matriz_de_adyacencia.resize(ciudades.size(), vector<Ruta>(ciudades.size()));
    }

    void inicializar_ciudades() {
        for (int i = 0; i < ciudades.size(); i++) {
            ciudad_a_id[ciudades[i]] = i;
            id_a_ciudad[i] = ciudades[i];
        }
    }

    void agregar_ruta(const string& ciudad_a, const string& ciudad_b, int costo) {
        int a = ciudad_a_id[ciudad_a];
        int b = ciudad_a_id[ciudad_b];
        matriz_de_adyacencia[a][b] = Ruta(costo);
        matriz_de_adyacencia[b][a] = Ruta(costo);
    }

    vector<int> encontrar_nodos_con_grado_impar() {
        vector<int> nodos_impares;
        for (int i = 0; i < ciudades.size(); i++) {
            int grado = 0;
            for (int j = 0; j < ciudades.size(); j++) {
                if (matriz_de_adyacencia[i][j].costo > 0) {
                    grado++;
                }
            }
            if (grado % 2 != 0) {
                nodos_impares.push_back(i);
            }
        }
        return nodos_impares;
    }

    void duplicar_ruta(int a, int b) {
        matriz_de_adyacencia[a][b].es_duplicada = true;
        matriz_de_adyacencia[b][a].es_duplicada = true;
    }

    void hacer_grafo_euleriano() {
        vector<int> nodos_impares = encontrar_nodos_con_grado_impar();

        while (nodos_impares.size() >= 2) {
            int nodo1 = nodos_impares.back(); nodos_impares.pop_back();
            int nodo2 = nodos_impares.back(); nodos_impares.pop_back();
            duplicar_ruta(nodo1, nodo2);
        }
    }

    void priorizar_ciudades(const vector<string>& ciudades_prioritarias) {
        for (const auto& ciudad : ciudades_prioritarias) {
            int id = ciudad_a_id[ciudad];
            for (int j = 0; j < ciudades.size(); ++j) {
                if (matriz_de_adyacencia[id][j].costo > 0) {
                    matriz_de_adyacencia[id][j].costo = int(matriz_de_adyacencia[id][j].costo * 0.8); // 20% de descuento
                }
            }
        }
    }

    void optimizar_ruta() {
        vector<bool> en_mst(ciudades.size(), false);
        vector<int> clave(ciudades.size(), INT_MAX);
        vector<int> padre(ciudades.size(), -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, ciudad_inicial_id});
        clave[ciudad_inicial_id] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            en_mst[u] = true;

            for (int v = 0; v < ciudades.size(); ++v) {
                int costo = matriz_de_adyacencia[u][v].costo;
                if (costo > 0 && !en_mst[v] && costo < clave[v]) {
                    clave[v] = costo;
                    padre[v] = u;
                    pq.push({clave[v], v});
                }
            }
        }
    }

    void recorrer_ruta_euleriana() {
        vector<vector<Ruta>> copia = matriz_de_adyacencia;
        vector<int> pila;
        vector<int> recorrido;
        pila.push_back(ciudad_inicial_id);

        while (!pila.empty()) {
            int actual = pila.back();
            bool encontrada = false;
            for (int i = 0; i < ciudades.size(); i++) {
                if (copia[actual][i].costo > 0) {
                    pila.push_back(i);
                    copia[actual][i].costo = 0;
                    copia[i][actual].costo = 0;
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada) {
                recorrido.push_back(actual);
                pila.pop_back();
            }
        }

        int costo_total = 0;
        map<int, int> visitas;

        cout << "Ruta del cartero (Euleriana): ";
        for (int i = recorrido.size() - 1; i >= 0; i--) {
            cout << id_a_ciudad[recorrido[i]];
            if (i > 0) cout << " -> ";
            visitas[recorrido[i]]++;
        }
        cout << endl;

        for (int i = recorrido.size() - 1; i > 0; i--) {
            int a = recorrido[i];
            int b = recorrido[i - 1];

            int costo = matriz_de_adyacencia[a][b].costo;
            if (matriz_de_adyacencia[a][b].es_duplicada) {
                costo = int(costo * 1.3);
            }
            costo_total += costo;
        }

        cout << "Costo total del recorrido: " << costo_total << endl;

        if (costo_total > presupuesto_maximo) {
            cout << "ADVERTENCIA: Se superó el presupuesto máximo.\n";
        }

        for (auto& par : visitas) {
            if (par.first != ciudad_inicial_id && par.second > 2) {
                cout << "RESTRICCION VIOLADA: " << id_a_ciudad[par.first]
                     << " fue visitada más de 2 veces.\n";
            }
        }
    }

    void imprimir_matriz_adyacencia() {
        cout << "\nMatriz de Adyacencia (costos):\n\n";

        if (ciudades.empty()) {
            cout << "No hay ciudades para mostrar.\n";
            return;
        }
        int max_ancho_nombre = 10;
        for (const auto& nombre : ciudades) {
            if (!nombre.empty() && nombre.size() > max_ancho_nombre) {
                max_ancho_nombre = nombre.size();
            }
        }
        max_ancho_nombre += 5;

        int max_ancho_costo = 10;
        for (int i = 0; i < ciudades.size(); i++) {
            for (int j = 0; j < ciudades.size(); j++) {
                int costo = matriz_de_adyacencia[i][j].costo;
                if (costo != 0) {
                    int digitos = to_string(costo).size();
                    if (digitos > max_ancho_costo) {
                        max_ancho_costo = digitos;
                    }
                }
            }
        }
        max_ancho_costo += 2;

        cout << string(max_ancho_nombre, ' ');
        for (const auto& nombre : ciudades) {
            cout << nombre;
            int espacios = max_ancho_costo - nombre.size();
            if (espacios > 0) cout << string(espacios, ' ');
        }
        cout << endl;

        for (int i = 0; i < ciudades.size(); i++) {
            cout << ciudades[i];
            int espacios_nombre = max_ancho_nombre - ciudades[i].size();
            if (espacios_nombre > 0) cout << string(espacios_nombre, ' ');

            for (int j = 0; j < ciudades.size(); j++) {
                int costo = matriz_de_adyacencia[i][j].costo;
                string texto = (costo == 0) ? "0" : to_string(costo);
                cout << texto;
                int espacios_costo = max_ancho_costo - texto.size();
                if (espacios_costo > 0) cout << string(espacios_costo, ' ');
            }
            cout << endl;
        }
        cout << endl;
    }
};

// ------------------------- MAIN: Integración -------------------------
int main() {
    // Parte 1: Red Social
    RedSocial red_social;
    vector<int> influencers = red_social.top_influencers();
    red_social.asignar_ciudades_aleatorias({
        "Bogota", "Cali", "Chia", "Cajica", "Sopo",
        "Tabio", "Medellin", "Fusagasugá", "Cartagena", "Barranquilla"
    });

    vector<string> ciudades_prioritarias;
    for (int id : influencers) {
        ciudades_prioritarias.push_back(red_social.obtener_ciudad(id));
    }

    // Parte 2: Red Logística
    RedLogistica red_logistica(400, "Bogota");


    red_logistica.agregar_ruta("Bogota", "Chia", 15);
    red_logistica.agregar_ruta("Bogota", "Cali", 50);
    red_logistica.agregar_ruta("Chia", "Cajica", 10);
    red_logistica.agregar_ruta("Cajica", "Sopo", 12);
    red_logistica.agregar_ruta("Sopo", "Tabio", 8);
    red_logistica.agregar_ruta("Tabio", "Bogota", 18);
    red_logistica.agregar_ruta("Bogota", "Fusagasugá", 20);
    red_logistica.agregar_ruta("Fusagasugá", "Medellin", 40);
    red_logistica.agregar_ruta("Medellin", "Cartagena", 35);
    red_logistica.agregar_ruta("Cartagena", "Barranquilla", 15);
    red_logistica.agregar_ruta("Barranquilla", "Bogota", 60);
   
    cout << "Matriz de Adyacencia costos sin prioridades:\n\n";
    red_logistica.imprimir_matriz_adyacencia();
    red_logistica.hacer_grafo_euleriano();
    red_logistica.recorrer_ruta_euleriana();
    
    cout << "\n\nMatriz de Adyacencia costos con prioridades:\n\n";
    // Parte 3: Optimización de ruta
    red_logistica.priorizar_ciudades(ciudades_prioritarias);
    red_logistica.optimizar_ruta();

    red_logistica.imprimir_matriz_adyacencia();
    red_logistica.hacer_grafo_euleriano();
    red_logistica.recorrer_ruta_euleriana();

    return 0;
}