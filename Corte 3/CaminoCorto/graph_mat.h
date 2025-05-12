#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>

template <typename T, typename WeightType>
class Graph {

private:
    std::vector<std::vector<WeightType>> adjacencyMatrix;
    std::map<T, int> nodeIndex; // Mapea cada nodo a un índice de la matriz
    std::vector<T> indexNode;    // Permite recuperar el nodo original a partir de un índice
    int nextIndex = 0;           // Lleva la cuenta del siguiente índice disponible para un nuevo nodo
    WeightType maxWeight = std::numeric_limits<WeightType>::max(); // Representa una conexión inexistente

    // Función auxiliar para realizar el recorrido BFS y devolver los nodos alcanzables y predecesores
    std::unordered_map<int, int> bfsReachable(int start, std::vector<bool>& visited) const {
        std::unordered_map<int, int> predecessor;
        std::queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        predecessor[start] = start;

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            // Explorar los vecinos de 'current'
            for (int neighbor = 0; neighbor < adjacencyMatrix[current].size(); ++neighbor) {
                if (adjacencyMatrix[current][neighbor] != maxWeight && !visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                    predecessor[neighbor] = current;
                }
            }
        }
        
        return predecessor;
    }

    

public:
    // Constructor por defecto
    Graph() = default;

    // Constructor de copia
    Graph(const Graph<T, WeightType>& other) 
        : adjacencyMatrix(other.adjacencyMatrix),
          nodeIndex(other.nodeIndex),
          indexNode(other.indexNode),
          nextIndex(other.nextIndex),
          maxWeight(other.maxWeight) {}

    // Operador de asignación de copia
    Graph<T, WeightType>& operator=(const Graph<T, WeightType>& other) {
        if (this != &other) { // Evitar autoasignación
            adjacencyMatrix = other.adjacencyMatrix;
            nodeIndex = other.nodeIndex;
            indexNode = other.indexNode;
            nextIndex = other.nextIndex;
            maxWeight = other.maxWeight;
        }
        return *this;
    }

    // Constructor de movimiento
    Graph(Graph<T, WeightType>&& other) noexcept
        : adjacencyMatrix(std::move(other.adjacencyMatrix)),
          nodeIndex(std::move(other.nodeIndex)),
          indexNode(std::move(other.indexNode)),
          nextIndex(other.nextIndex),
          maxWeight(other.maxWeight) {
        other.nextIndex = 0; // Opcional: restablecer el estado de 'other'
    }

    // Operador de asignación de movimiento
    Graph<T, WeightType>& operator=(Graph<T, WeightType>&& other) noexcept {
        if (this != &other) { // Evitar autoasignación
            adjacencyMatrix = std::move(other.adjacencyMatrix);
            nodeIndex = std::move(other.nodeIndex);
            indexNode = std::move(other.indexNode);
            nextIndex = other.nextIndex;
            maxWeight = other.maxWeight;

            other.nextIndex = 0; // Opcional: restablecer el estado de 'other'
        }
        return *this;
    }

    // Destructor
    ~Graph() = default;

    // Método para agregar un nodo al grafo
    void addNode(const T& node) {
        if (nodeIndex.find(node) == nodeIndex.end()) {
            nodeIndex[node] = nextIndex;
            indexNode.push_back(node);
            nextIndex++;
            
            // Expande la matriz de adyacencia
            for (auto& row : adjacencyMatrix) {
                row.push_back(maxWeight); // Añade "no conexión" para nuevas columnas
            }
            adjacencyMatrix.push_back(std::vector<WeightType>(nextIndex, maxWeight)); // Nueva fila
        }
    }

    // Método para agregar una arista con opción de bidireccionalidad
    void addEdge(const T& from, const T& to, const WeightType& weight, bool bidirectional = true) {
        addNode(from);
        addNode(to);
        int fromIdx = nodeIndex[from];
        int toIdx = nodeIndex[to];
        
        adjacencyMatrix[fromIdx][toIdx] = weight;
        if (bidirectional) {
            adjacencyMatrix[toIdx][fromIdx] = weight;
        }
    }

    // Método para actualizar el peso de una arista existente (si no existe lo crea)
    void updateEdge(const T& from, const T& to, const WeightType& weight) {
        addEdge(from, to, weight);
    }
    
    // Función para obtener todos los nodos del grafo
    const std::vector<T>& getNodes() const {
        return indexNode;
    }

    // Función para obtener las aristas de un nodo específico
    std::vector<std::pair<T, WeightType>> getEdges(const T& node) const {
        std::vector<std::pair<T, WeightType>> edges;
        if (nodeIndex.find(node) != nodeIndex.end()) {
            int nodeIdx = nodeIndex.at(node);
            for (size_t i = 0; i < adjacencyMatrix[nodeIdx].size(); ++i) {
                if (adjacencyMatrix[nodeIdx][i] != maxWeight) {
                    edges.emplace_back(indexNode[i], adjacencyMatrix[nodeIdx][i]);
                }
            }
        }
        return edges;
    }


    // Función para verificar si el grafo es conexo
    bool isConnected() const {
        if (indexNode.empty()) {
            return true; // Un grafo vacío se considera conexo
        }
        
        std::vector<bool> visited(nextIndex, false);
        int start = 0; // Comenzamos en el primer nodo

        bfsReachable(start, visited);
        
        for (bool nodeVisited : visited) {
            if (!nodeVisited) {
                return false; // Si algún nodo no fue visitado, el grafo no es conexo
            }
        }
        
        return true; // Todos los nodos fueron visitados, el grafo es conexo
    }

    // Método BFS que encuentra el camino más corto en términos de aristas usando bfsReachable
    std::pair<int, std::vector<T>> bfsPath(const T& startNode, const T& goalNode) const {
        if (nodeIndex.find(startNode) == nodeIndex.end() || nodeIndex.find(goalNode) == nodeIndex.end()) {
            return {0, {}}; // Si alguno de los nodos no está en el grafo
        }

        int start = nodeIndex.at(startNode);
        int goal = nodeIndex.at(goalNode);

        std::vector<bool> visited(nextIndex, false);
        std::unordered_map<int, int> predecessor = bfsReachable(start, visited);
        
        if (!visited[goal]) {
            return {0, {}}; // No hay camino si el objetivo no fue alcanzado
        }
        
        std::vector<T> path;
        for (int current = goal; current != start; current = predecessor[current]) {
            path.push_back(indexNode[current]);
        }
        path.push_back(indexNode[start]);
        std::reverse(path.begin(), path.end());
        
        return {path.size() - 1, path};
    }
    
};

#endif // _GRAPH_H
