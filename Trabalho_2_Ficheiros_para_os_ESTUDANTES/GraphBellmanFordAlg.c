//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Marta Cruz
// Student Number : 119572
// Student Name : Catarina Ribeiro
// Student Number : 119467

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "instrumentation.h"

// Init Image library.  (Call once!)
// Currently, simply calibrate instrumentation and set names of counters.
void BellmanInit(void)
{ ///
  InstrCalibrate();
  // Name counters here...
  InstrName[0] = "iterations";
}

// Macros to simplify accessing instrumentation counters:
// Add macros here...
#define ITERATIONS InstrCount[0]

struct _GraphBellmanFordAlg
{
  unsigned int *marked; // To mark vertices when reached for the first time
  int *distance;        // The number of edges on the path from the start vertex
                        // distance[i]=-1, if no path found from the start vertex to i
  int *predecessor;     // The predecessor vertex in the shortest path
                        // predecessor[i]=-1, if no predecessor exists
  Graph *graph;
  unsigned int startVertex; // The root of the shortest-paths tree
};

GraphBellmanFordAlg *GraphBellmanFordAlgExecute(Graph *g,
                                                unsigned int startVertex)
{
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));
  assert(GraphIsWeighted(g) == 0);

  GraphBellmanFordAlg *result =
      (GraphBellmanFordAlg *)malloc(sizeof(struct _GraphBellmanFordAlg));
  assert(result != NULL);

  // Given graph and start vertex for the shortest-paths
  result->graph = g;
  result->startVertex = startVertex;

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // TO BE COMPLETED !!
  //
  // CREATE AND INITIALIZE
  // result->marked
  // result->distance
  // result->predecessor
  //

  // Mark all vertices as not yet visited, i.e., ZERO
  result->marked = calloc(numVertices, sizeof(int));
  assert(result->marked != NULL);

  // No vertex has (yet) a (valid) predecessor
  result->predecessor = malloc(numVertices * sizeof(int));
  assert(result->predecessor != NULL);

  // No vertex has (yet) a (valid) distance to the start vertex
  result->distance = malloc(numVertices * sizeof(int));
  assert(result->distance != NULL);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    result->predecessor[i] = -1;
    result->distance[i] = -1;
  }

  // THE ALGORTIHM TO BUILD THE SHORTEST-PATHS TREE

  result->distance[startVertex] = 0; // set distance of starting node to 0
  unsigned int update = 0;

  // "relaxation" process
  // this process is done at most #v - 1 times
  for (unsigned int i = 0; i < GraphGetNumVertices(result->graph) - 1; i++) // for #v - 1 times
  {

    for (unsigned int v = 0; v < GraphGetNumVertices(result->graph); v++) // go through all vertices
    {

      unsigned int *adjacents = GraphGetAdjacentsTo(result->graph, v); // fetch adjacent vertices
      // the first position of the array points to the number of outgoing adjacent vertices of vertex v (number of edges of type v->adjacent)

      for (unsigned int e = 1; e <= adjacents[0]; e++) // for each edge (v -> adjacent)
      {
        unsigned int adj = adjacents[e]; // fetch adjacent vertex
        // if distance of predecessor (which is v in this case) is not -1 && distance[v] + 1 < distance[adjacent] -> update
        if (result->distance[v] != -1 && (result->distance[v] + 1 < result->distance[adj] || result->distance[adj] == -1))
        {
          result->distance[adj] = result->distance[v] + 1; // update distance
          result->predecessor[adj] = v;                    // update predecessor
          result->marked[adj] = 1;                         // mark vertex
          update = 1;                                      // state something changed
          ITERATIONS++;
        }
      }

      free(adjacents);
    }
    // if nothing changes in this iteration -> stop
    if (!update)
    {
      break;
    }
    update = 0;
  }

  return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg **p)
{
  assert(*p != NULL);

  GraphBellmanFordAlg *aux = *p;

  free(aux->marked);
  free(aux->predecessor);
  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}
Stack *GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0)
  {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current])
  {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg *p, unsigned int v)
{
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack *s = GraphBellmanFordAlgPathTo(p, v);

  while (StackIsEmpty(s) == 0)
  {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg *p)
{
  assert(p != NULL);

  Graph *original_graph = p->graph;
  unsigned int num_vertices = GraphGetNumVertices(original_graph);

  // The paths tree is a digraph, with no edge weights
  Graph *paths_tree = GraphCreate(num_vertices, 1, 0);

  // Use the predecessors array to add the tree edges
  for (unsigned int w = 0; w < num_vertices; w++)
  {
    // Vertex w has a predecessor vertex v?
    int v = p->predecessor[w];
    if (v != -1)
    {
      GraphAddEdge(paths_tree, (unsigned int)v, w);
    }
  }

  // Display the tree in the DOT format
  GraphDisplayDOT(paths_tree);

  // Housekeeping
  GraphDestroy(&paths_tree);
}
