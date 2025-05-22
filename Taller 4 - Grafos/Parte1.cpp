#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>

using namespace std;

const int NUMERO_DE_PERSONAS = 1000;

class RedSocial {
private:
    bool matriz_adyacencia[NUMERO_DE_PERSONAS][NUMERO_DE_PERSONAS];
    vector<vector<int>> reacciones_por_persona;

    int valor_absoluto(int numero) {
        return (numero < 0) ? -numero : numero;
    }

    int maximo(int a, int b) {
        return (a > b) ? a : b;
    }

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

    int altura_dfs(int nodo, vector<bool>& visitado) {
        visitado[nodo] = true;
        int altura = 0;
        for (int vecino = 0; vecino < NUMERO_DE_PERSONAS; ++vecino) {
            if (matriz_adyacencia[nodo][vecino] && !visitado[vecino]) {
                int nueva_altura = 1 + altura_dfs(vecino, visitado);
                altura = maximo(altura, nueva_altura);
            }
        }
        return altura;
    }

    bool bfs_con_intermedio(int inicio, int intermedio, int fin) {
        queue<pair<int, int>> cola;
        vector<bool> visitado(NUMERO_DE_PERSONAS, false);

        cola.push({inicio, 0});
        visitado[inicio] = true;

        while (!cola.empty()) {
            int actual = cola.front().first;
            int saltos = cola.front().second;
            cola.pop();

            if (saltos > 7) return false;

            if (actual == intermedio) {
                queue<pair<int, int>> cola2;
                vector<bool> visitado2(NUMERO_DE_PERSONAS, false);
                cola2.push({intermedio, saltos});
                visitado2[intermedio] = true;

                while (!cola2.empty()) {
                    int nodo2 = cola2.front().first;
                    int saltos2 = cola2.front().second;
                    cola2.pop();

                    if (saltos2 > 7) return false;
                    if (nodo2 == fin) return true;

                    for (int vecino = 0; vecino < NUMERO_DE_PERSONAS; ++vecino) {
                        if (matriz_adyacencia[nodo2][vecino] && !visitado2[vecino]) {
                            visitado2[vecino] = true;
                            cola2.push({vecino, saltos2 + 1});
                        }
                    }
                }
                return false;
            }

            for (int vecino = 0; vecino < NUMERO_DE_PERSONAS; ++vecino) {
                if (matriz_adyacencia[actual][vecino] && !visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push({vecino, saltos + 1});
                }
            }
        }

        return false;
    }

public:
    RedSocial() {
        srand(time(0));
        generar_conexiones();
        generar_reacciones();
    }

    void most_connected() {
        int persona_max = -1;
        int max_conexiones = -1;
        for (int persona = 0; persona < NUMERO_DE_PERSONAS; ++persona) {
            int conteo = 0;
            for (int j = 0; j < NUMERO_DE_PERSONAS; ++j) {
                if (matriz_adyacencia[persona][j]) conteo++;
            }
            if (conteo > max_conexiones) {
                max_conexiones = conteo;
                persona_max = persona;
            }
        }

        vector<bool> visitado(NUMERO_DE_PERSONAS, false);
        int altura = altura_dfs(persona_max, visitado);

        cout << "Persona con más conexiones: " << persona_max << " (" << max_conexiones << " conexiones)\n";
        cout << "Altura del grafo desde esta persona: " << altura << "\n";
    }

    void most_positive_reactions() {
        int persona_max = -1;
        int total_max = -1;
        for (int persona = 0; persona < NUMERO_DE_PERSONAS; ++persona) {
            int suma = 0;
            for (int r : reacciones_por_persona[persona]) {
                if (r > 0) suma += r;
            }
            if (suma > total_max) {
                total_max = suma;
                persona_max = persona;
            }
        }

        cout << "Persona que emitió más reacciones positivas: " << persona_max << " (+" << total_max << ")\n";
    }

    void farthest_neighbor(int inicio) {
        vector<bool> visitado(NUMERO_DE_PERSONAS, false);
        queue<pair<int, int>> cola;
        cola.push({inicio, 0});
        visitado[inicio] = true;

        int nodo_mas_lejano = inicio;
        int distancia_max = 0;

        while (!cola.empty()) {
            int actual = cola.front().first;
            int dist = cola.front().second;
            cola.pop();

            if (dist > distancia_max) {
                distancia_max = dist;
                nodo_mas_lejano = actual;
            }

            for (int vecino = 0; vecino < NUMERO_DE_PERSONAS; ++vecino) {
                if (matriz_adyacencia[actual][vecino] && !visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push({vecino, dist + 1});
                }
            }
        }

        cout << "Vecino más lejano desde " << inicio << ": " << nodo_mas_lejano << " (distancia = " << distancia_max << ")\n";
    }

    void path_with_intermediate(int inicio, int fin, int intermedio) {
        bool existe = bfs_con_intermedio(inicio, intermedio, fin);
        if (existe)
            cout << "Existe un camino entre " << inicio << " y " << fin << " pasando por " << intermedio << " en máximo 7 saltos.\n";
        else
            cout << "No existe tal camino entre " << inicio << " y " << fin << " pasando por " << intermedio << " en máximo 7 saltos.\n";
    }
};

int main() {
    RedSocial red;
    cout << "Análisis de Red Social Interna\n\n";

    red.most_connected();
    cout << "\n";

    red.most_positive_reactions();
    cout << "\n";

    red.farthest_neighbor(100);
    cout << "\n";

    red.path_with_intermediate(0, 100, 50);
    cout << "\n";

    return 0;
}
