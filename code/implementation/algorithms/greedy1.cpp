/**
 * ALGORITMO: Greedy 1 (Siguiente Capítulo)
 * 
 * FUENTE: 
 * Estrategia heurística voraz clásica basada en el ratio de beneficio/costo. 
 * Referencia: "Greedy Algorithms" en "Introduction to Algorithms" (Cormen et al.).
 * 
 * CRITERIO LOCAL:
 * En cada paso, se evalúa el siguiente capítulo disponible de cada anime.
 * Se elige aquel capítulo que maximiza el ratio: satisfacción / (tiempo + energía).
 * Se repite hasta que ningún capítulo adicional quepa en los recursos restantes.
 * 
 * COMPLEJIDAD:
 * Temporal: O(Q * n), donde Q es el total de capítulos.
 * Espacial: O(n) para mantener el estado de progreso de cada anime.
 */

#include "../common.h"
#include <vector>
#include <algorithm>

ll greedy1(int n, int M, int E, const std::vector<Anime>& animes) {
    std::vector<int> current_cap(n, 0); // Indice del proximo capitulo a ver por anime
    std::vector<bool> anime_finished(n, false);
    ll total_sat = 0;
    int rem_M = M;
    int rem_E = E;

    while (true) {
        int best_anime = -1;
        double best_ratio = -1.0;

        for (int i = 0; i < n; ++i) {
            if (anime_finished[i]) continue;

            int cap_idx = current_cap[i];
            const auto& cap = animes[i].capitulos[cap_idx];

            if (cap.t <= rem_M && cap.c <= rem_E) {
                ll potential_v = cap.v;
                // Si es el ultimo capitulo, sumamos el bono al ratio
                if (cap_idx == animes[i].q - 1) {
                    potential_v += animes[i].b;
                }

                double ratio = (double)potential_v / (cap.t + cap.c);
                if (ratio > best_ratio) {
                    best_ratio = ratio;
                    best_anime = i;
                }
            }
        }

        if (best_anime == -1) break; // No se pueden agregar mas capitulos

        // Agregar capitulo
        int cap_idx = current_cap[best_anime];
        const auto& cap = animes[best_anime].capitulos[cap_idx];
        
        rem_M -= cap.t;
        rem_E -= cap.c;
        total_sat += cap.v;

        if (cap_idx == animes[best_anime].q - 1) {
            total_sat += animes[best_anime].b;
            anime_finished[best_anime] = true;
        } else {
            current_cap[best_anime]++;
        }
    }

    return total_sat;
}
