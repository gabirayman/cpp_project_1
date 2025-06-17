// gabi.rayman@gmail.com
#pragma once
#include "Graph.hpp"

namespace graph {
    // a node for a linked list that is used in Queue and Stack
    struct Node {
        int value;
        Node* next = nullptr;

        Node(int val);
    };

    // a Queue made from linked list
    struct Queue {
        Node* head;
        Node* tail;
    
        Queue();
        ~Queue();

        void enQueue(int val);
        int dequeue();
        bool isEmpty();
    };

    // a Stack made from linked list
    struct Stack {
        Node* top;

        Stack();
        ~Stack();

        void push(int val);
        int pop();
        bool isEmpty() const;
    };

    class Algorithms {
    public:        
        
        // Returns a BFS tree with start as its root
        static Graph bfs(Graph& g, int start);

        // Returns a DFS tree with start as its root
        static Graph dfs(Graph& g, int start);

        // Returns a tree of shortest paths from start using Dijkstras algorithm
        static Graph dijkstra(Graph& g, int start);

        // Returns the minimal spanning tree using Prims algorithm
        static Graph prim(Graph& g);

        // Returns the minimal spanning tree using Kruskals algorithm
        static Graph kruskal(Graph& g);

    };

}