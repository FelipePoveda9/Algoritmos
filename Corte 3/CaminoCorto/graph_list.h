#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <map>
#include <list>
#include <set>
#include <utility>
#include <limits>

template <typename T, typename WeightType>
class Graph {

private:
    std::map<T, std::list<std::pair<T, WeightType>>> adjacencyList; // Lista de adyacencia

public:
    // Constructor por defecto
    Graph() = default;

    // Constructor de copia
    Graph(const Graph<T, WeightType>& other) : adjacencyList(other.adjacencyList) {}

    // Operador de asignación de copia
    Graph<T, WeightType>& operator=(const Graph<T, WeightType>& other) {
        if (this != &other) { // Evitar autoasignación
            adjacencyList = other.adjacencyList;
        }
        return *this;
    }

    // Constructor de movimiento
    Graph(Graph<T, WeightType>&& other) noexcept
        : adjacencyList(std::move(other.adjacencyList)) {}

    // Operador de asignación de movimiento
    Graph<T, WeightType>& operator=(Graph<T, WeightType>&& other) noexcept {
        if (this != &other) { // Evitar autoasignación
            adjacencyList = std::move(other.adjacencyList);
        }
        return *this;
    }

    // Destructor
    ~Graph() = default;

    // Método para agregar un nodo al grafo
    void addNode(const T& node) {
        if (adjacencyList.find(node) == adjacencyList.end()) {
            adjacencyList[node]; // Crea una entrada vacía para el nodo
        }
    }

    // Método para agregar una arista con opción de bidireccionalidad
    void addEdge(const T& from, const T& to, const WeightType& weight, bool bidirectional = true) {
        addNode(from);
        addNode(to);
        adjacencyList[from].emplace_back(to, weight);
        if (bidirectional) {
            adjacencyList[to].emplace_back(from, weight);
        }
    }

    // Método para actualizar el peso de una arista existente
    void updateEdge(const T& from, const T& to, const WeightType& weight, bool bidirectional = true) {
        auto update = [&](const T& src, const T& dest) {
            auto& edges = adjacencyList[src];
            for (auto& edge : edges) {
                if (edge.first == dest) {
                    edge.second = weight;
                    return;
                }
            }
            edges.emplace_back(dest, weight); // Agrega la arista si no existe
        };
        update(from, to);
        if (bidirectional) {
            update(to, from);
        }
    }
    
    // Función para obtener todos los nodos del grafo
    std::set<T> getNodes() const {
        std::set<T> nodes;
        for (const auto& pair : adjacencyList) {
            nodes.insert(pair.first);
        }
        return nodes;
    }

    // Función para obtener las aristas de un nodo específico
    std::list<std::pair<T, WeightType>> getEdges(const T& node) const {
        if (adjacencyList.find(node) != adjacencyList.end()) {
            return adjacencyList.at(node);
        }
        return {}; // Retorna una lista vacía si el nodo no tiene aristas
    }
};

#endif // _GRAPH_H
