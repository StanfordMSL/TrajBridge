"""
Helper functions for trajectory data.
"""

import numpy as np
import math
from scipy.spatial.transform import Rotation

# Some useful constants
Ndr = 5
Ncp = 12
M = np.zeros((Ncp,Ncp))
for i in range(Ncp):
    ci = (1/(Ncp-1))*i
    for j in range(Ncp):
        M[i,j] = ci**j
M = np.linalg.inv(M).T

def fo_to_xu(fo:np.ndarray,m:float=None,I:np.ndarray=None,wMf:np.ndarray=None):
    """
    Converts a flat output vector to a state vector and control
    input (normalized motor forces).

    Args:
        fo:     Flat output vector.
        m:      Quadcopter mass.
        I:      Quadcopter inertia matrix.
        wMf:    Quadcopter motor force matrix.

    Returns:
        xu:    State vector and control input.
    """

    # Unpack
    pt = fo[0:3,0]
    vt = fo[0:3,1]
    at = fo[0:3,2]
    jt = fo[0:3,3]
    st = fo[0:3,4]

    psit  = fo[3,0]
    psidt = fo[3,1]
    psiddt = fo[3,2]
    
    # Compute Gravity
    gt = np.array([0.00,0.00,-9.81])

    # Compute Thrust
    alpha:np.ndarray = at+gt

    # Compute Intermediate Frame xy
    xct = np.array([ np.cos(psit), np.sin(psit), 0.0 ])
    yct = np.array([-np.sin(psit), np.cos(psit), 0.0 ])
    
    # Compute Orientation
    xbt = np.cross(alpha,yct)/np.linalg.norm(np.cross(alpha,yct))
    ybt = np.cross(xbt,alpha)/np.linalg.norm(np.cross(xbt,alpha))
    zbt = np.cross(xbt,ybt)
    
    Rt = np.hstack((xbt.reshape(3,1), ybt.reshape(3,1), zbt.reshape(3,1)))
    qt = Rotation.from_matrix(Rt).as_quat()

    # Compute Thrust Variables
    c = zbt.T@alpha
    cd = zbt.T@jt

    # Compute Angular Velocity
    B1 = c
    D1 = xbt.T@jt
    A2 = c
    D2 = -ybt.T@jt
    B3 = -yct.T@zbt
    C3 = np.linalg.norm(np.cross(yct,zbt))
    D3 = psidt*(xct.T@xbt)

    wxt = (B1*C3*D2)/(A2*(B1*C3))
    wyt = (C3*D1)/(B1*C3)
    wzt = ((B1*D3)-(B3*D1))/(B1*C3)

    wt = np.array([wxt,wyt,wzt])

    if m is None or I is None or wMf is None:
        u = np.zeros(4)
    else:
        # Compute Remainder of Intermediate Terms
        E1 =  xbt.T@st - 2*cd*wyt - c*wxt*wzt
        E2 = -ybt.T@st - 2*cd*wxt + c*wyt*wzt
        E3 =  psiddt*xct.T@xbt + 2*psidt*wzt*xct.T@ybt - 2*psidt*wyt*xct.T@zbt - wxt*wyt*yct.T@ybt - wxt*wzt*yct.T@zbt

        # Find w_dot_x, w_dot_y, w_dot_z
        wdxt = (B1*C3*E2)/(A2*(B1*C3))
        wdyt = (C3*E1)/(B1*C3)
        wdzt = ((B1*E3)-(B3*E1))/(B1*C3)

        wdt = np.array([wdxt,wdyt,wdzt])

        uthr = m*c
        utau = I@wdt + np.cross(wt,I@wt)
        uw = np.hstack((uthr,utau))
    
        u = wMf@uw

    return np.hstack((pt,vt,qt,wt,u))

def ts_to_fo(tk:float,tf:float,CP:np.ndarray,kdr:int=12) -> np.ndarray:
    """
    Converts a trajectory spline (defined by tf,CP) to a flat output.

    Args:
        tk:     Current time.
        tf:     Trajectory final time.
        CP:     Control points.
        kdr:    Derivative order.

    Returns:
        fo:     Flat output vector.
    """
    fo = np.zeros((4,kdr))
    for i in range(0,kdr):
        nt = get_nt(tk,tf,i)
        fo[:,i] = (CP @ M @ nt) / (tf**i)

    return fo

def ts_to_xu(tk:float,tf:float,CP:np.ndarray,m:float,I:np.ndarray,wMf:np.ndarray,kdr:int=12) -> np.ndarray:
    """
    Converts a trajectory spline (defined by tf,CP) to a state vector and control input.

    Args:
        tk:     Current time.
        tf:     Trajectory final time.
        CP:     Control points.
        m:      Quadcopter mass.
        I:      Quadcopter inertia matrix.
        wMf:    Quadcopter motor force matrix.
        kdr:    Derivative order.

    Returns:
        xu:    State vector and control input.
    """
    fo = ts_to_fo(tk,tf,CP,kdr)
    return fo_to_xu(fo,m,I,wMf)

