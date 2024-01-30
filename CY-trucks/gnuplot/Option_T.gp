reset
set terminal pngcairo enhanced font "Arial,12" size 800,600
set termoption dash
set output 'CY-trucks/images/Option_T.png'
set datafile separator ";" 
datafile = 'CY-trucks/temp/Option_T.csv'
set title 'Option[T] : Nb itinéraires=f(Ville)'
set ylabel 'Nb itinéraires'
set xlabel 'Noms villes'
set xtics rotate by -45
set yrange [0:*] 
set style fill solid
set boxwidth 0.7
set style data histograms
set style histogram clustered

plot 'CY-trucks/temp/Option_T.csv' using 2:xtic(1) lc rgb "#00bf63" ti 'Total itinéraires'  , '' using 3:xtic(1) lc rgb "#7ed957" ti 'Première ville'  

set output










