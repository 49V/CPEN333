// Object Oriented Car Simulator
#include <iostream>
#include <string>
#include "State.h"
#include "Car.h"
#include "Car.cpp"
#define FINISH_LINE_DISTANCE 402.3

int main(){
	
	Car car1("Mazda 3", 1600, 790, 0.61);
	Car car2("Toyota Prius", 1450, 740, 0.58);
	
	// Drive for 60 seconds with these intervals
	double dt = 0.01;
	double t = 0;
	
	//GO!!!!
	car1.accelerate(true);
	car2.accelerate(true);
	
	
	while(1){
		car1.drive(dt);
		car2.drive(dt);
		
		// Since the state is private in Car, we need to reload it each time
		State car1State = car1.getState();
	    State car2State = car2.getState();
		
		// Print the name of the winner and exit the loop
		if(car1State.position >= FINISH_LINE_DISTANCE){
			std::cout << "Car 1 is in the winner" << std::endl;
			break;
		}
		
		else if(car2State.position >= FINISH_LINE_DISTANCE){
			
			std::cout << "Car 2 is in the winner"<< std::endl;
			break;
		}
		
	}
	
	return 0;
}