def xu_to_fo(xuv:np.ndarray,m:float=None,I:np.ndarray=None,fMw:np.ndarray=None) -> np.ndarray:
    """
    Converts a state vector to approximation of flat output vector.

    Args:
        xuv:     State vector.

    Returns:
        fo:     Flat output vector.
    """

    # Unpack variables
    wxk,wyk,wzk = xuv[10],xuv[11],xuv[12]

    # Initialize output
    fo = np.zeros((4,5))

    # Compute position terms
    fo[0:3,0] = xuv[0:3]

    # Compute velocity terms
    fo[0:3,1] = xuv[3:6]

    # Compute acceleration terms
    Rk = Rotation.from_quat(xuv[6:10]).as_matrix()      # Rotation matrix
    xbt,ybt,zbt = Rk[:,0],Rk[:,1],Rk[:,2]               # Body frame vectors
    gt = np.array([0.00,0.00,-9.81])                    # Acceleration due to gravity vector
    c = (fMw@xuv[13:17])[0]/m                           # Acceleration due to thrust vector

    fo[0:3,2] = c*zbt-gt

    # Compute yaw term
    psi = np.arctan2(Rk[1,0], Rk[0,0])

    fo[3,0]  = psi

    # Compute yaw rate term
    xct = np.array([np.cos(psi), np.sin(psi), 0])     # Intermediate frame x vector
    yct = np.array([-np.sin(psi), np.cos(psi), 0])    # Intermediate frame y vector
    B1 = c
    B3 = -yct.T@zbt
    C3 = np.linalg.norm(np.cross(yct,zbt))
    D1 = wyk*(B1*C3)/C3
    D3 = (wzk*(B1*C3)+(B3*D1))/B1

    psid = D3/(xct.T@xbt)

    fo[3,1] = psid

    # Compute yaw acceleration term
    Iinv = np.linalg.inv(I)
    rv1:np.ndarray = xuv[10:13]            # intermediate variable
    rv2:np.ndarray = I@xuv[10:13]          # intermediate variable
    utau = (fMw@xuv[13:17])[1:4]
    wd = Iinv@(utau - np.cross(rv1,rv2))
    E1 = wd[1]*(B1*C3)/C3
    E3 = (wd[2]*(B1*C3)+(B3*E1))/B1

    psidd = (E3 - 2*psid*wzk*xct.T@ybt + 2*psid*wyk*xct.T@zbt + wxk*wyk*yct.T@ybt + wxk*wzk*yct.T@zbt)/(xct.T@xbt)

    fo[3,2] = psidd


    return fo

def get_nt(tk:float,tf:float,kd:int):  
    """
    Generates the normalized time vector based on desired derivative order.

    Args:
        tk:     Current time.
        tf:     Trajectory final time.
        kd:     Derivative order.

    Returns:
        nt:      the normalized time vector.
    """

    tn = tk/tf

    nt = np.zeros(Ncp)
    for i in range(kd,Ncp):
        c = math.factorial(i)/math.factorial(i-kd)
        nt[i] = c*tn**(i-kd)
    
    return nt

def nearest_quaternion(q:np.ndarray,qr:np.ndarray) -> np.ndarray:
    """
    Finds the nearest quaternion to a reference quaternion.

    Args:
        q:      Quaternion.
        qr:     Reference quaternion.

    Returns:
        qc:     Closest quaternion to reference.
    """
    q1 = 1.0*q
    q2 = -1.0*q

    qc = q1
    if np.linalg.norm(q2-qr) < np.linalg.norm(q1-qr):
        qc = q2

    return qc

def nearest_xv_ds(tXUi:np.ndarray, xv_cr:np.ndarray,
               Tpi:np.ndarray, CPi:np.ndarray,
               wts:np.ndarray = np.array([1.0,1.0,1.0,
                                          1.0,1.0,1.0,
                                          1.0,1.0,1.0,1.0,
                                          1.0,1.0,1.0]),
               t_la:float=0.5) -> np.ndarray:
    # Final time value of nearest xv (weighted MSE)
    dxv = tXUi[1:14,:]-xv_cr.reshape(-1,1)
    t0 = tXUi[0,np.argmin(wts.T@dxv**2)]
    
    # Project forward using a time horizon (capped to end of ideal trajectory)
    tf = min(t0 + t_la,Tpi[-1])

    # Determine piecewise data to use
    idx = min(np.where(Tpi < tf)[0][-1],len(Tpi)-2)
    CPf = CPi[idx,:,:]
    tkf,tff = tf-Tpi[idx],Tpi[idx+1]-Tpi[idx]

    # Extract a clean xv from it
    fof = ts_to_fo(tkf,tff,CPf)                                  
    xv_ds = fo_to_xu(fof)[0:13]

    return xv_ds

