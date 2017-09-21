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
		driveEnable = ON;
	}
	
	else{
		driveEnable = OFF;
	}
	
	return;
}

// Drives the car for the amount of time dt
void Car::drive(double dt){
	
	double rho = 1.225;
	
	if(driveEnable){
		carState.acceleration = physics::compute_acceleration(engine_force - drag_force, mass);
		carState.velocity = physics::compute_velocity(carState.acceleration, carState.velocity, dt);
		carState.position = physics::compute_position(carState.position, carState.velocity, dt);
		drag_force = physics::compute_drag_force(rho, drag_area, carState.velocity);
	}
	
	return;
}

// Returns the mass of the car
double Car::getMass(){
	return mass;
}

std::string Car::getModel(){
	return model;
}

// Returns the car's state;
State Car::getState(){
	return carState;
}

int main(){
	State state;
	Car corolla("Corolla", 0.58, 2000, 1000);
	
	std::cout << corolla << std:: endl;
}