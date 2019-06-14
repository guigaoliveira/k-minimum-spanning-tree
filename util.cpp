#include <fstream>
#include <random>
#include "util.hpp"
#include "heap.hpp"
#include <memory>
#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>

template class Heap<Mst>;

int getRandomNumber(int min = 1, int max = 20)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int getTotalEdgesComplete(int n)
{
    return (n * (n - 1)) / 2;
}

int getTotalEdgesGrid(int n, int m)
{
    return (2 * n * m) - m - n;
}

Graph createCompleteGraph(int n)
{
    int numberOfEdges = getTotalEdgesComplete(n);
    Edge edges[numberOfEdges];
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            edges[count] = {i, j, getRandomNumber()};
            count++;
        }
    }

    Graph graph(n, numberOfEdges, edges);
    return graph;
}

Graph createGridGraph(int n, int m)
{
    int numberOfEdges = getTotalEdgesGrid(n, m);
    Edge edges[numberOfEdges];
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int nodeActual = i * m + j;
            if (j + 1 != m)
            {
                edges[count] = {nodeActual, nodeActual + 1, getRandomNumber()};
                count++;
            }
            if (i + 1 != n)
            {
                edges[count] = {nodeActual, nodeActual + m, getRandomNumber()};
                count++;
            }
        }
    }

    Graph graph(n * m, numberOfEdges, edges);
    return graph;
}

void createFileForGraph(std::string const &name, Graph g)
{
    std::ofstream file;
    file.open(name + ".in");

    if (!file.is_open())
    {
        std::cout << "Nao foi possivel criar instancia de grafo"
                  << "\n";
        return;
    }

    if (g.numberOfNodes == g.numberOfEdges)
    {
        file << g.numberOfNodes << "\n";
    }
    else
    {
        file << g.numberOfNodes << " " << g.numberOfEdges << "\n";
    }

    for (int i = 0; i < g.numberOfEdges; ++i)
    {
        Edge edge = g.listEdges[i];
        file << edge.src << " " << edge.dest << " " << edge.weight << "\n";
    }

    file.close();
}

void merge(Edge edges[], int inicio, int meio, int fim, Edge vetAux[])
{
    int esq = inicio;
    int dir = meio;

    for (unsigned int i = inicio; i < fim; ++i)
    {
        if ((esq < meio) && ((dir >= fim) || (edges[esq].weight < edges[dir].weight)))
        {

            vetAux[i] = edges[esq];
            ++esq;
        }
        else
        {
            vetAux[i] = edges[dir];
            ++dir;
        }
    }

    for (unsigned int i = inicio; i < fim; ++i)
        edges[i] = vetAux[i];
}

Edge *mergeSort(Edge edges[], int inicio, int fim, Edge vetorAux[])
{
    if ((fim - inicio) >= 2)
    {
        int meio = ((inicio + fim) / 2);
        mergeSort(edges, inicio, meio, vetorAux);
        mergeSort(edges, meio, fim, vetorAux);
        merge(edges, inicio, meio, fim, vetorAux);
    }
    return edges;
}

bool isConnected(DisjointSets &ds, int numberOfEdges)
{
    int curr = -1;
    int roots = 0;
    for (int i = 0; i < numberOfEdges; ++i)
    {
        int parent = ds.find(i);
        if (curr != parent)
        {
            curr = parent;
            roots++;
        }
    }
    return roots == 1;
}

Mst kruskalMST(Graph &g)
{
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;
    int startCreatePartition = 0;
    Edge *mstListEdges = new Edge[g.numberOfNodes - 1];
    bool *mstNodesMarked = new bool[g.numberOfNodes - 1]{false};

    Edge *listEdgesSorted = new Edge[g.lengthListEdges];
    Edge *edgesAux = new Edge[g.lengthListEdges];
    std::copy(g.listEdges, g.listEdges + g.lengthListEdges, listEdgesSorted);
    mergeSort(listEdgesSorted, 0, g.lengthListEdges, edgesAux);

    DisjointSets dsKruskal(g.numberOfNodes);
    DisjointSets dsToCheckConnetivity(g.numberOfNodes);

    for (int i = 0; i < g.lengthListEdges; ++i)
    {
        int u = listEdgesSorted[i].src;
        int v = listEdgesSorted[i].dest;
        int set_u = dsKruskal.find(u);
        int set_v = dsKruskal.find(v);
        int state = g.listEdges[i].state;

        if (state != EdgeState::OPEN)
            startCreatePartition++;
        if (state == EdgeState::EXCLUDED)
            continue;
        if (set_u != set_v)
        {
            int weight = listEdgesSorted[i].weight;
            mstListEdges[countEdges] = {u, v, weight, listEdgesSorted[i].state};
            totalWeight += weight;
            countEdges++;
            dsToCheckConnetivity.doUnion(u, v);
            dsKruskal.doUnion(set_u, set_v);
            if (!mstNodesMarked[u])
            {
                mstNodesMarked[u] = true;
                countNodes++;
            }
            if (!mstNodesMarked[v])
            {
                mstNodesMarked[v] = true;
                countNodes++;
            }
        }
    }

    Graph copy = g;
    Graph mstGraph(countNodes, countEdges, mstListEdges);
    Mst mst(copy, mstGraph, totalWeight,
            startCreatePartition,
            isConnected(dsToCheckConnetivity, countEdges));
    delete[] mstListEdges;
    return mst;
}

