import numpy as np
import cv2

def halft_pontilhado(img):
	(row, col) = img.shape
	img = np.floor((10/255) * img)
	img_out = np.zeros((row * 3, col *3))

	mask = np.array([[6, 8, 4],
			 [1, 0, 3],
			 [5, 2, 7]])

	for i in range(0, row):
		for j in range (0, col):
			for x in range (0, 3):
				for y in range(0, 3):
					img_out [3 * i + x, 3 * j + y] = int(img[i, j] >= mask[x, y])
	return img_out

def halft_floyd_steinberg(img):
	(row, col) = img.shape
	tmp = np.zeros((row, col))
	for i in range(0, row - 1):
		if i%2 == 0:
			var = range (0, col - 1)
		else:
			var = range (col - 2, -1, -1)
		for j in var:
			if img[i, j] < 128:
				tmp [i, j] = 0
			else:
				tmp [i, j] = 1
			erro = img[i, j] - tmp [i, j] * 255
			img[i +1, j] = img[i+1, j] + (7/16) * erro
			img[i-1, j+1] = img[i-1, j+1] + (3/16) * erro
			img[i, j+1] = img[i, j+1] + (5/16) * erro
			img[i+1, j+1] = img[i+1, j+1] + (1/16) * erro
	return tmp

images = ['baboon.pgm']

for i in range(0, len(images)):
	img = cv2.imread('images/' + images[i], -1)
#	img = halft_pontilhado(img)
	img = halft_floyd_steinberg(img)
	cv2.imwrite('baboonn.pbm', img)
