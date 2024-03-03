"""
CS 6384 Homework 3 Programming
Implement the harris_corner() function and the non_maximum_suppression() function in this python script
Harris corner detector
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt

def convert_to_grayscale_img(im):
    height, width, rgb = im.shape
    
    red = im[:height, :width, 0]
    green = im[:height, :width, 1]
    blue = im[:height, :width, 2]

    grayscale_img = 0.299 * red + 0.587 * green + 0.114 * blue

    return grayscale_img

#TODO: implement this function
# input: R is a Harris corner score matrix with shape [height, width]
# output: mask with shape [height, width] with valuse 0 and 1, where 1s indicate corners of the input image 
# idea: for each pixel, check its 8 neighborhoods in the image. If the pixel is the maximum compared to these
# 8 neighborhoods, mark it as a corner with value 1. Otherwise, mark it as non-corner with value 0
def non_maximum_suppression(R):
    height, width = R.shape
    mask = np.zeros((height, width))

    for px in range( 1, height - 1 ):
        for py in range( 1, width - 1 ):
            window = R[ px - 1 : px + 2, py - 1 : py + 2 ]
            window_max = window.max()
            center = window[1,1]
            potential_corner = np.zeros_like(window, dtype=np.uint8)
            potential_corner[window < center] = 1
            num_pixels_satisfy = np.sum(potential_corner)

            if ( R[px,py] == window.max() and num_pixels_satisfy == 8 ):
                mask[px, py] = 1

    return mask.astype(np.uint8)


#TODO: implement this function
# input: im is an RGB image with shape [height, width, 3]
# output: corner_mask with shape [height, width] with valuse 0 and 1, where 1s indicate corners of the input image
# Follow the steps in Lecture 7 slides 26-27
# You can use opencv functions and numpy functions
def harris_corner(im):

    # step 0: convert RGB to gray-scale image
    grayscale_img = convert_to_grayscale_img(im)
    
    # step 1: compute image gradient using Sobel filters
    # https://opencv24-python-tutorials.readthedocs.io/en/latest/py_tutorials/py_imgproc/py_gradients/py_gradients.html
    sobelx = cv2.Sobel(grayscale_img,cv2.CV_64F,1,0,ksize=3)
    sobely = cv2.Sobel(grayscale_img,cv2.CV_64F,0,1,ksize=3)

    # step 2: compute products of derivatives at every pixels
    Ix2 = sobelx ** 2
    Iy2 = sobely ** 2
    Ixy = sobelx * sobely

    # step 3: compute the sums of products of derivatives at each pixel using Gaussian filter (window size: 5x5, sigma = 1.5) from OpenCV
    Sx2 = cv2.GaussianBlur(Ix2, (5,5), 1.5)
    Sy2 = cv2.GaussianBlur(Iy2, (5,5), 1.5)
    Sxy = cv2.GaussianBlur(Ixy, (5,5), 1.5)

    # step 4: compute determinant and trace of the M matrix
    det = ( Sx2 * Sy2 ) - ( Sxy ** 2 )
    trace = Sx2 + Sy2
    
    # step 5: compute R scores with k = 0.05
    k = 0.05
    R = det - ( k * ( trace ** 2 ) )
    
    # step 6: thresholding
    # up to now, you shall get a R score matrix with shape [height, width]
    threshold = 0.01 * R.max()
    R[R < threshold] = 0
    
    # step 7: non-maximum suppression
    #TODO implement the non_maximum_suppression function above
    corner_mask = non_maximum_suppression(R)

    return corner_mask


# main function
if __name__ == '__main__':

    # read the image in data
    # rgb image
    rgb_filename = 'data/000006-color.jpg'
    im = cv2.imread(rgb_filename)
    
    # your implementation of the harris corner detector
    corner_mask = harris_corner(im)
    
    # opencv harris corner
    img = im.copy()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)
    dst = cv2.cornerHarris(gray, 2, 3, 0.04)
    opencv_mask = dst > 0.01 * dst.max()
        
    # visualization for your debugging
    fig = plt.figure()
        
    # show RGB image
    ax = fig.add_subplot(1, 3, 1)
    plt.imshow(im[:, :, (2, 1, 0)])
    ax.set_title('RGB image')
        
    # show our corner image
    ax = fig.add_subplot(1, 3, 2)
    plt.imshow(im[:, :, (2, 1, 0)])
    index = np.where(corner_mask > 0)
    plt.scatter(x=index[1], y=index[0], c='y', s=5)
    ax.set_title('our corner image')
    
    # show opencv corner image
    ax = fig.add_subplot(1, 3, 3)
    plt.imshow(im[:, :, (2, 1, 0)])
    index = np.where(opencv_mask > 0)
    plt.scatter(x=index[1], y=index[0], c='y', s=5)
    ax.set_title('opencv corner image')

    plt.show()
