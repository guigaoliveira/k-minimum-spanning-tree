#include "util.hpp"

template class MinHeap<Mst>;

/* 
    Função que retorna um número aleatório.
 */
int getRandomNumber(int min = 1, int max = 20)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

/*
    Função que retorna o número de arestas de um grafo completo de n vértices.
 */
int getTotalEdgesComplete(int n)
{
    return (n * (n - 1)) / 2;
}

/*
  Função que retorna o número de arestas de um grafo completo de n*m vértices.
 */
int getTotalEdgesGrid(int n, int m)
{
    return (2 * n * m) - m - n;
}

/* 
    Função que cria um grafo completo.
 */
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

/* 
    Função que cria um grafo grid.
 */
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

/*
    Função para criar um arquivo para um grafo em um formato específico (instância).
 */
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

/*
    Função que junta arrays ordenados, auxiliar para o mergeSort
 */
void merge(Edge edges[], int start, int mid, int end, Edge aux[])
{
    int left = start;
    int right = mid;

    for (unsigned int i = start; i < end; ++i)
    {
        if ((left < mid) && ((right >= end) || (edges[left].weight < edges[right].weight)))
        {

            aux[i] = edges[left];
            ++left;
        }
        else
        {
            aux[i] = edges[right];
            ++right;
        }
    }

    for (unsigned int i = start; i < end; ++i)
        edges[i] = aux[i];
}

/*
    Função do algoritmo de ordenação mergeSort.
 */
void mergeSort(Edge edges[], int start, int end, Edge aux[])
{
    if ((end - start) < 2)
        return;

    int mid = ((start + end) / 2);
    mergeSort(edges, start, mid, aux);
    mergeSort(edges, mid, end, aux);
    merge(edges, start, mid, end, aux);
}

/*
    Função para verificação de conectividade de um grafo, a partir de um disjoint-set.
 */
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

/*
    Função que executa o algoritmo de Krukal para gerar a árvore geradora mínima de um grafo
 */
Mst kruskalMST(Graph &g)
{
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;
    int startCreatePartition = 0;
    Edge *mstListEdges = new Edge[g.numberOfNodes - 1];
    Edge *listEdgesSorted = new Edge[g.lengthListEdges];
    Edge *edgesAux = new Edge[g.lengthListEdges];
    std::copy(g.listEdges, g.listEdges + g.lengthListEdges, listEdgesSorted);
    mergeSort(listEdgesSorted, 0, g.lengthListEdges, edgesAux);

    DisjointSets dsKruskal(g.numberOfNodes);
    DisjointSets dsToCheckConnetivity(g.numberOfNodes);

    for (unsigned int i = 0; countEdges < g.numberOfNodes - 1; ++i)
    {
        int u = listEdgesSorted[i].src;
        int v = listEdgesSorted[i].dest;
        int set_u = dsKruskal.find(u);
        int set_v = dsKruskal.find(v);
        EdgeState state = listEdgesSorted[i].state;

        if (state != EdgeState::OPEN)
            startCreatePartition++;
        if (state == EdgeState::EXCLUDED)
            continue;
        if (set_u != set_v || state == EdgeState::INCLUDED)
        {
            int weight = listEdgesSorted[i].weight;
            mstListEdges[countEdges] = {u, v, weight, state};
            totalWeight += weight;
            countEdges++;
            dsToCheckConnetivity.doUnion(u, v);
            dsKruskal.doUnion(set_u, set_v);
        }
    }

    Graph mstGraph(countEdges + 1, countEdges, mstListEdges);
    Mst mst(g, mstGraph, totalWeight, startCreatePartition,
            isConnected(dsToCheckConnetivity, countEdges));
    delete[] mstListEdges;
    return mst;
}

/*
    Função que cria uma partição para o algoritmo de geração de árvores geradoras mínimas.
 */
void partition(Mst &Ps, MinHeap<Mst> &heap)
{
    Graph p = Ps.currentGraph;
    Graph p1 = p;

    for (int i = Ps.startCreatePartition; i < p.lengthListEdges; ++i)
    {
        Edge edge = p.listEdges[i];

        bool del = edge.state != EdgeState::EXCLUDED && edge.state != EdgeState::INCLUDED;

        if (del)
            p1.listEdges[i].state = EdgeState::EXCLUDED;

        Mst p1Mst = kruskalMST(p1);

        if (p1Mst.isConnected && p1Mst.totalWeight > Ps.totalWeight)
        {
            heap.insert(p1Mst);
        }

        if (del)
            p1.listEdges[i].state = EdgeState::INCLUDED;
    }
}

/*
    Função para gerar as árvores geradoras mínimas de um grafo.
 */
void generateKSpanningTrees(Graph &g)
{
    std::cout << "Comecando geracao de msts do grafo..."
              << "\n";
    MinHeap<Mst> heap(100000);
    Mst graphMst = kruskalMST(g);
    heap.insert(graphMst);
    while (heap.size())
    {
        Mst Ps = heap.remove();
        createFileForGraph(g.pathToSave + "/mst_" +
                               std::to_string(Ps.totalWeight) + "_" + g.filename,
                           Ps.mstGraph);
        std::cout << "Nova árvore  a ser salva. Peso:" << Ps.totalWeight << "\n";
        partition(Ps, heap);
    }
    std::cout << "Arquivos das msts salvos em: " << g.pathToSave << "\n";
}

/*
    Função para ler um arquivo contendo uma instância de um grafo.
 */
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
        std::cout << n;
        std::cout << m;
        numberOfVertices = n;
        numberOfEdges = m;
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
            std::to_string(numberOfVertices) + graphType,
            pathToSave);
    return g;
}
