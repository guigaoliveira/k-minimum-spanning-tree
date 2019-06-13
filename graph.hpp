#include <algorithm>

#ifndef GRAPH_HPP
#define GRAPH_HPP

enum EdgeState
{
    OPEN,
    INCLUDED,
    EXCLUDED,
};

struct Node
{
    int value, weight;
    Node *next;
};

struct Edge
{
    int src, dest, weight;
    EdgeState state;
};

class Mst;

class Graph
{
public:
    Graph(int nOfVertices, int nOfEdges, Edge edges[]);
    Graph(int nOfVertices, int nOfEdges);
    Edge *listEdges;
    Node **head;
    int lengthListEdges;
    // bool *excludedList;
    // bool *includedList;
    int hashLengthMax;
    Node *createAdjListNode(int value, int weight, Node *next);
    int numberOfNodes;
    int numberOfEdges;
    void addEdge(int src, int dest, int weight);
    void addEdges(Edge edges[]);
    int getNumberOfNodes();
    int getNumberOfEdges();
    Mst kruskalMST();
    void generateKSpanningTrees();
};

class Mst
{
public:
    Graph currentGraph;
    //Graph mstGraph;
    int countEdges;
    int totalWeight;
    bool isConnected;
    /* Mst(Graph &gcurr, Graph &gmst, int t, bool c) : currentGraph(gcurr),
                                                    mstGraph(gmst), totalWeight(t), isConnected(c)
    {
    } */
    Mst(Graph &gcurr, int t, int nEdges, bool c) : currentGraph(gcurr),
                                                   countEdges(nEdges),
                                                   totalWeight(t), isConnected(c)
    {
    }
    /*     Mst(const Mst &mst) : currentGraph(mst.currentGraph),
                          //mstGraph(mst.mstGraph),
                          totalWeight(mst.totalWeight),
                          isConnected(mst.isConnected)
    {
    } */

    ~Mst()
    {
    }
    bool operator<(Mst const &mst2)
    {
        return totalWeight < mst2.totalWeight;
    }
};

#endif
