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
    Edge *listEdges;
    int lengthListEdges;

public:
    Node **head;
    Graph(int nOfEdges, int nOfVertices);
    Graph(int nOfEdges, int nOfVertices, Edge edges[]);
    ~Graph();
    void addEdge(int src, int dest, int weight);
    void addEdges(Edge edges[]);
    int getNumberOfVertices();
    int getNumberOfEdges();
    int kruskalMST();
};

#endif
