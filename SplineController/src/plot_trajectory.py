import numpy as np
from scipy.spatial.transform import Rotation as R
import matplotlib.pyplot as plt
from typing import List
from trajectory_helper import *

def unpack_trajectory(Tkf:np.ndarray,CP:np.ndarray,hz:int):
    # Unpack the trajectory
    Nsm = CP.shape[0]

    XX:List[np.ndarray] = []
    for i in range(Nsm):
        tf = Tkf[i+1]-Tkf[i]
        Nt = int(tf*hz+1)
        T = np.linspace(0,tf,Nt)
        X = np.zeros((13,Nt))
        for j in range(Nt):
            fo = ts_to_fo(T[j],tf,CP[i,:])
            X[:,j] = fo_to_xu(fo)[0:13]

        XX.append(X)

    # Ensure continuity of the quaternion
    qr = np.array([0.0,0.0,0.0,1.0])
    for i in range(Nsm):
        Nxv = XX[i].shape[1]
        for j in range(Nxv):
            q = XX[i][6:10,j]
            qc = nearest_quaternion(q,qr)

            XX[i][6:10,j] = qc
            qr = qc
    return XX

def flight_plot(Tkf:np.ndarray,CP:np.ndarray,hz:int=30,n:int=30):
    # Unpack the trajectory
    XX = unpack_trajectory(Tkf,CP,hz)

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
        quad_frame(X[:,-1],ax)

    plt.show()

def time_plot(Tkf:np.ndarray,CP:np.ndarray,hz:int=30):
    # Unpack the trajectory
    XX = unpack_trajectory(Tkf,CP,hz)
    X = np.hstack(XX)
    
    # Plot Positions and Velocities
    ylabels = [["$p_x$","$p_y$","$p_z$"],["$v_x$","$v_y$","$v_z$"]]
    fig, axs = plt.subplots(3, 2, figsize=(10, 4))
    for i in range(2):
        for j in range(3):
            idd = j+(3*i)

            axs[j,i].plot(X[idd,:],alpha=0.5)
            axs[j,i].set_ylabel(ylabels[i][j])
            axs[j,i].set_ylim([-6.2,6.2])

    axs[0, 0].set_title('Position')
    axs[0, 1].set_title('Velocity')
    
    plt.tight_layout()
    plt.show()

    # Plot Orientation and Body Rates
    ylabels = [["$q_x$","$q_y$","$q_z$","q_w"],["$\omega_x$","$\omega_y$","$\omega_z$"]]
    fig, axs = plt.subplots(4, 2, figsize=(10, 4))
    for i in range(2):
        for j in range(4):
            if not ((i==1) and (j==3)):
                idd = 6+j+(4*i)

                axs[j,i].plot(X[idd,:],alpha=0.5)
                axs[j,i].set_ylabel(ylabels[i][j])
                axs[j,i].set_ylim([-1.5,1.5])

    axs[0, 0].set_title('Orientation')
    axs[0, 1].set_title('Body Rates')
    
    plt.tight_layout()
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