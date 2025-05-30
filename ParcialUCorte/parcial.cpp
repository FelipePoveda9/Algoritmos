#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <unordered_map>
#include <queue>
#include <stack>
#include <set>

using namespace std;

// Clase Valoracion: representa una valoración hecha por un usuario con un puntaje de 1 a 10
class Valoracion {
    int idUsuario;
    int puntaje;

public:
    Valoracion(int id, int p) : idUsuario(id), puntaje(p) {}
    int getUsuario() const { return idUsuario; }
    int getPuntaje() const { return puntaje; }
};

// Clase Contenido: representa un contenido generado por un usuario
class Contenido {
    int idCreador;
    vector<Valoracion> valoraciones;

public:
    Contenido(int id) : idCreador(id) {}

    void agregarValoracion(int idUsuario, int puntaje) {
        valoraciones.emplace_back(idUsuario, puntaje);
    }

    const vector<Valoracion>& getValoraciones() const {
        return valoraciones;
    }
};

// Clase Usuario: representa un usuario con ID, conexiones y contenidos creados
class Usuario {
    int id;
    vector<int> conexiones;
    vector<Contenido> contenidos;

public:
    Usuario(int id_) : id(id_) {}

    int getId() const { return id; }

    void agregarConexion(int idUsuario) {
        conexiones.push_back(idUsuario);
    }

    void agregarContenido(const Contenido& contenido) {
        contenidos.push_back(contenido);
    }

    const vector<int>& getConexiones() const { return conexiones; }
    const vector<Contenido>& getContenidos() const { return contenidos; }
};

// Clase principal MediaNest que contiene la lógica del programa
class MediaNest {
    vector<Usuario> usuarios;
    vector<vector<bool>> matrizAdyacencia;

public:
    MediaNest() {
        srand(time(0));

        // Crear 1000 usuarios con IDs de 0 a 999
        usuarios.reserve(1000);
        matrizAdyacencia.resize(1000, vector<bool>(1000, false));
        for (int i = 0; i < 1000; ++i) {
            usuarios.emplace_back(i);
        }

        // Generar conexiones entre usuarios (entre 1 y 30 conexiones únicas)
        for (int i = 0; i < 1000; ++i) {
            set<int> conexionesUnicas;
            int numConexiones = rand() % 30 + 1;

            while (conexionesUnicas.size() < numConexiones) {
                int conectado = rand() % 1000;
                if (conectado != i && !matrizAdyacencia[i][conectado]) {
                    conexionesUnicas.insert(conectado);
                    matrizAdyacencia[i][conectado] = matrizAdyacencia[conectado][i] = true;
                    usuarios[i].agregarConexion(conectado);
                    usuarios[conectado].agregarConexion(i);
                }
            }
        }

        // Generar contenidos y valoraciones
        for (int i = 0; i < 1000; ++i) {
            int numContenidos = rand() % 500 + 1;
            for (int j = 0; j < numContenidos; ++j) {
                Contenido c(i);
                int numValoraciones = rand() % 50 + 1;
                for (int k = 0; k < numValoraciones; ++k) {
                    int usuarioValorador = rand() % 1000;
                    int puntaje = rand() % 10 + 1;
                    c.agregarValoracion(usuarioValorador, puntaje);
                }
                usuarios[i].agregarContenido(c);
            }
        }
    }

    // Método requerido para encontrar el usuario con más conexiones y altura del grafo desde ese nodo
    void most_connected() {
        int maxConexiones = -1, idMax = -1;
        for (const auto& u : usuarios) {
            int conexiones = u.getConexiones().size();
            if (conexiones > maxConexiones) {
                maxConexiones = conexiones;
                idMax = u.getId();
            }
        }

        // Calcular altura con DFS desde idMax
        vector<bool> visitado(1000, false);
        int altura = dfs(idMax, visitado);

        cout << "El usuario con más conexiones es " << idMax << " con " << maxConexiones << " conexiones" << endl;
        cout << "La altura del grafo desde el nodo " << idMax << " es " << altura << endl;
    }

    // DFS para calcular altura
    int dfs(int nodo, vector<bool>& visitado) {
        visitado[nodo] = true;
        int total = 1;
        for (int i = 0; i < 1000; ++i) {
            if (matrizAdyacencia[nodo][i] && !visitado[i]) {
                total += dfs(i, visitado);
            }
        }
        return total;
    }

    // Método requerido para encontrar el usuario que más valoraciones positivas ha dado
    void mostPositiveRaters() {
        unordered_map<int, int> contador;

        for (const auto& u : usuarios) {
            for (const auto& c : u.getContenidos()) {
                for (const auto& v : c.getValoraciones()) {
                    if (v.getPuntaje() >= 7) {
                        contador[v.getUsuario()]++;
                    }
                }
            }
        }

        int maxPos = -1, idMax = -1;
        for (const auto& p : contador) {
            if (p.second > maxPos) {
                maxPos = p.second;
                idMax = p.first;
            }
        }

        cout << "El usuario que más valoraciones positivas ha dado es " << idMax
             << " con " << maxPos << " valoraciones >= 7" << endl;
    }

    // Método requerido para encontrar el vecino más lejano desde A con BFS
    void farthest_neighbor(int A) {
        vector<int> dist(1000, -1);
        queue<int> q;
        q.push(A);
        dist[A] = 0;

        int maxDist = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 1000; ++i) {
                if (matrizAdyacencia[u][i] && dist[i] == -1) {
                    dist[i] = dist[u] + 1;
                    maxDist = max(maxDist, dist[i]);
                    q.push(i);
                }
            }
        }

        cout << "El vecino más lejano del usuario " << A << " está a " << maxDist << " saltos" << endl;
    }

    // Método requerido para verificar si existe un camino entre A y B pasando por C y con máximo 7 saltos
    void pathWithIntermediate(int A, int B, int C) {
        int distAC = bfs_distance(A, C);
        int distCB = bfs_distance(C, B);
        int totalDist = (distAC != -1 && distCB != -1) ? distAC + distCB : -1;

        if (totalDist != -1 && totalDist <= 7) {
            cout << "Existe un camino entre " << A << " y " << B
                 << " pasando por " << C << " con distancia de " << totalDist << " saltos" << endl;
        } else {
            cout << "No existe un camino válido entre " << A << " y " << B
                 << " pasando por " << C << " con máximo 7 saltos" << endl;
        }
    }

    // BFS para calcular distancia entre dos nodos
    int bfs_distance(int start, int end) {
        vector<int> dist(1000, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == end) return dist[u];
            for (int i = 0; i < 1000; ++i) {
                if (matrizAdyacencia[u][i] && dist[i] == -1) {
                    dist[i] = dist[u] + 1;
                    q.push(i);
                }
            }
        }
        return -1;
    }
};

int main() {
    MediaNest app;
    cout << "Se crearon 1000 usuarios" << endl;
    app.most_connected();
    app.mostPositiveRaters();
    int A = 47, B = 907, C = 274;
    app.farthest_neighbor(A);
    app.pathWithIntermediate(A, B, C);
    return 0;
}
