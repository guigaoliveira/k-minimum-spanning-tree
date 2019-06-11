#include <iostream>
#include <memory>
#include "heap.hpp"
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "util.hpp"
#include <queue>
#include <vector>

template class Heap<Mst>;

Graph::Graph(int nOfVertices, int nOfEdges)
{
    numberOfNodes = nOfVertices;
    head = new Node *[numberOfNodes]();
    numberOfEdges = nOfEdges;
    listEdges = new Edge[nOfEdges];
    lengthListEdges = 0;
    for (int i = 0; i < numberOfNodes; ++i)
        head[i] = nullptr;
}

Graph::Graph(int nOfVertices, int nOfEdges, Edge edges[]) : Graph(nOfVertices, nOfEdges)
{
    addEdges(edges);
}

Graph::~Graph()
{
    /* for (int i = 0; i < numberOfNodes; ++i)
    {
        delete[] head[i];
    }
    delete[] head;
    delete[] listEdges; */
}
Graph::Graph(const Graph &g2) : numberOfNodes(g2.numberOfNodes),
                                numberOfEdges(g2.numberOfEdges),
                                listEdges(g2.numberOfEdges ? new Edge[g2.numberOfEdges] : nullptr),
                                lengthListEdges(g2.lengthListEdges),
                                head(g2.numberOfNodes ? new Node *[numberOfNodes]() : nullptr)
{
    std::copy(g2.listEdges, g2.listEdges + numberOfEdges, listEdges);
    std::copy(g2.head, g2.head + numberOfNodes, head);
}

Node *Graph::createAdjListNode(int value, int weight, Node *next)
{
    Node *newNode = new Node;
    newNode->value = value;
    newNode->weight = weight;
    newNode->next = next;
    return newNode;
}

void Graph::addEdge(int src, int dest, int weight, EdgeState state)
{
    head[src] = createAdjListNode(dest, weight, head[src]);
    head[dest] = createAdjListNode(src, weight, head[dest]);
    listEdges[lengthListEdges] = {src, dest, weight, state};
    lengthListEdges++;
}

void Graph::addEdges(Edge edges[])
{
    for (int i = 0; i < numberOfEdges; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight, edges[i].state);
}

int Graph::getNumberOfNodes()
{
    return numberOfNodes;
}

int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

Mst Graph::kruskalMST()
{
    int totalWeight = 0;
    int countEdges = 0;
    int countNodes = 0;
    std::cout << numberOfNodes - 1;
    std::unique_ptr<Edge[]> mstListEdges(new Edge[numberOfNodes - 1]);
    std::unique_ptr<bool[]> mstNodesMarked(new bool[numberOfNodes - 1]{false});

    sortArrayOfNodes(listEdges, lengthListEdges);
    DisjointSets ds(numberOfNodes);
    for (int i = 0; countEdges < numberOfNodes - 1; ++i)
    {
        int u = listEdges[i].src;
        int v = listEdges[i].dest;
        EdgeState state = listEdges[i].state;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v && state != EdgeState::EXCLUDED)
        {
            ds.merge(set_u, set_v);
            int weight = listEdges[i].weight;
            mstListEdges[countEdges] = {u, v, weight, state};
            totalWeight += weight;
            countEdges++;
            if (!mstNodesMarked[u])
            {
                mstNodesMarked[u] = true;
                countNodes++;
            }
            if (!mstNodesMarked[v])
            {
                mstNodesMarked[v] = true;
                countNodes++;
            }
        }
    }
    Graph g(countNodes, countEdges, mstListEdges.get());
    Mst mst(g, totalWeight, numberOfNodes == countNodes);
    return mst;
}

/* void partition(Graph &p, std::unique_ptr<Heap<Mst>> &heap)
{
    Graph p1 = p;
    Graph p2 = p;
    for (int i = 0; i < p.getNumberOfEdges(); ++i)
    {
        Edge edge = p.listEdges[i];
        if (edge.state == EdgeState::OPEN)
        {
            p1.listEdges[i].state = EdgeState::EXCLUDED;
            p2.listEdges[i].state = EdgeState::INCLUDED;
        }
        Mst graphMst = p1.kruskalMST();
        if (graphMst.isConnected)
        {
            heap->insert(graphMst);
        }
        p1 = p2;
    }
}
 */

class Comparison
{
    bool reverse;

public:
    Comparison(const bool &revparam = false)
    {
        reverse = revparam;
    }
    bool operator()(const Mst &lhs, const Mst &rhs) const
    {
        if (reverse)
            return (lhs.totalWeight > rhs.totalWeight);
        else
            return (lhs.totalWeight < rhs.totalWeight);
    }
};

void Graph::generateKSpanningTrees(int k)
{
    typedef std::priority_queue<Mst, std::vector<Mst>, Comparison> pq;
    pq heap(Comparison(true));
    Mst graphMst = kruskalMST();
    std::cout << graphMst.totalWeight;
    heap.push(graphMst);
    Mst Ps = heap.top();
    while (!heap.empty() && Ps.totalWeight)
    {
        Ps = heap.top();
        std::cout << Ps.totalWeight;
        heap.pop();
        Graph p = Ps.graph;
        Graph p1 = Ps.graph;
        Graph p2 = Ps.graph;
        for (int i = 0; i < p.getNumberOfEdges(); ++i)
        {
            Edge edge = p.listEdges[i];
            if (edge.state == EdgeState::OPEN)
            {
                p1.listEdges[i].state = EdgeState::EXCLUDED;
                p2.listEdges[i].state = EdgeState::INCLUDED;
            }
            p1.kruskalMST();
            /*  Mst graphMst = p1.kruskalMST();
            if (graphMst.isConnected)
            {
                //heap.push(graphMst);
            } */
            // p1 = p2;
        }
    }
}