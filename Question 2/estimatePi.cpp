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
* The estimated value for pi
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
	std::uniform_real_distribution<double> distribution(LOWER_LIMIT, UPPER_LIMIT);
	
	// Generate random distributions for x and y samples
	for(int i = 0; i < numberOfSamples; ++i){
		x[i] = distribution(rnd);
		y[i] = distribution(rnd);
		
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
* Given an number of samples, returns an estimate of Pi.
* This version cleverly uses multithreading to speed up computations
* @param int numberOfSamples:
* An integer number of samples greater than 0
* @return double estimatedPi:
* The estimated value for pi
*/
double estimate_pi_multithread(int numberOfSamples){
	
	double estimatedPi, probability;
	double samplesInZone = 0;
	const double unitArea = 4;
	
	// Get the number of available cores
	int numberOfThreads = std::thread::hardware_concurrency();

	// Hit counts for each thread
	std::vector<int> hits(numberOfThreads, 0);
	
	//Create and store our threads
	std::vector<std::thread> threads;
	int mSamples = 0;
	
	for(int i = 0; i < numberOfThreads - 1; ++i){
		threads.push_back(std::thread(pi_hits, std::ref(hits), i, numberOfSamples / numberOfThreads));
		mSamples += numberOfSamples / numberOfThreads;
	}
	
	// Remaining samples
	threads.push_back(std::thread(pi_hits, std::ref(hits), numberOfThreads - 1, numberOfSamples - mSamples));
	
	// Wait for threads to finish
	for(int i = 0; i < numberOfThreads; ++i){
		threads[i].join();
	}
	
	for(int i = 0; i < numberOfThreads; ++i){
		samplesInZone += hits[i];
	}
	
	probability = samplesInZone / double(numberOfSamples);
	estimatedPi =  probability * unitArea;

	return estimatedPi;
	
}

// count number of hits using nsamples, populates hits[idx]
void pi_hits(std::vector<int>& hits, int index, int numberOfSamples) {

	double x, y, radius;
	const double circleRadius = 1;
	int hitCount = 0;
	
	// single instance of random engine and distribution
	static std::default_random_engine rnd;
	static std::uniform_real_distribution<double> dist(-1.0, 1.0);
	
	// Generate the distribution
	for(int i = 0; i < numberOfSamples; ++i){

		x = dist(rnd);
		y = dist(rnd);
		
		radius = calculate_radius(x, y);
		
		if(radius <= circleRadius){
			++hitCount;
		}
		
	}
  
	hits[index] = hitCount;
  
	return;
  
}

/*
* Given an number of samples, returns an estimate of Pi.
* This version naively uses multithreading to try to speed up computations
* @param int numberOfSamples:
* An integer number of samples greater than 0
* @return double estimatedPi:
* The estimated value for pi
*/
double estimate_pi_multithread_naive(int numberOfSamples){
	
	double estimatedPi, probability;
	double samplesInZone = 0;
	const double unitArea = 4;
	
	// Stores whether each sample falls within the circle
	std::vector<bool> hits(numberOfSamples, false);
	
	// Create and store all threads
	std::vector<std::thread> threads;
	for(int i = 0; i < numberOfSamples; ++i){
		threads.push_back(std::thread(pi_sampler, std::ref(hits), i));
	}
	
	// Wait for all threads to complete
	for(int i = 0; i < numberOfSamples; ++i){
		threads[i].join();
	}
	
	// Check how many hits we have
	for(int i = 0; i < numberOfSamples; ++i){
		if(hits[i]){
			++samplesInZone;
		}
	}
	
	probability = samplesInZone / double(numberOfSamples);
	estimatedPi =  probability * unitArea;

	return estimatedPi;
}

/*
* Generates a random sample and sets the value of 'inside' to true
* if within the unit circle
* @param std::vector<bool>& hits :
* A vector containing boolean values. If a sample is within the unit circle
* the value at that index is set to true, otherwise it is set to false
* @param int index:
* The index in hits, at which we assign the boolean value 
* @return void
*/
void pi_sampler(std::vector<bool>& hits, int index){
	
	double x, y, radius;
	const double circleRadius = 1.0;
	// Create a single instance of random engine and distribution
	static std::default_random_engine rnd(std::chrono::system_clock::now().time_since_epoch().count());
	static std::uniform_real_distribution<double> dist(-1.0, 1.0);	
	
	x = dist(rnd);
	y = dist(rnd);
	
	radius = calculate_radius(x, y);
	
	if(radius < circleRadius){
		hits[index] = 1;
	}
	
	else{
		hits[index] = 0;
	}
	
	return;
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
	
	const int numberOfSamples = 100000000;
	
	
	// Sequential
	auto t1 = std::chrono::high_resolution_clock::now();
	double estimatedPi = estimate_pi(numberOfSamples);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = t2 - t1;
	auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	long ms = duration_ms.count();
	std::cout << "Sequential: My estimate of PI is: " << estimatedPi << std::endl;
	std::cout << "The runtime was: " << ms << std::endl;

	std::cout << "------------------------------------" << std::endl;
	
	// Concurrent
	t1 = std::chrono::high_resolution_clock::now();
	estimatedPi = estimate_pi_multithread(numberOfSamples);
	t2 = std::chrono::high_resolution_clock::now();
	duration = t2 - t1;
	duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	ms = duration_ms.count();
	std::cout << "Concurrent: My estimate of PI is: " << estimatedPi << std::endl;
	std::cout << "The runtime was: " << ms << std::endl;

	
	
	return 0;
}