"""
CS 6384 Homework 2 Programming: Part 4 - non-local means filter
Implement the nlm_filtering() function in this python script
"""
 
import cv2
import numpy as np
import math

def get_intensity_weight_val(
    x: float, 
    intensity_range_variance: float
) -> float:
    
    return np.exp( 
        -1.0 * ( ( pow( x , 2 ) ) / ( 2 * intensity_range_variance ) )
    )

def calc_sum_squared_differences(
    img: np.float32, 
    px: int, 
    py: int, 
    qx: int, 
    qy: int, 
    patch_size: int
) -> float:
    
    patch_offset = patch_size // 2 

    #print( "\t\t  Getting SSD between:", "(", px, ",", py, ") and (", qx, ",", qy, ")" )

    p_mat = img[px - patch_offset : px + patch_offset, py - patch_offset : py + patch_offset]
    q_mat = img[qx - patch_offset : qx + patch_offset, qy - patch_offset : qy + patch_offset]

    res_mat = p_mat - q_mat
    return np.sum(res_mat * res_mat)

def get_zero_padded_img_matrix(
    img: np.float32,
    padding_offset: int,
) -> np.float32:

    return np.pad(img, ((padding_offset, padding_offset), (padding_offset, padding_offset)), mode='constant')

def get_non_local_means_pixel_val(
    zero_padded_img_mat: np.float32, 
    i: int, 
    j: int,
    window_size: int,
    patch_size: int,
    intensity_variance: float
) -> float:

    window_offset = window_size // 2 
    patch_offset = patch_size // 2

    sigma_f_q = 0
    W_normalization_term = 0

    for patch_i_offset in range(-window_offset + patch_offset, window_offset - patch_offset + 1):
        for patch_j_offset in range(-window_offset + patch_offset, window_offset - patch_offset + 1):
            patch_i = i + patch_i_offset
            patch_j = j + patch_j_offset

            SSD = calc_sum_squared_differences(
                zero_padded_img_mat, i, j, patch_i, patch_j, patch_size
            )
            wpq = get_intensity_weight_val(SSD, intensity_variance)
            f_q = zero_padded_img_mat[patch_i][patch_j]

            sigma_f_q += wpq * f_q
            W_normalization_term += wpq

    return ( sigma_f_q / W_normalization_term )


def nlm_filtering(
    img: np.uint8,
    intensity_variance: float,
    patch_size: int,
    window_size: int,
) -> np.uint8:
    """
    Homework 2 Part 4
    Compute the filtered image given an input image, kernel size of image patch, spatial variance, and intensity range variance
    """

    img = img / 255
    img = img.astype("float32")
    img_filtered = np.zeros(img.shape) # Placeholder of the filtered image
    
    # Todo: For each pixel position [i, j], you need to compute the filtered output: img_filtered[i, j] using a non-local means filter
    # step 1: compute window_sizexwindow_size filter weights of the non-local means filter in terms of intensity_variance. 
    # step 2: compute the filtered pixel img_filtered[i, j] using the obtained kernel weights and the pixel values in the search window
    # Please see slides 30 and 31 of lecture 6. Clarification: the patch_size refers to the size of small image patches (image content in yellow, 
    # red, and blue boxes in the slide 30); intensity_variance denotes sigma^2 in slide 30; the window_size is the size of the search window as illustrated in slide 31.
    # Tip: use zero-padding to address the black border issue. 

    # ********************************
    # Your code is here.

    sizeX, sizeY = img.shape
    center_offset = window_size // 2
    zero_padded_img_mat = get_zero_padded_img_matrix(img, center_offset)

    for i in range(sizeX):
        for j in range(sizeY):
            #print( "Getting pixel val for:", "(", i, ",", j, ")" )
            img_filtered[i, j] = get_non_local_means_pixel_val(
                zero_padded_img_mat, 
                i + center_offset, 
                j + center_offset, 
                window_size, 
                patch_size,
                intensity_variance
            )

    # ********************************
            
    img_filtered = img_filtered * 255
    img_filtered = np.uint8(img_filtered)
    return img_filtered

 
if __name__ == "__main__":
    img = cv2.imread("data/img/butterfly.jpeg", 0) # read gray image
    img = cv2.resize(img, (256, 256), interpolation = cv2.INTER_AREA) # reduce image size for saving your computation time
    cv2.imwrite('results/im_original.png', img) # save image 
    
    # Generate Gaussian noise
    noise = np.random.normal(0,0.6,img.size)
    noise = noise.reshape(img.shape[0],img.shape[1]).astype('uint8')
   
    # Add the generated Gaussian noise to the image
    img_noise = cv2.add(img, noise)
    cv2.imwrite('results/im_noisy.png', img_noise)
    
    # Bilateral filtering
    intensity_variance = 1
    patch_size = 5 # small image patch size
    window_size = 15 # serach window size
    img_bi = nlm_filtering(img_noise, intensity_variance, patch_size, window_size)
    cv2.imwrite('results/im_nlm.png', img_bi)