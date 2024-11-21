filename(n) = sprintf("/tmp/rv_1D_%d.dat", n)
plot for [i=0:499] filename(i) using 1:2 with lines notitle
