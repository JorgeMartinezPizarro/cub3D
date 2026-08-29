def generar_xpm_piedra(nombre="piedra_128.xpm"):
    ancho, alto = 128, 128
    # Usaremos 4 tonos de gris para simular textura de roca
    colores = {
        " ": "#808080",
        ".": "#606060",
        "X": "#A0A0A0",
        "O": "#404040"
    }
    
    import random
    random.seed(42)
    caracteres = list(colores.keys())
    
    lineas = [
        "/* XPM */",
        f"static char * piedra_128[] = {{",
        f"\"{ancho} {alto} {len(colores)} 1\","
    ]
    for codigo, hex_val in colores.items():
        lineas.append(f"\"{codigo} c {hex_val}\",")
        
    for y in range(alto):
        fila = "".join(random.choices(caracteres, weights=[40, 30, 20, 10], k=ancho))
        lineas.append(f"\"{fila}\",")
    
    lineas[-1] = lineas[-1].rstrip(",") + "};"
    with open(nombre, "w") as f:
        f.write("\n".join(lineas))

def generar_xpm_madera(nombre="madera_128.xpm"):
    ancho, alto = 128, 128
    colores = {
        "a": "#8B4513", # Marrón oscuro
        "b": "#A0522D", # Marrón medio
        "c": "#CD853F"  # Marrón claro
    }
    
    import math
    lineas = [
        "/* XPM */",
        f"static char * madera_128[] = {{",
        f"\"{ancho} {alto} {len(colores)} 1\","
    ]
    for codigo, hex_val in colores.items():
        lineas.append(f"\"{codigo} c {hex_val}\",")
        
    keys = list(colores.keys())
    for y in range(alto):
        fila = []
        for x in range(ancho):
            val = int((math.sin(x * 0.1 + y * 0.02) + 1) * 1.5) % len(keys)
            fila.append(keys[val])
        lineas.append(f"\"{''.join(fila)}\",")
        
    lineas[-1] = lineas[-1].rstrip(",") + "};"
    with open(nombre, "w") as f:
        f.write("\n".join(lineas))

def generar_xpm_ladrillo(nombre="ladrillo_128.xpm"):
    ancho, alto = 128, 128
    colores = {
        "#": "#D3D3D3", # Mortero (gris)
        "R": "#B22222", # Ladrillo rojo
        "r": "#8B0000"  # Ladrillo oscuro
    }
    
    lineas = [
        "/* XPM */",
        f"static char * ladrillo_128[] = {{",
        f"\"{ancho} {alto} {len(colores)} 1\","
    ]
    for codigo, hex_val in colores.items():
        lineas.append(f"\"{codigo} c {hex_val}\",")
        
    for y in range(alto):
        fila = []
        es_linea_mortero = (y % 16 == 0)
        offset = 16 if (y // 16) % 2 == 1 else 0
        for x in range(ancho):
            if es_linea_mortero:
                fila.append("#")
            else:
                x_mod = (x + offset) % 32
                if x_mod == 0:
                    fila.append("#")
                else:
                    fila.append("R" if (x + y) % 3 == 0 else "r")
        lineas.append(f"\"{''.join(fila)}\",")
        
    lineas[-1] = lineas[-1].rstrip(",") + "};"
    with open(nombre, "w") as f:
        f.write("\n".join(lineas))

def generar_xpm_metal(nombre="metal_128.xpm"):
    ancho, alto = 128, 128
    colores = {
        "0": "#202020", "1": "#404040", "2": "#606060",
        "3": "#808080", "4": "#A0A0A0", "5": "#C0C0C0"
    }
    
    import random
    random.seed(100)
    lineas = [
        "/* XPM */",
        f"static char * metal_128[] = {{",
        f"\"{ancho} {alto} {len(colores)} 1\","
    ]
    for codigo, hex_val in colores.items():
        lineas.append(f"\"{codigo} c {hex_val}\",")
        
    keys = list(colores.keys())
    for y in range(alto):
        fila = []
        for x in range(ancho):
            base = (x + y) % len(keys)
            ruido = random.choice([-1, 0, 1])
            idx = max(0, min(len(keys) - 1, base + ruido))
            fila.append(keys[idx])
        lineas.append(f"\"{''.join(fila)}\",")
        
    lineas[-1] = lineas[-1].rstrip(",") + "};"
    with open(nombre, "w") as f:
        f.write("\n".join(lineas))

if __name__ == "__main__":
    generar_xpm_piedra()
    generar_xpm_madera()
    generar_xpm_ladrillo()
    generar_xpm_metal()