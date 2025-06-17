// gabi.rayman@gmail.com
#pragma once

namespace graph {
    class Graph {
    public:
        struct Edge { // each edge represents a connection in the graph
            int dest;
            int weight;
        };
        struct Vertex { // each vertex has an id and an array of edges connected to it
            int id;
            Edge* edges;
            int edgeCount;
        };
    private:
        Vertex* verticies; // an array of verticies for the each vertex in the graph
        int verteciesCount; // total number of vertecies in the graph
    public:
        Graph(int size); // regular constructor
        Graph(const Graph& other); // copy constructor
        Graph& operator=(const Graph& other); // assignment operator
        ~Graph(); //deconstructor

        // functions on the graph:
        // addEdge helper function
        void addOneSidedEdge(int source, int dest, int weight = 1);

        // Adds an edge from source to dest with an optional weight
        void addEdge(int source, int dest, int weight = 1); 
        // removeEdge helper function
        void removeOneSidedEdge(int source, int dest);

        // Removes the edge from source to dest, if edge does not exist, throws error
        void removeEdge(int source, int dest);

        // Prints the graph
        void printGraph();

        // size getter
        int getSize();

        // gets a reference to a vertex for iteration on edges
        const Vertex& getVertex(int id);

        int getWeight(int source, int dest);
    };
}

