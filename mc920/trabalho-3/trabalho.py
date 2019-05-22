import numpy as np
import cv2

def morphological_operations (inverse, k1, k2, k3):
    kernel1 = np.ones((1,k1),np.uint8)
    dilation1 = cv2.dilate(inverse,kernel1,iterations = 1)
    erosion1 = cv2.erode(dilation1,kernel1,iterations = 1)

    kernel2 = np.ones((k2,1),np.uint8)
    dilation2 = cv2.dilate(inverse,kernel2,iterations = 1)
    erosion2 = cv2.erode(dilation2,kernel2,iterations = 1)

    img_and = cv2.bitwise_and(erosion1,erosion2)

    kernel3 = np.ones((1,k3),np.uint8)
    closing = cv2.morphologyEx(img_and, cv2.MORPH_CLOSE, kernel3)

    connectivity = 4
    return cv2.connectedComponentsWithStats(closing, connectivity, cv2.CV_32S)

# Read image
img = cv2.imread("images/bitmap.pbm", -1)

# Convert to binary image
img[img == 255] = 1

# Invert image to apply morphological operations
inverse = np.ones(img.shape, np.uint8)
inverse [img == 1] = 0

output1 = morphological_operations (inverse, 100, 200, 30)

for x1, y1, width1, height1, area1 in output1[2]:
        # Extract rectangle to calculate ratio
        rectangle = inverse[y1:y1+height1, x1:x1+width1]

        # Ratio black and white
        total_blacks_dots = np.sum(rectangle)
        ratio_black_to_white = total_blacks_dots/(width1 * height1)

        # Ratio transitions
        total_transition = 0
        for i in range (0, height1):
            total_transition += (rectangle[i, :-1] < rectangle[i, 1:]).sum()
        for i in range (0, width1):
            total_transition += (rectangle[:-1, i] < rectangle[1:, i]).sum()

        if total_transition != 0:
            ratio_transition = total_transition/total_blacks_dots
        else:
            ratio_transition = 0

        # Applying morphological operations on each line
        if ratio_black_to_white > 0.2 and ratio_black_to_white < 0.5 and ratio_transition > 0.25:
                output2 = morphological_operations (rectangle, 10, 10, 13)
                # Drawing rectangles
                for x2, y2, width2, height2, area2 in output2[2][1:]:
                    cv2.rectangle(inverse, (x1 + x2, y1 + y2), (x1 + x2 + width2, y1 + y2 + height2), 1, 1)

cv2.imwrite("image.pbm", inverse)
