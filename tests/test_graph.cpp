#include <iostream>
#include "../graph.hpp"
#include "../util.hpp"
#include <string>

int main()
{
    for (int i = 5; i < 30; ++i)
    {
        if (i % 2 == 0)
        {
            std::string pathFileComplete = "completo/" + std::to_string(i) + "completo";
            createFileForGraph(pathFileComplete, createCompleteGraph(i));

            std::string pathFileGrid = "grid/" + std::to_string(i) + "grid";
            createFileForGraph(pathFileGrid, createGridGraph(2, i / 2));
        }
    }
    return 0;
}