#include <iostream>
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "util.hpp"

Node *Graph::createAdjListNode(int value, int weight, Node *head)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = head;
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
    for (int i = 0; i < numberOfVertices; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight);
}

Graph::Graph(int nOfVertices, int nOfEdges)
{
    head = new Node *[nOfVertices]();
    numberOfVertices = nOfVertices;
    numberOfEdges = nOfEdges;
    listEdges = new Edge[nOfEdges];
    lengthListEdges = 0;
    for (int i = 0; i < nOfVertices; ++i)
        head[i] = nullptr;
}

Graph::Graph(int nOfVertices, int nOfEdges, Edge edges[]) : Graph(nOfVertices, nOfEdges)
{
    addEdges(edges);
}

Graph::~Graph()
{
    for (int i = 0; i < numberOfVertices; ++i)
    {
        delete[] head[i];
    }

    delete[] head;
}

int Graph::getNumberOfVertices()
{
    return numberOfVertices;
}

int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

Graph Graph::kruskalMST()
{
    Edge *mstListEdges = new Edge[numberOfVertices - 1];
    int mstListEdgeCount = 0;

    SortArrayOfNodes(listEdges, lengthListEdges);
    DisjointSets ds(numberOfVertices);

    for (int i = 0; mstListEdgeCount < numberOfVertices - 1; ++i)
    {
        int u = listEdges[i].src;
        int v = listEdges[i].dest;
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            mstListEdges[mstListEdgeCount] = {u, v, listEdges[i].weight};
            ds.merge(set_u, set_v);
            mstListEdgeCount++;
        }
    }

    Graph g(numberOfVertices, mstListEdgeCount, mstListEdges);
    return g;
}