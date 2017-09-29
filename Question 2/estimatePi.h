#ifndef ESTIMATEPI
#define ESTIMATEPI

double calculate_radius(double x, double y);
double estimate_pi(int numberOfSamples);
double estimate_pi_multithread(int numberOfSamples);
double estimate_pi_multithread_naive(int numberOfSamples);
void pi_sampler(std::vector<bool>& hits, int index);
void pi_hits(std::vector<int>& hits, int index, int numberOfSamples);

#endif