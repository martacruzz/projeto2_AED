// This module presents the testings done to obtain the matlab
// graphs necessary for the development of the technical report

// Created by: Marta Cruz (119572)

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

  BellmanInit();
  TransitiveInit();

  unsigned int MINVERTICE = atoi(argv[1]);
  unsigned int INCVERTICE = atoi(argv[2]);
  unsigned int MAXVERTICE = atoi(argv[3]);
  unsigned int CASE = atoi(argv[4]); // 0 -> bellman best ; 1 -> bellman worst; 2 -> transitive best; 3 -> transitive worst

  // Generate multiple graphs and output Instrumentation values
  Graph *g = NULL;
  GraphBellmanFordAlg *result_bellman = NULL;
  Graph *result_transitive = NULL;
  for (unsigned int i = MINVERTICE; i <= MAXVERTICE; i += INCVERTICE)
  {
    InstrReset();

    switch (CASE)
    {
    case 0:
      // bellman best case
      g = GraphGenerateBellmanFordBest(i);
      result_bellman = GraphBellmanFordAlgExecute(g, 0);
      GraphBellmanFordAlgDestroy(&result_bellman); // housekeeping;
      break;
    case 1:
      // bellman worst case
      g = GraphGenerateBellmanFordWorst(i);
      result_bellman = GraphBellmanFordAlgExecute(g, 0);
      GraphBellmanFordAlgDestroy(&result_bellman); // housekeeping;
      break;
    case 2:
      // transitive best case
      g = GraphGenerateTransitiveBest(i);
      result_transitive = GraphComputeTransitiveClosure(g);
      GraphDestroy(&result_transitive); // housekeeping;
      break;
    case 3:
      // transitive worst case
      g = GraphGenerateTransitiveWorst(i);
      result_transitive = GraphComputeTransitiveClosure(g);
      GraphDestroy(&result_transitive); // housekeeping;
      break;
    default:
      break;
    }
    InstrPrintTest(); // output data
    GraphDestroy(&g); // housekeeping;
  }
}