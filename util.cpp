#include <iostream>
#include <fstream>
#include <random>
#include "util.hpp"

int getRandomNumber(int min = 1, int max = 20)
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
            edges[count] = {i, j, getRandomNumber()};
            count++;
        }
    }

    Graph graph(n, numberOfEdges, edges);
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

    Graph graph(n * m, numberOfEdges, edges);
    return graph;
}

void createFileForGraph(std::string &name, Graph g)
{
    std::ofstream file;
    file.open(name + ".in");

    if (!file.is_open())
        return;

    int numberOfNodes = g.getNumberOfNodes();

    file << numberOfNodes << "\n";

    for (int i = 0; i < numberOfNodes; ++i)
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

void sortArrayOfNodes(Edge edges[], int length)
{
    int i, j, flag = 1;
    Edge temp;
    for (i = length - 1; i > 0 && flag; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
                flag = 1;
            }
        }
    }
}

int hashCode(int a, int b)
{
    return a >= b ? a * a + a + b : a + b * b;
}