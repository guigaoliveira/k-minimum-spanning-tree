#include <iostream>
#include "../graph.hpp"

// Driver program to test above functions
int main()
{
    /* Let us create above shown weighted 
       and unidrected graph */
    int V = 9, E = 14;
    Graph g(V, E);

    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    std::cout << "Arestas da MST sao \n";

    Graph g2 = g.kruskalMST();

    for (int i = 0; i < g2.getNumberOfEdges(); ++i)
    {
        std::cout << g2.listEdges[i].src << " - " << g2.listEdges[i].dest << "\n";
    }

    return 0;
}