#ifndef GAUSS_NOISE
#define GAUSS_NOISE
#include <stdlib.h>
#include <math.h>

class GaussNoise {
	double *receive;
	int sig_len;

	double get_gauss_val() {
		static double memory = MAXFLOAT;
		if (memory != MAXFLOAT) {
			double z = memory;
			memory = MAXFLOAT;
			return z;
		}
		double x, y, r = MAXFLOAT, tmp;
		while ((r > 1.0) || (r == 0)) {
   			x = 2.0 * (double) rand() / RAND_MAX - 1.0;
   			y = 2.0 * (double) rand() / RAND_MAX - 1.0;
			r = x * x + y * y;
		}
		tmp = sqrt(-2.0 * log(r) / r);
		memory = x * tmp;
		return y * tmp;
	}

public:
	
	GaussNoise(int sig_len) : sig_len(sig_len) {
		receive = new double[sig_len];
	}

	double *add_noise(double *signal, double disp) {
		double val = sqrt(disp);
		for (int i = 0; i < sig_len; ++i)
			*(receive + i) = *(signal + i) + get_gauss_val() * val;
		return receive;
	}
};
#endif
