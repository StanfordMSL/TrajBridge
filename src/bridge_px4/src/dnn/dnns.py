import numpy as np
import torch
import torch.nn.functional as F
from torch.utils.data import Dataset

class PolNN(torch.nn.Module):
    def __init__(self,Nhtr:int,Nhrz:int):
        # Constants
        nx  = 13                                # number of states
        nu  = 4                                 # number of inputs 
        nhl = 100                               # number of hidden layers
        ni  = (nu*Nhtr)+(nx*Nhrz)+nx            # Total input size
        no  = nu                                # Total output size

        self.base_sp = "polNN"                  # base savepath
        # Initialize NN Variables
        super(PolNN, self).__init__()           # Init parent call
        self.Nhtr = Nhtr                        # History count
        self.Nhrz = Nhrz                        # Horizon count
        
        # Initialize NN Structure
        self.linear = torch.nn.Linear(ni,nhl)
        self.layer1 = torch.nn.Linear(nhl,nhl)
        self.layer2 = torch.nn.Linear(nhl,nhl)
        self.layer3 = torch.nn.Linear(nhl,nhl)
        self.output_layer = torch.nn.Linear(nhl,no)

    def forward(self,x):
        x = self.linear(x)
        x = self.layer1(F.relu(x))
        x = self.layer2(F.relu(x))
        x = self.layer3(F.relu(x))
        u = self.output_layer(x)
        return u        

class AffNN(torch.nn.Module):
    def __init__(self,Nhtr,Nhrz):
        # Constants
        nx  = 13                                # number of states
        nu  = 4                                 # number of inputs
        npr = 4                                 # number of parameters 
        nhl = 100                               # number of hidden layers
        nxu = nx+nu                             # number of states+inputs (combined data)
        ni  = (nxu*Nhtr)+(nxu*Nhrz)+nxu+npr     # Total input size
        no  = nu*nu+nu                          # Total output size
        self.base_sp = "affNN"                  # base savepath

        # Initialize NN Variables
        super(AffNN, self).__init__()          # Init parent call
        self.Nhtr = Nhtr                        # History count
        self.Nhrz = Nhrz                        # Horizon count
        
        # Initialize NN Structure
        self.linear = torch.nn.Linear(ni,nhl)
        self.layer1 = torch.nn.Linear(nhl,nhl)
        self.layer2 = torch.nn.Linear(nhl,nhl)
        self.layer3 = torch.nn.Linear(nhl,nhl)
        self.output_layer = torch.nn.Linear(nhl,no)

    def forward(self,x):
        x = self.linear(x)
        x = self.layer1(F.relu(x))
        x = self.layer2(F.relu(x))
        x = self.layer3(F.relu(x))
        u = self.output_layer(x)
        return u

class NNGym():
    def __init__(self,device,gym,Nhtr,Nhrz,pid):
        if gym == "polNN":                             # gym trains a policy (S->U)
            self.dnn = PolNN(Nhtr,Nhrz).to(device)
        elif gym == "affNN":                           # gym trains an affine transform (S->Ab)
            self.dnn = AffNN(Nhtr,Nhrz).to(device)
        
        self.uniq_sp = "_"+str(Nhtr)+"htr"+str(Nhrz)+"hrz_p"+str(pid)+"_"

        self.crit = torch.nn.SmoothL1Loss(reduction='mean')
        self.opti = torch.optim.Adam(self.dnn.parameters(), lr=1e-3)

        self.lhis = np.zeros(0)  
    
# # Test
# model = PolNN(10,30)
# print(model.layer1.weight.shape)