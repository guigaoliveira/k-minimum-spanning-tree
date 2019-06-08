#include <iostream>
#include <algorithm>
#include "graph.hpp"
#include "disjoint_set.hpp"

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
        head[i] = nullptr;

    for (int i = 0; i < nOfVertices; ++i)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        head[src] = createAdjListNode(dest, weight, head[src]);
        head[dest] = createAdjListNode(src, weight, head[dest]);
    }
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
    return numberOfVertices;
}

bool compareWeight(Node *head1, Node *head2)
{
    return (head1->weight < head2->weight);
}

int Graph::kruskalMST()
{
    int mst_wt = 0;

    std::sort(head, sizeof(head) / sizeof(head[0]), compareWeight);

    DisjointSets ds(numberOfVertices);

    for (int i = 0; i < numberOfEdges - 1; i++)
    {
        Node *node = head[i];
        int u = i;
        int v = node->value;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v)
        {
            std::cout << u << " - " << v << std::endl;
            mst_wt += node->weight;
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
    return 0;
}