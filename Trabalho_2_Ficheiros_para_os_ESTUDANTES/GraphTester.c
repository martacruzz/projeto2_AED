// This module presents the testings done to obtain the matlab
// graphs necessary for the development of the technical report

// Created by: Marta Cruz

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphGenerator.h"
#include "GraphBellmanFordAlg.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"

int main(int argc, char **argv)
{
  if (argc < 5)
  {
    fprintf(stderr, "Usage: %s MIN_VERTICES INC_VERTICES MAX_VERTICES CASE\n", argv[0]);
    exit(1);
  }

  unsigned int MINVERTICE = argv[1];
  unsigned int INCVERTICE = argv[2];
  unsigned int MAXVERTICE = argv[3];
  unsigned int CASE = argv[4]; // 0 -> bellman best ; 1 -> bellman worst; 2 -> transitive best; 3 -> transitive worst

  // Generate multiple graphs and output Instrumentation values
  for (unsigned int i = MINVERTICE; i < MAXVERTICE; i += INCVERTICE)
  {
    InstrReset();

    switch (CASE)
    {
    case 0:
      // bellman best case
      Graph *g = GraphGenerateBellmanFordBest(i);
      break;
    case 1:
      // bellman worst case
      Graph *g = GraphGenerateBellmanFordWorst(i);
      break;
    case 2:
      // bellman best case
      Graph *g = GraphGenerateTransitiveBest(i);
      break;
    case 3:
      // bellman best case
      Graph *g = GraphGenerateTransitiveWorst(i);
      break;
    default:
      break;
    }
    InstrPrint(); // output data
  }
}