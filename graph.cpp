#include <iostream>
#include "heap.hpp"
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "util.hpp"

template class Heap<Mst>;

Graph::Graph(int nOfVertices, int nOfEdges)
{
    numberOfNodes = nOfVertices;
    head = new Node *[numberOfNodes]();
    numberOfEdges = nOfEdges;
    listEdges = new Edge[nOfEdges];
    lengthListEdges = 0;
    for (int i = 0; i < numberOfNodes; ++i)
        head[i] = nullptr;
}

Graph::Graph(int nOfVertices, int nOfEdges, Edge edges[]) : Graph(nOfVertices, nOfEdges)
{
    addEdges(edges);
}

Graph::~Graph()
{
    for (int i = 0; i < numberOfNodes; ++i)
    {
        delete[] head[i];
    }

    delete[] head;
}
Graph::Graph(const Graph &g2) : numberOfEdges(g2.numberOfEdges),
                                numberOfNodes(g2.numberOfNodes),
                                listEdges(g2.numberOfEdges ? new Edge[g2.numberOfEdges] : nullptr),
                                lengthListEdges(g2.lengthListEdges)
{
    std::copy(g2.listEdges, g2.listEdges + numberOfEdges, listEdges);
    head = new Node *[numberOfNodes]();
    for (int i = 0; i < numberOfNodes; ++i)
        head[i] = g2.head[i];
}

Node *Graph::createAdjListNode(int value, int weight, Node *head)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = head;
    return newNode;
}

void Graph::addEdge(int src, int dest, int weight, int state)
{
    head[src] = createAdjListNode(dest, weight, head[src]);
    head[dest] = createAdjListNode(src, weight, head[dest]);
    listEdges[lengthListEdges] = {src, dest, weight, state};
    lengthListEdges++;
}

void Graph::addEdges(Edge edges[])
{
    for (int i = 0; i < numberOfEdges; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight, edges[i].state);
}

int Graph::getNumberOfNodes()
{
    return numberOfNodes;
}

int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

Mst *Graph::kruskalMST()
{
    int totalWeight = 0;
    Edge *mstListEdges = new Edge[numberOfNodes - 1];
    int countEdges = 0;
    bool *mstNodesMarked = new bool[numberOfNodes - 1]{false};
    int countNodes = 0;
    sortArrayOfNodes(listEdges, lengthListEdges);
    DisjointSets ds(numberOfNodes);

    for (int i = 0; countEdges < numberOfNodes - 1; ++i)
    {
        int u = listEdges[i].src;
        int v = listEdges[i].dest;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v && listEdges[i].state != 0)
        {
            ds.merge(set_u, set_v);
            int weight = listEdges[i].weight;
            mstListEdges[countEdges] = {u, v, weight, listEdges[i].state};
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

    Graph g(countNodes, countEdges, mstListEdges);
    delete[] mstNodesMarked;
    delete[] mstListEdges;
    Mst *mst = new Mst(&g, totalWeight, numberOfNodes == countNodes);
    return mst;
}

void partition(Graph *p, Heap<Mst> *list)
{
    Graph p1 = *p;
    Graph p2 = *p;
    for (int i = 0; i < p->getNumberOfEdges(); ++i)
    {
        Edge edge = p->listEdges[i];
        if (edge.state == -1)
        {
            p1.listEdges[i].state = 0;
            p2.listEdges[i].state = 1;
        }
        Mst *graphMst = p1.kruskalMST();
        if (graphMst->isConnected)
        {
            list->insert(*graphMst);
        }
        p1 = p2;
        delete graphMst;
    }
}

void Graph::generateKSpanningTrees(int k)
{
    Heap<Mst> *list = new Heap<Mst>(numberOfEdges * k);
    Mst *graphMst = kruskalMST();
    list->insert(*graphMst);
    Mst Ps;
    while (graphMst->totalWeight)
    {
        Ps = list->remove();
        partition(Ps.graph, list);
    }
}