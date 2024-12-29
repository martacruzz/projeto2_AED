// Header file for GraphGenerator.c
// Describes functions that will be used in test modules

// Created by Marta Cruz : 119572

#ifndef _GRAPH_GENERATOR_
#define _GRAPH_GENERATOR_

#include "Graph.h"

Graph *GraphGenerateBellmanFordWorst(unsigned int numVertices);

Graph *GraphGenerateBellmanFordBest(unsigned int numVertices);

Graph *GraphGenerateTransitiveWorst(unsigned int numVertices);

Graph *GraphGenerateTransitiveBest(unsigned int numVertices);

#endif //_GRAPH_GENERATOR_