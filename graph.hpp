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
    Edge *listEdges;
    int lengthListEdges;
    Node **head;
    Graph(int nOfVertices, int nOfEdges);
    Graph(int nOfVertices, int nOfEdges, Edge edges[]);
    ~Graph();
    void addEdge(int src, int dest, int weight);
    void addEdges(Edge edges[]);
    int getNumberOfVertices();
    int getNumberOfEdges();
    Graph kruskalMST();
};

#endif
