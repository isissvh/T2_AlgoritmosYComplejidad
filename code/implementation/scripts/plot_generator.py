import pandas as pd
import matplotlib.pyplot as plt
import glob
import os
import sys

def generate_plots():
    # rutas para leer y guardar datos
    script_dir = os.path.dirname(os.path.abspath(__file__))
    base_dir = os.path.dirname(script_dir)
    measurements_dir = os.path.join(base_dir, "data", "measurements")
    plots_dir = os.path.join(base_dir, "data", "plots")

    csv_pattern = os.path.join(measurements_dir, "*.csv")
    csv_files = glob.glob(csv_pattern)

    # comprobar que existan los csv
    if not csv_files:
        print(f"No se encontraron archivos CSV en {measurements_dir}.")
        return

    df_list = [pd.read_csv(f) for f in csv_files]
    df = pd.concat(df_list, ignore_index=True)

    # chequear columnas
    required_cols = {'algoritmo', 'n', 'tiempo_ms', 'memoria_kb', 'satisfaccion'}
    if not required_cols.issubset(df.columns):
        missing = required_cols - set(df.columns)
        print(f"Error: Faltan las siguientes columnas requeridas en los CSV: {missing}")
        sys.exit(1)

    # calcular el promedio para cada n y algoritmo
    grouped = df.groupby(['algoritmo', 'n']).mean(numeric_only=True).reset_index()
    grouped = grouped.sort_values(by=['algoritmo', 'n'])

    os.makedirs(plots_dir, exist_ok=True)

    # Gráfico de tiempos
    plt.figure(figsize=(10, 6))
    for algo in grouped['algoritmo'].unique():
        subset = grouped[grouped['algoritmo'] == algo]
        plt.plot(subset['n'], subset['tiempo_ms'], marker='o', label=algo)
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Cantidad de Animes (n) - Escala Log')
    plt.ylabel('Tiempo de Ejecución (ms) - Escala Log')
    plt.title('Tiempo de Ejecución según Tamaño de Entrada')
    plt.legend()
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'tiempo_vs_n.png'), dpi=300)
    plt.close()
    
    # Gráfico zoom para ver mejor a Fuerza Bruta
    brute_force_n_values = grouped[grouped['algoritmo'] == 'BruteForce']['n'].unique()
    
    if len(brute_force_n_values) == 0:
        print("No se encontraron mediciones de BruteForce, no se puede generar el gráfico de zoom.")
    else:
        if len(brute_force_n_values) == 1:
            print("Advertencia: Solo hay un punto de BruteForce. La tendencia del zoom estará limitada.")
            
        zoom_subset = grouped[grouped['n'].isin(brute_force_n_values)]
        
        plt.figure(figsize=(10, 6))
        for algo in zoom_subset['algoritmo'].unique():
            sub = zoom_subset[zoom_subset['algoritmo'] == algo]
            plt.plot(sub['n'], sub['tiempo_ms'], marker='o', label=algo)
        
        # Escala lineal en X, log en Y
        plt.yscale('log')
        plt.xlabel('Cantidad de Animes (n)')
        plt.ylabel('Tiempo de Ejecución (ms) - Escala Log')
        plt.title('Zoom de Tiempo de Ejecución en Instancias Pequeñas')
        plt.legend()
        plt.grid(True, which="both", ls="--", alpha=0.5)
        plt.tight_layout()
        plt.savefig(os.path.join(plots_dir, 'tiempo_vs_n_zoom_bruteforce.png'), dpi=300)
        plt.close()

    # Gráfico de memoria
    plt.figure(figsize=(10, 6))
    for algo in grouped['algoritmo'].unique():
        subset = grouped[grouped['algoritmo'] == algo]
        plt.plot(subset['n'], subset['memoria_kb'], marker='s', label=algo)
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Cantidad de Animes (n) - Escala Log')
    plt.ylabel('Uso de Memoria (KB) - Escala Log')
    plt.title('Uso de Memoria según Tamaño de Entrada')
    plt.legend()
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'memoria_vs_n.png'), dpi=300)
    plt.close()

    # Gráfico de calidad (ratio greedy / DP)
    plt.figure(figsize=(10, 6))
    dp_vals = grouped[grouped['algoritmo'] == 'DynamicProgramming'][['n', 'satisfaccion']].rename(columns={'satisfaccion': 'dp_sat'})
    
    for algo in ['Greedy1', 'Greedy2']:
        subset = grouped[grouped['algoritmo'] == algo]
        merged = pd.merge(subset, dp_vals, on='n')
        # Calcular el ratio evitando división por cero
        merged['ratio'] = merged.apply(lambda row: row['satisfaccion'] / row['dp_sat'] if row['dp_sat'] != 0 else 0, axis=1)
        plt.plot(merged['n'], merged['ratio'], marker='x', label=f'Calidad {algo}')
    
    # Eje X en log, Eje Y lineal de 0 a 1.05
    plt.xscale('log')
    plt.ylim(0, 1.05)
    
    # Línea horizontal para Optimal DP
    plt.axhline(y=1.0, color='r', linestyle='--', label='Optimal DP')
    
    plt.xlabel('Cantidad de Animes (n) - Escala Log')
    plt.ylabel('Ratio de Calidad (Satisfacción Greedy / Satisfacción DP)')
    plt.title('Calidad de las Heurísticas Greedy respecto a la Solución Óptima')
    plt.legend()
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'calidad_vs_n.png'), dpi=300)
    plt.close()

    print(f"Gráficos generados en {plots_dir}")

if __name__ == "__main__":
    generate_plots()
