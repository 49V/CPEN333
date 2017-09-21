/*************************************************
*	Car.h
*************************************************/

#include <string>
#include "State.h"

class Car{
	
	std::string model;
	bool driveEnable;
	double drag_area,drag_force, engine_force, mass;
	State carState;
	
	public:
	
		Car(std::string model, double drag_area, double engine_force, double mass);
		std::string getModel();
		double getMass();
		void accelerate(bool on);
		void drive(double dt);
		State getState();
	
};