#ifndef UTIL_HPP
#define UTIL_HPP

#include "graph.hpp"
#include <string>

Graph createCompleteGraph(int n);
Graph createGridGraph(int n, int m);
void printList(Node *ptr, int i);
void createFileForGraph(std::string &name, Graph g);
int getRandomNumber(int min, int max);
Edge *sortArrayOfNodes(Edge edges[], int length);
int hashCode(int a, int b);

#endif