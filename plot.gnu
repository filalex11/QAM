set xlabel "дисперсия шума"
set ylabel "вероятность ошибки на сигнал"
set mxtics 1
set mytics 10
set grid mxtics mytics xtics ytics
unset key
set logscale y
set format y "10^{%L}"
plot "err_prob" w l lw 2 lc "red"
