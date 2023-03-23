# Some Useful Functions
import numpy as np
from math import acos

def quatrot(v_in:np.ndarray,q:np.ndarray):
    v_in.reshape(3,1)

    r_in = np.append(0,v_in)
    qc   = quatcon(q)
        
    r_out = quatmap(quatmap(q)@r_in)@qc
    v_out = r_out[1:4]

    return v_out

def quatmult(qa:np.ndarray,qb:np.ndarray):
    q_out = quatmap(qa)@qb

    return q_out
    
def quataug_aa(q1:np.ndarray,a:np.ndarray):  
    q2 = np.zeros(4)
    q2[0] = np.cos(a[3]/2)
    q2[1] = a[0]*np.sin(a[3]/2)
    q2[2] = a[1]*np.sin(a[3]/2)
    q2[3] = a[2]*np.sin(a[3]/2)

    q_out = quatmap(q2)@q1

    return q_out
    
def psicalc(q):
    xb = np.array([1.0,0.0,0.0])
    xW = quatrot(xb,q)
    A = np.diag([1.0,1.0,0.0])

    v1 = np.array([1.0,0.0,0.0])
    v2 = A@xW

    psi = acos(v1@v2/np.linalg.norm(v2))

    return psi
    
def quatcon(q):
    qc   = np.append(q[0],-q[1:4])

    return qc

def quatmap(p):
    M = np.array([[ p[0], -p[1], -p[2], -p[3]],
                  [ p[1],  p[0], -p[3],  p[2]],
                  [ p[2],  p[3],  p[0], -p[1]],
                  [ p[3], -p[2],  p[1],  p[0]] ])
    
    return M

def quat2rotm(q):
    # Extract the values from Q
    q0 = q[0]
    q1 = q[1]
    q2 = q[2]
    q3 = q[3]
     
    # First row of the rotation matrix
    r00 = 2 * (q0 * q0 + q1 * q1) - 1
    r01 = 2 * (q1 * q2 - q0 * q3)
    r02 = 2 * (q1 * q3 + q0 * q2)
     
    # Second row of the rotation matrix
    r10 = 2 * (q1 * q2 + q0 * q3)
    r11 = 2 * (q0 * q0 + q2 * q2) - 1
    r12 = 2 * (q2 * q3 - q0 * q1)
     
    # Third row of the rotation matrix
    r20 = 2 * (q1 * q3 - q0 * q2)
    r21 = 2 * (q2 * q3 + q0 * q1)
    r22 = 2 * (q0 * q0 + q3 * q3) - 1
     
    # 3x3 rotation matrix
    R = np.array([[r00, r01, r02],
                  [r10, r11, r12],
                  [r20, r21, r22]])
    
    return R    

def rotm2quat(R):
    tr = R[0,0]+R[1,1]+R[2,2]

    # Note: Code initially uses q = [x,y,z,w] convention, which is not what the rest of the library uses.
    q = np.zeros(4)
    if tr > 0:
        S = np.sqrt(tr+1.0)
        q[3] = 0.5*S
        S = 0.5/S
        q[0] = (R[2,1]-R[1,2])*S
        q[1] = (R[0,2]-R[2,0])*S
        q[2] = (R[1,0]-R[0,1])*S
    else:
        i = 0
        if (R[1,1]>R[0,0]):
            i = 1
        if (R[2,2]>R[i,i]):
            i = 2
        j = (i+1)%3
        k = (j+1)%3

        S = np.sqrt(R[i,i]-R[j,j]-R[k,k]+1)
        q[i] =0.5*S
        S = 0.5/S
        q[3] = (R[k,j] - R[j,k]) * S
        q[j] = (R[j,i] + R[i,j]) * S
        q[k] = (R[k,i] + R[i,k]) * S
    
    # Change back to library convention
    qout = np.zeros(4)
    qout[0] = q[3]
    qout[1:4] = q[0:3]

    return qout

def veemap(A):
    return np.array([A[2,1],A[0,2],A[1,0]])

def cfac(N,k):
    # cfac = N!/(N-k)!
    cfac = np.math.factorial(N)/np.math.factorial(N-k)

    return cfac

def cross(a,b):
    c = [a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]]
    
    return np.array(c)

def noise_gen(Ee:np.ndarray,angle_axis=False):
    # Note: When used on full state, the orientation is in angle-axis form
    E = Ee[:,0:-1]
    e = Ee[:,-1]

    # Generate Raw Noise
    w = E@(2*np.random.random(E.shape[0])-1) + e

    # Check if noise is for full state or other
    if angle_axis == True:            
        w[8] += 1e-9                                   # Ensure angle-axis vector is non-zero
        w[6:9] = w[6:9]/(np.linalg.norm(w[6:9]))     # Ensure angle-axis vector is unit normal
    else:                   
        pass

    return w

def x_aug(x0:np.ndarray,wt:np.ndarray):
    # Note: orientation here is in angle-axis form
    x0s = np.zeros(13)
    
    # Update Non-Quaternion Terms
    x0s[0:6] = x0[0:6] + wt[0:6]
    x0s[10:13] = x0[10:13] + wt[10:13]

    # Update Quaternion Terms
    x0s[6:10] = quataug_aa(x0[6:10],wt[6:10])

    return x0s
