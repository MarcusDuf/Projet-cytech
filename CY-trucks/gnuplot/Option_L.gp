reset
set terminal pngcairo enhanced font "Arial,12" size 800,600
set output 'CY-trucks/images/Option_L.png'
set datafile separator ";" 
datafile = 'CY-trucks/temp/Option_L.csv'
set title 'Option[L] : Distance=f(Itinéraire)'
set ylabel 'Distance(km)'
set xlabel 'Itinéraires ID'
set xrange [0:*] 
set yrange [0:*]    
set style fill solid
set boxwidth 0.7
 
plot 'CY-trucks/temp/Option_L.csv' using ($0+1):2:($0+1):xtic(1) notitle with boxes lc var 

set output
