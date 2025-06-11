#include "definite_integral.h"

double definite_integral(double (*function)(double), double a, double b, int n) {
	if (n <= 0)return 0;
	
	double step_size = (b-a)/n;
	double res = 0;

	for (int i = 0; i < n;i++) {
		res += ((function(a + i * step_size) + function(a + (i + 1) * step_size)) / 2) * step_size;
	}

	return res;
};


