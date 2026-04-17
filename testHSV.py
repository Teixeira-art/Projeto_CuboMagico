import cv2
import numpy as np
import kociemba

cam = cv2.VideoCapture(0)
corFinal = ''

# string final do cubo
cubo = ""

side = 0

while True:
    conf, img = cam.read() #primeira varivel é um bool para conferir se conseguiu ler a camera
    if not conf:
        continue

    h_img, w_img, _ = img.shape #terceira variavel são os canais da imagem
    offset = 100

    lado = min(w_img, h_img) - 2 * offset

    x1 = (w_img - lado) // 2
    y1 = (h_img - lado) // 2
    x2 = x1 + lado
    y2 = y1 + lado

    cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 0), 3)

    cube_side = ""

    cell = lado // 3

    for i in range(3):
        for j in range(3):
            xx1 = x1 + j * cell
            yy1 = y1 + i * cell

            xx2 = x1 + (j + 1) * cell if j < 2 else x2
            yy2 = y1 + (i + 1) * cell if i < 2 else y2

            # quadrado maior
            cv2.rectangle(img, (xx1, yy1), (xx2, yy2), (255, 0, 0), 1)

            piece = img[yy1:yy2, xx1:xx2]

            # usar só a parte central da peça
            ph, pw, _ = piece.shape
            margem_y = ph // 4
            margem_x = pw // 4

            centro = piece[margem_y:ph - margem_y, margem_x:pw - margem_x]

            # desenhar a área central
            cx1 = xx1 + margem_x
            cy1 = yy1 + margem_y
            cx2 = xx2 - margem_x
            cy2 = yy2 - margem_y
            cv2.rectangle(img, (cx1, cy1), (cx2, cy2), (0, 255, 0), 1)

            # converter para HSV
            centro_hsv = cv2.cvtColor(centro, cv2.COLOR_BGR2HSV)
            media = np.average(centro_hsv, axis=(0, 1))

            h, s, v = int(media[0]), int(media[1]), int(media[2])

            # classificação em HSV
            if s < 50 and v > 120:
                corFinal = 'U'  # Branco

            elif 20 <= h <= 35 and s > 60:
                corFinal = 'D'  # Amarelo

            elif 10 <= h < 20 and s > 60:
                corFinal = 'L'  # Laranja

            elif (0 <= h < 10 or 170 <= h <= 179) and s > 60:
                corFinal = 'R'  # Vermelho

            elif 40 <= h <= 85 and s > 60:
                corFinal = 'F'  # Verde

            elif 90 <= h <= 140 and s > 60:
                corFinal = 'B'  # Azul

            else:
                corFinal = '?' 

            cube_side += corFinal

            cv2.putText(img, corFinal, (xx1 + 10, yy1 + 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255, 255, 255), 2)

    cv2.imshow('Img', img)
    key = cv2.waitKey(10) & 0xFF

    if key == ord('s'):
        cubo += cube_side
        print("Face salva:", side)
        print(cube_side)
        side += 1

    if side == 6:
        print("Cubo completo!")
        break

cam.release()

#Garantir a cor correta na peça central
cubo = cubo[:4] + "U" + cubo[5:]   #Branco
cubo = cubo[:13] + "R" + cubo[14:] #Vermelho
cubo = cubo[:22] + "F" + cubo[23:] #Verde
cubo = cubo[:31] + "D" + cubo[32:] #Amarelo
cubo = cubo[:40] + "L" + cubo[41:] #Laranja
cubo = cubo[:49] + "B" + cubo[50:] #Azul

print("Cube string:", cubo)

sol = kociemba.solve(cubo)
print("Solution:", sol)
