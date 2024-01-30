reset
set terminal pngcairo enhanced font "Arial,12" size 800,600
set output 'CY-trucks/images/Option_D1.png'
set datafile separator ";" 
datafile = 'CY-trucks/temp/Option_D1.csv'
set title 'Option[D1] : Nb itinéraires=f(Conducteur)'
set ylabel 'Conducteurs'
set xlabel 'Nb itinéraires'
set yrange [0:*] reverse     
set style fill solid  
unset key  
           
myBoxWidth = 0.8
set offsets 0,0,0.5-myBoxWidth/2.,0.5

plot 'CY-trucks/temp/Option_D1.csv' using (0.5*$1):0:(0.5*$1):(myBoxWidth/2.):($0+1):ytic(2) with boxxy lc var

set output

