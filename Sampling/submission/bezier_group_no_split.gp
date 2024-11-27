set xlabel "100E' / E_{max}"
set ylabel "Φ'"
plot "/tmp/neutrino_0.dat" with lines smooth bezier title "β = 0.01", \
     "/tmp/neutrino_2.dat" with lines smooth bezier title "β = 0.1", \
     "/tmp/neutrino_3.dat" with lines smooth bezier title "β = 0.9", \
     "/tmp/neutrino_4.dat" with lines smooth bezier title "β = 0.99"
