#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

struct Node // struct para representar nos
{
    int value, weight;
    Node *next;
};

enum EdgeState // enum para representar os estados das arestas
{
    OPEN,
    INCLUDED,
    EXCLUDED,
};

struct Edge // struct para representar arestas
{
    int src, dest, weight;
    EdgeState state;
};


class Mst;

// Classe para representar um grafo
class Graph
{
public:
    Edge *listEdges;
    int lengthListEdges;
    int numberOfNodes;
    int numberOfEdges;
    std::string filename;
    std::string pathToSave;
    Graph(int V, int E, Edge edges[]);
    Graph(int V, int E, Edge edges[], std::string filename, std::string pathToSave);
    Graph(int V, int E);
    void addEdge(int src, int dest, int weight);
    void addEdges(Edge edges[]);
    Graph(const Graph &g2);
};

// Classe para representar uma árvore geradora mínima
class Mst
{
public:
    Graph currentGraph;
    Graph mstGraph;
    int totalWeight;
    int startCreatePartition;
    bool isConnected;

    Mst(Graph &gcurr, Graph &gmst, int t, int startPartition, bool c)
        : currentGraph(gcurr),
          mstGraph(gmst),
          totalWeight(t),
          startCreatePartition(startPartition),
          isConnected(c)
    {
    }

    Mst(bool conn = false) : currentGraph(Graph(0, 0)),
                             mstGraph(Graph(0, 0)),
                             totalWeight(0),
                             startCreatePartition(0),
                             isConnected(conn)
    {
    }

    Mst(const Mst &mst) : currentGraph(mst.currentGraph),
                          mstGraph(mst.mstGraph),
                          totalWeight(mst.totalWeight),
                          isConnected(mst.isConnected),
                          startCreatePartition(mst.startCreatePartition)
    {
    }

    ~Mst() {}

    bool operator<(Mst const &mst2)
    {
        return totalWeight < mst2.totalWeight;
    }
};

#endif
