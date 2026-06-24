# Documentación de la Tarea 2 - AniMaraton

## Estructura del Proyecto

- `implementation/`: Contiene el código fuente en C++.
  - `algorithms/`: Implementación de los 4 enfoques (Brute Force, DP, Greedy 1, Greedy 2).
  - `general.cpp`: Programa principal que coordina la lectura de datos y mediciones.
  - `common.h`: Estructuras de datos compartidas.
  - `makefile`: Archivo para compilar y ejecutar pruebas.
- `scripts/`: Scripts en Python.
  - `testcases_generator.py`: Genera casos de prueba aleatorios.
  - `plot_generator.py`: Genera gráficos a partir de las mediciones guardadas en CSV.
- `data/`: Almacenamiento de entradas, salidas, mediciones y gráficos.

## Instrucciones de Compilación y Ejecución

Se ha habilitado un `makefile` automatizado dentro del directorio `implementation` que facilita la ejecución de todo el proyecto.

Para ejecutar la recolección y generación de datos de manera secuencial o en conjunto, entra al directorio primero:
```bash
cd implementation
```

### Ejecutar todo el proceso (Recomendado)
El siguiente comando automatiza todo: genera los casos, compila y ejecuta los algoritmos (con optimizaciones extremas), y genera los gráficos.
```bash
make clean && make
make pipeline
```

### Ejecución manual paso a paso
Si prefieres correr cada paso de manera individual:

1. **Generar Casos de Prueba**
   ```bash
   make generate
   ```

2. **Compilar y Ejecutar Algoritmos**
   ```bash
   make clean && make
   make run_all
   ```
   Esto generará archivos `.csv` en `data/measurements/` con los tiempos y uso de memoria.

3. **Generar Gráficos**
   ```bash
   make plot
   ```
   Los gráficos se guardarán en `data/plots/`.

## Algoritmos Implementados

1. **Fuerza Bruta**: Backtracking recursivo que explora todos los prefijos.
2. **Programación Dinámica**: Solución óptima mediante una matriz DP de dos dimensiones (tiempo y energía).
3. **Greedy 1**: Heurística que elige el siguiente capítulo con mejor ratio satisfacción/costo.
4. **Greedy 2**: Heurística que elige el mejor prefijo global disponible basado en el ratio total.
