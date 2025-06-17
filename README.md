In this project I have made Graphs with adjency lists, and if you use the regular addEdge and removeEdge functions, the graph will be undirected.
there are special one sided adds and removes which will make directed graphs. the dfs bfs and dijkstras will return directed graphs (trees), and prims and kruskals
return an undirected graph (minimal spanning trees) https://en.wikipedia.org/wiki/Minimum_spanning_tree . I have watched youtube videos (which I have links to in the Algorithms.cpp file)
which I used to go over the logic of the algorithms when needed.
run make Main see a small usage of the Algorithm functions
run make test to see tests which make sure the algorithms work as planned. the tests use graphs that checks that the algorithm works, either by rules of the graph, or by using
a graph that I know the outcome and compared it. these are not checking all cases but they give a good idea that the algorithms work.
run make valgrind to check for memory leeks. 
run make clean to clean all executables.
