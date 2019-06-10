#ifndef GRAPH_HPP
#define GRAPH_HPP

struct Node
{
    int value, weight;
    Node *next;
};

struct Edge
{
    int src, dest, weight, state;
};

class Mst;

class Graph
{
private:
    Node *createAdjListNode(int value, int weight, Node *head);
    int numberOfNodes;
    int numberOfEdges;

public:
    Graph(int nOfVertices, int nOfEdges);
    Graph(int nOfVertices, int nOfEdges, Edge edges[]);
    ~Graph();
    Graph(const Graph &g2);
    Edge *listEdges;
    int lengthListEdges;
    Node **head;
    void addEdge(int src, int dest, int weight, int state = -1);
    void addEdges(Edge edges[]);
    int getNumberOfNodes();
    int getNumberOfEdges();
    Mst *kruskalMST();
    void generateKSpanningTrees(int k);
};

class Mst
{
public:
    Graph *graph;
    int totalWeight;
    bool isConnected;

    Mst(int t = 0, bool c = 0) : totalWeight(t), isConnected(c)
    {
        graph = new Graph(0, 0);
    }
    Mst(Graph *g, int t = 0, bool c = 0) : totalWeight(t), isConnected(c)
    {
        graph = g;
    }
    ~Mst()
    {
        delete graph;
    }
    Mst(Graph *g, int t, int c)
    {
        graph = g;
        totalWeight = t;
        isConnected = c;
    }
    bool operator<(Mst const &mst2)
    {
        return totalWeight < mst2.totalWeight;
    }
};

#endif
