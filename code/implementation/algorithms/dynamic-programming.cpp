/**
 * ALGORITMO: Programación Dinámica
 * 
 * FUENTE: 
 * Este algoritmo es una adaptación del Problema de la Mochila (Knapsack Problem)
 * para múltiples dimensiones (tiempo y energía) y opciones mutuamente excluyentes 
 * (Multiple-Choice Multidimensional Knapsack Problem).
 * Referencia: "Knapsack Problems" (Kellerer, Pferschy, Speranza) - Capítulo 11.
 * 
 * COMPLEJIDAD:
 * Temporal: O(n * M * E * max(qi))
 * Espacial: O(M * E) - utilizando optimización de espacio para DP.
 */

#include "../common.h"
#include <vector>
#include <algorithm>

ll dynamic_programming(int n, int M, int E, const std::vector<Anime>& animes) {
    // Usamos un vector 1D para mejorar cache y velocidad de copiado
    // dp[m * (E + 1) + e] almacena la máxima satisfacción
    std::vector<ll> dp((M + 1) * (E + 1), 0);

    for (const auto& anime : animes) {
        std::vector<ll> next_dp = dp;

        ll prefix_t = 0;
        ll prefix_e = 0;
        ll prefix_v = 0;

        for (int k = 0; k < anime.q; ++k) {
            prefix_t += anime.capitulos[k].t;
            prefix_e += anime.capitulos[k].c;
            prefix_v += anime.capitulos[k].v;

            ll total_v = prefix_v + (k == anime.q - 1 ? anime.b : 0);

            if (prefix_t > M || prefix_e > E) break;

            for (int m = M; m >= prefix_t; --m) {
                for (int e = E; e >= prefix_e; --e) {
                    ll prev_val = dp[(m - prefix_t) * (E + 1) + (e - prefix_e)];
                    if (prev_val + total_v > next_dp[m * (E + 1) + e]) {
                        next_dp[m * (E + 1) + e] = prev_val + total_v;
                    }
                }
            }
        }
        dp = std::move(next_dp);
    }

    return dp[M * (E + 1) + E];
}
