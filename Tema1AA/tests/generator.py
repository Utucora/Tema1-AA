import random
import os

def generate_test_file(filename, N, M, T_count, max_cost=20):
    """
    Genereaza fisier conform imaginii:
    Linia 1: N M T
    Linia 2: T indici (terminalele)
    Urmatoarele M linii: X Y C
    """
    # Validari de siguranta
    if M < N - 1: M = N - 1 # Minim arbore
    max_edges = N * (N - 1) // 2
    if M > max_edges: M = max_edges
    if T_count > N: T_count = N

    with open(filename, 'w') as f:
        # Linia 1
        f.write(f"{N} {M} {T_count}\n")
        
        # Linia 2: Terminalele
        terminals = random.sample(range(N), T_count)
        f.write(" ".join(map(str, terminals)) + "\n")
        
        edges = set()
        
        # 1. Construim un schelet conex (Arbore)
        # Conectam fiecare nod i cu un nod anterior random
        for i in range(1, N):
            parent = random.randint(0, i-1)
            cost = random.randint(1, max_cost)
            f.write(f"{parent} {i} {cost}\n")
            edges.add(tuple(sorted((parent, i))))
            
        # 2. Umplem restul de muchii pana la M
        remaining = M - (N - 1)
        while remaining > 0:
            u = random.randint(0, N-1)
            v = random.randint(0, N-1)
            if u != v:
                edge = tuple(sorted((u, v)))
                if edge not in edges:
                    cost = random.randint(1, max_cost)
                    f.write(f"{u} {v} {cost}\n")
                    edges.add(edge)
                    remaining -= 1

if __name__ == "__main__":
    if not os.path.exists("in"):
        os.makedirs("in")

    print("Generare teste...")

    # --- CATEGORIA 1: TESTE MICI (N <= 20) ---
    # Pentru validare Exact vs Euristici (conform restrictiilor din imagine)
    
    # Test 6: Mic dar dens
    generate_test_file("in/test06.txt", N=15, M=40, T_count=5)
    
    # Test 7: Maximul admis de algoritmul exact
    generate_test_file("in/test07.txt", N=20, M=30, T_count=8)
    
    # --- CATEGORIA 2: TESTE MEDII/MARI (N > 20) ---
    # ATENTIE: Pe acestea NU rulam algoritmul Exact (va da timeout).
    # Le folosim strict pentru a compara Metric vs Greedy in grafice.
    # Formatul ramane IDENTIC.
    
    generate_test_file("in/test_medium_01.txt", N=50, M=100, T_count=10)
    generate_test_file("in/test_large_01.txt", N=100, M=300, T_count=20)
    
    print("Fisiere generate in folderul 'tests/in/'")