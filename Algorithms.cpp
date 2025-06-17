// gabi.rayman@gmail.com
#include "Algorithms.hpp"
#include <stdexcept>
#include <limits>

namespace graph {

    // Node

    Node::Node(int val) {
        value = val;
        next = nullptr;
    }


    // Queue

    Queue::Queue() {
        head = nullptr;
        tail = nullptr;
    }

    Queue::~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void Queue::enQueue(int val) {
        Node* newNode = new Node(val);
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    int Queue::dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        Node* temp = head;
        int val = temp->value;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        return val;
    }

    bool Queue::isEmpty() {
        return head == nullptr;
    }


    // Stack

    Stack::Stack() {
        top = nullptr;
    }

    Stack::~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void Stack::push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    int Stack::pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        Node* temp = top;
        int val = temp->value;
        top = top->next;
        delete temp;
        return val;
    }

    bool Stack::isEmpty() const {
        if (top == nullptr) {
            return true;
        }
        return false;
    }

    Graph Algorithms::bfs(Graph& g, int start) {
        int size = g.getSize();

        // Create new graph for tree that is returned
        Graph tree(size);

        //  visited array 0 = not visited 1 = visited
        int* visited = new int[size+1];
        for (int i = 1; i <= size; i++) {
            visited[i] = 0;
        }

        // initialize Queue
        Queue queue;

        // mark root as visited
        // int visitedIndex = g.getIndexById(start);
        visited[start] = 1;

        // enqueue the root node
        queue.enQueue(start);
        
        while (!queue.isEmpty()) {
            int currentId = queue.dequeue(); // current vertex id

            const Graph::Vertex& currentVertex = g.getVertex(currentId); // current vertex edge array

            for (int i = 0; i < currentVertex.edgeCount; i++) { // go through neighbors of current vertex
                int neighborId = currentVertex.edges[i].dest; // the current neighbor id
                // int neighborIndex = g.getIndexById(neighborId);  

                if (visited[neighborId] == 0) {
                    visited[neighborId] = 1;
                    queue.enQueue(neighborId);
                    tree.addOneSidedEdge(currentId, neighborId); // here we add a one sided edge as the tree we are returning is a directed tree
                    // if you want to preserve the weights, comment out the line above and uncomment the two next lines
                    // int weight = g.getWeight(currentId, neighborId);
                    // forest.addOneSidedEdge(currentId, neighborId, weight); // add Edge to forest         
                }
        
            }
        }

        delete[] visited;

        return tree;
    }

