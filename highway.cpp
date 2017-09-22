#include "Car.cpp"
#include "Prius.h"
#include "Tesla.h"
#include "Mazda.h"
#include "Herbie.h"
#define ON true
#define OFF false

// WHY WAS INCLUDING THAT HEADER FILE CUCKING ME?

int main(){

	int fleetSize = 5;
	int simulationTime = 180;
	int dt;
	// Create a mixed fleet of 100 cars!
	Herbie herbie;
	
	
	Prius *priusFleet = new Prius[fleetSize];
	Tesla *teslaFleet = new Tesla[fleetSize];
	Mazda *mazdaFleet = new Mazda[fleetSize];
	
	
	herbie.accelerate(true);
	for(int i = 0; i < fleetSize; i++){
		priusFleet[i].accelerate(true);
		teslaFleet[i].accelerate(true);
		mazdaFleet[i].accelerate(true);
	}
	
	//Let's drive!
	dt = 10; // There is a lot of cars mate...

	for(int i = 0; i < simulationTime; i += dt){

		std::cout << "Simulation Time: " << i << " ---------------------------------------" << std::endl;
		// Make sure all the cars start driving
		herbie.drive(dt);
		for(int j = 0; j < fleetSize; j++){
			priusFleet[j].drive(dt);
			teslaFleet[j].drive(dt);
			mazdaFleet[j].drive(dt);
			std::cout << "Prius " << j << " " << priusFleet[j] << std::endl;
			std::cout << "Tesla " << j << " " << teslaFleet[j] << std::endl;
			std::cout << "Mazda " << j << " " << mazdaFleet[j] << std::endl;
		}
		
		// Display Positions
		std::cout << "Herbie " << "0 " << herbie << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl;
		
	}
	
	delete[] priusFleet;
	delete[] mazdaFleet;
	delete[] teslaFleet;
	
}