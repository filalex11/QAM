#include <stdio.h>
#include "QAMModul.h"
#include "GaussNoise.h"
#include "QAMDemodul.h"
#define SIG_COUNT 64
#define SIG_LEN 30
#define TEST_COUNT 10000

int main() {
	QAMModul mod(SIG_COUNT, 1e-5, 5e9, SIG_LEN);
	QAMDemodul demod(SIG_COUNT, SIG_LEN, mod.get_constel());
	GaussNoise noise(SIG_LEN);
	FILE *plot = fopen("err_prob", "w");
	double *signal, *res, disp, snr_db, snr;
	int i, message, receive, err_count;
	for (snr_db = 0; snr_db <= 30; snr_db += 1) {
		snr = pow(10.0, snr_db / 10.0);
		err_count = 0;
		disp = mod.get_avg_energy() / (2.0 * snr);
		for (i = 0; i < TEST_COUNT; ++i) {
			message = rand() % SIG_COUNT;
			signal = mod.get_signal(message);
			res = noise.add_noise(signal, disp);
			receive = demod.demodul(res);
			if (message != receive)
				++err_count;
		}
		fprintf(plot, "%e %e\n", snr_db, (double) err_count / TEST_COUNT);
	}
	fclose(plot);
	return 0;
}
