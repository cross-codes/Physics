set xlabel "Iterations"
set ylabel "Standard deviation"
set yrange [0:6]
plot "/tmp/project_monte_carlo.dat" with lines title "Monte Carlo", \
     "/tmp/project_reject_1.dat" with lines title "Reject sampling y = 2x", \
     "/tmp/project_reject_2.dat" with lines title "Reject sampling y = 2(1 - x)", \
     "/tmp/project_reject_3.dat" with lines title "Reject sampling y = 3(1 - x)²", \
     "/tmp/project_russian_1.dat" with lines title "Russain roulette - Const", \
     "/tmp/project_russian_2.dat" with lines title "Russian roulette - Var"

