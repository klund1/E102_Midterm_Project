% plot_simulation_results.m
%
% plots the result of the simulation of our control system
%
% assumes that the system output is stored as a timeseries y and the
% control effort is stored as a timeseries u (Simulink does this for us)


subplot(1,2,1)
plot(y.time,y.data)
grid on
title('System Output vs. Time')
xlabel('Time (s)')
ylabel('System Output (V)')
ylim([0,5])

subplot(1,2,2)
plot(u.time,u.data)
grid on
title('Control Input vs. Time')
xlabel('Time (s)')
ylabel('Control Input (V)')
ylim([0,5])
