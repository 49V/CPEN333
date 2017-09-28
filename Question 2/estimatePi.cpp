#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include "estimatePi.h"
#define UPPER_LIMIT 1
#define LOWER_LIMIT -1


/* 
* Given an number of samples, returns an estimate of Pi
*
* @param int numberOfSamples:
* An integer number of samples greater than 0
* @return double estimatedPi
* A double containing the estimated value for pi
*/
double estimate_pi(int numberOfSamples){
	
	const double circleRadius = 1;
	const double unitArea = 4;
	double samplesInZone = 0;
	double probability, estimatedPi, radius;
	std::vector<double> x(numberOfSamples, 0);
	std::vector<double> y(numberOfSamples, 0);
 	
	// Specify the engine and distribution
	std::default_random_engine rnd(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> distributionX(LOWER_LIMIT, UPPER_LIMIT);
	std::uniform_real_distribution<double> distributionY(LOWER_LIMIT, UPPER_LIMIT);
	
	
	// Generate random distributions for x and y samples
	for(int i = 0; i < numberOfSamples; ++i){
		x[i] = distributionX(rnd);
		y[i] = distributionY(rnd);
		
		// Check how many samples are within the zone
		// We know that the radius of the unit circle is 1
		// If our calculated point is greater than this, we are 
		// outside the unit circle
		radius = calculate_radius(x[i], y[i]);
		
		if(radius <= circleRadius){
			++samplesInZone;
		}
		
		//std::cout << "X: " << x[i] << std::endl;
		//std::cout << "Y: " << y[i] << std::endl;
	}
	
	
	// Estimate pi based upon the probability 
	probability = samplesInZone / double(numberOfSamples);
	estimatedPi = unitArea * probability;
	
	return estimatedPi;
}

/*
* Calculates the radius from the origin given x, and y coordinates in Cartesian coordinates
*
* @param double x:
* X co-ordinate relative to some origin
* @param double y:
* Y co-ordinate relative to some origin
* @ return double radius:
* The radius as calculated from the two points 
*/
double calculate_radius(double x, double y){
	
	x = std::abs(x);
	y = std::abs(y);
	
	return sqrt((x * x) + (y * y));
	
}

int main(){
	
	const int numberOfSamples = 1000;
	double estimatedPi = estimate_pi(numberOfSamples);
	std::cout << "My estimate of PI is: " << estimatedPi << std::endl;
	
	return 0;
}