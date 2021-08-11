# gnuplot learn 

```gnuplot
plot "J_history.txt" using 1:2 "%lf,%lf" w l 
set term "pdf"
set output "a.pdf"
set title "GD cost value"
set grid xtics ytics ls 100
set xlabel "times"
set ylabel "cost value"
replot

```