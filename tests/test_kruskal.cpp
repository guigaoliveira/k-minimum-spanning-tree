#include "../graph.hpp"
#include "../util.hpp"

// lembra de tirar a adaptação do krukal para testar esse arquivo
int main()
{
    int V = 9, E = 14;
    Graph g(V, E);

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

    Mst mst = kruskalMST(g);

    for (int i = 0; i < mst.mstGraph.numberOfEdges; ++i)
    {
        std::cout << mst.mstGraph.listEdges[i].src
                  << " - " << mst.mstGraph.listEdges[i].dest
                  << " - " << mst.mstGraph.listEdges[i].weight << "\n";
    }

    std::cout << "Custo: " << mst.totalWeight << "\n";
    return 0;
}
