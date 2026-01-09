#include "utils.h"

// Helper specific: Kruskal doar pe un subset activ de noduri
static int kruskal_on_subset(Graph *g, int mask) {
    // Mapam nodurile din masca la un set contiguu pentru Union-Find
    // Dar folosim implementarea simplă: ignorăm muchiile care au capete în afara măștii
    
    // Reset Union-Find
    int parent[MAX_N];
    for(int i=0; i<g->n; i++) parent[i] = i;

    // Funcții locale find/unite (pentru a nu intra în conflict cu utils.c dacă nu sunt exportate)
    // Repetăm logica simplă aici sau o facem statică
    // Pentru simplitate, rescriem logica inline
    int mst_cost = 0;
    int edges_taken = 0;
    int nodes_in_subset = 0;
    
    for(int i=0; i<g->n; i++) 
        if((mask >> i) & 1) nodes_in_subset++;

    // Sortarea e deja făcută dacă apelăm qsort în main sau utils, 
    // dar pentru siguranță putem presupune că g->edge_list e sortată o singură dată la început
    // Vom sorta local o copie
    Edge local_edges[MAX_N*MAX_N];
    int le_count = 0;
    for(int i=0; i<g->edge_count; i++) {
        int u = g->edge_list[i].u;
        int v = g->edge_list[i].v;
        if ( ((mask >> u) & 1) && ((mask >> v) & 1) ) {
            local_edges[le_count++] = g->edge_list[i];
        }
    }
    
    // Sortare
    // (Putem folosi un qsort aici)
    extern int cmp_edges(const void *a, const void *b); // Din utils
    qsort(local_edges, le_count, sizeof(Edge), cmp_edges);

    // DSU logic
    int local_parent[MAX_N];
    for(int i=0; i<g->n; i++) local_parent[i] = i;
    
    for(int i=0; i<le_count; i++) {
        int u = local_edges[i].u;
        int v = local_edges[i].v;
        
        // Find
        int root_u = u; while(root_u != local_parent[root_u]) root_u = local_parent[root_u];
        int root_v = v; while(root_v != local_parent[root_v]) root_v = local_parent[root_v];
        
        if(root_u != root_v) {
            local_parent[root_u] = root_v; // Unite
            mst_cost += local_edges[i].cost;
            edges_taken++;
        }
    }

    if (nodes_in_subset > 0 && edges_taken != nodes_in_subset - 1) return INF;
    return mst_cost;
}


int solve_exact(Graph *g) {
    if (g->n > 20) return -1; // Prea mare pentru exact

    int min_cost = INF;
    int non_terminals[MAX_N];
    int nt_count = 0;

    for(int i=0; i<g->n; i++) {
        if(!g->is_terminal[i]) non_terminals[nt_count++] = i;
    }

    int limit = 1 << nt_count;
    for(int m=0; m < limit; m++) {
        int current_mask = 0;
        
        // Adaugă terminalele
        for(int t=0; t<g->k; t++) current_mask |= (1 << g->terminals[t]);
        
        // Adaugă subsetul de noduri Steiner
        for(int i=0; i<nt_count; i++) {
            if((m >> i) & 1) current_mask |= (1 << non_terminals[i]);
        }

        int cost = kruskal_on_subset(g, current_mask);
        if (cost < min_cost) min_cost = cost;
    }
    
    return min_cost;
}