// Object Oriented Car Simulator
#include <iostream>
#include <string>
#include "State.h"
#include "Car.h"

int main(){
	Car car1("Mazda 3", 1600, 790, 0.61);
	Car car2("Toyota Prius", 1450, 740, 0.58);
	
	// Drive for 60 seconds with these intervals
	double dt = 0.01;
	
	//GO!!!!
	car1.accelerate(true);
	car2.accelerate(true);
	
	for(double t = 0; t <= 60; t += dt){
		car1.drive(dt);
		car2.drive(dt);
		
		// Print who is in the lead
	}
	
	return 0;
}