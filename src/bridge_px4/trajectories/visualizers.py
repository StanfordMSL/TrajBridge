import numpy as np
import util as ut
import matplotlib.pyplot as plt
from typing import List

import matplotlib.pyplot as plt
import matplotlib.animation as animation

def trajviz(Xs:List[np.ndarray],step=800,itr=False,trig_list=None,labels=None):
    # Some Useful Terms
    frame_body = np.array([ [0.2, 0.0, 0.0],
                            [0.0, 0.2, 0.0],
                            [0.0, 0.0, 0.1]])

    # Initialize Plot
    plt.figure()
    ax  = plt.axes(projection='3d')

    Xa = Xs[0]
    # If there is a map, plot map
    plim = np.array([[min(Xa[0,:])-1.0, max(Xa[0,:])+1.0],
                     [min(Xa[1,:])-1.0, max(Xa[1,:])+1.0],
                     [min(Xa[2,:])-1.0, max(Xa[2,:])+1.0]])

    xlim = plim[0,:]
    ylim = plim[1,:]
    zlim = plim[2,:]
    ratio = plim[:,1]-plim[:,0]

    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    ax.set_zlim(zlim)

    ax.set_box_aspect(ratio)  # aspect ratio is 1:1:1 in data space

    # If there are drones, plot their trajectories with appropriate step size.
    count = 0
    for X in Xs:
        # print(X)
        # Plot the Full Trajectory (line)
        pos = X[0:3,:]
        ax.plot(pos[0,:], pos[1,:], pos[2,:])
        N = X.shape[1]
        for i in range(0,N,step):
            pos  = X[0:3,i]
            quat = X[6:10,i]

            frame_labels = ["red","green","blue"]
            for j in range(0,3):
                arm = ut.quatrot(frame_body[j,:],quat)

                frame = np.zeros((3,2))
                if (j == 2):
                    frame[:,0] = pos
                else:
                    frame[:,0] = pos - arm

                frame[:,1] = pos + arm

                ax.plot(frame[0,:],frame[1,:],frame[2,:], frame_labels[j], label='_nolegend_')
            
            
        if trig_list is None:
            pass
        else:
            pos  = X[0:3,trig_list[count]]
            ax.scatter(pos[0],pos[1],pos[2], label='_nolegend_')
        
        count += 1

    if labels is None:
        pass
    else:
        plt.legend(labels)

    if itr == True:
        plt.show(block=False)
        plt.pause(1.0)
        plt.close()
    else:
        plt.show()

def uplot(U:np.ndarray,trig=None):
    N = U.shape[1]
    _, axs = plt.subplots(4)

    ylabs = ["m1","m2","m3","m4"]
    lims = np.array([[ 0.0, 1.0],
                    [  0.0, 1.0],
                    [  0.0, 1.0],
                    [  0.0, 1.0]])

    for i in range(0,4):
        axs[i].plot(U[i,:])
        axs[i].set(ylabel=ylabs[i])
        axs[i].hlines(lims[i,0],0,N,'red','--')
        axs[i].hlines(lims[i,1],0,N,'red','--')

        if trig is None:
            pass
        else:
            axs[i].scatter(trig,U[i,trig],c='red')
        
    plt.show()

def xvsxplot(Xs:List[np.ndarray],labels=None):
    _, axs = plt.subplots(6)
    ylabs = ["p_x","p_y","p_z","v_x","v_y","v_z"]
    lims = np.array([[-5.0, 5.0],
                     [-5.0, 5.0],
                     [-5.0, 5.0],
                     [-5.0, 5.0],
                     [-5.0, 5.0],
                     [-5.0, 5.0]])

    for i in range(0,6):
        for X in Xs:
            axs[i].plot(X[i,:])
        axs[i].set(ylabel=ylabs[i])
        axs[i].set_ylim(lims[i,:])

    plt.show()

    _, axs = plt.subplots(7)
    ylabs = ["q_w","q_x","q_y","q_z","w_x","w_y","w_z"]
    lims = np.array([[-1.2, 1.2],
                     [-1.2, 1.2],
                     [-1.2, 1.2],
                     [-1.2, 1.2],
                     [-9.0, 9.0],
                     [-9.0, 9.0],
                     [-9.0, 9.0]])

    for i in range(0,7):
        for X in Xs:
            axs[i].plot(X[i+6,:])
        axs[i].set(ylabel=ylabs[i])
        axs[i].set_ylim(lims[i,:])

    if labels is None:
        pass
    else:
        plt.legend(labels)

    plt.show()

def uvsuplot(UU:List[np.ndarray],labels=None):
    N = UU[0].shape[1]
    _, axs = plt.subplots(4)

    ylabs = ["m1","m2","m3","m4"]
    lims = np.array([[ 0.0, 1.0],
                    [  0.0, 1.0],
                    [  0.0, 1.0],
                    [  0.0, 1.0]])

    for i in range(0,4):
        for U in UU:
            axs[i].plot(U[i,:])
        axs[i].set(ylabel=ylabs[i])
        axs[i].hlines(lims[i,0],0,N,'red','--', label='_nolegend_')
        axs[i].hlines(lims[i,1],0,N,'red','--', label='_nolegend_')
    
    if labels is None:
        pass
    else:
        plt.legend(labels)

    plt.show()

