/**
 * ALGORITMO: Greedy 2 (Mejor Prefijo Global)
 * 
 * FUENTE: 
 * Adaptación de la heurística greedy para el problema de la mochila con opciones 
 * excluyentes. 
 * Referencia: "Heuristic Search" (Stefan Edelkamp, Stefan Schrödl).
 * 
 * CRITERIO LOCAL:
 * En cada iteración, se analizan todos los prefijos posibles (de 1 a qi capítulos) 
 * de todos los animes que aún no han sido seleccionados.
 * Se elige el prefijo con el mejor ratio: satisfacción_total / (tiempo_total + energía_total).
 * Una vez seleccionado un prefijo para un anime, este anime se marca como utilizado.
 * 
 * COMPLEJIDAD:
 * Temporal: O(n * n * max(qi))
 * Espacial: O(n)
 */

#include "../common.h"
#include <vector>
#include <algorithm>

ll greedy2(int n, int M, int E, const std::vector<Anime>& animes) {
    std::vector<bool> used(n, false);
    ll total_sat = 0;
    int rem_M = M;
    int rem_E = E;

    while (true) {
        int best_anime = -1;
        int best_ki = -1;
        double best_ratio = -1.0;

        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;

            ll cur_t = 0;
            ll cur_e = 0;
            ll cur_v = 0;

            for (int k = 0; k < animes[i].q; ++k) {
                cur_t += animes[i].capitulos[k].t;
                cur_e += animes[i].capitulos[k].c;
                cur_v += animes[i].capitulos[k].v;

                if (cur_t <= rem_M && cur_e <= rem_E) {
                    ll total_v = cur_v + (k == animes[i].q - 1 ? animes[i].b : 0);
                    double ratio = (double)total_v / (cur_t + cur_e);
                    
                    if (ratio > best_ratio) {
                        best_ratio = ratio;
                        best_anime = i;
                        best_ki = k;
                    }
                } else {
                    break; 
                }
            }
        }

        if (best_anime == -1) break;

        // Asignar el mejor prefijo encontrado
        used[best_anime] = true;
        ll cur_t = 0, cur_e = 0, cur_v = 0;
        for (int k = 0; k <= best_ki; ++k) {
            cur_t += animes[best_anime].capitulos[k].t;
            cur_e += animes[best_anime].capitulos[k].c;
            cur_v += animes[best_anime].capitulos[k].v;
        }
        rem_M -= cur_t;
        rem_E -= cur_e;
        total_sat += cur_v + (best_ki == animes[best_anime].q - 1 ? animes[best_anime].b : 0);
    }

    return total_sat;
}
