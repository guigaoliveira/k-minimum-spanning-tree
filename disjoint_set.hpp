#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

class DisjointSets // classe que implementa disjoint-sets (união-busca)
{
private:
    int *parents, *ranks;
    int n;

public:
    DisjointSets(int k);
    int find(int u);
    void doUnion(int x, int y);
};

#endif
