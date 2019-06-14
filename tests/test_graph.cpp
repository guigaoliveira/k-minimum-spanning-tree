#include <iostream>
#include "../graph.hpp"
#include "../util.hpp"
#include <string>

int main()
{
    std::cout << "Testando geracao de instancias de grafos completos e grid..."
              << "\n";
    std::string pathFileComplete = "";
    for (int i = 5; i <= 10; ++i)
    {
        pathFileComplete = "completo/" + std::to_string(i) + "completo";
        createFileForGraph(pathFileComplete, createCompleteGraph(i));
    }

    std::string pathFileGrid = "grid/" + std::to_string(5 * 5) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(5, 5));

    pathFileGrid = "grid/" + std::to_string(2 * 6) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(2, 6));

    pathFileGrid = "grid/" + std::to_string(3 * 6) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(3, 6));

    pathFileGrid = "grid/" + std::to_string(2 * 8) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(2, 8));

    pathFileGrid = "grid/" + std::to_string(4 * 5) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(4, 5));

    pathFileGrid = "grid/" + std::to_string(5 * 6) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(5, 6));

    pathFileGrid = "grid/" + std::to_string(2 * 5) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(2, 5));

    pathFileGrid = "grid/" + std::to_string(3 * 3) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(3, 3));

    pathFileGrid = "grid/" + std::to_string(3 * 9) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(9, 3));

    pathFileGrid = "grid/" + std::to_string(2 * 11) + "grid";
    createFileForGraph(pathFileGrid, createGridGraph(2, 11));

    std::cout << "Arquivos salvos na pastas /completo e /grid!"
              << "\n";
    Edge e[] = {{0, 1, 4}, {2, 3, 2}};
    Graph g(4, 2, e);
    Graph g2 = g;

    std::cout << "Teste de copia: "
              << "\n";
    for (int i = 0; i < g.numberOfEdges; ++i)
    {
        Edge edge = g.listEdges[i];
        std::cout << edge.src << " " << edge.dest << " " << edge.weight << "\n";
    }
    return 0;
}
