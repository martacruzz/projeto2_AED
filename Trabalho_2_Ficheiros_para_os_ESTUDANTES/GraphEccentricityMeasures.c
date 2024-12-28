//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Marta Cruz
// Student Number : 119572
// Student Name : Catarina Ribeiro
// Student Number : 119467

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures
{
  unsigned int *
      centralVertices; // centralVertices[0] = number of central vertices
                       // array size is (number of central vertices + 1)
  int *eccentricity;   // the eccentricity value of each vertex
  Graph *graph;        // the graph
  int graphRadius;     // the graph radius
  int graphDiameter;   // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures *GraphEccentricityMeasuresCompute(Graph *g)
{
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array

  // Verifica se o grafo é direcionado
  assert(GraphIsDigraph(g));

  // Verifica se o grafo não é ponderado
  assert(GraphIsWeighted(g) == 0);

  // Aloca memória para a estrutura principal
  GraphEccentricityMeasures *result = (GraphEccentricityMeasures *)malloc(sizeof(GraphEccentricityMeasures));
  assert(result != NULL); //verifica se a alocação de memória foi bem-sucedida

   // Associa o grafo original à estrutura de resultados
  result->graph = g;

  // Obtém a matriz de todas as menores distâncias entre os pares de vértices
  GraphAllPairsShortestDistances *distances = GraphAllPairsShortestDistancesExecute(g);

  // Obtém o número total de vértices no grafo
  unsigned int numVertices = GraphGetNumVertices(g);

  // Aloca memória para o array que armazenará a excentricidade de cada vértice
  result->eccentricity = (int *)malloc(numVertices * sizeof(int));
  assert(result->eccentricity != NULL); // Verifica se a alocação foi bem-sucedida

  // Inicializa o raio do grafo (menor excentricidade)
  int graphRadius = 0;

  // Inicializa o diâmetro do grafo (maior excentricidade)
  int graphDiameter = 0;

  // Loop principal para calcular a excentricidade de cada vértice
  for (unsigned int v = 0; v < numVertices; v++) {
    int maxDistance = 0; // Inicializa a maior distância para o vértice atual

    // Loop para verificar todas as distâncias do vértice v para os outros vértices
    for (unsigned int w = 0; w < numVertices; w++) {
      int distance = GraphGetDistanceVW(distances, v, w); // Obtém a distância de v para w
      if (distance != 0 && distance > maxDistance) { // Ignora distâncias iguais a 0
        maxDistance = distance; // Atualiza a maior distância encontrada
      }
    }

    result->eccentricity[v] = maxDistance; // Armazena a excentricidade do vértice v

    // Atualiza o raio e o diâmetro do grafo com base na excentricidade
    if (maxDistance != 0) { // Ignora vértices sem conecxões válidas
      if (graphRadius == 0 || maxDistance < graphRadius) {
        graphRadius = maxDistance; // Atualiza o raio se encontrar uma excentricidade menor
      }
      if (graphDiameter == 0 || maxDistance > graphDiameter) {
        graphDiameter = maxDistance; // Atualiza o diâmetro se encontrar uma excentricidade maior
      }
    }
  }

  // Armazena os valores calculados de raio e diâmetro na estrutura
  result->graphRadius = graphRadius;
  result->graphDiameter = graphDiameter;

  // Determina quantos vértices são centrais (com excentricidade igual ao raio)
  unsigned int numCentralVertices = 0;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (result->eccentricity[v] == graphRadius) {
      numCentralVertices++; // Incrementa o contador de vértices centrais
    }
  }

  // Aloca memória para o array que armazenará os vértices centrais
  result->centralVertices = (unsigned int *)malloc((numCentralVertices + 1) * sizeof(unsigned int));
  assert(result->centralVertices != NULL); // Verifica se a alocação foi bem-sucedida

  result->centralVertices[0] = numCentralVertices; // O primeiro elemento armazena o número de vértices centrais

  // Preenche o array de vértices centrais
  unsigned int index = 1;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (result->eccentricity[v] == graphRadius) {
      result->centralVertices[index++] = v; // Armazena o vértice central no array
    }
  }

  // Libera a memória utilizada pela matriz de distâncias
  GraphAllPairsShortestDistancesDestroy(&distances);

  // Retorna a estrutura contendo os resultados
  return result;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures **p)
{
  assert(*p != NULL);

  GraphEccentricityMeasures *aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures *p,
                               unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int *GraphGetCentralVertices(const GraphEccentricityMeasures *p)
{
  // Verifica se o ponteiro para a estrutura não é nulo
  assert(p != NULL);
  
  // Verifica se o array de vértices centrais na estrutura foi inicializado
  assert(p->centralVertices != NULL);

  // Obtém o número de vértices centrais do primeiro elemento do array
  unsigned int numCentralVertices = p->centralVertices[0];

  // Aloca memória para a cópia do array de vértices centrais, incluindo o tamanho no índice 0
  unsigned int *copy = (unsigned int *)malloc((numCentralVertices + 1) * sizeof(unsigned int));
  assert(copy != NULL); // Verifica se a alocação de memória foi bem-sucedida

  // Copia todos os elementos do array original para o array recém-alocado
  for (unsigned int i = 0; i <= numCentralVertices; i++) {
    copy[i] = p->centralVertices[i];
  }

  // Retorna o ponteiro para a cópia do array de vértices centrais
  return copy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures *p)
{
  assert(p != NULL);

  // Imprime o raio e o diâmetro do grafo
  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  // Imprime os valores de excentricidade de cada vértice
  printf("\nVertex Eccentricity:\n");
  unsigned int numVertices = GraphGetNumVertices(p->graph);
  for (unsigned int v = 0; v < numVertices; v++) {
    printf("  Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  // Imprime os vértices centrais
  unsigned int numCentralVertices = p->centralVertices[0];
  printf("\nThere are %u central vertices:\n", numCentralVertices);
  for (unsigned int v = 1; v <= numCentralVertices; v++) {
    printf("%u ", p->centralVertices[v]);
  }
  printf("\n");
}
