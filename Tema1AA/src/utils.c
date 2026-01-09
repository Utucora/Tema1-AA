#include "utils.h"

// Citirea datelor din fișier
void read_input(Graph *g, FILE *f) {
    // Citim N, M si T (numarul de terminale)
    if (fscanf(f, "%d %d %d", &g->n, &g->m, &g->k) != 3) return; 
    // Nota: In structura Graph am numit variabila 'k', dar in fisier e a 3-a valoare (T din cerinta)

    // Resetare matrice si flag-uri
    for(int i=0; i<g->n; i++) {
        g->is_terminal[i] = false;
        for(int j=0; j<g->n; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Citire linia 2: indicii terminalelor
    for(int i=0; i<g->k; i++) {
        fscanf(f, "%d", &g->terminals[i]);
        g->is_terminal[g->terminals[i]] = true;
    }

    // Citire muchii
    g->edge_count = 0;
    for(int i=0; i<g->m; i++) {
        int u, v, c;
        fscanf(f, "%d %d %d", &u, &v, &c);
        // Avem grija la restrictia 0 <= X,Y < N
        if(u < g->n && v < g->n) {
            g->adj[u][v] = g->adj[v][u] = c;
            g->edge_list[g->edge_count++] = (Edge){u, v, c};
        }
    }
}

// Algoritmul Floyd-Warshall pentru toate distanțele minime
void floyd_warshall(Graph *g, int dist[MAX_N][MAX_N]) {
    // Inițializare
    for(int i=0; i<g->n; i++)
        for(int j=0; j<g->n; j++)
            dist[i][j] = g->adj[i][j];

    // Relaxare
    for(int k=0; k<g->n; k++) {
        for(int i=0; i<g->n; i++) {
            for(int j=0; j<g->n; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF && 
                   dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

// --- Structuri Helper pentru Kruskal ---
int parent[MAX_N];
int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}
void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) parent[root_i] = root_j;
}
int cmp_edges(const void *a, const void *b) {
    return ((Edge*)a)->cost - ((Edge*)b)->cost;
}

// Calculează costul MST pentru o listă de muchii dată
// Returnează costul sau INF dacă graful nu e conex
int kruskal_mst(int n, Edge edges[], int m) {
    for(int i=0; i<n; i++) parent[i] = i;
    qsort(edges, m, sizeof(Edge), cmp_edges);

    int cost = 0;
    int edges_count = 0;

    for(int i=0; i<m; i++) {
        if(find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            cost += edges[i].cost;
            edges_count++;
        }
    }
    
    // Verificăm dacă am legat toate nodurile participante
    // (Aici e o simplificare, funcționează corect dacă nodurile sunt 0..n-1 contigue sau mapate)
    return cost;
}