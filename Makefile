run: QAMModul.h GaussNoise.h QAMDemodul.h main.cpp
	g++ -Wall -O9 -s QAMModul.h GaussNoise.h QAMDemodul.h main.cpp -o build
	./build
	gnuplot --persist << load "plot.gnu"
