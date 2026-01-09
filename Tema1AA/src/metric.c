#include "utils.h"

int solve_metric(Graph *g) {
    int dist[MAX_N][MAX_N];
    floyd_warshall(g, dist);

    Edge metric_edges[MAX_N * MAX_N];
    int m_count = 0;

    // Creăm graf complet între terminale
    for(int i=0; i < g->k; i++) {
        for(int j=i+1; j < g->k; j++) {
            int u = g->terminals[i];
            int v = g->terminals[j];
            if (dist[u][v] != INF) {
                metric_edges[m_count++] = (Edge){i, j, dist[u][v]}; 
                // NOTA: Folosim indicii 0..k-1 pentru algoritmul Kruskal pe graful metric
            }
        }
    }

    // Kruskal pe cele K terminale
    return kruskal_mst(g->k, metric_edges, m_count);
}