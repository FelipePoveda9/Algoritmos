#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>

template <typename T, typename WeightType>
class Graph {

    private:
        std::map<std::pair<T, T>, WeightType> edges;
        std::set<T> nodes;

        // Función auxiliar para realizar el recorrido BFS y devolver los nodos alcanzables y predecesores
        std::unordered_map<T, T> bfsReachable(const T& start, std::unordered_map<T, bool>& visited) const 
        {
            std::unordered_map<T, T> predecessor; // Para rastrear el camino en bfsPath
            std::queue<T> queue;
            
            visited[start] = true;
            queue.push(start);
            predecessor[start] = start;

            while (!queue.empty()) {
                T current = queue.front();
                queue.pop();

                for (const auto& [neighbor, weight] : getEdges(current)) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        queue.push(neighbor);
                        predecessor[neighbor] = current;
                    }
                }
            }
            
            return predecessor;
        }

    public:
    // Constructor
    Graph() = default;

    // Constructor de copia
    Graph(const Graph<T, WeightType>& other): edges(other.edges), nodes(other.nodes) {}

    // Operador de asignación de copia  
    Graph<T, WeightType>& operator=(const Graph<T, WeightType>& other) {
        if (this != &other) { // Evitar autoasignación
            nodes = other.nodes;
            edges = other.edges;
        }
        return *this;
    }

    // constructor de movimiento
    Graph(Graph<T, WeightType>&& other): edges(std::move(other.edges)), nodes(std::move(other.nodes)) {}

    // Operador de asignación de movimiento
    Graph<T, WeightType>& operator=(Graph<T, WeightType>&& other) {
        if (this != &other) { // Evitar autoasignación
            nodes = std::move(other.nodes);
            edges = std::move(other.edges);
        }
        return *this;
    }

    // Destructor
    ~Graph() = default;

    // método para agregar un nodo al grafo
    void addNode(const T& node) {
        nodes.insert(node);
    }

    // método para agregar una arista al grafo con peso (opcional por defecto 1), da la opcion de hacerla bidereccional o no
    void addEdge(const T& from, const T& to, const WeightType& weight, bool bidirectional = true) {
        edges[{from, to}] = weight;
        if (bidirectional) {
            edges[{to, from}] = weight;
        }
    }

    // método para actualizar el peso de una arista existente si no existe lo crea
    void updateEdge(const T& from, const T& to, const WeightType& weight) {
        auto it = edges.find({from, to});
        if (it != edges.end()) {
            it->second = weight;
        } else {
            addEdge(from, to, weight);
        }
    }
    
    // funcion getter para obtener los nodos del grafo
    const std::set<T>& getNodes() const {
        return nodes;
    }

    // Funcion getter para obtener las aristas de un nodo
    const std::map<T, WeightType> getEdges(const T& node) const {
        std::map<T, WeightType> result;
        for (const auto& edge : edges) {
            if (edge.first.first == node) {
                result[edge.first.second] = edge.second;
            }
        }
        return result;
    }

    // Funcion getter para obtener el peso de una arista
    WeightType getWeight(const T& from, const T& to) const {
        auto it = edges.find({from, to});
        if (it != edges.end()) {
            return it->second;
        }
        return WeightType();
    }

    // Funcion para verificar si el grafo es conexo
    bool isConnected() const {
        if (nodes.empty()) {
            return true; // Un grafo vacío se considera conexo
        }
        
        std::unordered_map<T, bool> visited;
        T start = *nodes.begin();
        
        // Llamamos a bfsReachable desde un nodo arbitrario y revisamos si todos los nodos se visitaron
        bfsReachable(start, visited);
        
        for (const auto& node : nodes) {
            if (!visited[node]) {
                return false; // Si algún nodo no fue visitado, el grafo no es conexo
            }
        }
        
        return true; // Todos los nodos fueron visitados, el grafo es conexo
    }

     // Método BFS que encuentra el camino más corto en términos de aristas usando bfsReachable
     std::pair<int, std::vector<T>> bfsPath(const T& start, const T& goal) const
     {
        std::unordered_map<T, bool> visited;
        std::unordered_map<T, T> predecessor = bfsReachable(start, visited);
        
        if (!visited[goal]) {
            return {0, {}};
        }
        
        std::vector<T> path;
        T current = goal;
        while (current != start) {
            path.push_back(current);
            current = predecessor[current];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        
        return {path.size() - 1, path};
     }



    

};


#endif // _GRAPH_H