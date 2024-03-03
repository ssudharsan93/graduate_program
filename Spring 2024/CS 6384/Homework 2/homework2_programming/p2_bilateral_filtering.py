"""
CS 6384 Homework 2 Programming: Part 3 - bilateral filter
Implement the bilateral_filtering() function in this python script
"""
 
import cv2
import numpy as np
import math

def get_spatial_gaussian_val(
    k: float, 
    l: float, 
    spatial_variance: float,
) -> float:
    
    return ( 1.0  / ( 2 * np.pi * spatial_variance ) ) * np.exp( 
        -1.0 * ( ( pow( k , 2 ) + pow( l , 2 ) ) / ( 2 * spatial_variance ) )
    )

def get_intensity_gaussian_val(
    x: float, 
    intensity_range_variance: float
) -> float:
    
    return ( 1.0  / ( math.sqrt( 2 * np.pi * intensity_range_variance ) ) ) * np.exp( 
        -1.0 * ( ( pow( x , 2 ) ) / ( 2 * intensity_range_variance ) )
    )

def get_zero_padded_img_matrix(
    img: np.float32,
    padding_offset: int,
) -> np.float32:

    return np.pad(img, ((padding_offset, padding_offset), (padding_offset, padding_offset)), mode='constant')

def bilateral_filtering(
    img: np.uint8,
    spatial_variance: float,
    intensity_variance: float,
    kernel_size: int,
) -> np.uint8:
    """
    Homework 2 Part 3
    Compute the bilaterally filtered image given an input image, kernel size, spatial variance, and intensity range variance
    """

    img = img / 255
    img = img.astype("float32")
    img_filtered = np.zeros(img.shape) # Placeholder of the filtered image

    spatial_filter_weights = np.zeros((kernel_size, kernel_size))
    intensity_range_filter_weights = np.zeros((kernel_size, kernel_size))
    
    # Todo: For each pixel position [i, j], you need to compute the filtered output: img_filtered[i, j]
    # step 1: compute kernel_sizexkernel_size spatial and intensity range weights of the bilateral filter in terms of spatial_variance and intensity_variance. 
    # step 2: compute the filtered pixel img_filtered[i, j] using the obtained kernel weights and the neighboring pixels of img[i, j] in the kernel_sizexkernel_size local window
    # The bilateral filtering formula can be found in slide 15 of lecture 6
    # Tip: use zero-padding to address the black border issue.

    # ********************************
    # Your code is here.

    sizeX, sizeY = img.shape
    center_offset = kernel_size // 2
    zero_padded_img_mat = get_zero_padded_img_matrix(img, center_offset)

    for i in range(sizeX):
        for j in range(sizeY):

            i_left_offset = -1 * center_offset
            i_right_offset = center_offset
            j_left_offset = -1 * center_offset
            j_right_offset = center_offset

            i_center = i + center_offset
            j_center = j + center_offset

            img_window_mat = np.array([ 
                        [
                            zero_padded_img_mat[i_itr + i_center][j_itr + j_center]
                            for i_itr in range(i_left_offset, i_right_offset + 1)
                        ] 
                        for j_itr in range(j_left_offset, j_right_offset + 1) 
            ])

            spatial_filter_weights = np.array([ 
                        [ 
                            get_spatial_gaussian_val(i_itr, j_itr, spatial_variance) 
                            for i_itr in range(i_left_offset, i_right_offset + 1)
                        ] 
                        for j_itr in range(j_left_offset, j_right_offset + 1) 
            ])

            intensity_filter_weights = np.array([ 
                        [
                            get_intensity_gaussian_val(
                                zero_padded_img_mat[i_center][j_center] - zero_padded_img_mat[i_itr + i_center][j_itr + j_center], 
                                intensity_variance
                            )
                            for i_itr in range(i_left_offset, i_right_offset + 1)
                        ] 
                        for j_itr in range(j_left_offset, j_right_offset + 1) 
            ])

            result_matrix = spatial_filter_weights * intensity_filter_weights * img_window_mat
            pixel_val = np.sum(result_matrix)
            normalization_term = np.sum(spatial_filter_weights * intensity_filter_weights)

            img_filtered[i, j] = pixel_val / normalization_term
    
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
    spatial_variance = 30 # signma_s^2
    intensity_variance = 0.5 # sigma_r^2
    kernel_size = 7
    img_bi = bilateral_filtering(img_noise, spatial_variance, intensity_variance, kernel_size)
    cv2.imwrite('results/im_bilateral.png', img_bi)