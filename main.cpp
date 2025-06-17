// gabi.rayman@gmail.com
#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

int main() {
    // make a graph with 5 verticies
    Graph g(5);

    // add edges 
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 7);
    g.addEdge(3, 5, 5);
    g.addEdge(1, 4, 5);

    std::cout << "Original Graph:" << std::endl;
    g.printGraph();
    std::cout << std::endl;

    g.removeEdge(1, 4);
    std::cout << "removed edge 1 -> 4, 4 -> 1:" << std::endl;
    g.printGraph();
    std::cout << std::endl;

    // bfs tree
    Graph bfsTree = Algorithms::bfs(g, 1);
    std::cout << "bfs Tree starting from vertex 1:" << std::endl;
    bfsTree.printGraph();
    std::cout << std::endl;

    // dfs tree
    Graph dfsTree = Algorithms::dfs(g, 1);
    std::cout << "dfs tree starting from vertex 1:" << std::endl;
    dfsTree.printGraph();
    std::cout << std::endl;

    // dijkstra tree
    Graph dijkstraTree = Algorithms::dijkstra(g, 1);
    std::cout << "dijkstra shortest path tree from vertex 1:" << std::endl;
    dijkstraTree.printGraph();
    std::cout << std::endl;

    // prims
    Graph primTree = Algorithms::prim(g);
    std::cout << "prims minimum spanning tree:" << std::endl;
    primTree.printGraph();
    std::cout << std::endl;

    // kruskals
    Graph kruskalTree = Algorithms::kruskal(g);
    std::cout << "kruskals minimum spanning tree:" << std::endl;
    kruskalTree.printGraph();
    std::cout << std::endl;

    return 0;
}