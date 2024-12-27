//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : Marta Cruz
// Student Number : 119572
// Student Name : Catarina Ribeiro
// Student Number : 119467

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances
{
  int **distance; // The 2D matrix storing the all-pairs shortest distances
                  // It is stored as an array of pointers to 1D rows
                  // Idea: an INDEFINITE distance value is stored as -1
  Graph *graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances *GraphAllPairsShortestDistancesExecute(
    Graph *g)
{
  assert(g != NULL);

  // COMPLETE THE CODE

  // Verifica se o grafo é direcionado
  assert(GraphIsDigraph(g));

  // Verifica se o grafo não é ponderado
  assert(GraphIsWeighted(g) == 0);

  // Aloca memória para a estrutura que armazenará os resultados
  GraphAllPairsShortestDistances *result = (GraphAllPairsShortestDistances *)malloc(sizeof(GraphAllPairsShortestDistances));
  assert(result != NULL); // Garante que a alocação foi bem-sucedida

  // Associa o grafo original à estrutura de resultados
  result->graph = g;

  // Obtém o número total de vértices no grafo
  unsigned int numVertices = GraphGetNumVertices(g);

  // Aloca memória para a matriz de distâncias (array de ponteiros para linhas)
  result->distance = (int **)malloc(numVertices * sizeof(int *));
  assert(result->distance != NULL); // Garante que a matriz foi alocada corretamente

  // Itera sobre cada vértice do grafo para calcular as distâncias
  for (unsigned int v = 0; v < numVertices; v++) {
    // Aloca memória para a linha correspondente ao vértice v na matriz
    result->distance[v] = (int*)malloc(numVertices * sizeof(int));
    assert(result->distance[v] != NULL); // Verifica se a alocação foi bem feita

    // Executa o Algoritmo de Bellman-Ford para calcular as distâncias a partir do vértice v
    GraphBellmanFordAlg* bellman_alg = GraphBellmanFordAlgExecute(g, v);

    // Itera sobre todos os vértices para preencher as distâncias
    for (unsigned int u = 0; u < numVertices; u++) {
      // Se o vértice u for alcançável a partir do vértice v
      if (GraphBellmanFordAlgReached(bellman_alg, u)) {
        // Armazena a distância mínima de v até u na matriz
        result->distance[v][u] = GraphBellmanFordAlgDistance(bellman_alg, u);
      }
    }

    // Liberta os recursos usados pela execução do Algoritmo de Bellman-Ford
    GraphBellmanFordAlgDestroy(&bellman_alg);
  }

  return result;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances **p)
{
  assert(*p != NULL);

  GraphAllPairsShortestDistances *aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances *p, unsigned int v,
                       unsigned int w)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances *p)
{
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    for (unsigned int j = 0; j < numVertices; j++)
    {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1)
      {
        // INFINITY - j was not reached from i
        printf(" INF");
      }
      else
      {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
