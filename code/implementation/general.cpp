/**
 * PROGRAMA PRINCIPAL: general.cpp
 * 
 * FUENTE: 
 * Este archivo implementa el flujo principal de ejecución, lectura de datos y medición 
 * de rendimiento (tiempo y memoria). La medición de memoria utiliza rusage (Linux).
 * Referencias: Documentación de <chrono> (cppreference.com) y <sys/resource.h> (man pages).
 * 
 * DESCRIPCIÓN:
 * Lee la entrada, ejecuta los 4 enfoques algorítmicos (Fuerza Bruta, DP, Greedy 1 y Greedy 2)
 * e imprime y guarda los resultados junto a los tiempos de ejecución y uso de memoria.
 */
#include "common.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

long get_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // En KB en Linux
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada>" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];
    std::ifstream infile(input_path);
    if (!infile.is_open()) {
        std::cerr << "No se pudo abrir " << input_path << std::endl;
        return 1;
    }

    int n, M, E;
    infile >> n >> M >> E;

    std::vector<Anime> animes(n);
    for (int i = 0; i < n; ++i) {
        infile >> animes[i].nombre >> animes[i].q >> animes[i].b;
        animes[i].capitulos.resize(animes[i].q);
        for (int j = 0; j < animes[i].q; ++j) {
            infile >> animes[i].capitulos[j].t >> animes[i].capitulos[j].c >> animes[i].capitulos[j].v;
        }
    }

    std::string base_name = fs::path(input_path).stem().string();
    std::string measure_file = "data/measurements/" + base_name + ".csv";
    std::ofstream out_measure(measure_file);
    out_measure << "algoritmo,n,M,E,satisfaccion,tiempo_ms,memoria_kb" << std::endl;

    auto run_and_measure = [&](const std::string& name, auto func) {
        // Solo correr Fuerza Bruta si n es pequeño
        if (name == "BruteForce" && n > 20) {
            std::cout << "Skipping BruteForce for " << base_name << " (n=" << n << ")" << std::endl;
            return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        ll res = func(n, M, E, animes);
        auto end = std::chrono::high_resolution_clock::now();
        
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        long mem = get_memory_usage();

        std::cout << "[" << name << "] Res: " << res << " | Time: " << duration << "ms | Mem: " << mem << "KB" << std::endl;
        out_measure << name << "," << n << "," << M << "," << E << "," << res << "," << duration << "," << mem << std::endl;
        
        // Guardar salida individual
        std::string output_file = "data/outputs/" + base_name + "_" + name + ".txt";
        std::ofstream out_res(output_file);
        out_res << res << std::endl;
    };

    run_and_measure("BruteForce", brute_force);
    run_and_measure("DynamicProgramming", dynamic_programming);
    run_and_measure("Greedy1", greedy1);
    run_and_measure("Greedy2", greedy2);

    return 0;
}
