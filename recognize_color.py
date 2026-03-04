import cv2
import numpy as np

cam = cv2.VideoCapture(0)
corChange = ''
corFinal = ''

cube_side = np.empty((3, 3), dtype=object)
cubo = np.empty((6,3,3),dtype=object)

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

    #DESENHA OS 9 MINI-QUADRADOS (3x3) DENTRO DO QUADRADO GRANDE
    cell = lado // 3
    
    for row in range(3):
        for col in range(3):
            xx1 = x1 + col * cell
            yy1 = y1 + row * cell

            # fecha certinho no limite do quadrado grande na última linha/coluna
            xx2 = x1 + (col + 1) * cell if col < 2 else x2
            yy2 = y1 + (row + 1) * cell if row < 2 else y2
          
            cv2.rectangle(img, (xx1, yy1), (xx2, yy2), (255, 0, 0), 1)
          
            piece = img[yy1:yy2 , xx1:xx2]
            media = np.average(piece, axis =(0,1))
          
            r, g, b = int(media[2]), int(media[1]), int(media[0])
            cor = [r, g, b]
        

            if r >= 100 and g >= 100 and b >= 110:
                corFinal = 'Branco'
            elif r >= 100 and g >= 100 and b <= 80
                corFinal = 'Amarelo'
            elif r >= 140 and g >= 65 and g < 140 and b <= 80:
                corFinal = 'Laranja'
            elif np.argmax(cor) == 0:
                corFinal = 'Vermelho'
            elif np.argmax(cor) == 1:
                 corFinal = 'Verde'
            elif np.argmax(cor) == 2:
                  corFinal = 'Azul'

            cube_side[row][col] = corFinal

    key = cv2.waitKey(10) & 0xFF

    if key == ord('m'):
        print(cube_side)




    cv2.imshow('Img', img)
    cv2.waitKey(10)
