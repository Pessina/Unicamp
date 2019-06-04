import cv2
import numpy as np

gray1 = cv2.imread('images/foto4A.jpg', 0)
gray2 = cv2.imread('images/foto4B.jpg', 0)

def orb(img):
    # Initiate ORB detector
    orb = cv2.ORB_create()
    # find the keypoints with ORB
    kp = orb.detect(img,None)
    # compute the descriptors with ORB
    kp, des = orb.compute(img, kp)
    # draw only keypoints location,not size and orientation
    img_ret = cv2.drawKeypoints(img, kp, None, color=(0,255,0), flags=0)
    return kp, des, img_ret

def brief(img):
    # Initiate FAST detector
    star = cv2.xfeatures2d.StarDetector_create()
    # Initiate BRIEF extractor
    brief = cv2.xfeatures2d.BriefDescriptorExtractor_create()
    # find the keypoints with STAR
    kp = star.detect(img,None)
    # compute the descriptors with BRIEF
    kp, des = brief.compute(img, kp)
    img_ret = cv2.drawKeypoints(img, kp, None, color=(0,255,0), flags=0)
    return kp, des, img_ret

def find_matches(img1, kp1, des1, img2, kp2, des2):
    # BFMatcher with default params
    bf = cv2.BFMatcher(cv2.NORM_HAMMING)
    matches = bf.knnMatch(des1,des2, k=2)
    # Apply ratio test to find best matches and print distances
    good = []
    for m,n in matches:
        if m.distance < 0.45*n.distance:
            good.append([m])

    # cv2.drawMatchesKnn expects list of lists as matches.
    img_ret = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good, None, flags=2)
    return matches, img_ret

# Identify points of interest and descriptors
orb_kp1, orb_des1, orb_image1 = orb(gray1)
# brief_kp1, brief_des1, brief_image1 = brief(gray1)

orb_kp2, orb_des2, orb_image2 = orb(gray2)
# brief_kp2, brief_des2, brief_image2 = brief(gray2)

# Find matches
matches, match_image = find_matches(gray1, orb_kp1, orb_des1, gray2, orb_kp2, orb_des2)

# cv2.imwrite('orb_final_image.jpg', orb_image1)
# cv2.imwrite('brief_final_image.jpg', brief_image1)
cv2.imwrite('matches_final_image.jpg', match_image)
