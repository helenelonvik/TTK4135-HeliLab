%% PART 10.3 
run('part2.m')

%Task 10.3.1 (Q,R and K)
Q_lqr = diag([15 0.1 0.1 1]);
R_lqr = diag([0.1]);
K_lqr = dlqr(A1,B1,Q_lqr,R_lqr)


x_opt = [x1,x2,x3,x4];

figure();
f = load('pitch_10_3.mat');
plot(f.ans(1,:), f.ans(2,:), t(1:80), 180*x3(1:80)/pi,'r--','Linewidth', 1); grid on;
legend('p^*', 'p');
currentFigure =gcf;
title(currentFigure.Children(end),'Pitch (q = 0.1) with feedback');


figure();
f = load('travel_10_3.mat');
plot(f.ans(1,:), f.ans(2,:), t(1:80), 180*x1(1:80)/pi,'r--','Linewidth', 1); grid on;
legend('{\lambda}^*', '{\lambda}');
currentFigure =gcf;
title(currentFigure.Children(end),'Travel (q = 0.1) with feedback');


%{
figure();
f = load('travel_10_2.mat');
plot(f.ans(1,:), f.ans(2,:), t, 180*u/pi,'r--','Linewidth', 1); grid on;

figure();
f = load('pitch_10_2.mat');
plot(f.ans(1,:), f.ans(2,:), t, 180*u/pi,'r--','Linewidth', 1); grid on;

%}
