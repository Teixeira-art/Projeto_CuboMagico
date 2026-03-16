import cv2
import numpy as np
import kociemba

cam = cv2.VideoCapture(0)
corChange = ''
corFinal = ''

#os lados do cubo e o cubo total são strings vazias, já pensando na implementação com o kocyemba
cubo = ""

side = 0

while True:
    _, img = cam.read()
    h, w, _ = img.shape
    offset = 100

    lado = min(w, h) - 2 * offset

    x1 = (w - lado) // 2
    y1 = (h - lado) // 2
    x2 = x1 + lado
    y2 = y1 + lado

    campo = img[y1:y2, x1:x2]
    cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 0), 3)

    cube_side = ""

    # 9 quadrados
    cell = lado // 3

    for i in range(3):
        for j in range(3):
            xx1 = x1 + j * cell
            yy1 = y1 + i * cell

            xx2 = x1 + (j + 1) * cell if j < 2 else x2
            yy2 = y1 + (i + 1) * cell if i < 2 else y2

            cv2.rectangle(img, (xx1, yy1), (xx2, yy2), (255, 0, 0), 1)

            piece = img[yy1:yy2 , xx1:xx2]
            media = np.average(piece, axis =(0,1))

            r, g, b = int(media[2]), int(media[1]), int(media[0])
            cor = [r, g, b]

            if r >= 100 and g >= 100 and b >= 110: 
                corFinal = 'U' #Branco
            elif r >= 100 and g >= 100 and b <= 80:
                corFinal = 'D' #Amarelo
            elif r >= 140 and g >= 65 and g < 140 and b <= 80:
                corFinal = 'L' #Laranja
            elif np.argmax(cor) == 0:
                corFinal = 'R' #Vermelho
            elif np.argmax(cor) == 1:
                corFinal = 'F' #Verde
            elif np.argmax(cor) == 2:
                corFinal = 'B' #Azul

            cube_side = cube_side + corFinal
    
    cv2.imshow('Img', img)

    key = cv2.waitKey(10) & 0xFF

    if key == ord('s'):
        cubo = cubo + cube_side
        print("Face salva:", side)
        print(cube_side)
        side += 1

    if side == 6:
        print("Cubo completo!")
        break


print("Scramble:" + cubo)

sol = kociemba.solve(cubo)

print("Solution:" + sol)
