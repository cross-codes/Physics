set xlabel "Iterations"
set ylabel "Absolute deviation"
set yrange [0:0.1]
plot "/tmp/project_monte_carlo_diff.dat" with lines title "Monte Carlo", \
     "/tmp/project_reject_1_diff.dat" with lines title "Reject sampling y = 2x", \
     "/tmp/project_reject_2_diff.dat" with lines title "Reject sampling y = 2(1 - x)", \
     "/tmp/project_reject_3_diff.dat" with lines title "Reject sampling y = 3(1 - x)²", \
     "/tmp/project_russian_1_diff.dat" with lines title "Russain roulette - Const", \
     "/tmp/project_russian_2_diff.dat" with lines title "Russian roulette - Var"

