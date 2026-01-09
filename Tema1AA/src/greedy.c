#include "utils.h"

int solve_greedy(Graph *g) {
    int dist[MAX_N][MAX_N];
    floyd_warshall(g, dist); // Precalculăm distanțele

    bool in_tree[MAX_N] = {0};
    // Pornim cu primul terminal
    in_tree[g->terminals[0]] = true;
    int connected_count = 1;
    int total_cost = 0;

    while (connected_count < g->k) {
        int best_dist = INF;
        int best_terminal_idx = -1;

        // Căutăm cel mai apropiat terminal care NU este încă în arbore
        for(int i=0; i < g->k; i++) {
            int u = g->terminals[i];
            if (in_tree[u]) continue;

            // Distanța minimă de la 'u' la ORICE nod deja din arbore (simulat prin terminale deja conectate)
            // Notă: Pentru simplitate, verificăm distanța față de terminalele deja conectate.
            // O versiune mai avansată ar ține minte toate nodurile din cale.
            for(int j=0; j < g->k; j++) {
                int v = g->terminals[j];
                if (in_tree[v]) {
                    if (dist[u][v] < best_dist) {
                        best_dist = dist[u][v];
                        best_terminal_idx = u;
                    }
                }
            }
        }

        if (best_terminal_idx != -1) {
            in_tree[best_terminal_idx] = true;
            total_cost += best_dist;
            connected_count++;
        } else {
            break; // Graf neconex
        }
    }

    return total_cost;
}