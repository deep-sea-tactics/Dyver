#import dependencies 
import cv2
import numpy as np
import torch
import torchvision
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import mathplotlib.pyplot as plt

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")



#get dataset(IT HAS A LICENSE THOUGH IDK HOW TO REFERENCE IT)
dataset = "https://universe.roboflow.com/mate-rov-v2-2026/mate-rov-2026-european-green-crab-computer-vision-model-vkrz4" 

#transfer learn

#test epoch ==10-15

#save model

# render model

#use with cv2

#need to add git lfs and model weights and dataset to repo
