clear

% Parameters
Ndr = 5;     % Number of Drones.
T  = 15;    % Total Time for Trajectory.
hz = 0;     % Frame Step. Set to 0 if you want to follow raw waypoints.
R  = 1.5;   % Radius of formation (assumed circular)

% Trajectory
P = [ 1.0   1.0   1.0    0.0  -1.0  -1.0  -1.0   0.0   1.0;
     -1.0   0.0   1.0    1.0   1.0   0.0  -1.0  -1.0  -1.0; 
      1.0   1.0   1.0    1.0   1.0   1.0   1.0   1.0   1.0];

% Pre-processing
angle = 2*pi/Ndr;
Nfr = size(P,2);
dt = round(T/(Nfr-1),2);

% Trajectory Generation
if (hz == 0)
    traj = zeros(4*Ndr+1,Nfr);

    for k = 1:Nfr
        t = (k-1)*dt;
        traj(1,k) = t;
        traj(2:end,k) = swarm_setpoint(P(:,k),R,Ndr,angle);
    end
end

liveplot(P,traj,Ndr)

% Write to csv
name = ['traj_',num2str(Ndr),'dr',num2str(T),'s.csv'];
writematrix(traj,name) 

function X = swarm_setpoint(P,R,N,angle)
    X = zeros(4*N,1);
    
    for k = 1:N
        idx = 1+(k-1)*4;
        theta = (k-1)*angle;
        
        if k > 2
            z = 0.0;
        else
            z = 0.0;
        end
        X(idx:idx+2,:) = P + R.*[cos(theta) ; sin(theta) ; z];
        X(idx+3,:) = 0.0;
    end
end

function liveplot(P,traj,Ndr)

figure(1)
clf

% Plot the center line
plot3(P(1,:),P(2,:),P(3,:),'k--');
xlim([-8.0 8.0]);
ylim([-3.0 3.0]);
zlim([ 0.0 3.0]);
daspect([1 1 1])
hold on


% Plot the initial points
labels = {'1','2','3','4','5'};

for k = 1:Ndr
    idx = 2+(k-1)*4;
    h(k) = plot3(traj(idx,1),traj(idx+1,1),traj(idx+2,1),'*-');
    text(traj(idx,1),traj(idx+1,1),traj(idx+2,1),labels{k})

end
pause(1);

curr_time = 0.0;
dt = traj(1,2);


while (curr_time <= traj(1,end))
    tic
    j = ceil(curr_time/dt + 1e-3);
    
    for k = 1:Ndr
        idx = 2+(k-1)*4;
        
        h(k).XData = traj(idx,1:j);
        h(k).YData = traj(idx+1,1:j);
        h(k).ZData = traj(idx+2,1:j);
        

    end
    drawnow
        
    curr_time = curr_time + toc;
end

for k = 1:Ndr
    idx = 2+(k-1)*4;
    h(k).XData = traj(idx,:);
    h(k).YData = traj(idx+1,:);
    h(k).ZData = traj(idx+2,:);
end
drawnow
    
end