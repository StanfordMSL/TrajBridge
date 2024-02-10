import numpy as np
import json
import os
import pickle
import synthesize.generate_min_snap as gms
import synthesize.trajectory_helper as th
from typing import List,Dict,Union
from controller.pilot import Pilot

def generate_course(cohort_name:str,course_name:str,roster:List[str],debug=True):

    # Generate Data Primitives
    tf,CPs_tn,CPs_tt = generate_control_points(course_name)
    Quads_tn,Quads_tt = generate_quad_frames(course_name)
    Pilots = [Pilot(cohort_name,pilot_name) for pilot_name in roster]

    T_tn = generate_T(course_name,200,1)
    T_t0 = generate_T(course_name,200,2)
    T_t1 = generate_T(course_name,200,3)
    T_t2 = generate_T(course_name,200,4)

    # Some useful intermediate variables
    CP_t01 = [CPs_tn[0]]
    Quads_t0 = [Quads_tn[0]]

    # Generate Data Files
    generate_data(cohort_name,"train",tf,CPs_tn,Quads_tn,Pilots,T_tn)
    generate_data(cohort_name,"test0",tf,CP_t01,Quads_t0,Pilots,T_t0)
    generate_data(cohort_name,"test1",tf,CP_t01,Quads_tt,Pilots,T_t1)
    generate_data(cohort_name,"test2",tf,CPs_tt,Quads_tt,Pilots,T_t2)    

def generate_data(
        cohort_name:str,data_folder:str,
        tf,CPs:List[np.ndarray],
        Quads:List[Dict],
        Pilots:List[Pilot],
        Tdata:np.ndarray):
    
    # Some useful constants
    sfti_path = os.path.dirname(
        os.path.dirname(os.path.dirname(__file__)))         
    cohort_name_path = os.path.join(
        sfti_path,"cohorts",cohort_name)

    for id_CP,CP in enumerate(CPs):
        for id_quad,quad in enumerate(Quads):
            tXU = generate_tXU(tf,CP,quad,Tdata)

            for pilot in Pilots:
                # Generate Testing Data
                Xhy,Xhn,Unn = generate_nnX(tXU,pilot)
                data = {"CP":CP,"quad":quad,"Xhy":Xhy,"Xhn":Xhn,"Unn":Unn}

                # Configure Data Paths
                data_path = os.path.join(
                    cohort_name_path,pilot.name,data_folder)
                os.makedirs(data_path,exist_ok=True)

                data_name  = os.path.join(
                    data_path,
                    f"CP{id_CP+1:03d}"+f"_quad{id_quad+1:03d}.pkl")
                
                # Save Data
                with open(data_name,'wb') as file:
                    pickle.dump(data,file)

def generate_control_points(course_name:str,rng_seed:int=0) -> (np.ndarray,List[np.ndarray]):
    """
    Generates a set of control points for a course by perturbing the nominal
    flat outputs. Generator will always generate the number of control points
    specified in the course config file.

    Args:
        course_name:    Name of the course to generate control points for.
        rng_seed:       Random number generator seed.

    Returns:
        tf:     Optimal trajectory time.
        CPs:    List of control point solutions.
    """
    # Set random number generator seed
    np.random.seed(rng_seed)

    # Some useful constants
    sfti_path = os.path.dirname(
        os.path.dirname(os.path.dirname(__file__)))         
    course_path = os.path.join(
        sfti_path,'configs','courses',course_name+".json")    

    # Load parameters from config file
    with open(course_path) as json_file:
        config = json.load(json_file) 

    tf = config["flight_time"]
    fo0 = np.array(config["flat_outputs"]["initial"],dtype=float)        
    fof = np.array(config["flat_outputs"]["final"],dtype=float)     
    w_fo0_lb = np.array(config["flat_outputs"]["perturbation"]["bounds"][0],dtype=float) 
    w_fo0_ub = np.array(config["flat_outputs"]["perturbation"]["bounds"][1],dtype=float)
    N_tn = config["flat_outputs"]["perturbation"]["Ntrain"]
    N_tt = config["flat_outputs"]["perturbation"]["Ntest"]

    # Generate Control Points    
    CPs_tn,n_tn = [gms.solve_min_snap(tf,fo0,fof)],1
    while n_tn < N_tn:
        w_fo0 = np.random.uniform(w_fo0_lb,w_fo0_ub)
        CP = gms.solve_min_snap(tf,fo0+w_fo0,fof)

        if CP is not False:
            CPs_tn.append(CP)
            n_tn += 1
    
    CPs_tt,n_tt = [],0
    while n_tt < N_tt:
        w_fo0 = np.random.uniform(w_fo0_lb,w_fo0_ub)
        CP = gms.solve_min_snap(tf,fo0+w_fo0,fof)

        if CP is not False:
            CPs_tt.append(CP)
            n_tt += 1

    return tf,CPs_tn,CPs_tt

