"""
CS 6384 Homework 5 Programming
Implement the __getitem__() function in this python script
"""
import torch
import torch.utils.data as data
import csv
import os, math
import sys
import time
import random
import numpy as np
import cv2
import glob
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches


# The dataset class
class CrackerBox(data.Dataset):
    def __init__(self, image_set = 'train', data_path = 'data'):

        self.name = 'cracker_box_' + image_set
        self.image_set = image_set
        self.data_path = data_path
        self.classes = ('__background__', 'cracker_box')
        self.width = 640
        self.height = 480
        self.yolo_image_size = 448
        self.scale_width = self.yolo_image_size / self.width
        self.scale_height = self.yolo_image_size / self.height
        self.yolo_grid_num = 7
        self.yolo_grid_size = self.yolo_image_size / self.yolo_grid_num
        # split images into training set and validation set
        self.gt_files_train, self.gt_files_val = self.list_dataset()
        # the pixel mean for normalization
        self.pixel_mean = np.array([[[102.9801, 115.9465, 122.7717]]], dtype=np.float32)

        # training set
        if image_set == 'train':
            self.size = len(self.gt_files_train)
            self.gt_paths = self.gt_files_train
            print('%d images for training' % self.size)
        else:
            # validation set
            self.size = len(self.gt_files_val)
            self.gt_paths = self.gt_files_val
            print('%d images for validation' % self.size)


    # list the ground truth annotation files
    # use the first 100 images for training
    def list_dataset(self):
    
        filename = os.path.join(self.data_path, '*.txt')
        gt_files = sorted(glob.glob(filename))
        
        gt_files_train = gt_files[:100]
        gt_files_val = gt_files[100:]
        
        return gt_files_train, gt_files_val


    # TODO: implement this function
    def __getitem__(self, idx):
    
        # gt file
        filename_gt = self.gt_paths[idx]

        ### ADD YOUR CODE HERE ###
                
        ##### Image Tensor Code Start #####

        pixel_mean_tensor = torch.tensor(self.pixel_mean)
        filename_comps = filename_gt.split("-")
        img_filename = filename_comps[0] + ".jpg"
        cv2_image = cv2.imread(img_filename)
        rescaled_cv2_image = cv2.resize(
            cv2_image, 
            (0, 0),
            fx=self.scale_width, 
            fy=self.scale_height,
        ).astype('float32')
        norm_image = ( rescaled_cv2_image - self.pixel_mean ) / 255.0
        norm_image_tensor = torch.FloatTensor(norm_image)
        image_blob = norm_image_tensor.permute(2, 0, 1)

        ##### Image Tensor Code End #####

        ##### Bounding Box Code Start #####

        gt_box_blob_arr = np.zeros(
            (self.yolo_grid_num, self.yolo_grid_num, 5), 
            dtype=float
        )

        gt_mask_blob_arr = np.zeros(
            (self.yolo_grid_num, self.yolo_grid_num), 
            dtype=int
        )

        gt_bbox_coords = np.loadtxt(filename_gt, delimiter=' ')

        resizing_factors_for_coords = np.array([
            self.scale_width,
            self.scale_height,
            self.scale_width,
            self.scale_height,
        ])

        gt_bbox_resized_coords = gt_bbox_coords * resizing_factors_for_coords

        gt_cell_values = np.zeros((5,))
        gt_cell_values[2:4] = [
            abs(gt_bbox_resized_coords[2] - gt_bbox_resized_coords[0]),
            abs(gt_bbox_resized_coords[3] - gt_bbox_resized_coords[1]),
        ]
        gt_cell_values[0:2] = [
            gt_bbox_resized_coords[0] + gt_cell_values[2] / 2.0,
            gt_bbox_resized_coords[1] + gt_cell_values[3] / 2.0
        ]
        gt_cell_values[4] = 1.0

        grid_x_idx = int(gt_cell_values[0] // 64)
        grid_y_idx = int(gt_cell_values[1] // 64)

        x_offset = gt_cell_values[0] % self.yolo_grid_size
        y_offset = gt_cell_values[1] % self.yolo_grid_size

        gt_cell_values[0:2] = [
            x_offset / self.yolo_grid_size, 
            y_offset / self.yolo_grid_size
        ]

        gt_cell_values[2:4] /= float(self.yolo_image_size)

        gt_box_blob_arr[:,:] = gt_cell_values
        gt_mask_blob_arr[grid_y_idx][grid_x_idx] = 1

        gt_box_blob = torch.FloatTensor(gt_box_blob_arr).permute(2, 0, 1)
        gt_mask_blob = torch.FloatTensor(gt_mask_blob_arr)

        #print(gt_bbox_coords)
        #print(resizing_factors_for_coords)
        #print(gt_bbox_resized_coords)
        #print(gt_cell_values)
        #print(grid_x_idx)
        #print(grid_y_idx)
        #print(self.yolo_grid_size)
        #print(self.yolo_image_size)
        #print(gt_box_blob_test)
        #print(gt_mask_blob_test)

        ##### Bounding Box Code End #####

        # this is the sample dictionary to be returned from this function
        sample = {'image': image_blob,
                  'gt_box': gt_box_blob,
                  'gt_mask': gt_mask_blob}

        return sample


    # len of the dataset
    def __len__(self):
        return self.size
        

# draw grid on images for visualization
def draw_grid(image, line_space=64):
    H, W = image.shape[:2]
    image[0:H:line_space] = [255, 255, 0]
    image[:, 0:W:line_space] = [255, 255, 0]


# the main function for testing
if __name__ == '__main__':
    dataset_train = CrackerBox('train')
    dataset_val = CrackerBox('val')
    
    # dataloader
    train_loader = torch.utils.data.DataLoader(dataset_train, batch_size=1, shuffle=False, num_workers=0)
    
    # visualize the training data
    for i, sample in enumerate(train_loader):
        
        image = sample['image'][0].numpy().transpose((1, 2, 0))
        gt_box = sample['gt_box'][0].numpy()
        gt_mask = sample['gt_mask'][0].numpy()

        y, x = np.where(gt_mask == 1)
        cx = gt_box[0, y, x] * dataset_train.yolo_grid_size + x * dataset_train.yolo_grid_size
        cy = gt_box[1, y, x] * dataset_train.yolo_grid_size + y * dataset_train.yolo_grid_size
        w = gt_box[2, y, x] * dataset_train.yolo_image_size
        h = gt_box[3, y, x] * dataset_train.yolo_image_size

        x1 = cx - w * 0.5
        x2 = cx + w * 0.5
        y1 = cy - h * 0.5
        y2 = cy + h * 0.5

        print(image.shape, gt_box.shape)
        
        # visualization
        fig = plt.figure()
        ax = fig.add_subplot(1, 3, 1)
        im = image * 255.0 + dataset_train.pixel_mean
        im = im.astype(np.uint8)
        plt.imshow(im[:, :, (2, 1, 0)])
        plt.title('input image (448x448)', fontsize = 16)

        ax = fig.add_subplot(1, 3, 2)
        draw_grid(im)
        plt.imshow(im[:, :, (2, 1, 0)])
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=2, edgecolor='g', facecolor="none")
        ax.add_patch(rect)
        plt.plot(cx, cy, 'ro', markersize=12)
        plt.title('Ground truth bounding box in YOLO format', fontsize=16)
        
        ax = fig.add_subplot(1, 3, 3)
        plt.imshow(gt_mask)
        plt.title('Ground truth mask in YOLO format (7x7)', fontsize=16)
        plt.show()
