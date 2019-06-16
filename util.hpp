#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <iostream>
#include "graph.hpp"
#include "disjoint_set.hpp"
#include "min_heap.hpp"

Graph createCompleteGraph(int n);
Graph createGridGraph(int n, int m);
void printList(Node *ptr, int i);
void createFileForGraph(std::string const &name, Graph g);
Graph readGraphFromFile(std::string filename, std::string graphType, std::string pathToSave);
int getRandomNumber(int min, int max);
void mergeSort(Edge edges[], int start, int end, Edge aux[]);
Mst kruskalMST(Graph &g);
void generateKSpanningTrees(Graph &g);
bool isConnected(DisjointSets &ds, int numberOfEdges);

#endif