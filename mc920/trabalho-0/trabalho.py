import numpy as np
import cv2
import matplotlib.pyplot as plt
from sklearn.feature_extraction import image

# Leitura das imagens
img = cv2.imread('./images/baboon.png', cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread('./images/butterfly.png', cv2.IMREAD_GRAYSCALE)

# Imagem auxiliar
vis = np.zeros((512, 512), np.uint8)

# Alterar brilho da imagem pelo lambda

# def img_lambda (x):
#     l = 1.5
#     x = float(x)
#     x = x / 255
#     x = x ** (1/l)
#     x = x * 255
#     return x
#
# img_lambda = np.vectorize(img_lambda)
# img = img_lambda(img)

# Planos de bit da imagem\

# Mascara para extracao do plano
# def bit_plane (x):
#     plane = int('00000001', 2)
#     x = x & plane
#     return x
#
# bit_plane = np.vectorize(bit_plane)
# img = bit_plane(img)

# Criando mosaico

# h = w = 128
# mosaic = []
#
# Crop da imagem, em blocos de 128x128
# for y in range (0, 512, 128):
#     for x in range (0, 512, 128):
#         mosaic.append(img[y:y+h, x:x+w])

# Reordenacao dos blocos do mosaico
# indexList = [5, 10, 12, 2,
#             7, 15, 0, 8,
#             11, 13, 1, 6,
#             3, 14, 9, 4]
#
# mosaic = [mosaic[i] for i in indexList]

# Reconstrucao da imagem 512x512
# for i in range (0, len(mosaic)):
#     y = (i/4) * 128
#     x = (i % 4) *128
#     vis[y:y+h, x:x+w] = mosaic[i]

# Combinacao de imagens

# vis = img * 0.2 + img2 * 0.8

# Print matplotlib

plt.imshow(vis, cmap="gray")
plt.show()

# Print com opencv

# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
