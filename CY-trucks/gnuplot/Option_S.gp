reset
set terminal pngcairo enhanced font "Arial,12" size 1200,1000
set termoption dash
set output 'CY-trucks/images/Option_S.png'
set datafile separator ";" 
datafile = 'CY-trucks/temp/Option_S.csv'
set title 'Option[S] : Distance=f(Itinéraire)'
set ylabel 'Distance (Km)'
set xlabel 'Itinéraires Id' 
set xtics rotate by -45  
set yrange [ 0: * ]

plot 'CY-trucks/temp/Option_S.csv' using 4:xtic(1) with filledcurves above lc rgb '#00bf63' title "Distance Max/Min (Km)",'' using 2:xtic(1)  with filledcurves above lc rgb '#FFFFFF' notitle, '' using 3:xtic(1)  title "Distance moyenne (Km)" smooth mcspline lc rgb '#7ed957'
      
     set output

 




