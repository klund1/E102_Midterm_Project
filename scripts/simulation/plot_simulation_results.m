% plot_simulation_results.m
%
% plots the result of the simulation of our control system
%
% assumes that the system output is stored as a timeseries y and the
% control effort is stored as a timeseries u (Simulink does this for us)


subplot(1,2,1)
plot(y.time,y.data)
grid on
hold on
fplot(@(x) 2.5*.98, [0 max(y.time)], 'r--')
title('System Output vs. Time')
xlabel('Time (s)')
ylabel('System Output (V)')
ylim([0,5])

subplot(1,2,2)
stairs(u.time,u.data)
grid on
title('Control Input vs. Time')
xlabel('Time (s)')
ylabel('Control Input (V)')
ylim([0,5])
