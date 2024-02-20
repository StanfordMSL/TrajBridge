import numpy as np

class BallTimer():
    '''
    Timer that checks if drone is in an l2-norm ball. Resets on exit
    '''
    def __init__(self,t0:float,pos_des:np.ndarray,dt:float,pos_tol:float):
        self.t0 = t0                                      # Initial time
        self.pos_des = pos_des                             # Desired position
        
        self.dt = dt                                     # Duration
        self.pos_tol = pos_tol                           # Tolerance

    def check(self,time_now:float,position_now:np.ndarray):
        tf = self.t0 + self.dt                                      # Final time
        tk = time_now                                               # Current time
        sk = np.linalg.norm((position_now-self.pos_des))            # Current distance error (l2-norm)
        tol = self.pos_tol                                          # Tolerance
        
        if (sk < tol) and (tk > tf):
            return True                                             # Time finished
        elif (sk > tol):
            self.t0 = tk                                            # Reset initial time

        return False                                                # Time not finished
    
    def reset(self,t0:float,pos_des:np.ndarray,dt:float=None,pos_tol:float=None):
        self.t0 = t0
        self.pos_des = pos_des

        if dt is not None:
            self.dt = dt
        if pos_tol is not None: 
            self.pos_tol = pos_tol
    