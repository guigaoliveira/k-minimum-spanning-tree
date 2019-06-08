#include <iostream>
#include "graph.hpp"

Node *Graph::createAdjListNode(int value, int weight, Node *head)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = head;
    return newNode;
}

Graph::Graph(Edge edges[], int nOfEdges, int nOfVertices)
{
    head = new Node *[nOfVertices]();
    numberOfVertices = nOfVertices;
    numberOfEdges = nOfEdges;

    for (int i = 0; i < nOfVertices; ++i)
        head[i] = NULL;

    for (int i = 0; i < nOfVertices; ++i)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        head[src] = createAdjListNode(dest, weight, head[src]);
        head[dest] = createAdjListNode(src, weight, head[dest]);
    }
}

int Graph::getNumberOfVertices()
{
    return numberOfVertices;
}

int Graph::getNumberOfEdges()
{
    return numberOfVertices;
}

Graph::~Graph()
{
    for (int i = 0; i < numberOfVertices; ++i)
    {
        delete[] head[i];
    }
    delete[] head;
}
