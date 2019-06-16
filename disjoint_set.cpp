
#include <iostream>
#include "disjoint_set.hpp"

DisjointSets::DisjointSets(int k)
{
    n = k;
    parents = new int[n + 1];
    ranks = new int[n + 1];

    // inicia todos os nos com ranks 0 e sendo pais de si mesmo
    for (int i = 0; i <= n; i++)
    {
        ranks[i] = 0;
        parents[i] = i;
    }
}

// Método para buscar o pai de um no "u" usando compressão de caminho
int DisjointSets::find(int u)
{
    if (u != parents[u])
        parents[u] = find(parents[u]);
    return parents[u];
}

// Método que faz a união por ranks de dois subconjuntos disjuntos
void DisjointSets::doUnion(int x, int y)
{
    x = find(x), y = find(y);

    if (ranks[x] > ranks[y])
        parents[y] = x;
    else
        parents[x] = y;

    if (ranks[x] == ranks[y])
        ranks[y]++;
}
