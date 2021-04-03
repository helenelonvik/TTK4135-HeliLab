close all
clear
run('init02.m')
global N nx alpha beta lambda_t
% addpath('Help functions')
% x = [lambda r p p_dot e e_dot]'
% u = [p_c e_c]'
%oppg 1
A_c = [0 1 0 0 0 0;
       0 0 -K_2 0 0 0;
       0 0 0 1 0 0;
       0 0 -K_1*K_pp -K_1*K_pp 0 0;
       0 0 0 0 0 1;
       0 0 0 0 -K_3*K_ep -K_3*K_ed];
B_c = [0 0; 
       0 0;
       0 0;
       K_1*K_pp 0;
       0 0;
       0 K_3*K_ep];

% 10.4.2
I = eye(6);
T = 0.25;   %sampling time
A = I+T*A_c;
B = T*B_c;
%X_k+1 = A*X_k + B*u_k

% 10.4.3
% Inital values
close all
q1 = 0.5;
q2 = 0.5;
alpha = 0.2;
beta = 20;
lambda_start = pi;
lambda_final = 0;
lambda_t = 2*pi/3;
time_padding = 5;
sim_t = 20;

% Number of states and inputs
nx = size(A,2);                % Number of states (number of columns in A)
nu = size(B,2);                % Number of inputs(number of columns in B)
N = 40;                        % Time horizon for states
M = N;
n = N*nx+M*nu;

x0 = [lambda_start ;0 ;0 ;0; 0; 0];
xf = [lambda_final; 0; 0; 0; 0; 0];
x = zeros(N*6,1);
x(1:6) = x0;
Q_1 = 2*diag([1 0 0 0 0 0]);
P_1 = diag([q1 q2]);

%Generating A_eq and B_eq
A_eq = gen_aeq(A, B, N, nx, nu);
B_eq = zeros(size(A_eq,1),1);
B_eq(1:nx) = A*x0;
G = 2*gen_q(Q_1,P_1,N,M);

% Initialize z                 
z  = zeros(n,1);
z0 = z;

% Bounds
pk      = 30*pi/180;
ul 	    = [-pk; -inf];                   % Lower bound on control -- u1
uu 	    = [pk; inf];                     % Upper bound on control -- u1

xl(1:nx,1)    = -Inf*ones(nx,1);         % Lower bound on states (no bound)
xu(1:nx,1)    = Inf*ones(nx,1);          % Upper bound on states (no bound)
xl(3)   = ul(1);                         % Lower bound on state x3
xu(3)   = uu(1);                         % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]   = gen_constraints(N,M,xl,xu,ul,uu);
vlb(n)      = 0;                        % We want the last input to be zero
vub(n)      = 0;                        % We want the last input to be zero

f = @(z) 1/2*z'*G*z;
opt = optimoptions('fmincon','Algorithm','sqp','MaxFunEvals',40000);
tic
[Z, ZVAL, EXITFLAG] = fmincon(f, z0, [], [], A_eq, B_eq, vlb, vub, @confun, opt);
toc


% Extract control inputs and states
u1 = [Z(N*nx+1:nu:n);Z(n-1)];           % Control input 1 from solution
u2 = [Z(N*nx+2:nu:n);Z(n)];             % Control input 2 from solution
x1 = [x0(1);Z(1:nx:N*nx)];              % State x1 from solution
x2 = [x0(2);Z(2:nx:N*nx)];              % State x2 from solution
x3 = [x0(3);Z(3:nx:N*nx)];              % State x3 from solution
x4 = [x0(4);Z(4:nx:N*nx)];              % State x4 from solution
x5 = [x0(5);Z(5:nx:N*nx)];              % State x5 from solution
x6 = [x0(6);Z(6:nx:N*nx)];              % State x6 from solution

num_pads = time_padding/T;
zero_padding = zeros(num_pads,1);
unit_padding  = ones(num_pads,1);

u1  = [zero_padding; u1; zero_padding];
u2  = [zero_padding; u2; zero_padding];
x1  = [lambda_start*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

t = 0:T:T*(length(u1)-1);
u = [u1 u2];
% figure(1); 
% subplot(nx,1,1); 
% plot(t,x1); grid on; 
% title('travel')
% subplot(nx,1,2)
% plot(t,x2); grid on; 
% title('travel dot')
% subplot(nx,1,3)
% plot(t,x3); grid on;
% title('pitch')
% subplot(nx,1,4)
% plot(t,x4); grid on; 
% title('pitch dot')
% subplot(nx,1,5)
% plot(t,x5); grid on;
% title('elevation')
% subplot(nx,1,6)
% plot(t,x6); grid on;
% title('elevation dot')

% figure();
% f = load('pitch_10_4_3.mat');
% plot(f.ans(1,:), f.ans(2,:), t(1:80), 180*x3(1:80)/pi,'r--','Linewidth', 1); grid on;
% legend('p^*', 'p');
% currentFigure =gcf;
% title(currentFigure.Children(end),'p^* vs p, without feedback');
% 
% 
% figure();
% f = load('travel_10_4_3.mat');
% plot(f.ans(1,:), f.ans(2,:), t(1:80), 180*x1(1:80)/pi,'r--','Linewidth', 1); grid on;
% legend('{\lambda}^*', '{\lambda}');
% currentFigure =gcf;
% title(currentFigure.Children(end),' {\lambda}^* vs {\lambda}, without feedback');
% 
% figure();
% f = load('elevation_10_4_3.mat');
% plot(f.ans(1,:), f.ans(2,:), t(1:80), 180*x5(1:80)/pi,'r--','Linewidth', 1); grid on;
% legend('e^*', 'e');
% currentFigure =gcf;
% title(currentFigure.Children(end),'e^* vs e, without feedback');


% 10.4.4
% close all
% 5 1 1 .5 30 10
% 15 0.1 0.1 1 10 20
Q_lqr = diag([5 0.1 0.5 1 15 5]);
R_lqr = diag([0.1 0.1]);
K_lqr = dlqr(A,B,Q_lqr,R_lqr);
 
x_opt =[x1 x2 x3 x4 x5 x6];



figure();
f = load('pitch_10_4.mat');
plot(f.ans(1,1:10000), f.ans(2,1:10000), t(1:80), 180*x3(1:80)/pi,'r--','Linewidth', 1); grid on;
legend('p^*', 'p');
currentFigure =gcf;
title(currentFigure.Children(end),'p^* vs p, with feedback');


figure();
f = load('travel_10_4.mat');
plot(f.ans(1,1:10000), f.ans(2,1:10000), t(1:80), 180*x1(1:80)/pi,'r--','Linewidth', 1); grid on;
legend('{\lambda}^*', '{\lambda}');
currentFigure =gcf;
title(currentFigure.Children(end),' {\lambda}^* vs {\lambda}, with feedback');

figure();
f = load('elevation_10_4.mat');
plot(f.ans(1,1:10000), f.ans(2,1:10000), t(1:80), 180*x5(1:80)/pi,'r--','Linewidth', 1); grid on;
legend('e^*', 'e');
currentFigure =gcf;
title(currentFigure.Children(end),'e^* vs e, with feedback');