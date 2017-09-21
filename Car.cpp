/*************************************************
*	Car.cpp
*************************************************/

#include <string>
#include "State.h"
#include "Physics.h"
#include "Car.h"
#define ON 1
#define OFF 0

Car::Car(std::string model, double drag_area, double engine_force, double mass){
	
	this->model = model;
	this->drag_area = drag_area;
	this->drag_force = 0;
	this->driveEnable = OFF;
	this->engine_force = engine_force;
	this->mass = mass;
	
	
	//std::cout << carState << std::endl;
}

// Turns the accelerator on/off
void Car::accelerate(bool on){
	
	if(on){
		this->driveEnable = ON;
	}
	
	else{
		this->driveEnable = OFF;
	}
	
	return;
}

// Drives the car for the amount of time dt
void Car::drive(double dt){
	
	double acceleration, position, velocity;
	
	if(this->driveEnable){
		
	}
	
	return;
}

// Returns the mass of the car
double Car::getMass(){
	return (this -> mass);
}

std::string Car::getModel(){
	return (this -> model);
}

// Returns the car's state;
State Car::getState(){
	return carState;
}

int main(){
	State state;
	Car corolla("Corolla", 0.58, 2000, 1000);
	
	std::cout << "Mass: " << corolla.getMass() << std::endl;
	
	std::cout << "Model: " << corolla.getModel() << std::endl;
}