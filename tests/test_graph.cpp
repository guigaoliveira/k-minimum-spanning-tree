#include <iostream>
#include "../graph.hpp"
#include "../util.hpp"
#include <string>

int main()
{
    std::cout << "Testando geracao de instancias de grafos completos e grid..."
              << "\n";
    for (int i = 5; i < 30; ++i)
    {
        if (i % 2 == 0)
        {
            std::string pathFileComplete = "completo/" + std::to_string(i) + "completo";
            createFileForGraph(pathFileComplete, createCompleteGraph(i));

            std::string pathFileGrid = "grid/" + std::to_string(i) + "grid";
            createFileForGraph(pathFileGrid, createGridGraph(2, i));
        }
    }
    std::cout << "Arquivos salvos na pastas /completo e /grid!"
              << "\n";
    Edge e[] = {{0, 1, 4, -1}, {2, 3, 2, -1}};
    Graph g(4, 2, e);
    Graph g2 = g;

    std::cout << "Teste de copia: "
              << "\n";
    for (int i = 0; i < g2.getNumberOfNodes(); ++i)
    {
        Node *node = g2.head[i];
        while (node != nullptr)
        {
            std::cout << i << " " << node->value << " " << node->weight << "\n";
            node = node->next;
        }
    }
    return 0;
}
