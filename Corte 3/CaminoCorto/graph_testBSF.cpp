#include <iostream>
#include <string>
#include <set>
#include <map>
// #include "graph_set.h"
#include "graph_mat.h"
// #include "graph_list.h"

/*
* Este programa inicializa in grafo del ejemplo de la aerolinea
* y muestra la lista de adyacencia de las ciudades
*/

void printAdjacencyList(const Graph<std::string, int>& graph) {
    for (const auto& node : graph.getNodes()) {
        std::cout << node << " --> ";
        
        // Obtener los arcos del nodo y recorrerlos
        const auto& edges = graph.getEdges(node);
        bool first = true;
        
        for (const auto& edge : edges) {
            if (!first) {
                std::cout << " --> ";
            }
            std::cout << edge.first << "(" << edge.second << ")";
            first = false;
        }
        
        std::cout << std::endl;
    }
}




void initAirlineGraph(Graph<std::string, int>& airlineGraph) {
    airlineGraph.addNode("Atlanta");
    airlineGraph.addNode("Boston");
    airlineGraph.addNode("Chicago");
    airlineGraph.addNode("Dallas");
    airlineGraph.addNode("Denver");
    airlineGraph.addNode("Los Angeles");
    airlineGraph.addNode("New York");
    airlineGraph.addNode("Portland");
    airlineGraph.addNode("San Francisco");
    airlineGraph.addNode("Seattle");

    airlineGraph.addEdge("Atlanta", "Chicago", 599);
    airlineGraph.addEdge("Atlanta", "Dallas", 725);
    airlineGraph.addEdge("Atlanta", "New York", 756);
    airlineGraph.addEdge("Boston", "New York", 191);
    airlineGraph.addEdge("Boston", "Seattle", 2489);
    airlineGraph.addEdge("Chicago", "Denver", 907);
    airlineGraph.addEdge("Dallas", "Denver", 650);
    airlineGraph.addEdge("Dallas", "Los Angeles", 1240);
    airlineGraph.addEdge("Dallas", "San Francisco", 1468);
    airlineGraph.addEdge("Denver", "San Francisco", 954);
    airlineGraph.addEdge("Portland", "San Francisco", 550);
    airlineGraph.addEdge("Portland", "Seattle", 130);
}

void testIsConnected(const Graph<std::string, int>& graph) {
    if (graph.isConnected()) {
        std::cout << "El grafo es conexo." << std::endl;
    } else {
        std::cout << "El grafo no es conexo." << std::endl;
    }
}

void testBfsPath(const Graph<std::string, int>& graph, const std::string& start, const std::string& goal) {
    auto [edgeCount, path] = graph.bfsPath(start, goal);
    if (path.empty()) {
        std::cout << "No existe un camino de " << start << " a " << goal << "." << std::endl;
    } else {
        std::cout << "Camino más corto de " << start << " a " << goal << ":\n";
        std::cout << "Número de aristas: " << edgeCount << "\nCamino: ";
        for (const auto& city : path) {
            std::cout << city;
            if (city != path.back()) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}



int main() {
    Graph<std::string, int> airlineGraph;
    initAirlineGraph(airlineGraph);
    printAdjacencyList(airlineGraph);

    // Prueba de la función isConnected
    testIsConnected(airlineGraph);

    // Prueba de la función bfsPath entre dos ciudades
    testBfsPath(airlineGraph, "Atlanta", "San Francisco");
    testBfsPath(airlineGraph, "Dallas", "Seattle");
   
    return 0;
}