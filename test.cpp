// gabi.rayman@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace graph;



TEST_CASE("graph creation and addEdge, undirectedness and non existing edge") {
    Graph g(3);
    g.addEdge(1, 2, 5);
    g.addEdge(2, 3, 7);

    CHECK(g.getSize() == 3);
    CHECK(g.getWeight(1, 2) == 5);
    CHECK(g.getWeight(2, 3) == 7);
    CHECK(g.getWeight(2, 1) == 5); // check undirectedness
    CHECK_THROWS(g.getWeight(1, 3)); // for non existing edge
}

TEST_CASE("remove edge") {
    Graph g(3);
    g.addEdge(1, 2, 4);
    g.removeEdge(1, 2);

    CHECK_THROWS(g.getWeight(1, 2));
    CHECK_THROWS(g.getWeight(2, 1));
}

TEST_CASE("remove non existing edge") {
    Graph g(3);
    g.addEdge(1, 2, 4);
    
    CHECK_THROWS(g.removeEdge(1, 3));
}

TEST_CASE("bfs produces tree, check if edge that closes cycle is removed") {
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 2); // closes cycle, check if removed in tree

    Graph bfsTree = Algorithms::bfs(g, 1);

    CHECK_THROWS(bfsTree.removeOneSidedEdge(4, 2));
    CHECK_THROWS(bfsTree.removeOneSidedEdge(2, 4));
    CHECK_NOTHROW(bfsTree.getWeight(2, 3));
}

TEST_CASE("dfs on a a graph with 5 nodes and 7 edges") {
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(1, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 1);
    g.addEdge(2, 5);

    Graph dfsTree = Algorithms::dfs(g, 1);

    // The tree should have only 4 edges
    int edgeCount = 0;
    for (int i = 1; i <= 5; i++) {
        const Graph::Vertex& vertex = dfsTree.getVertex(i);
        edgeCount += vertex.edgeCount;
    }

    CHECK(edgeCount == 4); // must be exactly 4 tree edges, as a tree has n-1 edges

}

// here we have  1 -> 2 which costs us 1, and 1 -> 3 which costs us 4,
// but 1 -> 2 -> 3 costs 1+2 = 3 which is cheaper, so we will go through 1 -> 2 -> 3 -> 4 (as only way to get to 4)
// so the outcome should remove 1 -> 3 and then 
TEST_CASE("Dijkstra returns shortest path tree") {
    Graph g(4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 1);

    Graph shortestTree = Algorithms::dijkstra(g, 1);

    CHECK(shortestTree.getWeight(1, 2) == 1);
    CHECK(shortestTree.getWeight(2, 3) == 2);
    CHECK(shortestTree.getWeight(3, 4) == 1);

    CHECK_THROWS(shortestTree.getWeight(1,3)); // check that 1 to 3 does not exist
}



TEST_CASE("Prim and Kruskal produce same minimal spanning tree") { // I use the example in this video to check the answer is correct: https://www.youtube.com/watch?v=cplfcGZmX7I&ab_channel=MichaelSambol
    Graph g(7);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 5, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 6, 6);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 6, 7);
    g.addEdge(6, 7, 9);

    Graph primTree = Algorithms::prim(g);
    Graph kruskalTree = Algorithms::kruskal(g);

    // we will check total weight
    int totalPrim = 0;
    int totalKruskal = 0;

    for (int i = 1; i <= 7; i++) {
        const graph::Graph::Vertex& vertex = primTree.getVertex(i);
        for (int j = 0; j < vertex.edgeCount; j++) {
            totalPrim += vertex.edges[j].weight;
        }
    }

    for (int i = 1; i <= 7; i++) {
        const graph::Graph::Vertex& vertex = kruskalTree.getVertex(i);
        for (int j = 0; j < vertex.edgeCount; j++) {
            totalKruskal += vertex.edges[j].weight;
        }
    }

    //it would have counted everything twice so we will devide in half
    totalPrim = totalPrim/2;
    totalKruskal =totalKruskal/2;

    // check if they did they got the same weight for minimal spanning tree
    CHECK(totalPrim  == totalKruskal);
    CHECK(totalKruskal == 24); // as shown in the youtube video above
    CHECK(totalPrim == 24);
}