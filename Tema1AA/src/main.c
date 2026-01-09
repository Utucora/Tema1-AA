#include <stdio.h>
#include <time.h>
#include "utils.h"

// Am adaugat un parametru nou: optimal_cost
// Daca optimal_cost este > 0, calculam eroarea. Daca e 0, afisam "N/A"
void run_algo(const char* name, int (*func)(Graph*), Graph *g, int optimal_cost) {
    clock_t start = clock();
    int cost = func(g);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    if (cost == -1) {
        // Skip case
        printf("%s, SKIP, 0.000, N/A\n", name);
    } else {
        if (optimal_cost > 0) {
            double error = ((double)(cost - optimal_cost) / optimal_cost) * 100.0;
            // Afisam: Algoritm, Cost, Timp, Eroare
            printf("%s, %d, %.6f, %.2f%%\n", name, cost, elapsed, error);
        } else {
            // Nu avem optim (test mare), deci nu putem calcula eroarea
            printf("%s, %d, %.6f, N/A\n", name, cost, elapsed);
        }
    }
}

int main() {
    Graph g;
    read_input(&g, stdin);

    int optimal_cost = 0;

    // 1. Exact (Doar dacă N <= 20)
    // Rulam Exact primul ca sa aflam Costul Optim
    if (g.n <= 20) {
        clock_t start = clock();
        optimal_cost = solve_exact(&g);
        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        
        // Pentru Exact, eroarea este mereu 0.00%
        printf("Exact, %d, %.6f, 0.00%%\n", optimal_cost, elapsed);
    } else {
        printf("Exact, SKIP, 0.000, N/A\n");
        optimal_cost = 0; // Semnifică faptul că nu cunoaștem optimul
    }

    // 2. Metric Closure (trimitem optimal_cost pentru comparatie)
    run_algo("Metric", solve_metric, &g, optimal_cost);

    // 3. Greedy (trimitem optimal_cost pentru comparatie)
    run_algo("Greedy", solve_greedy, &g, optimal_cost);

    return 0;
}