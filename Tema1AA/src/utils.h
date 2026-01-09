#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 100       // Maxim noduri (pentru matrici statice)
#define INF 100000000   // O valoare suficient de mare pt infinit

// Structura pentru o muchie (folosită la Kruskal)
typedef struct {
    int u, v, cost;
} Edge;

// Structura principală a grafului
typedef struct {
    int n;              // Nr noduri
    int m;              // Nr muchii
    int k;              // Nr terminale
    int terminals[MAX_N];      // Lista indecșilor terminalelor
    bool is_terminal[MAX_N];   // Lookup rapid: e nodul i terminal?
    int adj[MAX_N][MAX_N];     // Matrice de adiacență (costuri)
    Edge edge_list[MAX_N * MAX_N]; // Lista muchiilor (pt Kruskal)
    int edge_count;
} Graph;

// --- Funcții din utils.c ---
void read_input(Graph *g, FILE *f);
void floyd_warshall(Graph *g, int dist[MAX_N][MAX_N]);
int kruskal_mst(int n, Edge edges[], int m);

// --- Funcții din algoritmi specifici ---
int solve_exact(Graph *g);
int solve_metric(Graph *g);
int solve_greedy(Graph *g);

#endif