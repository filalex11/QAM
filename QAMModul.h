#ifndef QAMMODUL_H
#define QAMMODUL_H
#include <stdlib.h>
#include <math.h>

class QAMModul {
	const int sig_count;
	const double T, f;
	const int sig_len;
	double **signals;
	double avg_energy;
public:
	QAMModul(int sig_count, double T, double f, int sig_len) 
			: sig_count(sig_count), T(T), f(f), sig_len(sig_len) {
		double *s1 = new double[sig_count],
			   *s2 = new double[sig_count];
		int sqr_sig_count = (int) sqrt(sig_count);
		for (int i = 0; i < sqr_sig_count; ++i) {
			for (int j = 0; j < sqr_sig_count; ++j) {
				*(s1 + i * sqr_sig_count + j) = 
						1.0 - 2.0 * i / (sqr_sig_count - 1);
				*(s2 + i * sqr_sig_count + j) = 
						1.0 - 2.0 * j / (sqr_sig_count - 1);
			}
		}
		signals = new double*[sig_count];
		for (int i = 0; i < sig_count; ++i) {
			*(signals + i) = new double[sig_len];
			for (int j = 0; j < sig_len; ++j)
				*(*(signals + i) + j) = sqrt(2.0 / T) *
					   	(*(s1 + i) * cos(2.0 * M_PI * f * j * T / sig_len) +
						 *(s2 + i) * sin(2.0 * M_PI * f * j * T / sig_len));
		}
		delete [] s1;
		delete [] s2;
		avg_energy = 0;
		for (int i = 0; i < sig_count; ++i)
			for (int j = 0; j < sig_len; ++j)
				avg_energy += *(*(signals + i) + j) * *(*(signals + i) + j);
		avg_energy /= sig_count;
	}
	
	inline int get_sig_len() const {return sig_len;}

	inline double get_avg_energy() const {return avg_energy;}

	inline double *get_signal(int num) const {return *(signals + num);}

	inline double **get_constel() const {return signals;}
		
	~QAMModul() {
		for (int i = 0; i < sig_count; ++i)
			delete [] *(signals + i);
		delete [] signals;
	}
};
#endif
