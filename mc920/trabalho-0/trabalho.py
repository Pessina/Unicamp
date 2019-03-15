import numpy as np
import cv2
import matplotlib.pyplot as plt
from sklearn.feature_extraction import image

img = cv2.imread('./images/baboon.png', cv2.IMREAD_GRAYSCALE)

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

# def bit_plane (x):
#     plane = int('00000001', 2)
#     x = x & plane
#     return x
#
# bit_plane = np.vectorize(bit_plane)
# img = bit_plane(img)

# Criando mosaico

patches = image.extract_patches_2d(img, (128, 128))

plt.imshow(img, cmap="gray")
plt.show()

# Print com opencv

# cv2.imshow('image', img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
