def generar_xpm_cuadricula_2000s():
    width, height = 384, 256
    half_w = width // 2  # 192 píxeles por sub-imagen horizontal
    half_h = height // 2 # 128 píxeles por sub-imagen vertical
    
    # Matriz inicializada con espacios transparentes
    matriz = [[' ' for _ in range(width)] for _ in range(height)]
    
    def dibujar_manos_cuadrante(qx, qy, pose_tipo):
        ox = qx * half_w
        oy = qy * half_h
        
        # Paleta extendida para simular relieve y volumen poligonal típico del 2000:
        # 'A' = Sombra profunda / perfiles
        # 'B' = Sombra lateral / media
        # 'C' = Tono piel base
        # 'D' = Luz / brillo cenital
        
        if pose_tipo == 1: # Pose 1: Brazos rectos y palmas abiertas hacia adelante
            for y in range(int(oy + 75), int(oy + 128)):
                for x in range(int(ox + 42), int(ox + 72)):
                    matriz[y][x] = 'B' if x < ox + 50 else 'C'
                for x in range(int(ox + 120), int(ox + 150)):
                    matriz[y][x] = 'B' if x < ox + 128 else 'C'
            for y in range(int(oy + 38), int(oy + 80)):
                for x in range(int(ox + 35), int(ox + 79)):
                    dx, dy = x - (ox + 57), y - (oy + 59)
                    if dx*dx + dy*dy < 420:
                        if dy < -10: matriz[y][x] = 'D'
                        elif dx > 12: matriz[y][x] = 'A'
                        elif dx < -12: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'
                for x in range(int(ox + 113), int(ox + 157)):
                    dx, dy = x - (ox + 135), y - (oy + 59)
                    if dx*dx + dy*dy < 420:
                        if dy < -10: matriz[y][x] = 'D'
                        elif dx > 12: matriz[y][x] = 'A'
                        elif dx < -12: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'

        elif pose_tipo == 2: # Pose 2: Manos abiertas hacia los lados
            for y in range(int(oy + 70), int(oy + 128)):
                for x in range(int(ox + 28), int(ox + 58)):
                    matriz[y][x] = 'B' if x < ox + 36 else 'C'
                for x in range(int(ox + 126), int(ox + 156)):
                    matriz[y][x] = 'B' if x < ox + 134 else 'C'
            for y in range(int(oy + 32), int(oy + 78)):
                for x in range(int(ox + 22), int(ox + 68)):
                    dx, dy = x - (ox + 45), y - (oy + 55)
                    if dx*dx + dy*dy < 440:
                        if dy < -8: matriz[y][x] = 'D'
                        elif dx > 10: matriz[y][x] = 'A'
                        elif dx < -10: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'
                for x in range(int(ox + 116), int(ox + 162)):
                    dx, dy = x - (ox + 139), y - (oy + 55)
                    if dx*dx + dy*dy < 440:
                        if dy < -8: matriz[y][x] = 'D'
                        elif dx > 10: matriz[y][x] = 'A'
                        elif dx < -10: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'

        elif pose_tipo == 3: # Pose 3: Manos encontradas al centro (gesto cerrado)
            for y in range(int(oy + 72), int(oy + 128)):
                for x in range(int(ox + 48), int(ox + 78)):
                    matriz[y][x] = 'B' if x < ox + 56 else 'C'
                for x in range(int(ox + 110), int(ox + 140)):
                    matriz[y][x] = 'B' if x < ox + 118 else 'C'
            for y in range(int(oy + 40), int(oy + 88)):
                for x in range(int(ox + 62), int(ox + 108)):
                    dx, dy = x - (ox + 85), y - (oy + 64)
                    if dx*dx + dy*dy < 460:
                        if dy < -10: matriz[y][x] = 'D'
                        elif dx > 12: matriz[y][x] = 'A'
                        elif dx < -12: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'
                for x in range(int(ox + 76), int(ox + 122)):
                    dx, dy = x - (ox + 99), y - (oy + 64)
                    if dx*dx + dy*dy < 460:
                        if dy < -10: matriz[y][x] = 'D'
                        elif dx > 12: matriz[y][x] = 'A'
                        elif dx < -12: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'

        elif pose_tipo == 4: # Pose 4: Manos en ángulo dinámico
            for y in range(int(oy + 68), int(oy + 128)):
                for x in range(int(ox + 42), int(ox + 72)):
                    matriz[y][x] = 'B' if x < ox + 50 else 'C'
                for x in range(int(ox + 118), int(ox + 148)):
                    matriz[y][x] = 'B' if x < ox + 126 else 'C'
            for y in range(int(oy + 35), int(oy + 82)):
                for x in range(int(ox + 50), int(ox + 98)):
                    dx, dy = x - (ox + 74), y - (oy + 58)
                    if dx*dx + dy*dy < 440:
                        if dy < -8: matriz[y][x] = 'D'
                        elif dx > 10: matriz[y][x] = 'A'
                        elif dx < -10: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'
                for x in range(int(ox + 94), int(ox + 142)):
                    dx, dy = x - (ox + 118), y - (oy + 58)
                    if dx*dx + dy*dy < 440:
                        if dy < -8: matriz[y][x] = 'D'
                        elif dx > 10: matriz[y][x] = 'A'
                        elif dx < -10: matriz[y][x] = 'B'
                        else: matriz[y][x] = 'C'

    # Rellenar cada cuadrante de la imagen única con las 4 poses
    dibujar_manos_cuadrante(0, 0, 1) # Cuadrante Superior Izquierdo
    dibujar_manos_cuadrante(1, 0, 2) # Cuadrante Superior Derecho
    dibujar_manos_cuadrante(0, 1, 3) # Cuadrante Inferior Izquierdo
    dibujar_manos_cuadrante(1, 1, 4) # Cuadrante Inferior Derecho

    nombre_archivo = "manos_cuadricula_384x256_2000s.xpm"
    with open(nombre_archivo, 'w') as f:
        f.write("/* XPM */\n")
        f.write(f"static char * manos_cuadricula_384x256_2000s_xpm[] = {{\n")
        # Ancho, Alto, 5 colores, 1 carácter por píxel
        f.write(f"\"{width} {height} 5 1\",\n")
        f.write("\"A c #8E523A\",\n")  # Sombra profunda / borde
        f.write("\"B c #B86B4D\",\n")  # Sombra lateral
        f.write("\"C c #E29B78\",\n")  # Tono piel base
        f.write("\"D c #F6C1A4\",\n")  # Brillo superior / luz
        f.write("\"  c None\",\n")     # Transparente
        
        for y in range(height):
            fila_str = "".join(matriz[y])
            f.write(f"\"{fila_str}\",\n")
            
        f.write("};\n")
    print(f"Archivo XPM único 2000s generado con éxito: {nombre_archivo}")

if __name__ == "__main__":
    generar_xpm_cuadricula_2000s()