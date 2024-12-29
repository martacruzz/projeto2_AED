// This module creates 4 generator functions that represent
// the best / worst case for the Bellman-Ford and
// Transitive-closure algorithms

// Created by Marta Cruz : 119572

#include "GraphGenerator.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Graph.h"

Graph *GraphGenerateBellmanFordWorst(unsigned int numVertices)
{
  // Generate complete unweighted digraph (WC for the bellman-ford module)
  Graph *g = GraphCreateComplete(numVertices, 1);
  return g;
}

Graph *GraphGenerateBellmanFordBest(unsigned int numVertices)
{
  // Generate a single-leveled graph with root on 0 for example (BC for the bellman-ford module)
  Graph *g = GraphCreate(numVertices, 1, 0);

  for (unsigned int v = 1; v < numVertices; v++)
  {
    GraphAddEdge(g, 0, v);
  }
  return g;
}

Graph *GraphGenerateTransitiveWorst(unsigned int numVertices)
{
  // Generate a complete graph (WC for transitive closure module)
  Graph *g = GraphCreateComplete(numVertices, 1);
  return g;
}

Graph *GraphGenerateTransitiveBest(unsigned int numVertices)
{
  // Generate a single-leveled graph with root on 0 for example (BC for the transitive closure module)
  Graph *g = GraphCreate(numVertices, 1, 0);

  for (unsigned int v = 1; v < numVertices; v++)
  {
    GraphAddEdge(g, 0, v);
  }
  return g;
}