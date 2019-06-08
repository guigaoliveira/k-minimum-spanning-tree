#include <iostream>
#include <fstream>
#include <random>
#include "util.hpp"

int getRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Graph createCompleteGraph(int n)
{
    int numberOfEdges = (n * (n - 1)) / 2;
    Edge edges[numberOfEdges];
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (i != j)
            {
                edges[count] = {i, j, getRandomNumber()};
                count++;
            }
        }
    }

    Graph graph(edges, numberOfEdges, n);
    return graph;
}

Graph createGridGraph(int n, int m)
{
    int numberOfEdges = (2 * n * m) - m - n;
    Edge edges[numberOfEdges];
    int count = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int nodeActual = i * m + j;
            if (j + 1 != m)
            {
                edges[count] = {nodeActual, nodeActual + 1, getRandomNumber()};
                count++;
            }
            if (i + 1 != n)
            {
                edges[count] = {nodeActual, nodeActual + m, getRandomNumber()};
                count++;
            }
        }
    }

    Graph graph(edges, numberOfEdges, n * m);
    return graph;
}

void createFileForGraph(std::string &name, Graph g)
{
    std::ofstream file;
    file.open(name + ".in");

    if (!file.is_open())
        return;

    int numberOfVertices = g.getNumberOfVertices();

    file << numberOfVertices << "\n";

    for (int i = 0; i < numberOfVertices; ++i)
    {
        Node *node = g.head[i];
        while (node != nullptr)
        {
            file << i << " " << node->value << " " << node->weight << "\n";
            node = node->next;
        }
    }

    file.close();
}