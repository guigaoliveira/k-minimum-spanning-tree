#include "graph.hpp"

Graph::Graph(int V, int E)
{
    numberOfNodes = V;
    head = new Node *[V]();
    numberOfEdges = E;
    listEdges = new Edge[E];
    lengthListEdges = 0;
    filename = "";
    pathToSave = "";
    for (unsigned int i = 0; i < numberOfNodes; ++i)
        head[i] = nullptr;
}

Graph::Graph(int V, int E, Edge edges[]) : Graph(V, E)
{
    addEdges(edges);
}

Graph::Graph(int V, int E, Edge edges[],
             std::string file = "",
             std::string path = "") : Graph(V, E)
{
    addEdges(edges);
    filename = file;
    pathToSave = path;
}

Graph::Graph(const Graph &g2) : numberOfNodes(g2.numberOfNodes),
                                numberOfEdges(g2.numberOfEdges),
                                listEdges(g2.numberOfEdges ? new Edge[g2.numberOfEdges] : nullptr),
                                head(g2.numberOfNodes ? new Node *[g2.numberOfNodes]() : nullptr),
                                lengthListEdges(g2.lengthListEdges),
                                filename(g2.filename),
                                pathToSave(g2.pathToSave)
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

void Graph::addEdge(int src, int dest, int weight)
{
    head[src] = createAdjListNode(dest, weight, head[src]);
    listEdges[lengthListEdges] = {src, dest, weight, EdgeState::OPEN};
    lengthListEdges++;
}

void Graph::addEdges(Edge edges[])
{
    for (unsigned int i = 0; i < numberOfEdges; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight);
}