import cv2
import numpy as np

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
    good2 = []
    for m,n in matches:
        if m.distance < 0.75*n.distance:
            good2.append([m])
            good.append(m)

    # cv2.drawMatchesKnn expects list of lists as matches.
    img_ret = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good2, None, flags=2)
    return good, matches, img_ret

def homography_matrix(good, img1, kp1, des1, img2, kp2, des2):
    src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
    dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)
    M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
    matchesMask = mask.ravel().tolist()
    h,w = img1.shape
    pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
    dst = cv2.perspectiveTransform(pts,M)
    img2 = cv2.polylines(img2,[np.int32(dst)],True,255,3, cv2.LINE_AA)
    draw_params = dict(matchColor = (0,255,0), # draw matches in green color
                   singlePointColor = None,
                   matchesMask = matchesMask, # draw only inliers
                   flags = 2)
    img3 = cv2.drawMatches(img1,kp1,img2,kp2,good,None,**draw_params)
    return M, mask, img3

gray1 = cv2.imread('images/foto4A.jpg', 0)
gray2 = cv2.imread('images/foto4B.jpg', 0)

img1 = cv2.imread('images/foto4A.jpg', -1)
img2 = cv2.imread('images/foto4B.jpg', -1)

# Identify points of interest and descriptors
orb_kp1, orb_des1, orb_image1 = orb(gray1)
# brief_kp1, brief_des1, brief_image1 = brief(gray1)

orb_kp2, orb_des2, orb_image2 = orb(gray2)
# brief_kp2, brief_des2, brief_image2 = brief(gray2)

# Find matches
good, matches, match_image = find_matches(img1, orb_kp1, orb_des1, img2, orb_kp2, orb_des2)

# Homography Matrix
M, mask, homography_image = homography_matrix(good, gray1, orb_kp1, orb_des1, gray2, orb_kp2, orb_des2)

# Warp Perspective
dst = cv2.warpPerspective(img1, M, (gray1.shape[1] + gray2.shape[1], gray2.shape[0]))

# Creating panoramic image
dst[0:gray2.shape[0], 0:gray2.shape[1]] = img2

cv2.imwrite('panoramic_image.jpg', dst)
