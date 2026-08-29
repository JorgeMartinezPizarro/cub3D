def generar_xpm_cuadricula():
    width, height = 384, 256
    half_w = width // 2  # 192 píxeles por sub-imagen horizontal
    half_h = height // 2 # 128 píxeles por sub-imagen vertical
    
    # Definición de colores XPM: ' ' = Transparente, '.' = Tono piel claro, '+' = Sombra brazo
    matriz = [[' ' for _ in range(width)] for _ in range(height)]
    
    def dibujar_manos_cuadrante(qx, qy, pose_tipo):
        ox = qx * half_w
        oy = qy * half_h
        
        # Coordenadas relativas adaptadas al cuadrante de 192x128
        if pose_tipo == 1: # Pose 1: Brazos rectos y palmas abiertas hacia adelante
            for y in range(int(oy + 80), int(oy + 128)):
                for x in range(int(ox + 40), int(ox + 75)): matriz[y][x] = '+'
                for x in range(int(ox + 115), int(ox + 150)): matriz[y][x] = '+'
            for y in range(int(oy + 45), int(oy + 90)):
                for x in range(int(ox + 48), int(ox + 82)): matriz[y][x] = '.'
                for x in range(int(ox + 108), int(ox + 142)): matriz[y][x] = '.'
                
        elif pose_tipo == 2: # Pose 2: Manos abiertas hacia los lados
            for y in range(int(oy + 75), int(oy + 128)):
                for x in range(int(ox + 30), int(ox + 60)): matriz[y][x] = '+'
                for x in range(int(ox + 130), int(ox + 160)): matriz[y][x] = '+'
            for y in range(int(oy + 40), int(oy + 85)):
                for x in range(int(ox + 35), int(ox + 70)): matriz[y][x] = '.'
                for x in range(int(ox + 120), int(ox + 155)): matriz[y][x] = '.'
                
        elif pose_tipo == 3: # Pose 3: Manos encontradas al centro (gesto cerrado)
            for y in range(int(oy + 75), int(oy + 128)):
                for x in range(int(ox + 50), int(ox + 80)): matriz[y][x] = '+'
                for x in range(int(ox + 110), int(ox + 140)): matriz[y][x] = '+'
            for y in range(int(oy + 50), int(oy + 95)):
                for x in range(int(ox + 70), int(ox + 105)): matriz[y][x] = '.'
                for x in range(int(ox + 85), int(ox + 120)): matriz[y][x] = '.'
                
        elif pose_tipo == 4: # Pose 4: Manos en ángulo dinámico
            for y in range(int(oy + 70), int(oy + 128)):
                for x in range(int(ox + 45), int(ox + 75)): matriz[y][x] = '+'
                for x in range(int(ox + 115), int(ox + 145)): matriz[y][x] = '+'
            for y in range(int(oy + 40), int(oy + 85)):
                for x in range(int(ox + 55), int(ox + 90)): matriz[y][x] = '.'
                for x in range(int(ox + 98), int(ox + 133)): matriz[y][x] = '.'

    # Rellenar cada cuadrante de la imagen única con las 4 poses diferentes
    dibujar_manos_cuadrante(0, 0, 1) # Cuadrante Superior Izquierdo (Pose 1)
    dibujar_manos_cuadrante(1, 0, 2) # Cuadrante Superior Derecho (Pose 2)
    dibujar_manos_cuadrante(0, 1, 3) # Cuadrante Inferior Izquierdo (Pose 3)
    dibujar_manos_cuadrante(1, 1, 4) # Cuadrante Inferior Derecho (Pose 4)

    nombre_archivo = "manos_cuadricula_384x256.xpm"
    with open(nombre_archivo, 'w') as f:
        f.write("/* XPM */\n")
        f.write(f"static char * manos_cuadricula_384x256_xpm[] = {{\n")
        f.write(f"\"{width} {height} 3 1\",\n")
        f.write("\". c #ECB798\",\n")
        f.write("\"+ c #D28668\",\n")
        f.write("\"  c None\",\n")
        
        for y in range(height):
            fila_str = "".join(matriz[y])
            f.write(f"\"{fila_str}\",\n")
            
        f.write("};\n")
    print(f"Archivo XPM único generado con éxito: {nombre_archivo}")

generar_xpm_cuadricula()