#include "CPU_operations.h"

void Marices_cpu::fill(double * m1, double value, int n)
{
	for (int i = 0; i < n; ++i) {
		m1[i] = value;
	}
}

