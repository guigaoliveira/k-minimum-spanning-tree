#ifndef UTIL_HPP
#define UTIL_HPP

#include "graph.hpp"
#include <string>

Graph createCompleteGraph(int n);
Graph createGridGraph(int n, int m);
void printList(Node *ptr, int i);
void createFileForGraph(std::string &name, Graph g);
int getRandomNumber(int min, int max);
void SortArrayOfNodes(Edge edges[], int length);

#endif