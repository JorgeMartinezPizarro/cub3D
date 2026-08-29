def generar_xpm_tres_puertas():
    width, height = 128, 128
    
    def crear_matriz_puerta(estado):
        matriz = [[' ' for _ in range(width)] for _ in range(height)]
        for y in range(10, 118):
            for x in range(14, 114):
                if y == 10 or y == 117 or x == 14 or x == 113:
                    matriz[y][x] = '#'
                else:
                    if estado == 1: # Cerrada
                        matriz[y][x] = '='
                    elif estado == 2: # Entornada / Entreabierta
                        if x < 60: matriz[y][x] = '='
                        else: matriz[y][x] = ' '
                    elif estado == 3: # Abierta
                        if x < 35: matriz[y][x] = '='
                        else: matriz[y][x] = ' '
        if estado == 1: matriz[64][95] = '-'
        elif estado == 2: matriz[64][50] = '-'
        elif estado == 3: matriz[64][25] = '-'
        return matriz

    nombres = ["puerta_cerrada.xpm", "puerta_entornada.xpm", "puerta_abierta.xpm"]
    
    for i, nombre in enumerate(nombres, start=1):
        matriz = crear_matriz_puerta(i)
        with open(nombre, 'w') as f:
            f.write("/* XPM */\n")
            f.write(f"static char * {nombre.replace('.xpm', '')}_xpm[] = {{\n")
            f.write(f"\"{width} {height} 4 1\",\n")
            f.write("\"# c #3E2723\",\n")
            f.write("\"= c #8D6E63\",\n")
            f.write("\"- c #FFD54F\",\n")
            f.write("\"  c None\",\n")
            for y in range(height):
                f.write(f"\"{''.join(matriz[y])}\",\n")
            f.write("};\n")
        print(f"Generado: {nombre}")

generar_xpm_tres_puertas()