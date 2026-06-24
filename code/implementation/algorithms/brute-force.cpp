/**
 * ALGORITMO: Fuerza Bruta (Backtracking)
 * 
 * FUENTE: 
 * Este algoritmo es una implementación clásica de búsqueda exhaustiva mediante 
 * backtracking para resolver problemas de optimización combinatoria. 
 * Referencia general: "Introduction to Algorithms" (Cormen et al.) - Capítulos sobre 
 * búsqueda exhaustiva.
 * 
 * COMPLEJIDAD:
 * Temporal: O(prod(qi + 1)), donde qi es la cantidad de capítulos del anime i.
 * Espacial: O(n) por la profundidad de la recursión.
 */

#include "../common.h"
#include <algorithm>

ll backtrack(int idx, int M, int E, const std::vector<Anime>& animes) {
    if (idx == (int)animes.size()) {
        return 0;
    }

    ll max_sat = 0;
    
    // Opción 1: No ver ningún capítulo de este anime (ki = 0)
    max_sat = backtrack(idx + 1, M, E, animes);

    // Opción 2: Ver un prefijo de capítulos ki (1 <= ki <= qi)
    ll current_t = 0;
    ll current_e = 0;
    ll current_v = 0;
    
    for (int k = 0; k < animes[idx].q; ++k) {
        current_t += animes[idx].capitulos[k].t;
        current_e += animes[idx].capitulos[k].c;
        current_v += animes[idx].capitulos[k].v;

        if (current_t <= M && current_e <= E) {
            ll bonus = (k == animes[idx].q - 1) ? animes[idx].b : 0;
            ll res = backtrack(idx + 1, M - current_t, E - current_e, animes);
            max_sat = std::max(max_sat, current_v + bonus + res);
        } else {
            // Si ya no cabe este prefijo, los más largos tampoco
            break;
        }
    }

    return max_sat;
}

ll brute_force(int n, int M, int E, const std::vector<Anime>& animes) {
    return backtrack(0, M, E, animes);
}
