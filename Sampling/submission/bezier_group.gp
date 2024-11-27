set multiplot layout 2,1
set key outside
set xlabel "100E' / E_{max}"
set ylabel "Φ'"
set title "β <= 0.9"
plot "/tmp/neutrino_0.dat" with lines smooth bezier title "Original spectrum", \
     "/tmp/neutrino_1.dat" with lines smooth bezier title "β = 0.01", \
     "/tmp/neutrino_2.dat" with lines smooth bezier title "β = 0.1", \
     "/tmp/neutrino_3.dat" with lines smooth bezier title "β = 0.9"


set key outside
set xlabel "100E' / E_{max}"
set ylabel "Φ'"
set title "β = 0.99"
plot "/tmp/neutrino_4.dat" with lines smooth bezier title "β = 0.99"
unset multiplot
