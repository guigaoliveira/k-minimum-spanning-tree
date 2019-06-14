#include <iostream>
#include "../graph.hpp"
#include "../util.hpp"

int main()
{
    Edge edges[] = {
        {0, 1, 5},
        {1, 2, 4},
        {2, 3, 5},
        {3, 4, 3},
        {1, 4, 6},
        {2, 4, 7}};

    Edge *edgesCopy = new Edge[6];
    std::copy(edges, edges + 6, edgesCopy);
    Edge *edgesAux = new Edge[6];
    mergeSort(edgesCopy, 0, 6, edgesAux);

    for (int i = 0; i < 6; ++i)
    {
        Edge edge = edges[i];
        std::cout << edge.src << " " << edge.dest << " " << edge.weight << "\n";
    }
    std::cout << "ordenado: "
              << "\n";
    for (int i = 0; i < 6; ++i)
    {
        Edge edge = edgesAux[i];
        std::cout << edge.src << " " << edge.dest << " " << edge.weight << "\n";
    }
    return 0;
}
