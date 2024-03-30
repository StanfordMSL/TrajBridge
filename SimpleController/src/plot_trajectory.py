import numpy as np
import matplotlib.pyplot as plt
from typing import List,Tuple
import numpy as np
import trajectory_helper as th
from scipy.spatial.transform import Rotation as R

def CP_to_3D(Tp:List[np.ndarray],CP:List[np.ndarray],
                hz:int=30,n:int=500,plot_last:bool=False):

    # Unpack the trajectory
    XX:List[np.ndarray] = []
    for i in range(len(Tp)):
        _,X = unpack_trajectory(Tp[i],CP[i],hz)
        XX.append(X)

    # Initialize World Frame Plot
    traj_colors = ["red","green","blue","orange","purple","brown","pink","gray","olive","cyan"]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    plim = np.array([
        [ -8.0,  8.0],
        [ -3.0,  3.0],
        [  1.0, -3.0]])
    
    xlim = plim[0,:]
    ylim = plim[1,:]
    zlim = plim[2,:]
    ratio = plim[:,1]-plim[:,0]

    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    ax.set_zlim(zlim)

    ax.set_box_aspect(ratio)  # aspect ratio is 1:1:1 in data space
    ax.invert_zaxis()

    # Rollout the world frame trajectory
    for idx,X in enumerate(XX):
        # Plot the world frame trajectory
        ax.plot(X[0,:], X[1,:], X[2,:],color=traj_colors[idx%len(traj_colors)],alpha=0.5)             # spline

        for i in range(0,X.shape[1],n):
            quad_frame(X[:,i],ax)

        if plot_last == True or idx == 0:
            quad_frame(X[:,-1],ax)

    plt.show(block=False)

def tXU_to_3D(tXU_list:List[np.ndarray],
              n:int=None):

    # Initialize World Frame Plot
    traj_colors = ["red","green","blue","orange","purple","brown","pink","gray","olive","cyan"]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    plim = np.array([
        [ -8.0,  8.0],
        [ -3.0,  3.0],
        [  1.0, -3.0]])
    
    xlim = plim[0,:]
    ylim = plim[1,:]
    zlim = plim[2,:]
    ratio = plim[:,1]-plim[:,0]

    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    ax.set_zlim(zlim)

    ax.set_box_aspect(ratio)  # aspect ratio is 1:1:1 in data space

    ax.invert_zaxis()

    # Rollout the world frame trajectory
    for idx,tXU in enumerate(tXU_list):
        # Plot the world frame trajectory
        ax.plot(tXU[1,:], tXU[2,:], tXU[3,:],color=traj_colors[idx%len(traj_colors)],alpha=0.5)             # spline

        # Plot Initial and Final
        quad_frame(tXU[1:14,0],ax)
        quad_frame(tXU[1:14,-1],ax)
            
        if n is not None:
            for i in range(n,tXU.shape[1],n):
                quad_frame(tXU[1:14,i],ax)


    plt.show()

def quad_frame(x:np.ndarray,ax:plt.Axes):
    frame_body = np.diag([0.6,0.6,-0.2])
    frame_labels = ["red","green","blue"]
    pos  = x[0:3]
    quat = x[6:10]
    
    for j in range(0,3):
        Rj = R.from_quat(quat).as_matrix()
        arm = Rj@frame_body[j,:]

        frame = np.zeros((3,2))
        if (j == 2):
            frame[:,0] = pos
        else:
            frame[:,0] = pos - arm

        frame[:,1] = pos + arm

        ax.plot(frame[0,:],frame[1,:],frame[2,:], frame_labels[j],label='_nolegend_')

def unpack_trajectory(Tp:np.ndarray,CP:np.ndarray,hz:int,
                      mode:str='xv',trim:bool=True) -> Tuple[np.ndarray,np.ndarray]:
    # Unpack the trajectory
    Nt = int(Tp[-1]*hz+1)
    T = np.zeros(Nt)

    if mode == 'xv':
        X = np.zeros((13,Nt))
    else:
        X = np.zeros((Nt,4,12))
        
    idx = 0
    for k in range(Nt):
        tk = Tp[0]+k/hz

        if trim == True:
            tk = np.minimum(Tp[-1],tk)
        if tk > Tp[idx+1] and idx < len(Tp)-2:
            idx += 1

        t0,tf = Tp[idx],Tp[idx+1]
        fo = th.ts_to_fo(tk-t0,tf-t0,CP[idx,:,:])

        T[k] = tk
        if mode == 'xv':
            X[:,k] = th.fo_to_xu(fo)[0:13]
        else:
            X[k,:,:] = fo

    # Ensure continuity of the quaternion
    if mode == 'xv':
        qr = np.array([0.0,0.0,0.0,1.0])
        for k in range(Nt):
            q = X[6:10,k]
            qc = th.nearest_quaternion(q,qr)

            X[6:10,k] = qc
            qr = qc
        
    return T,X