Graph Algorithms::dfs(Graph& g, int start) {

        int size = g.getSize();

        // Create new graph for tree/forest that is returned
        Graph forest(size);

        //  visited array 0 = not visited 1 = visited
        int* visited = new int[size+1];

        //  parent array so that parent[node] = the parent of node
        int* parent = new int[size+1];
        
        // initiating parent and visited
        for (int i = 1; i <= size; i++) {
            visited[i] = 0;
            parent[i] = 0; // initialy zero (nodes start from 1)
        }

        // initialize stack
        Stack stack;

        // push root node into the stack
        stack.push(start);

        // start dfs search
        while (!stack.isEmpty()) {
            int current = stack.pop();    // current vertex

            if (visited[current] == 0) { // checking if vertex is in visited
                visited[current] = 1; // mark visited
                
                // we will now check if this is not a root node, (as a root node does not need to be added to itself as addEdge(2,2) for example is the same as not doing anything)
                if (parent[current] != 0) {
                    forest.addOneSidedEdge(parent[current], current); // here we add a one sided edge as the tree we are returning is a directed tree

                    // if you want to preserve the weights, comment out the line above and uncomment the two next lines
                    // int weight = g.getWeight(parent[current], current);
                    // forest.addOneSidedEdge(parent[current], current, weight); // add Edge to forest
                }
                
                // get reference to current vertex from the graph
                const Graph::Vertex& currentVertex = g.getVertex(current);

                // iterate through the neighbors of current vertex
                for (int i = 0; i < currentVertex.edgeCount; i++) {
                    int neighbor = currentVertex.edges[i].dest;

                    if (!visited[neighbor]) { // if neighbor has not been seen
                        stack.push(neighbor);
                        parent[neighbor] = current; // set the neighbors parent as current (as we got to them through current)
                    }
                }
            }
            if (stack.isEmpty()) { // if the stack is empty,
                // we have reached the end of a tree, and now we will iterate through the visited
                // arry and push a non visited node to the stack for the next tree.
                for (int i = 1; i <= size; i++) {
                    if (visited[i] == 0) {
                        stack.push(i);
                        break;
                    }
                }
            }
        }

        delete[] visited;
        delete[] parent;

        return forest;
    }


    Graph Algorithms::dijkstra(Graph& g, int start) {
        // I reminded myself about dijkstras algorithm here: https://www.youtube.com/watch?v=_lHSawdgXpI
        int size = g.getSize();
        Graph tree(size); // tree of weighted shortest distances to return

        int INF = std::numeric_limits<int>::max(); // largest int used for infinity in dijkstras

        int* distance = new int[size+1]; // to keep track of distances
        int* parent = new int[size+1];      // to keep track of parents for adding edges to the returned tree
        int* visited = new int[size+1];     // to keep track of visited nodes while traversing the graph g

        // initializing arrays
        for (int i=0; i <= size; i++) {
            distance[i] = INF;
            parent[i] = 0;
            visited[i] = 0;
        }

        int current = start;
        distance[current] = 0; // make the starting distance 0

        while (true) {
            
            const Graph::Vertex& currentVertex = g.getVertex(current);

            for (int i = 0; i < currentVertex.edgeCount; i++) { // go through neighbors of current vertex
                Graph::Edge neighbor = currentVertex.edges[i];

                if (visited[neighbor.dest]) { // we do not need to check visited nodes
                    continue;
                }

                // if the distance of current vertex plus distance to neighbor is smaller
                // than the current distance[neighbor] -> update
                if ( (distance[currentVertex.id] != INF) && (neighbor.weight + distance[currentVertex.id] < distance[neighbor.dest]) ) { 

                    // update distance
                    distance[neighbor.dest] = neighbor.weight + distance[currentVertex.id];

                    // update path parent to current best path
                    parent[neighbor.dest] = currentVertex.id;
                }        
            }

            // mark current as visited
            visited[currentVertex.id] = 1;

            // find smallest unvisited node in our distance array
            int smallest = INF;
            int smallestIndex = -1;
            for (int i = 1; i <= size; i++) {
                if ( (!visited[i]) && (distance[i] < smallest) ) {
                    smallest = distance[i];
                    smallestIndex = i;
                }
            }

            if (smallest == INF) { // all are visited
                break;
            }

            current = smallestIndex; // set current to smallest non visited element in distance array

        }

        for (int i=1; i <= size; i++) {
            int source = parent[i];
            if (source != 0) {
                int weight = g.getWeight(parent[i], i);
                tree.addOneSidedEdge(source, i, weight);
            }
        }

        delete[] distance;
        delete[] parent;
        delete[] visited;

        return tree;
    }

    Graph Algorithms::prim(Graph& g) {
        // here I reminded myself about prims algorithm here: https://www.youtube.com/watch?v=cplfcGZmX7I
        // I also was not sure about if a mst is directed or not and I got that here: https://en.wikipedia.org/wiki/Minimum_spanning_tree
        // "A minimum spanning tree (MST) or minimum weight spanning tree is a subset of the edges of a connected, edge-weighted undirected graph ..."
        int size = g.getSize();
        Graph tree(size); // tree of minimum spanning tree to return

        int* parent = new int[size+1];      // to keep track of parents for adding edges to the returned tree
        int* visited = new int[size+1];     // to keep track of visited nodes while traversing the graph g

        // initializing arrays
        for (int i=1; i <= size; i++) {
            parent[i] = 0;
            visited[i] = 0;
        }

        visited[1] = 1; // here we arbitrarily start with the first node. 

        while (true) {

            int smallest = std::numeric_limits<int>::max();
            int smallestIndex = -1;
            int fromIndex = -1;

            // here we go through visited vertecies and find unvisited neighbors, and find the minimum weight (or one of them)
            for (int i = 1; i <= size; i++) { 
                if (visited[i]) { // we go through visited nodes to find the smallest weight to connect another node to a visited node

                    const Graph::Vertex& currentVertex = g.getVertex(i);

                    for (int j = 0; j < currentVertex.edgeCount; j++) { // go through neighbors of current vertex
                        Graph::Edge neighbor = currentVertex.edges[j];
                        if (!visited[neighbor.dest] && neighbor.weight < smallest) { // if this is unvisited and smaller weight than what we have seen so far
                            smallest = neighbor.weight;
                            smallestIndex = neighbor.dest;
                            fromIndex = i; // keep track of the parent to build the minimal spanning tree
                        }
                    }
                }
            }

            if (smallestIndex == -1) { // we have no more unvisited vertecies, so we brake the while loop
                break;
            }

            visited[smallestIndex] = 1; // mark visited
            parent[smallestIndex] = fromIndex; // remember the chosen index's parent for building minimal spannin tree

        }

        for (int i=1; i <= size; i++) { // build tree
            int source = parent[i];
            if (source != 0) {
                int weight = g.getWeight(parent[i], i);
                tree.addEdge(source, i, weight); // add a double sided edge to the tree as it is not directed
            }
        }

        delete[] parent;
        delete[] visited;
        
        return tree;

    }

    Graph Algorithms::kruskal(Graph& g) {
        // to remind myself about kruskal I watched this: https://www.youtube.com/watch?v=JZBQLXgSGfs
        int size = g.getSize();

        int* root = new int[size+1]; // root for making joint sets

        // I am going to use a struct to make an array of edges
        // first I am going to find the size needed of the edgeArray
        int maxEdges = 0;
        for (int i = 1; i <= size; i++) {
            const Graph::Vertex& currentVertex = g.getVertex(i);

            for (int j = 0; j < currentVertex.edgeCount; j++) {
                Graph::Edge neighbor = currentVertex.edges[j];

                if (currentVertex.id < neighbor.dest) { // only take one of each direction
                    maxEdges++;
                }
            }
        }

        struct Edge {
            int source, dest, weight;
        };

        Edge* edgeArray = new Edge[maxEdges]; // array that we will sort
        int edgeCounter = 0; // counter so we can add the next element at every iteration

        Graph tree(size); // tree of minimum spanning tree to return

        // intialize root array for tracking root of joint sets
        for (int i=1; i <= size; i++) {
            root[i] = i; // initially every node is it's own set
        }


        for (int i = 1; i <= size; i++) { 

            const Graph::Vertex& currentVertex = g.getVertex(i);

            for (int j = 0; j < currentVertex.edgeCount; j++) { // go through neighbors of current vertex
                Graph::Edge neighbor = currentVertex.edges[j];

                if (currentVertex.id < neighbor.dest) { // to make sure we dont get duplicates

                    edgeArray[edgeCounter] = {currentVertex.id, neighbor.dest, neighbor.weight};
                    edgeCounter++;

                }
            }
        }

        // now we will sort , I used bubble sort as I found here: https://www.quora.com/What-is-the-easiest-sort-algorithm-to-implement
        bool swapped;
        for (int i=0; i < maxEdges; i++) {
            swapped = false;
            for (int j=0; j < maxEdges-i-1; j++) {
                if (edgeArray[j].weight > edgeArray[j+1].weight) {
                    //swap
                    Edge temp = edgeArray[j];
                    edgeArray[j] = edgeArray[j+1];
                    edgeArray[j+1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }

        // we will now implement kruskels algorithm and add the smallest weighted edges as long as they dont make a cycle
        for (int i=0; i < maxEdges; i++) {
            Edge currentEdge = edgeArray[i];
            if (root[currentEdge.source] != root[currentEdge.dest]) { // check if they are part of the same set
                int rootSrc  = root[currentEdge.source];
                int rootDest = root[currentEdge.dest];

                //we will join source and dest
                for (int j=1; j <= size; j++) {
                    if (root[j] == rootDest) {
                        root[j] = rootSrc;
                    }
                }
                // add to tree
                tree.addEdge(currentEdge.source, currentEdge.dest, currentEdge.weight);
            }
        }        
        
        delete[] edgeArray;
        delete[] root;

        return tree;

    }
}


