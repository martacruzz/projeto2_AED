//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Marta Cruz
// Student Number : 119572
// Student Name : Catarina Ribeiro
// Student Number : 119467

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph *GraphComputeTransitiveClosure(Graph *g)
{
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE
  unsigned int numVertices = GraphGetNumVertices(g);
  Graph *rslt = GraphCreate(numVertices, 1, 0); // pointer that will hold the transitive closure of g

  for (unsigned int v = 0; v < numVertices; v++) // for each vertex of g
  {
    // generate the spanning tree to each other vertex
    GraphBellmanFordAlg *spanningTree = GraphBellmanFordAlgExecute(g, v);

    // add edge from v to all reachable vertices
    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++)
    {
      if (GraphBellmanFordAlgReached(spanningTree, i) == 1) // if i is reachable through v
      {
        GraphAddEdge(rslt, v, i); // add edge from v to i
      }
    }

    GraphBellmanFordAlgDestroy(&spanningTree); // housekeeping
  }

  return rslt;
}