void partition(Mst &Ps, Heap<Mst> &heap)
{
    Graph p = Ps.currentGraph;
    Graph p1 = p;
    Graph p2 = p;

    bool del = false;

    for (int i = Ps.startCreatePartition; i < p.lengthListEdges; ++i)
    {
        Edge edge = p.listEdges[i];

        bool del = edge.state != EdgeState::EXCLUDED && edge.state != EdgeState::INCLUDED;

        if (del)
            p1.listEdges[i].state = EdgeState::EXCLUDED;

        Mst p1Mst = kruskalMST(p1);

        if (p1Mst.isConnected && p1Mst.totalWeight > Ps.totalWeight)
            heap.insert(p1Mst);

        if (del)
            p2.listEdges[i].state = EdgeState::INCLUDED;

        p1 = p2;
    }
}

void generateKSpanningTrees(Graph &g)
{
    // Inicia a heap com numero maximo de msts para um grafo completo
    std::cout << "Comecando geracao de msts do grafo..."
              << "\n";
    Heap<Mst> heap(100000);
    Mst graphMst = kruskalMST(g);
    heap.insert(graphMst);
    while (heap.size())
    {
        Mst Ps = heap.remove();
        createFileForGraph(g.pathToSave + "/mst_" +
                               std::to_string(Ps.totalWeight) + "_" + g.filename,
                           Ps.mstGraph);
        partition(Ps, heap);
    }
    std::cout << "Arquivos das msts salvos em: " << g.pathToSave << "\n";
}

Graph readGraphFromFile(std::string filename, std::string graphType, std::string pathToSave)
{
    std::ifstream file;
    file.open(filename);

    std::string line;

    if (!file.is_open())
    {
        std::cout << "Nao foi possivel abrir o arquivo '" << filename << "'. \n";
        exit(0);
    }

    int numberOfVertices = 0;
    int fileVertices = 0;
    int numberOfEdges = 0;
    Edge *edges;

    if (graphType == "completo") // caso grafo completo
    {
        getline(file, line);
        numberOfVertices = stoi(line);
        numberOfEdges = getTotalEdgesComplete(numberOfVertices);
    }

    if (graphType == "grid") // caso grafo grid
    {
        getline(file, line);
        std::stringstream ss;
        std::string tmp;
        ss << line;
        int number = 0;
        int values[2];
        int k = 0;
        while (!ss.eof())
        {
            ss >> tmp;
            if (std::stringstream(tmp) >> number)
                values[k++] = number;
            tmp = "";
        }
        int n = values[0];
        int m = values[1];
        fileVertices = n;
        numberOfVertices = n * m;
        numberOfEdges = getTotalEdgesGrid(n, m);
    }

    if (!numberOfVertices || !numberOfEdges)
    {
        std::cout << "Nao eh possivel criar o grafo";
        exit(0);
    }

    edges = new Edge[numberOfEdges];

    // ler valores das arestas
    int i = 0;
    while (getline(file, line))
    {
        std::stringstream ss;
        std::string tmp;

        ss << line;

        int number = 0;
        int values[3];
        int k = 0;

        while (!ss.eof())
        {
            ss >> tmp;
            if (std::stringstream(tmp) >> number)
            {
                values[k++] = number;
            }
            tmp = "";
        }

        edges[i++] = {values[0], values[1], values[2]};
    }

    file.close();

    Graph g(numberOfVertices,
            numberOfEdges,
            edges,
            std::to_string(fileVertices) + graphType,
            pathToSave);
    return g;
}