def generate_quad_frames(course_name:str,rng_seed:int=0):
    """
    Generates a set of quadcopter frames by perturbing the nominal frame.

    Args:
        course_name:    Name of the course to generate quadcopter frames for.
        rng_seed:       Random number generator seed.
    
    Returns:
        frames: List of quadcopter frames of type Dict.
    """
    # Set random number generator seed
    np.random.seed(rng_seed)

    # Some useful constants
    sfti_path = os.path.dirname(
        os.path.dirname(os.path.dirname(__file__)))         
    course_path = os.path.join(
        sfti_path,'configs','courses',course_name+".json")    

    # Load parameters from config file
    with open(course_path) as json_file:
        config = json.load(json_file) 

    N_tn = config["quad_set"]["Ntrain"]
    N_tt = config["quad_set"]["Ntest"]

    bounds = config["quad_set"]["bounds"]

    # Generate Quadcopter Frames
    Quads_tn = [{} for _ in range(N_tn)]
    for quad in Quads_tn:
        # Pull from random distributions
        m =  np.random.uniform(
            bounds["mass"][0],bounds["mass"][1])
        mless_Ipp = np.random.uniform(
            bounds["massless_moments_of_inertia"][0],bounds["massless_moments_of_inertia"][1])
        l_base = np.random.uniform(
            bounds["arm_base_length"][0],bounds["arm_base_length"][1])
        lfxo = np.random.uniform(
            bounds["arm_front_x_offset"][0],bounds["arm_front_x_offset"][1])
        lfyo = np.random.uniform(
            bounds["arm_front_y_offset"][0],bounds["arm_front_y_offset"][1])
        lbxo = np.random.uniform(
            bounds["arm_back_x_offset"][0],bounds["arm_back_x_offset"][1])
        lbyo = np.random.uniform(
            bounds["arm_back_y_offset"][0],bounds["arm_back_y_offset"][1])
        nf = np.random.uniform(
            bounds["normalized_thrust"][0],bounds["normalized_thrust"][1])
        bG = np.random.uniform(bounds["torque_gain"][0],bounds["torque_gain"][1])

        # Intermediate steps
        Ipp = mless_Ipp*m
        lfx = l_base + lfxo
        lfy = l_base + lfyo
        lbx = l_base + lbxo
        lby = l_base + lbyo

        I   = np.diag(Ipp)
        fMw = nf*np.array([
            [ -1.0, -1.0, -1.0, -1.0],
            [ -lfy,  lfy,  lby, -lby],
            [  lfx, -lbx,  lfx, -lbx],
            [   bG,   bG,  -bG,  -bG]])
        
        # Save to a dictionary
        quad["m"] = m
        quad["I"] = I
        quad["wMf"] = np.linalg.inv(fMw)
        quad["Ipp"] = Ipp
        quad["lfx"] = lfx
        quad["lfy"] = lfy
        quad["lbx"] = lbx
        quad["lby"] = lby
        quad["nf"] = nf
        quad["bG"] = bG
        
    Quads_tt = [{} for _ in range(N_tt)]
    for quad in Quads_tt:
        # Pull from random distributions
        m =  np.random.uniform(
            bounds["mass"][0],bounds["mass"][1])
        mless_Ipp = np.random.uniform(
            bounds["massless_moments_of_inertia"][0],bounds["massless_moments_of_inertia"][1])
        l_base = np.random.uniform(
            bounds["arm_base_length"][0],bounds["arm_base_length"][1])
        lfxo = np.random.uniform(
            bounds["arm_front_x_offset"][0],bounds["arm_front_x_offset"][1])
        lfyo = np.random.uniform(
            bounds["arm_front_y_offset"][0],bounds["arm_front_y_offset"][1])
        lbxo = np.random.uniform(
            bounds["arm_back_x_offset"][0],bounds["arm_back_x_offset"][1])
        lbyo = np.random.uniform(
            bounds["arm_back_y_offset"][0],bounds["arm_back_y_offset"][1])
        nf = np.random.uniform(
            bounds["normalized_thrust"][0],bounds["normalized_thrust"][1])
        bG = np.random.uniform(bounds["torque_gain"][0],bounds["torque_gain"][1])

        # Intermediate steps
        Ipp = mless_Ipp*m
        lfx = l_base + lfxo
        lfy = l_base + lfyo
        lbx = l_base + lbxo
        lby = l_base + lbyo

        I   = np.diag(Ipp)
        fMw = nf*np.array([
            [ -1.0, -1.0, -1.0, -1.0],
            [ -lfy,  lfy,  lby, -lby],
            [  lfx, -lbx,  lfx, -lbx],
            [   bG,   bG,  -bG,  -bG]])
        
        # Save to a dictionary
        quad["m"] = m
        quad["I"] = I
        quad["wMf"] = np.linalg.inv(fMw)
        quad["Ipp"] = Ipp
        quad["lfx"] = lfx
        quad["lfy"] = lfy
        quad["lbx"] = lbx
        quad["lby"] = lby
        quad["nf"] = nf
        quad["bG"] = bG

    return Quads_tn,Quads_tt

