clear

% Parameters
Ndr = 4;     % Number of Drones.
T  = 10;    % Total Time for Trajectory.
hz = 0;     % Frame Step. Set to 0 if you want to follow raw waypoints.
R  = 1.5;   % Radius of formation (assumed circular)

% Trajectory
P = [ 1.0   1.0  -1.0  -1.0   1.0;
     -1.0   1.0   1.0  -1.0  -1.0; 
      1.0   1.0   1.0   1.0   1.0];

% Pre-processing
angle = 2*pi/Ndr;
Nfr = size(P,2);
dt = round(T/(Nfr-1),2);

if (hz == 0)
    traj = zeros(3*Ndr+1,Nfr);

    for k = 1:Nfr
        t = (k-1)*dt;
        traj(1,k) = t;
        traj(2:end,k) = swarm_setpoint(P(:,k),R,Ndr,angle);
    end
end

% liveplot(P,traj,Ndr)

function X = swarm_setpoint(P,R,N,angle)
    X = zeros(3*N,1);
    
    for k = 1:N
        idx = 1+(k-1)*3;
        theta = (k-1)*angle;
        
        X(idx:idx+2,:) = P + R.*[cos(theta) ; sin(theta) ; 0.0];
    end
end

function liveplot(P,traj,Ndr)

figure(1)
clf

% Plot the center line
plot3(P(1,:),P(2,:),P(3,:),'k--');
xlim([-3.0 3.0]);
ylim([-8.0 8.0]);
zlim([ 0.0 3.0]);
daspect([1 1 1])
hold on


% Plot the initial points
for k = 1:Ndr
    idx = 2+(k-1)*3;
    h(k) = plot3(traj(idx,1),traj(idx+1,1),traj(idx+2,1),'*-');
end
pause(1);

curr_time = 0.0;
dt = traj(1,2);
while (curr_time <= traj(1,end))
    tic
    j = ceil(curr_time/dt);
    
    for k = 1:Ndr
        idx = 2+(k-1)*3;
        h(k).XData = traj(idx,1:j);
        h(k).YData = traj(idx+1,1:j);
        h(k).ZData = traj(idx+2,1:j);
    end
    drawnow
    
    curr_time = curr_time + toc;
end




end