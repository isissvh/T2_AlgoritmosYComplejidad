#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

struct Capitulo {
    int t; // tiempo
    int c; // energía
    ll v;  // satisfacción
};

struct Anime {
    std::string nombre;
    int q; // cantidad de capítulos
    ll b;  // bono
    std::vector<Capitulo> capitulos;
};

struct Result {
    ll max_satisfaccion;
    double execution_time; // in seconds
    long long memory_usage; // in KB
};

// Signatures for algorithms
ll brute_force(int n, int M, int E, const std::vector<Anime>& animes);
ll dynamic_programming(int n, int M, int E, const std::vector<Anime>& animes);
ll greedy1(int n, int M, int E, const std::vector<Anime>& animes);
ll greedy2(int n, int M, int E, const std::vector<Anime>& animes);

#endif
