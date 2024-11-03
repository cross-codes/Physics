set xlabel "Iteration"
set ylabel "Estimator Value"
set logscale x
set logscale y

plot "/tmp/cgl.dat" using 1:2 title "Integral Estimator" with lines, \
     "/tmp/cgl.dat" using 1:3 title "Variance Estimator" with lines
