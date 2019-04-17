import numpy as np
import cv2
from scipy import signal
from scipy.ndimage import gaussian_filter
from matplotlib import pyplot as plt

images = ['baboon.png', 'butterfly.png', 'city.png', 'house.png', 'seagull.png']

h1 = np.array([
                [0, 0, -1, 0, 0],
                [0, -1, -2, -1, 0],
                [-1, -2, 16, -2, -1],
                [0, -1, -2, -1, 0],
                [0, 0, -1, 0, 0]
            ])
h2 = np.array([
                [1, 4, 6, 4, 1],
                [4, 16, 24, 16, 4],
                [6, 24, 36, 24, 6],
                [4, 16, 24, 16, 4],
                [1, 4, 6, 4, 1]
            ],  dtype=np.float32) / 256
h3 = np.array([
                [-1, 0, 1],
                [-2, 0, 2],
                [-1, 0, 1]
            ])
h4 = np.array([
                [-1, -2, -1],
                [0, 0, 0],
                [1, 2, 1]
            ])

for i in range(0, len(images)):
    img = cv2.imread('images/' + images[i], 0)

    # Apply filters
    processed_image_h1 = cv2.filter2D(img,-1,h1)
    processed_image_h2 = cv2.filter2D(img,-1,h2)
    processed_image_h3 = cv2.filter2D(img,-1,h3)
    processed_image_h4 = cv2.filter2D(img,-1,h4)
    processed_image_h5 = np.uint8(np.hypot(np.float32(processed_image_h3), np.float32(processed_image_h4)))

    # Gaussian filter
    for sigma in range (1, 10, 3):

        # Create gaussian filter
        x = cv2.getGaussianKernel(10,sigma)
        gaussian = x * x.T

        # Create fourier transform of gaussian filter
        gaussian_f = np.fft.fft2(gaussian, img.shape)
        gaussian_fshift = np.fft.fftshift(gaussian_f)

        # Create fourier transform of image
        f = np.fft.fft2(img)
        fshift = np.fft.fftshift(f)
        magnitude_spectrum = 20*np.log(np.abs(fshift))

        # Apply filter
        final_image = gaussian_f * f

        # Revert fourier transform
        img_back = np.fft.ifft2(final_image)
        img_back = np.abs(img_back)

        cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-gaussian' + str(sigma) + '.png',img_back)
        cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-fourier_magnitude_spectrum.png',magnitude_spectrum)

    # Print image matplotlib
    # plt.imshow(processed_image_h2, cmap = 'gray')
    # plt.show()

    # Print image opencv
    # cv2.imshow('image',np.uint8(processed_image_h2))
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-h1.png', processed_image_h1)
    cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-h2.png', processed_image_h2)
    cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-h3.png', processed_image_h3)
    cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-h4.png', processed_image_h4)
    cv2.imwrite('processed_images/' + images[i].split('.')[0] + '-h5.png', processed_image_h5)
