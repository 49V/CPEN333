#include "montecarlo.h"


double monteCarloIntegration::get_density(double x, double y, double z){
	
	double radius = calculate_radius(x, y, z);
	const double circleRadius = 1.0;
	
	if(radius <= circleRadius){
		return 1.0;
		//return (pow((x - 1), 2) + pow((y - 2), 2) + pow((z - 3), 2));
	}
 
	else{
		return 0.0;
	}
		
}

double monteCarloIntegration::calculate_radius(double x, double y, double z){
	
	x = std::abs(x);
	y = std::abs(y);
	z = std::abs(z);
	
	return sqrt((x * x) + (y * y) + (z * z));
}

void monteCarloIntegration::calculate_center_of_mass(std::vector<double>& rhoAverage, std::vector<double>& Cx, std::vector<double>& Cy, std::vector<double>& Cz, int index, double numberOfSamples){
		
	const double volume = 8.0;
	double xTest = 0.0;
	double yTest = 0.0;
	double zTest = 0.0;
	double rhoSum = 0;
	double density;
	
	for(int i = 0; i < numberOfSamples; ++i){
		density = get_density(this->x[i], this->y[i], this->z[i]);
		xTest += this->x[i] * density;
		yTest += this->y[i] * density;
		zTest += this->z[i] * density;
		rhoSum += density;
	}
	
	rhoAverage[index] = (volume / numberOfSamples) * rhoSum;
	Cx[index] = (volume / numberOfSamples) * xTest / rhoAverage[index];
	Cy[index] = (volume / numberOfSamples) * yTest / rhoAverage[index];
	Cz[index] = (volume / numberOfSamples) * zTest / rhoAverage[index];
	
	return;
	
}


void monteCarloIntegration::parallel_calculate_center_of_mass(double& rhoAverage, double& Cx, double& Cy, double& Cz, int numberOfSamples){

	int numberOfThreads = std::thread::hardware_concurrency();
	std::vector<double> partialRho (numberOfThreads, 0.0);
	std::vector<double> partialCx (numberOfThreads, 0.0);
	std::vector<double> partialCy (numberOfThreads, 0.0);
	std::vector<double> partialCz (numberOfThreads, 0.0);
	std::vector<std::thread> threads;

	Cx = 0;
	Cy = 0;
	Cz = 0;
	rhoAverage = 0;
	
	int mSamples = 0;
	//Partition data and start threads
	for(int i = 0; i < numberOfThreads - 1; ++i){
		threads.push_back(std::thread(&monteCarloIntegration::calculate_center_of_mass, this, std::ref(partialRho), std::ref(partialCx), std::ref(partialCy), std::ref(partialCz), i, numberOfSamples / numberOfThreads));
		mSamples += numberOfSamples / numberOfThreads;
	}
	
	// Deal with remaining samples
	threads.push_back(std::thread(&monteCarloIntegration::calculate_center_of_mass, this, std::ref(partialRho), std::ref(partialCx), std::ref(partialCy), std::ref(partialCz), (numberOfThreads - 1), (numberOfSamples - mSamples)));
	
	// Wait for the threads to finish
	for(int i = 0; i < numberOfThreads; ++i){
		threads[i].join();
	}
	
	
	// Add up all the values and come up with an average to return
	for(int i = 0; i < numberOfThreads; ++i){
		Cx += partialCx[i];
		Cy += partialCy[i];
		Cz += partialCz[i];
		rhoAverage += partialRho[i];
	}
	
	Cx = Cx / numberOfThreads;
	Cy = Cy / numberOfThreads;
	Cz = Cz / numberOfThreads;
	rhoAverage = rhoAverage / numberOfThreads;
	
	return;
}


int main(){

	int const numberOfSamples = 10000000;
	std::vector<double> Cx (1, 0);
	std::vector<double> Cy (1, 0);
	std::vector<double> Cz (1, 0);
	std::vector<double> rhoAverage(1, 0);
	double rho, x, y, z;
	
	monteCarloIntegration test(numberOfSamples);
	
	// Sequential Run
	test.calculate_center_of_mass(rhoAverage, Cx, Cy, Cz, 0, numberOfSamples);
	std::cout << "Sequential Run: " << std::endl;
	std::cout << "Rho: " << rhoAverage[0] << std::endl;
	std::cout << "Cx: " << Cx[0] << std::endl;
	std::cout << "Cy: " << Cy[0] << std::endl;
	std::cout << "Cz: " << Cz[0] << std::endl;
	std::cout << "-------------------------------" << std::endl;

	// Concurrent Run
	test.parallel_calculate_center_of_mass(rho, x, y, z, numberOfSamples);
	std::cout << "Parallel Run: " << std::endl;
	std::cout << "Rho: " << rho << std::endl;
	std::cout << "Cx: " << x << std::endl;
	std::cout << "Cy: " << y << std::endl;
	std::cout << "Cz: " << z << std::endl;

	return 0;
}