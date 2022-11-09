#!/usr/bin/env python3

import torch
import torch.nn.functional as F
import os
from dnn.dnns import *
from enum import Enum,auto

class Controller:
    def __init__(self):
        # DNN Policies
        use_cuda = torch.cuda.is_available()                    
        self.device = torch.device("cuda:0" if use_cuda else "cpu") 
        dir_path = os.path.dirname(os.path.realpath(__file__))
        address = dir_path+"/dnn/PolNN.pth"


        polNN = torch.load(address,map_location=self.device)
        polNN.eval()
        # polNN.eval()
        # motNN = torch.load('policies/motNN.pth')

if __name__ == '__main__':
    ctl = Controller()
