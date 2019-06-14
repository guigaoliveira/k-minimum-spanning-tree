#ifndef UTIL_HPP
#define UTIL_HPP

#include "graph.hpp"
#include "disjoint_set.hpp"
#include <string>
#include <fstream>
#include <sstream>

Graph createCompleteGraph(int n);
Graph createGridGraph(int n, int m);
void printList(Node *ptr, int i);
void createFileForGraph(std::string const &name, Graph g);
Graph readGraphFromFile(std::string filename, std::string graphType, std::string pathToSave);
int getRandomNumber(int min, int max);
Edge *mergeSort(Edge edges[], int inicio, int fim, Edge vetorAux[]);
Mst kruskalMST(Graph &g);
void generateKSpanningTrees(Graph &g);
bool isConnected(DisjointSets &ds, int numberOfEdges);

#endif