def lossplot(losses,labels=None):
    if not isinstance(losses,list):
        losses = [losses]
    if not isinstance(labels,list):
        labels = [labels]

    plt.figure()
    for loss in losses:
        eps = np.linspace(0,len(loss),len(loss))
        plt.plot(eps, loss)
    
    if labels is not None:
        plt.legend(labels)

    plt.title('Loss')
    plt.xlabel('iteration')
    plt.ylabel('Loss')
    plt.show()

def trajanimate(Xa:np.ndarray,Xs:np.ndarray,fps=100,save=False):
    # Define map limits variable if undefined
    plim = np.array([[min(Xa[0,:])-1.0, max(Xa[0,:])+1.0],
                     [min(Xa[1,:])-1.0, max(Xa[1,:])+1.0],
                     [min(Xa[2,:])-1.0, max(Xa[2,:])+1.0]])

    # Initialize Plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Set plot limits and ratios
    ax.set_xlim(plim[0,:])
    ax.set_ylim(plim[1,:])
    ax.set_zlim(plim[2,:])
    ax.set_box_aspect(plim[:,1]-plim[:,0])          # aspect ratio is 1:1:1 in data space

    # Initialize some useful variables
    N = Xa.shape[1]                                 # Number of frames (animation) of animation
    quad = []                                       # Drone frame (physical) variable
    labels = ["red","green","blue"]                 # Drone frame axes colors

    # Reference (star) Trajectory
    ln_s = ax.plot(Xs[0,:],Xs[1,:],Xs[2,:])[0]

    # Actual Line (position) Trajectory Variable
    ln_a = ax.plot([], [], [])[0]

    # Actual Frame Trajectory Variables
    for i in range(0,3):
        quad.append(ax.plot([], [], [],labels[i])[0])
    
    # Animation pdate function
    def update(idx,Xf):
        # Some Useful Terms
        frame_body = np.array([ [0.2, 0.0, 0.0],
                                [0.0, 0.2, 0.0],
                                [0.0, 0.0, 0.1]])
        pos  = Xf[0:3,idx]
        quat = Xf[6:10,idx]

        # Update Line
        ln_a.set_data(Xf[0,0:idx],Xf[1,0:idx])
        ln_a.set_3d_properties(Xf[2,0:idx])

        # Update Frame
        for j in range(0,3):
            arm = ut.quatrot(frame_body[j,:],quat)

            frame = np.zeros((3,2))
            if (j == 2):
                frame[:,0] = pos
            else:
                frame[:,0] = pos - arm

            frame[:,1] = pos + arm
            
            quad[j].set_data(frame[0,:],frame[1,:])
            quad[j].set_3d_properties(frame[2,:])
    
    # Animate
    ani = animation.FuncAnimation(fig, update, N, fargs=(Xa,), interval=1000/fps)

    # Save or plot live depending on user input
    if save is True:
        fig.set_size_inches(25.6,19.2)
        writervideo = animation.FFMpegWriter(fps=fps)
        ani.save('saves/traj.mp4', writer=writervideo)
        plt.close()

        print("Figure Saved.")
    else:
        plt.show()

def FOviz(FOs:List[np.ndarray],Xkf=None,step=10):
    # Some Useful Terms
    frame_body = np.array([ [0.2, 0.0, 0.0],
                            [0.0, 0.2, 0.0],
                            [0.0, 0.0, 0.1]])

    # Initialize Plot
    plt.figure()
    ax  = plt.axes(projection='3d')
    
    # If there is a map, plot map
    Xa = FOs[0]
    plim = np.array([[min(Xa[0,:])-1.0, max(Xa[0,:])+1.0],
                     [min(Xa[1,:])-1.0, max(Xa[1,:])+1.0],
                     [min(Xa[2,:])-1.0, max(Xa[2,:])+1.0]])

    xlim = plim[0,:]
    ylim = plim[1,:]
    zlim = plim[2,:]
    ratio = plim[:,1]-plim[:,0]

    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    ax.set_zlim(zlim)

    ax.set_box_aspect(ratio)  # aspect ratio is 1:1:1 in data space

    xc = np.array([1.0,0.0,0.0])
    for FO in FOs:
        pos = FO[:,0:3,0]
        ax.scatter(pos[0,0],pos[0,1],pos[0,2],marker='o')
        ax.plot(pos[:,0], pos[:,1], pos[:,2])

        for i in range(0,FO.shape[0]):
            xc = np.array([ np.cos(FO[i,3,0]), np.sin(FO[i,3,0]), 0.0 ])
            ln0 = pos[i,:].reshape((3,1))
            lnf = (pos[i,:]+xc).reshape((3,1))
            ln = np.hstack((ln0,lnf))
            ax.plot(ln[0,:], ln[1,:], ln[2,:],"black")

    if Xkf is not None:
        ax.scatter(Xkf[0,:],Xkf[1,:],Xkf[2,:],marker='o')

    plt.show()
    
def errbarplot(Eps:List[np.ndarray],lbs_pol,lbs_eps):
    N = len(Eps)
    Ns = Eps[0].shape[1]
    print(lbs_pol)
    
    plt.figure()
    _, axs = plt.subplots(N)
    axs[0].set_title('Test Performance ('+str(Ns)+' tests)')

    for idx,eps in enumerate(Eps):
        mu_eps = np.mean(eps,axis=1)
        sd_eps = np.std(eps,axis=1)

        axs[idx].errorbar(lbs_pol,mu_eps,sd_eps,linestyle="None",fmt="ob",capsize=3,ecolor="k")
        axs[idx].set_ylim([0.0,1.1*max(mu_eps+sd_eps)])
        axs[idx].set_ylabel('Mean '+lbs_eps[idx]+' Error')
