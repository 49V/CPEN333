/*************************************************
*	Car.h
*************************************************/
#ifndef CAR
#define CAR

#include <string>
#include "State.h"
#include <iostream>

class Car{
	
	friend std::ostream& operator<<(std::ostream& os, Car& car);
	
	protected:
	
		std::string model;
		bool driveEnable;
		double drag_area,drag_force, engine_force, mass;
		State carState;
	
	public:
	
		Car(std::string model, double drag_area, double engine_force, double mass);
		std::string getModel();
		double getMass();
		void accelerate(bool on);
		virtual void drive(double dt);
		State getState();
	
};

inline std::ostream& operator<<(std::ostream& os, Car& car){
	
	os << "Model: " << car.model << ", Engine Force: " << car.engine_force
       << ", Mass: " << car.mass << std::endl << "x: " 
	   << car.carState.position << ", v:" << car.carState.velocity
       << ", a: " << car.carState.acceleration;	   
	   
	return os;
}

#endif