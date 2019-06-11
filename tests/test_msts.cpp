#include <iostream>
#include "../graph.hpp"
#include "../util.hpp"

int main()
{
    Graph g = createCompleteGraph(5);
    g.generateKSpanningTrees(125);
    return 0;
}