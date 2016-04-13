#!/usr/bin/gnuplot
#plot the step response of our system


set term pngcairo size 1280,960 dashed font ",24"
set output "results.png"
set xlabel "Time (s)"
set ylabel "Voltage (V)"
set title "Step Response of the Controlled System"

set grid
set xrange [0:5]
set yrange [0:5.2]
set ytics 0.5

f1(x) = 0.98*2.5
f2(x) = 1.02*2.5

offset(x) = x-10




plot 'data_good_2.txt' using (offset($1)):3 title 'System Output' w l lt 1 lw 2 lc rgb 'blue', \
     'data_good_2.txt' using (offset($1)):2 title 'Control Input' w l lt 1 lw 2 lc rgb 'green', \
     f1(x) title '2% settling' lt 2 lw 2 lc rgb "red" ,f2(x) lt 2 lw 2 lc rgb "red" notitle
