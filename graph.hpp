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
    Edge *listEdges;
    Node **head;
    int lengthListEdges;
    bool *excludedList;
    bool *includedList;
    int hashLengthMax;
    void addEdge(int src, int dest, int weight);
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
    Mst(Graph &g, int t, bool c) : graph(g), totalWeight(t), isConnected(c)
    {
    }
    Mst(int t = 0, bool c = 0) : graph(Graph(0, 0)), totalWeight(t), isConnected(c)
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
