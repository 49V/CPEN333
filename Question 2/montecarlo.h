#ifndef MONTECARLOINTEGRATION
#define MONTECARLOINTEGRATION

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#inlude "math.h"

class monteCarloIntegration{
	
	public:
	
	int numberOfSamples;
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	
	monteCarloIntegration(int numberOfSamples){
		
		this->numberOfSamples = numberOfSamples;
		
		std::default_random_engine randomDistribution(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> distribution(-1.0, 1.0);
	
		
		for(int i = 0; i < numberOfSamples; ++i){
			x.push_back(distribution(randomDistribution));
			y.push_back(distribution(randomDistribution));
			z.push_back(distribution(randomDistribution));
		}
	
	}
	
	virtual double get_density(double x, double y, double z);
	void calculate_center_of_mass(std::vector<double>& Cx, std::vector<double>& Cy, std::vector<double>& Cz, int index);
	double calculate_radius(double x, double y, double z);
	
};


#endif