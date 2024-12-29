//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

#ifndef _GRAPH_TRANSITIVE_CLOSURE_
#define _GRAPH_TRANSITIVE_CLOSURE_

#include "Graph.h"

// Init Image library.  (Call once!)
// Currently, simply calibrate instrumentation and set names of counters.
void TransitiveInit(void);

Graph *GraphComputeTransitiveClosure(Graph *g);

#endif // _GRAPH_TRANSITIVE_CLOSURE_
