#include <iostream>
#include <memory>
#include "heap.hpp"
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "util.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>

/* 
template class Heap<Mst>;
 */
Graph::Graph(int nOfNodes, int nOfEdges)
{
    numberOfNodes = nOfNodes;
    head = new Node *[nOfNodes]();
    numberOfEdges = nOfEdges;
    listEdges = new Edge[nOfEdges];
    lengthListEdges = 0;
    hashLengthMax = hashCode(nOfNodes + nOfEdges, nOfNodes + nOfEdges);
    excludedList = new bool[hashLengthMax]{false};
    includedList = new bool[hashLengthMax]{false};
    for (int i = 0; i < numberOfNodes; ++i)
        head[i] = nullptr;
}

Graph::Graph(int nOfVertices, int nOfEdges, Edge edges[]) : Graph(nOfVertices, nOfEdges)
{
    addEdges(edges);
}

Node *Graph::createAdjListNode(int value, int weight, Node *next)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = next;
    return newNode;
}

void Graph::addEdge(int src, int dest, int weight)
{
    head[src] = createAdjListNode(dest, weight, head[src]);
    listEdges[lengthListEdges] = {src, dest, weight};
    lengthListEdges++;
}

void Graph::addEdges(Edge edges[])
{
    for (int i = 0; i < numberOfEdges; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight);
}

int Graph::getNumberOfNodes()
{
    return numberOfNodes;
}

int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

Mst Graph::kruskalMST()
{
    /*  std::cout << "[---- Novo kruskal ----]"
              << "\n"; */
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;
    bool *mstNodesMarked = new bool[numberOfNodes - 1]{false};

    // std::cout << "Quantidade de arestas: " << numberOfEdges << "\n";
    Edge *listEdgesTmp = new Edge[lengthListEdges];
    std::copy(listEdges, listEdges + lengthListEdges, listEdgesTmp);
    sortArrayOfNodes(listEdgesTmp, lengthListEdges);
    DisjointSets ds(numberOfNodes);
    for (int i = 0; i < numberOfEdges; ++i)
    {
        int u = listEdgesTmp[i].src;
        int v = listEdgesTmp[i].dest;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        // std::cout << "h: " << excludedList[hashCode(u, v)] << "\n";
        /*  std::cout << "---"
                  << "\n"; */
        // std::cout << "hashCode: " << excludedList[hashCode(u, v)] << "\n";
        /* std::cout << "u: " << u << "\n";
        std::cout << "v: " << v << "\n";
        std::cout << "set_u: " << set_u << "\n";
        std::cout << "set_v: " << set_v << "\n"; */

        if (excludedList[hashCode(u, v)])
        {
            std::cout << "(" << u << ", " << v << ")"
                      << "\n";
            continue;
        }
        if (set_u != set_v)
        {
            ds.merge(set_u, set_v);
            totalWeight += listEdgesTmp[i].weight;
            countEdges++;
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
    /*  std::cout << "countNodes: " << countNodes << "\n";
    std::cout << "countEdges: " << countEdges << "\n";
    std::cout << "Peso total: " << totalWeight << "\n";
    std::cout << "Eh conectado: " << (int)(numberOfNodes == countNodes) << "\n"; */

    // Graph g(countNodes + 1, countEdges, mstListEdges);
    /*     std::cout << "countNodes: " << countNodes << "\n";
    std::cout << "numberOfNodes: " << numberOfNodes << "\n";
    std::cout << "numberOfNodes == countNodes: " << (int)(numberOfNodes == countNodes) << "\n";
    std::cout << "Total: " << totalWeight << "\n"; */
    /* std::cout << "countNodes: " << countNodes << "\n";
    std::cout << "countEdges: " << countEdges << "\n"; */
    std::cout << totalWeight << "\n";
    Mst mst(*this, totalWeight, numberOfNodes == countNodes);
    delete[] mstNodesMarked;
    return mst;
}
bool compare(Mst i, Mst j) { return i.totalWeight > j.totalWeight; }

void partition(Mst Ps, std::vector<Mst> &heap)
{
    Graph p = Ps.graph;
    Graph p1 = p;
    Graph p2 = p;
    for (int i = 0; i < p.getNumberOfEdges(); ++i)
    {
        Edge edge = p.listEdges[i];
        int hashCodeEdge = hashCode(edge.src, edge.dest);
        if (!p.includedList[hashCodeEdge] && !p.excludedList[hashCodeEdge])
        {
            p1.excludedList[hashCodeEdge] = true;
            p2.includedList[hashCodeEdge] = true;
        }
        Mst p1Mst = p1.kruskalMST();
        if (p1Mst.isConnected)
        {
            heap.push_back(p1Mst);
        }
        p1 = p2;
    }
}
void Graph::generateKSpanningTrees(int k)
{
    std::vector<Mst> heap;
    Mst graphMst = kruskalMST();
    heap.push_back(graphMst);
    Mst Ps = heap.front();
    while (heap.size() != 0)
    {
        Ps = *std::min_element(std::begin(heap), std::end(heap), compare);
        std::cout << Ps.totalWeight << std::endl;
        heap.erase(std::min_element(std::begin(heap), std::end(heap), compare));
        partition(Ps, heap);
    }
}