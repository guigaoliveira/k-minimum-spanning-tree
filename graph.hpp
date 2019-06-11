#ifndef GRAPH_HPP
#define GRAPH_HPP

struct Node
{
    int value, weight;
    Node *next;
};

enum class EdgeState
{
    OPEN,
    INCLUDED,
    EXCLUDED
};

struct Edge
{
    int src, dest, weight;
    EdgeState state;
};

class Mst;

class Graph
{
private:
    Node *createAdjListNode(int value, int weight, Node *next);
    int numberOfNodes;
    int numberOfEdges;

public:
    explicit Graph(int nOfVertices, int nOfEdges, Edge edges[]);
    Graph(int nOfVertices, int nOfEdges);
    Graph(const Graph &g2);
    ~Graph();
    Edge *listEdges;
    int lengthListEdges;
    Node **head;
    void addEdge(int src, int dest, int weight, EdgeState state = EdgeState::OPEN);
    void addEdges(Edge edges[]);
    int getNumberOfNodes();
    int getNumberOfEdges();
    Mst kruskalMST();
    void generateKSpanningTrees(int k);
};

class Mst
{
public:
    Graph graph;
    int totalWeight;
    bool isConnected;

    Mst(Graph &g, int t = 0, bool c = 0) : graph(g), totalWeight(t), isConnected(c)
    {
    }
    Mst(int t = 0, bool c = 0) : graph(Graph(0, 0)), totalWeight(t), isConnected(c)
    {
    }
    Mst(Graph &g, int t, int c) : graph(g), totalWeight(t), isConnected(c)
    {
    }
    ~Mst()
    {
    }
    bool operator<(Mst const &mst2)
    {
        return totalWeight < mst2.totalWeight;
    }
};

#endif
