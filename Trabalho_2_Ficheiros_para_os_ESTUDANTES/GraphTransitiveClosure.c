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

// Init Image library.  (Call once!)
// Currently, simply calibrate instrumentation and set names of counters.
void TopoInit(void)
{ ///
  InstrCalibrate();
  // Name counters here...
  InstrName[0] = "iterations";
}

// Macros to simplify accessing instrumentation counters:
// Add macros here...
#define ITERATIONS InstrCount[0]

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
    GraphBellmanFordAlg *spanningTree = GraphBellmanFordAlgExecute(g, v); // the cost of this operation is calculated internally

    // add edge from v to all reachable vertices
    for (unsigned int i = 0; i < numVertices; i++)
    {
      if (GraphBellmanFordAlgReached(spanningTree, i) == 1) // if i is reachable through v
      {
        GraphAddEdge(rslt, v, i); // add edge from v to i
        ITERATIONS++;
      }
    }

    GraphBellmanFordAlgDestroy(&spanningTree); // housekeeping
  }

  return rslt;
}
