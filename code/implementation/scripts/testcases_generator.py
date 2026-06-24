import random
import os

def generate_test_case(n, M, E, filename):
    """
    Genera un caso de prueba para el problema AniMaraton.
    n: cantidad de animes
    M: minutos disponibles
    E: energía disponible
    filename: ruta del archivo de salida
    """
    with open(filename, 'w') as f:
        f.write(f"{n} {M} {E}\n")
        
        # Asignamos 1 capitulo a cada anime inicialmente
        q_list = [1] * n
        extra_caps = 700 - n
        
        # Repartimos capitulos extra asegurando que ningun q_i exceda 30
        for i in range(n):
            if extra_caps <= 0:
                break
            add = random.randint(0, min(29, extra_caps))
            q_list[i] += add
            extra_caps -= add
            
        random.shuffle(q_list)
        
        for i in range(n):
            name = f"anime_{i+1}"
            qi = q_list[i]
            bi = random.randint(0, 10**6) # Limite teorico 10^9
            
            f.write(f"{name} {qi} {bi}\n")
            for j in range(qi):
                t = random.randint(1, 100) # El limite es 300, pero 100 es mas razonable para M=3000
                c = random.randint(1, 50)  # El limite es 100, pero 50 es mas razonable para E=500
                v = random.randint(1, 10**5)
                f.write(f"{t} {c} {v}\n")

if __name__ == "__main__":
    output_dir = "data/inputs"
    os.makedirs(output_dir, exist_ok=True)
    
    # Configuraciones de prueba
    sets = {
        "small": [3, 5, 8],
        "medium": [20, 40, 80],
        "large": [100, 150, 200]
    }
    
    for set_name, n_values in sets.items():
        for n in n_values:
            for i in range(3): # Generamos 3 casos por cada n
                # Ajustamos M y E segun el tamaño n
                # n=3, M=200, E=100 aprox
                # n=200, M=3000, E=500
                M = min(3000, max(100, n * 20))
                E = min(500, max(50, n * 5))
                filename = os.path.join(output_dir, f"testcases_{n}_{i+1}.txt")
                generate_test_case(n, M, E, filename)
                print(f"Generado: {filename}")
