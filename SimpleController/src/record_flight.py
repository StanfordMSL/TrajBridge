import numpy as np
from datetime import datetime
import os
from typing import List,Literal

class FlightRecorder():
    def __init__(self,
                 nx:int,nu:int,nft:int,
                 hz:int
                 ):
        """
        FlightRecorder class for recording flight data and images. We record images every
        n_im time steps to save space.

        Args:
        nx:             Number of states
        nu:             Number of inputs
        nft:            Number of force/torque inputs
        hz:             Sampling frequency

        Flight Data:
        Tact:           Actual time
        Xref:           Reference state
        Uref:           Reference input
        Xact:           Actual state
        Uact:           Actual input
        Adv:            Advisor values
        Tsol:           Solve times
        Nimps:          Number of images per second to record
        Imgs:           Images
        
        Returns:
        None

        """
        
        # Some useful path(s)
        workspace_path = os.path.dirname(
            os.path.dirname(os.path.dirname(os.path.dirname(__file__))))
        
        # Check if output directory exists, if not, create it
        output_path = os.path.join(workspace_path,"cohorts",cohort_name,"output")
        if not os.path.exists(output_path):
            os.makedirs(output_path)

        # Initialize the trajectory data
        Ndata = int(hz*tf+1)
        self.Tact  = np.zeros(Ndata)
        self.Xact  = np.zeros((nx,Ndata))
        self.FTact = np.zeros((nu,Ndata))
        self.Adv = np.zeros((nu,Ndata))
        self.Tsol = np.zeros((Ntsol,Ndata))
        self.k = 0
        
        # Save the output path and base name
        self.output_path = output_path
        self.output_base = "flight_"+course_name+"_"+pilot_name

    def record(self,t_cr,x_ref,u_ref,x_act,u_act,img_cr,adv,t_sol):
        """"
        Record the flight data and images.
        
        Args:
        t_cr:       Current time
        x_ref:      Reference state
        u_ref:      Reference input
        x_act:      Actual state
        u_act:      Actual input
        img_cr:     Current image
        adv:        Advisor values
        t_sol:      Solve times
        
        Returns:
        None

        """
        # Record the trajectory data
        self.Tact[self.k] = t_cr
        self.Xref[:,self.k] = x_ref
        self.Uref[:,self.k] = u_ref
        self.Xact[:,self.k] = x_act
        self.Uact[:,self.k] = u_act
        self.Adv[:,self.k]  = adv
        self.Tsol[:,self.k] = t_sol

        # Record the image data
        if self.k%self.n_img == 0:
            self.Imgs[int(self.k/self.n_img),:,:,:] = img_cr

        # Increment the counter
        self.k += 1
        
    def save(self):
        """
        Save the flight data and images to a .pt file. The data is trimmed to the
        correct size before saving.

        Args:
        None

        Returns:
        output_path:    Path to the saved file (for debugging purposes)

        """
        # Trim the flight data
        self.Tact = self.Tact[0:self.k]
        self.Xref = self.Xref[:,0:self.k]
        self.Uref = self.Uref[:,0:self.k]
        self.Xact = self.Xact[:,0:self.k]
        self.Uact = self.Uact[:,0:self.k]
        self.Adv = self.Adv[:,0:self.k]
        self.Tsol = self.Tsol[:,0:self.k]
        
        # Trim the image data
        self.Imgs = self.Imgs[0:int(self.k/self.n_img),:,:,:]

        # Create the output name
        output_name = self.output_base+"_"+datetime.now().strftime("%Y%m%d_%H%M%S")+".pt"
        output_path = os.path.join(self.output_path,output_name)

        # Save the data
        torch.save(
            {'Tact':self.Tact,
             'Xref':self.Xref,
             'Uref':self.Uref,
             'Xact':self.Xact,
             'Uact':self.Uact,
             'Adv' :self.Adv,
             'Tsol':self.Tsol,
             'Imgs':self.preprocess_images(self.Imgs),
             'n_im':self.n_img
             },
            output_path)
    
        return output_path
    
    def preprocess_images(self,images:np.ndarray):
        """
        Converts raw images to processed images using a specified process configuration.
        """
   
        output = torch.zeros((images.shape[0],3,224,224))
        for i in range(images.shape[0]):
            output[i,:,:,:] = self.preprocess_image(images[i])

        return output