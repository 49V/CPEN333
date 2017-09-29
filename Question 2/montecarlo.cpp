#include "montecarlo.h"


double monteCarloIntegration::get_density(double x, double y, double z){
	
	double radius = calculate_radius(x, y, z);
	const double circleRadius = 1.0;
	
	if(radius <= circleRadius){
		//return 1.0;
		return (pow((x - 1), 2) + pow((y - 2), 2) + pow((z - 3), 2));
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

void monteCarloIntegration::calculate_center_of_mass(std::vector<double>& Cx, std::vector<double>& Cy, std::vector<double>& Cz, int index){
		
	const double volume = 8.0;
	double xTest = 0.0;
	double yTest = 0.0;
	double zTest = 0.0;
	double rhoSum = 0;
	double density, rhoAverage;
	
	for(int i = 0; i < this->numberOfSamples; ++i){
		density = get_density(this->x[i], this->y[i], this->z[i]);
		xTest += this->x[i] * density;
		yTest += this->y[i] * density;
		zTest += this->z[i] * density;
		rhoSum += density;
	}
	
	
	rhoAverage = (volume / this->numberOfSamples) * rhoSum;
	
	std::cout << "V: " << volume << " n: " << numberOfSamples << " p: " << rhoAverage << std::endl;
	
	Cx[index] = (volume / this->numberOfSamples) * xTest / rhoAverage;
	Cy[index] = (volume / this->numberOfSamples) * yTest / rhoAverage;
	Cz[index] = (volume / this->numberOfSamples) * zTest / rhoAverage;
	
	return;
	
}

int main(){

	int const numberOfSamples = 10000000;
	std::vector<double> Cx (1, 0);
	std::vector<double> Cy (1, 0);
	std::vector<double> Cz (1, 0);
	
	monteCarloIntegration test(numberOfSamples);
	
	
	test.calculate_center_of_mass(Cx, Cy, Cz, 0);
	
	std::cout << "Cx: " << Cx[0] << std::endl;
	std::cout << "Cy: " << Cy[0] << std::endl;
	std::cout << "Cz: " << Cz[0] << std::endl;
	
	return 0;
}