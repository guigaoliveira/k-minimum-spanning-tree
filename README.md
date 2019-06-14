# Implementação do algoritmo de Sörensen & Janssens para K-melhor Árvore Geradora Mínima. (ou tentativa)

### Projeto para a disciplina de Estrutura de Dados (UFRN).

## Para rodar
Usando o "clang" podemos compilar com o seguinte comando: 

```bash
    clang++ -std=c++14 -o test tests/nome_arquivo_de_teste.cpp graph.cpp util.cpp disjoint_set.cpp
    ./test
```

Para rodar uma instância de um grafo completo ou grid: 

```bash
    clang++ -std=c++14 -o test tests/test_instance.cpp graph.cpp util.cpp disjoint_set.cpp
    ./test tipo_do_grafo/nome_arquivo.in tipo_do_grafo path_do_arquivo 
```

