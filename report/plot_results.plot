#!/usr/bin/gnuplot
#plot the step response of our system


set term png size 1280,960
set output "results.png"
set xlabel "Time (s)"
set ylabel "Voltage (V)"
set title "Step Response of The Controlled System"

set grid
set xrange [0:10]

f1(x) = 0.98*2.5
f2(x) = 1.02*2.5

plot 'data_good_1.txt' using 1:3 title 'System Output' w l, \
     'data_good_1.txt' using 1:2 title 'Control Input' w l, \
     f1(x),f2(x)