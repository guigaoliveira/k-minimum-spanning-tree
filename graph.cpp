#include <iostream>
#include <memory>
#include "heap.hpp"
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "util.hpp"
#include <queue>
#include <vector>

template class Heap<Mst>;

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

Graph::~Graph()
{
    /* for (int i = 0; i < numberOfNodes; ++i)
    {
        delete[] head[i];
    }
    delete[] head;
    delete[] listEdges; */
}

/* Graph::Graph(const Graph &g2) : numberOfNodes(g2.numberOfNodes),
                                numberOfEdges(g2.numberOfEdges),
                                listEdges(g2.numberOfEdges ? new Edge[g2.numberOfEdges] : nullptr),
                                head(g2.numberOfNodes ? new Node *[numberOfNodes]() : nullptr),
                                lengthListEdges(g2.lengthListEdges),
                                excludedList(g2.hashLengthMax ? new bool[g2.hashLengthMax] : nullptr),
                                includedList(g2.hashLengthMax ? new bool[g2.hashLengthMax] : nullptr),
                                hashLengthMax(g2.hashLengthMax)
{
    std::copy(g2.listEdges, g2.listEdges + numberOfEdges, listEdges);
    std::copy(g2.head, g2.head + numberOfNodes, head);
    std::copy(g2.excludedList, g2.excludedList + hashLengthMax, excludedList);
    std::copy(g2.includedList, g2.includedList + hashLengthMax, includedList);
}
 */
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
    head[dest] = createAdjListNode(src, weight, head[dest]);
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
    std::cout << "[---- Novo kruskal ----]"
              << "\n";
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;

    Edge *mstListEdges = new Edge[numberOfNodes - 1];
    bool *mstNodesMarked = new bool[numberOfNodes - 1]{false};

    std::cout << "Quantidade de arestas: " << numberOfEdges << "\n";
    sortArrayOfNodes(listEdges, lengthListEdges);
    DisjointSets ds(numberOfNodes);
    for (int i = 0; i < numberOfEdges; ++i)
    {
        int u = listEdges[i].src;
        int v = listEdges[i].dest;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        std::cout << "---"
                  << "\n";
        std::cout << "hashCode: " << excludedList[hashCode(u, v)] << "\n";
        std::cout << "u: " << u << "\n";
        std::cout << "v: " << v << "\n";
        std::cout << "set_u: " << set_u << "\n";
        std::cout << "set_v: " << set_v << "\n";

        if (excludedList[hashCode(u, v)])
            continue;
        if (set_u != set_v)
        {
            ds.merge(set_u, set_v);
            int weight = listEdges[i].weight;
            mstListEdges[countEdges] = {u, v, weight};
            totalWeight += weight;
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
    std::cout << "countNodes: " << countNodes << "\n";
    std::cout << "countEdges: " << countEdges << "\n";
    std::cout << "Peso total: " << totalWeight << "\n";
    std::cout << "Eh conectado: " << (int)(numberOfNodes == countNodes) << "\n";

    Graph g(countNodes + 1, countEdges, mstListEdges);
    Mst mst(g, totalWeight, numberOfNodes == countNodes);
    delete[] mstNodesMarked;
    delete[] mstListEdges;
    return mst;
}

class Comparison
{
    bool reverse;

public:
    Comparison(const bool &revparam = false)
    {
        reverse = revparam;
    }
    bool operator()(const Mst &lhs, const Mst &rhs) const
    {
        if (reverse)
            return (lhs.totalWeight > rhs.totalWeight);
        else
            return (lhs.totalWeight < rhs.totalWeight);
    }
};

void Graph::generateKSpanningTrees(int k)
{
    std::cout << numberOfNodes << numberOfEdges;
    typedef std::priority_queue<Mst, std::vector<Mst>, Comparison> pq;
    pq heap(Comparison(true));
    Mst graphMst = kruskalMST();
    heap.push(graphMst);
    Mst Ps = heap.top();
    while (!heap.empty() && Ps.totalWeight)
    {
        std::cout << Ps.totalWeight << std::endl;
        Ps = heap.top();
        heap.pop();
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
                heap.push(p1Mst);
            }
            p1 = p2;
        }
    }
}