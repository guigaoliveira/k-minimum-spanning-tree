#include <chrono>
#include "../graph.hpp"
#include "../util.hpp"

using namespace std::chrono;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Argumentos faltando!\nUso: " << argv[0] << " <grafo>\n";
        exit(0);
    }

    Graph g = readGraphFromFile(argv[1], argv[2], argv[3] ? argv[3] : "msts");
    auto start = high_resolution_clock::now();
    generateKSpanningTrees(g);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "Tempo de execucao para instancia: "
              << duration.count() << " milissegundos."
              << "\n";

    return 0;
}