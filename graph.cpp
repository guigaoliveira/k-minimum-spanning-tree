#include "graph.hpp"

Graph::Graph(int V, int E)
{
    numberOfNodes = V;
    numberOfEdges = E;
    listEdges = new Edge[E];
    lengthListEdges = 0;
    filename = "";
    pathToSave = "";
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
                                lengthListEdges(g2.lengthListEdges),
                                filename(g2.filename),
                                pathToSave(g2.pathToSave)
{
    std::copy(g2.listEdges, g2.listEdges + numberOfEdges, listEdges);
}

// Método para adicionar uma aresta ao grafo
void Graph::addEdge(int src, int dest, int weight)
{
    listEdges[lengthListEdges] = {src, dest, weight, EdgeState::OPEN};
    lengthListEdges++;
}

// Método para adicionar arestas ao grafo
void Graph::addEdges(Edge edges[])
{
    for (unsigned int i = 0; i < numberOfEdges; ++i)
        addEdge(edges[i].src, edges[i].dest, edges[i].weight);
}