// gabi.rayman@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace graph {
    Graph::Graph(int size) {
        if (size <= 0) {
            throw std::invalid_argument("Graph size must be positive.");
        }

        verteciesCount = size;
        verticies = new Vertex[verteciesCount];
        for (int i=0; i < verteciesCount; i++) { //verticies[i] is a Vertex struct object
            verticies[i].id = i+1;
            verticies[i].edgeCount = 0;
            verticies[i].edges = nullptr;
        }
    }

    Graph::Graph(const Graph& other) {
        verteciesCount = other.verteciesCount;
        verticies = new Vertex[verteciesCount];

        for (int i=0; i < verteciesCount; i++) { //verticies[i] is a Vertex struct object
            verticies[i].id = other.verticies[i].id;
            verticies[i].edgeCount = other.verticies[i].edgeCount;

            if (other.verticies[i].edgeCount > 0){ //verticies[i].edges is an array of edges connected to a vertex
                verticies[i].edges = new Edge[other.verticies[i].edgeCount];
                for (int j=0; j < other.verticies[i].edgeCount; j++) {
                    verticies[i].edges[j] = other.verticies[i].edges[j];
                }

            } else {
             verticies[i].edges = nullptr;
            } 
        }
    }

    Graph& Graph::operator=(const Graph& other) {
        if (this == &other) { // checking if trying to do g = g for example
            return *this;
        }

        for (int i=0; i < verteciesCount; i++) { // delete current graph
            delete[] verticies[i].edges;
        }
        delete[] verticies;

        verteciesCount = other.verteciesCount;
        verticies = new Vertex[verteciesCount]; // make a new graph object to replace the old one

        for (int i=0; i < verteciesCount; i++) { // adding from the given graph its vertecies to the new one
            verticies[i].id = other.verticies[i].id;
            verticies[i].edgeCount = other.verticies[i].edgeCount;
            
            if (verticies[i].edgeCount > 0) { // adding given graphs edges to the new one, if that vertex has edges, else make nullptr
                verticies[i].edges = new Edge[verticies[i].edgeCount];
                for (int j=0; j < verticies[i].edgeCount; j++) {
                    verticies[i].edges[j] = other.verticies[i].edges[j];
                }
            } else {
             verticies[i].edges = nullptr; 
            }
        }
        return *this; 
    }

    Graph::~Graph() {
        for (int i=0; i < verteciesCount; i++) { // go through each vertex and free its edges array
            delete[] verticies[i].edges;
        }
        delete[] verticies; // delete the array of verticies

    }


    void Graph::addOneSidedEdge(int source, int dest, int weight) {
        if (source <= 0 || dest <= 0 || source > verteciesCount || dest > verteciesCount) { // checking that source and dest are valid inputs, positive ints, and in range of graph
            throw std::out_of_range("Source or destination vertex ID is out of bounds.");
        }

        if (source == dest) {
            throw std::invalid_argument("self loops are not allowed.");
        }

        for (int i=0; i < verteciesCount; i++) {
            if (verticies[i].id == source) {
                Vertex& v = verticies[i];  // v is the source vertex

                for (int j = 0; j < v.edgeCount; j++) {
                    if (v.edges[j].dest == dest) { // checking if edge already exists, and throw error
                        throw std::runtime_error("Edge already exists.");
                    }
                }

                Edge* temp = new Edge[v.edgeCount + 1]; // make new array to handle new size of edge array
                for (int j = 0; j < v.edgeCount; j++) {
                    temp[j] = v.edges[j];
                }

                temp[v.edgeCount] = Edge{dest, weight}; // adding new edge and then freeing the old one
                delete[] v.edges;
                v.edges = temp;
                v.edgeCount++; // update count

                break;
            }
        }
    }

    void Graph::addEdge(int source, int dest, int weight) {
        Graph::addOneSidedEdge(source, dest, weight);
        Graph::addOneSidedEdge(dest, source, weight);
    }

    void Graph::removeOneSidedEdge(int source, int dest) {
        if (source <= 0 || dest <= 0 || source > verteciesCount || dest > verteciesCount) { // checking that source and dest are valid inputs, positive ints, and in range of graph
            throw std::out_of_range("Source or destination vertex ID is out of bounds.");
        }

        if (source == dest) {
            throw std::invalid_argument("self loops are not allowed.");
        }

        for (int i=0; i < verteciesCount; i++) {

            if (verticies[i].id == source) {
                Vertex& v = verticies[i];  // v is the source vertex

                for (int j = 0; j < v.edgeCount; j++) {
                    if (v.edges[j].dest == dest) { // if we found the edge we want to remove

                        Edge* temp = new Edge[v.edgeCount - 1]; // make a new array of edges to deal with the new size of array
                        int tempIndex = 0;

                        for (int k = 0; k < v.edgeCount; k++) { 
                            if (v.edges[k].dest != dest) { // only add arrays that are not the removed array
                                temp[tempIndex] = v.edges[k];
                                tempIndex++;
                            }
                        }

                        delete[] v.edges; // free old edge array
                        v.edges = temp;
                        v.edgeCount--; // update count
                        return;
                    }
                }

                break;
            }
        } 
        
        throw std::runtime_error("Edge does not exist."); // it did not find the edge in the graph and will throw error
    }

    void Graph::removeEdge(int source, int dest) {
        Graph::removeOneSidedEdge(source, dest);
        Graph::removeOneSidedEdge(dest, source);
    }


    // void Graph::printGraph() {
    //     for (int i=0; i < verteciesCount; i++) {
    //         std::cout << "vertex " << verticies[i].id << ": ";
    //         for (int j=0; j < verticies[i].edgeCount; j++) {
    //             std::cout << "(v: " << verticies[i].edges[j].dest << ", w: " << verticies[i].edges[j].weight << ") ";
    //         }
    //         std::cout << "\n";
    //     }
    // }

    void Graph::printGraph() {
    for (int i = 0; i < verteciesCount; i++) {
        std::cout << "Vertex " << verticies[i].id << ":\n";
        for (int j = 0; j < verticies[i].edgeCount; j++) {
            std::cout << "  -> " << verticies[i].edges[j].dest << " (w: " << verticies[i].edges[j].weight << ")\n";
        }
    }
}

    int Graph::getSize() {
            return verteciesCount;
        }

    const Graph::Vertex& Graph::getVertex(int id) {
        if (id <= 0 || id > verteciesCount) {
            throw std::out_of_range("Vertex index out of range");
        }
        for (int i=0; i < verteciesCount; i++) {
            if (verticies[i].id == id) {
                return verticies[i];
            }
        }
        throw std::runtime_error("Vertex ID not found");
    }

    int Graph::getWeight(int source, int dest) {
            if (source <= 0 || dest <= 0 || source > verteciesCount || dest > verteciesCount) {
                throw std::out_of_range("source or destination vertex is out of range");
            }

            if (source == dest) {
                throw std::invalid_argument("self loops are not allowed.");
            }

            // Find the vertex that source == id
            for (int i = 0; i < verteciesCount; i++) { // go through 
                if (verticies[i].id == source) {
                    Vertex& v = verticies[i]; 
                    for (int j = 0; j < v.edgeCount; j++) {
                        if (v.edges[j].dest == dest) {
                            return v.edges[j].weight;
                        }
                    }
                    break; // source found but destination not found in edge array
                }
            }

            throw std::runtime_error("edge not found");
    }
}

