% get_simulation_values.m
%
% This script generates all of the values for the matrices needed in the 
% simulation of our control system and plant.

%% Plant matrices:

A = [-.5 .5; 0 -2]
B = [0; 2]
C = [1 0]

%% Determine the equivalent discrete plant:

D = 0;
Ts = 0.1;
dt_sys = c2d(ss(A,B,C,D),Ts)
Ad = dt_sys.a
Bd = dt_sys.b


%% Determine the feedback gain vector K

Q = [20 0; 0 1];
R = 4;

[K S P_K] = dlqr(Ad, Bd, Q, R)
K
P_K


%% Determine the reference gain Kr:
I = eye(2);
Kr = -inv( (C-D*K)*inv(Ad-I-Bd*K)*Bd + D )


%% Design the Observer: Determine the Observer gain vector L

P_L = 0.2*P_K;
L = acker(Ad',C',P_L).'


Qw = 0;
Rv = 0;
