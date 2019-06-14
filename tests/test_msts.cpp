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

    Graph g(5, 6, edges, "mst", "msts");

    generateKSpanningTrees(g);

    return 0;
}
