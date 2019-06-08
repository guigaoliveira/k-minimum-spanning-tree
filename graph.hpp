#ifndef GRAPH_HPP
#define GRAPH_HPP

struct Node
{
    int value, weight;
    Node *next;
};

struct Edge
{
    int src, dest, weight;
};

class Graph
{
private:
    Node *createAdjListNode(int value, int weight, Node *head);
    int numberOfVertices;
    int numberOfEdges;

public:
    Node **head;
    Graph(Edge edges[], int nOfEdges, int nOfVertices);
    ~Graph();
    int getNumberOfVertices();
    int getNumberOfEdges();
    int kruskalMST();
};

#endif
