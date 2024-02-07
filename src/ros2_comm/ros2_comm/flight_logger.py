import numpy as np
import pickle

class FlightLogger():
    '''
    Logger for debugging SFTI. Logs only the portion of the flight that uses the
    SFTI controller. For simplicity, we capture of only the first 10 seconds or 
    less (at 200hz this corresponds to 2000 frames).
    '''
    def __init__(self,N:int=2000):
        self.N = N
        self.Xd = np.zeros((13,N))
        self.Ta = np.zeros(N)
        self.Xa = np.zeros((13,N))
        self.Ufa = np.zeros((4,N))
        self.Ufn = np.zeros((4,N))
        self.k = 0

    def update(self,Xd:np.ndarray,Ta:float,Xa:np.ndarray,Ufa:np.ndarray,Ufn:np.ndarray):
        if self.k < self.N:    
            self.Xd[:,self.k] = Xd
            self.Ta[self.k] = Ta
            self.Xa[:,self.k] = Xa
            self.Ufa[:,self.k] = Ufa
            self.Ufn[:,self.k] = Ufn
            self.k += 1

    def save(self):
        self.Xd  = self.Xd[:,0:self.k]
        self.Ta  = self.Ta[0:self.k]
        self.Xa  = self.Xa[:,0:self.k]
        self.Ufa = self.Ufa[:,0:self.k]
        self.Ufn = self.Ufn[:,0:self.k]

        data = {"Xd":self.Xd,
                "Ta":self.Ta,"Xa":self.Xa,
                "Ufa":self.Ufa,"Ufn":self.Ufn}
        
        with open("data.pkl","wb") as f:
            pickle.dump(data,f)