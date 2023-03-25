# Imports
import numpy as np
import visualizers as viz
import util as ut
from scipy.spatial.transform import Rotation

# Variable Params
tf = 10.0                                   # final time (per trajectory)
zA = 7.0                                    # altitude for ALL points
xt = 1.0                                    # furthest x point (the tip)
z0 = 1.0                                    # nearest z point
z1 = 1.5                                    # furthest z point (the tip)
qA = np.array([1.00, 0.00, 0.00, 0.00])     # orientation for ALL points
psi_off = -(5./8.)*np.pi                           # Yaw offset
d_off = 5                                   # distance offset (l2-norm from target)

# Fixed Params
hz = 20        

# Line =======================================
name = "line"

# Generate Trajectory
N = int(tf*hz+1)
Nhf = ((N-1)//2)
T = np.linspace(0.0,tf,N)

x1 = np.linspace(0,xt,Nhf+1)
x2 = np.flip(x1)

X = np.zeros((13,N))
X[0,:] = np.hstack((x1,x2[1:]))
X[2,:] = zA
X[6:10,:] = qA.reshape((4,1))

# Visualize
# viz.trajviz([X],step=5)
viz.trajanimate(X,X)

traj = np.vstack((T,X))
np.savetxt(name+".csv", traj, delimiter=",")
