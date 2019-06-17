import numpy as np
import cv2

images = ['baboon', 'monalisa', 'peppers', 'watch']
# images = ['baboon']
for image in images:
    img = cv2.imread('images/' + image + '.png')
    Z = img.reshape((-1,3))

    # convert to np.float32
    Z = np.float32(Z)

    # define criteria, number of clusters(K) and apply kmeans()
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
    for K in [4, 16, 32, 64, 128]:
    # for K in [16]:
        I = 10
        ret,label,center=cv2.kmeans(Z,K,None,criteria,I,cv2.KMEANS_RANDOM_CENTERS)

        # Now convert back into uint8, and make original image
        center = np.uint8(center)
        res = center[label.flatten()]
        res2 = res.reshape((img.shape))

        cv2.imwrite('final_images/' + image + '_' + str(K) + '.png', res2)
