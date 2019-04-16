import numpy as np
import cv2
from scipy import signal
from scipy.ndimage import gaussian_filter
from matplotlib import pyplot as plt

img = cv2.imread('images/baboon.png', 0)

h1 = np.matrix([
                [0, 0, -1, 0, 0],
                [0, -1, 2, -1, 0],
                [-1, -2, 16, -2, -1],
                [0, -1, 2, -1, 0],
                [0, 0, -1, 0, 0]
            ])
h2 = np.matrix([
                [1, 4, 6, 4, 1],
                [4, 16, 24, 16, 4],
                [6, 24, 36, 24, 6],
                [4, 16, 24, 16, 4],
                [1, 4, 6, 4, 1]
            ]) / 256
h3 = np.matrix([
                [-1, 0, 1],
                [-2, 0, 2],
                [-1, 0, 1]
            ])
h4 = np.matrix([
                [-1, -2, -1],
                [0, 0, 0],
                [1, 2, 1]
            ])


# Apply filters
processed_image_h1 = cv2.filter2D(img,-1,h1)
processed_image_h2 = cv2.filter2D(img,-1,h2)
processed_image_h3 = cv2.filter2D(img,-1,h3)
processed_image_h4 = cv2.filter2D(img,-1,h4)
processed_image_h5 = np.uint8(np.hypot(np.float32(processed_image_h3), np.float32(processed_image_h4)))

# Gaussian filter

# Create gaussian filter
x = cv2.getGaussianKernel(5,1)
gaussian = x * x.T

# Create fourier transform of gaussian filter
gaussian_f = np.fft.fft2(gaussian, img.shape)
gaussian_fshift = np.fft.fftshift(gaussian_f)

# Create fourier transform of image
f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)

# Apply filter
final_image = gaussian_f * f

# Revert fourier transform
img_back = np.fft.ifft2(final_image)
img_back = np.abs(img_back)

# Print image
plt.imshow(img_back, cmap = 'gray')
plt.show()