def generate_T(course_name:str,hz:int=200,rng_seed:int=0):
    """
    Generates a time vector given a trajectory final time and control frequency with
    some noise.

    Args:
        tf:     Trajectory final time.
        hz:     Control frequency.
        std:    Standard deviation of the time vector.

    Returns:
        T:      Time vector.
    """

    # Set random number generator seed
    np.random.seed(rng_seed)

    # Some useful constants
    sfti_path = os.path.dirname(
        os.path.dirname(os.path.dirname(__file__)))         
    course_path = os.path.join(
        sfti_path,'configs','courses',course_name+".json")    

    # Load parameters from config file
    with open(course_path) as json_file:
        config = json.load(json_file) 

    tf = config["flight_time"]
    std = config["dt_std"]

    # Generate Time Vector
    N = int(tf*hz+1)
    T = np.linspace(0,tf,N) + np.random.normal(0,std,N)

    return T

def generate_tXU(tf:float,CP:np.ndarray,
                 quad:Dict[str, Union[float, np.ndarray]],
                 T:np.ndarray):
    """
    Generates the trajectory blocks for a set of control points. The trajectory
    blocks are 18xN arrays where N is the number of discrete time steps given
    the trajectory final time (tf) and control frequency (hz). Rows comprise of 
    trajectory time step (1x), full state (13x), and normalized motor force
    control (4x).

    Args:
        tf:         Trajectory final time.
        CPs:        List of control points.
        quad:       Quadcopter frame.
        T:          Time vector.

    Returns:
        tXU:     Trajectory block. 
    """

    # Some useful intermediate variables
    N,m,I,wMf = T.size,quad["m"],quad["I"],quad["wMf"]
    
    # Generate Trajectory Block
    tXU = np.zeros((18,N))
    for i in range(N):
        tk = T[i]
        fok = th.ts_to_fo(tk,tf,CP)
        xuk = th.fo_to_xu(fok,m,I,wMf)

        tXU[0,i] = tk
        tXU[1:,i] = xuk

    return tXU

def generate_nnX(tXU:np.ndarray,pilot:Pilot):
    # Some useful intermediate variables
    N = tXU.shape[1]
    x_ds = tXU[1:14,-1]
    t_ds = tXU[0,-1]
    u_pr = 0.5*np.ones(4)
    Xhy = np.zeros((pilot.Nhy,N))
    Xhn = np.zeros((pilot.Nhn,N))
    Unn = np.zeros((pilot.Nu,N))

    for i in range(N):
        t_cr = tXU[0,i]
        x_cr = tXU[1:14,i]
        u_cr = tXU[14:,i]
        h_ds = t_ds-t_cr

        _,_,_,Xhy[:,i],Xhn[:,i],_ = pilot.OODA(t_cr,x_cr,u_pr,h_ds,x_ds)
        Unn[:,i] = u_cr

        u_pr = tXU[14:,i]

    return Xhy,Xhn,Unn
