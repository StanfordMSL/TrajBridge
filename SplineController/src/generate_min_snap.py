# Minimum Snap Trajectory Generation Method
import numpy as np
import scipy.sparse as sps
import scipy.linalg as spl
import sys
import math
import qpsolvers

# Debugging
np.set_printoptions(threshold=sys.maxsize)
np.set_printoptions(linewidth=np.inf)

# Fixed parameters for minimum snap quadcopter trajectory planning problem
Nco = 8                                                         # Number of coefficients (degrees of polynomial+1) 
Nfo = 4                                                         # Number of Flat Outputs
kdr = np.array([4,4,4,2])                                       # Target derivative to minimize
mu  = np.array([1.0,1.0,1.0,1.0])                               # Scaling for each parameter

def solve_min_snap(tf:np.ndarray,fo0:np.ndarray,fo1:np.ndarray):
    # Some useful intermediate variables
    Tkf = np.array([0.0,tf])                                    # Keyframe times
    FOkf = np.array([fo0,fo1])                                # Keyframe Flat Outputs

    # Generate QP Terms
    P,q = Pq_gen(Tkf)                                           # Min Snap Cost
    A,b = Ab_gen(Tkf,FOkf)                                      # Keyframe Constraints
    G,_ = Gh_gen(Tkf)                                           # Continuity Constraints

    # Convert to Sparse
    P = sps.csc_matrix(P)
    A = sps.csc_matrix(A)
    G = sps.csc_matrix(G)

    # Solve QP to get coefficient solution (spline variables)
    try:
        sigma = qpsolvers.solve_qp(P,q,G=None,h=None,A=A,b=b,solver="osqp")       # Solve QP
        SM = sigma.reshape((-1,Nfo,Nco))                                # Reshape to match keyframes
        
        tf = Tkf[-1]
        Ti = np.linspace(0.0,tf,Nco)
        CP = SM2CP(SM,Ti)

        return CP
    
    except:
        # print("[adMS] Trajectory not feasible. Aborting.")
        return False
    
def Pq_gen(Tkf):
    # Unpack some stuff
    Nsm = len(Tkf)-1            # Number of segments

    Plist = []
    for i in range(0,Nsm):
        t0 = Tkf[i]
        tf = Tkf[i+1]

        for j in range(0,Nfo):
            P = mu[j]*Ps_gen(kdr[j],t0,tf)
            Plist.append(P)

    P = spl.block_diag(*Plist)
    q = np.zeros(Nsm*Nfo*Nco)

    return P,q

def Ps_gen(kdr:np.float64,t0:np.float64,tf:np.float64):
    Ps = np.zeros((Nco,Nco))
    for i in range(kdr,Nco):
        for j in range(i,Nco):
            c1 = cf_gen(i,kdr)
            c2 = cf_gen(j,kdr)
            tk = 1+i+j-(kdr*2)

            Pij = c1*c2*((tf**tk)-(t0**tk))/tk

            Ps[i,j] = Pij
            Ps[j,i] = Pij

    return Ps

def Ab_gen(Tkf:np.ndarray,FOkf:np.ndarray):
    # Unpack some stuff
    Nsm = len(Tkf)-1            # Number of segments

    A = np.zeros((0,(Nco*Nfo*Nsm)))
    b = np.zeros(0)

    for i in range(0,Nsm):
        t0 = Tkf[i]
        tf = Tkf[i+1]

        for j in range(0,Nfo):
            for k in range(0,kdr[j]):
                # Generate Coefficients for derivative compute
                a0 = poly2kdr(t0,k)
                af = poly2kdr(tf,k)
                
                # Extract Desired Values from FO
                b0 = FOkf[i,j,k]
                bf = FOkf[i+1,j,k]

                # Generate indices for constraints
                idx10 = i*Nfo*Nco+j*Nco
                idx1f = idx10+Nco
                idx20 = (i+1)*Nfo*Nco+j*Nco
                idx2f = idx20+Nco

                # Populate Output
                Ak = np.zeros((2,(Nco*Nfo*Nsm)))
                bk = np.zeros(2)
                if np.isnan(b0) == False:
                    Ak[0,idx10:idx1f] = a0
                    bk[0] = b0

                    if np.isnan(bf) == False:
                        Ak[1,idx10:idx1f] = af
                        bk[1] = bf
                    else:
                        if i < Nsm-1:
                            Ak[1,idx10:idx1f] = af
                            Ak[1,idx20:idx2f] = -af                     
                else:
                    if np.isnan(bf) == False:            
                        Ak[0,idx10:idx1f] = af
                        bk[0] = bf
                    else:
                        if i < Nsm-1:
                            Ak[0,idx10:idx1f] = af
                            Ak[0,idx20:idx2f] = -af
                # Trim
                idx = ~np.all(Ak== 0,axis=1)
                Ak = Ak[idx,:]
                bk = bk[idx]

                # Add to constriants
                A = np.vstack((A,Ak))
                b = np.append(b,bk)

    return A,b

def Gh_gen(Tkf:np.ndarray):
    # Unpack some stuff
    Nsm = len(Tkf)-1            # Number of segments

    idx_fo = 3
    kdr = 1
    G = np.zeros((0,(Nco*Nfo*Nsm)))
    h = np.zeros(0)
    for i in range(0,Nsm-1):
        t0 = Tkf[i]

        # Generate Coefficients for derivative compute
        g0 = poly2kdr(t0,kdr)

        # Generate indices for constraints
        idx10 = i*Nfo*Nco+idx_fo*Nco
        idx1f = idx10+Nco

        # Populate Output
        Gk = np.zeros((2,(Nco*Nfo*Nsm)))
        hk = np.zeros(2)
        Gk[0,idx10:idx1f] = g0
        Gk[1,idx10:idx1f] = -g0
        hk[0] = 10.0
        hk[1] = 10.0

        # Add to constriants
        G = np.vstack((G,Gk))
        h = np.append(h,hk)

    return G,h

def cf_gen(N,k):
    cfac = math.factorial(N)/math.factorial(N-k)

    return cfac

def poly2kdr(t,kdr):
    a = np.zeros(Nco)
    for i in range(kdr,Nco):
        c1 = cf_gen(i,kdr)
        a[i] = c1*(t**(i-kdr))

    return a
    
def SM2CP(SM:np.ndarray,T:np.ndarray):
    # Unpack some stuff
    Ncp = T.size

    # Output Variable
    FO = np.zeros((Nfo,Ncp))

    # Roll-out trajectory
    for i in range(0,Ncp):
        for j in range(0,Nfo):                    # at the ends, so we zero them accordingly.
            a = poly2kdr(T[i],0)
            FO[j,i] = a@SM[0,j,:]        
    return FO