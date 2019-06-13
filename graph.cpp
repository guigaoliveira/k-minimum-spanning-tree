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
    listEdges[lengthListEdges] = {src, dest, weight, EdgeState::OPEN};
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
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;
    Edge *mstListEdges = new Edge[numberOfNodes - 1];
    bool *mstNodesMarked = new bool[numberOfNodes - 1]{false};

    Edge *listEdgesSorted = sortArrayOfNodes(listEdges, lengthListEdges);
    DisjointSets ds(numberOfNodes);

    for (int i = 0; i < lengthListEdges; ++i)
    {
        int u = listEdgesSorted[i].src;
        int v = listEdgesSorted[i].dest;
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // std::cout << "state: " << listEdgesSorted[i].state << "\n";

        if (listEdgesSorted[i].state == EdgeState::EXCLUDED)
        {
            continue;
        }
        if (set_u != set_v)
        {
            int weight = listEdgesSorted[i].weight;
            mstListEdges[countEdges] = {u, v, weight, listEdgesSorted[i].state};
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
            ds.merge(set_u, set_v);
        }
    }

    Mst mst(*this, totalWeight, countEdges, numberOfNodes == countNodes);
    delete[] mstNodesMarked;
    delete[] mstListEdges;
    return mst;
}

bool compare(Mst i, Mst j) { return i.totalWeight < j.totalWeight; }

void partition(Mst &Ps, std::vector<Mst> &heap)
{
    Graph p = Graph(Ps.currentGraph.numberOfNodes, Ps.currentGraph.numberOfEdges, Ps.currentGraph.listEdges);
    Graph p1 = Graph(Ps.currentGraph.numberOfNodes, Ps.currentGraph.numberOfEdges, Ps.currentGraph.listEdges);
    Graph p2 = Graph(Ps.currentGraph.numberOfNodes, Ps.currentGraph.numberOfEdges, Ps.currentGraph.listEdges);

    for (int i = 0; i < p.numberOfEdges; ++i)
    {
        Edge edge = p.listEdges[i];

        if (edge.state == EdgeState::OPEN)
        {
            p1.listEdges[i].state = EdgeState::EXCLUDED;
        }

        Mst p1Mst = p1.kruskalMST();

        if (p1Mst.isConnected)
        {
            std::cout << p1Mst.totalWeight;
            heap.push_back(p1Mst);
        }

        p2.listEdges[i].state = EdgeState::INCLUDED;

        p1 = p2;
    }
}

void Graph::generateKSpanningTrees()
{
    std::vector<Mst> heap;
    Mst graphMst = kruskalMST();
    heap.push_back(graphMst);

    Mst Ps = *std::min_element(std::begin(heap), std::end(heap), compare);
    heap.erase(std::min_element(std::begin(heap), std::end(heap), compare));
    partition(Ps, heap);
}
