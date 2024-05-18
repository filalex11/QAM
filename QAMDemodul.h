#ifndef QAMDEMODUL_H
#define QAMDEMODUL_H
#include <math.h>
#include <stdio.h>
class QAMDemodul {
	int signal_count;
	int sig_len;
	double **signals;	
public:
	QAMDemodul(int signal_count, int sig_len, double **signals) : 
		signal_count(signal_count), sig_len(sig_len) {
		this->signals = new double*[signal_count];
		for (int i = 0; i < signal_count; ++i) {
			*(this->signals + i) = new double[sig_len];
			for (int j = 0; j < sig_len; ++j)
				*(*(this->signals + i) + j) = *(*(signals + i) + j);
		}
	}
	
	int demodul(double *receive_sig) {
		double min_dist = MAXFLOAT, cur_dist;
		int argmin = 0;
		for (int i = 0; i < signal_count; ++i) {
			cur_dist = 0;
			for (int j = 0; j < sig_len; ++j)
				cur_dist += (*(*(signals + i) + j) - *(receive_sig + j))
							* (*(*(signals + i) + j) - *(receive_sig + j));
			if (cur_dist < min_dist) {
				min_dist = cur_dist;
				argmin = i;
			}
		}
		return argmin;
	}

	~QAMDemodul() {
		for (int i = 0; i < signal_count; ++i)
			delete [] *(signals + i);
		delete [] signals;
	}
};
#endif
