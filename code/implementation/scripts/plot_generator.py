import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

def generate_plots():
    csv_files = glob.glob("data/measurements/*.csv")
    if not csv_files:
        print("No se encontraron archivos CSV.")
        return

    df_list = [pd.read_csv(f) for f in csv_files]
    df = pd.concat(df_list, ignore_index=True)

    # Agrupar por algoritmo y n para obtener promedios
    grouped = df.groupby(['algoritmo', 'n']).mean().reset_index()

    output_dir = "data/plots"
    os.makedirs(output_dir, exist_ok=True)

    # Plot 1: Tiempo de Ejecución vs n
    plt.figure(figsize=(10, 6))
    for algo in grouped['algoritmo'].unique():
        subset = grouped[grouped['algoritmo'] == algo]
        plt.plot(subset['n'], subset['tiempo_ms'], marker='o', label=algo)
    plt.yscale('log')
    plt.xlabel('Cantidad de Animes (n)')
    plt.ylabel('Tiempo de Ejecución (ms) - Escala Log')
    plt.title('Tiempo de Ejecución según Tamaño de Entrada')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.savefig(os.path.join(output_dir, 'tiempo_vs_n.png'))
    plt.close()

    # Plot 2: Uso de Memoria vs n
    plt.figure(figsize=(10, 6))
    for algo in grouped['algoritmo'].unique():
        subset = grouped[grouped['algoritmo'] == algo]
        plt.plot(subset['n'], subset['memoria_kb'], marker='s', label=algo)
    plt.xlabel('Cantidad de Animes (n)')
    plt.ylabel('Uso de Memoria (KB)')
    plt.title('Uso de Memoria según Tamaño de Entrada')
    plt.legend()
    plt.grid(True)
    plt.savefig(os.path.join(output_dir, 'memoria_vs_n.png'))
    plt.close()

    # Plot 3: Calidad de Solución (Relativa a DynamicProgramming)
    plt.figure(figsize=(10, 6))
    dp_vals = grouped[grouped['algoritmo'] == 'DynamicProgramming'][['n', 'satisfaccion']].rename(columns={'satisfaccion': 'dp_sat'})
    
    for algo in ['Greedy1', 'Greedy2']:
        subset = grouped[grouped['algoritmo'] == algo]
        merged = pd.merge(subset, dp_vals, on='n')
        merged['ratio'] = merged['satisfaccion'] / merged['dp_sat']
        plt.plot(merged['n'], merged['ratio'], marker='x', label=f'Calidad {algo}')
    
    plt.xlabel('Cantidad de Animes (n)')
    plt.ylabel('Ratio de Calidad (Satisfacción Greedy / Satisfacción DP)')
    plt.title('Calidad de las Heurísticas Greedy respecto a la Solución Óptima')
    plt.legend()
    plt.grid(True)
    plt.savefig(os.path.join(output_dir, 'calidad_vs_n.png'))
    plt.close()

    print(f"Gráficos generados en {output_dir}")

if __name__ == "__main__":
    generate_plots()
