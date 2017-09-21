#include "Car.h"
#include "Physics.h"
#define RHO 1.225

class Herbie : public Car{
	
	public:
	
		Herbie() : Car("Toyota Prius", 1400, 1000, .75) {}
	
		void drive(double dt){
			
			if(driveEnable){
				carState.acceleration = physics::compute_acceleration(engine_force, mass);
				carState.velocity = physics::compute_velocity(carState.acceleration, carState.velocity, dt);
				carState.position = physics::compute_position(carState.position, carState.velocity, dt);
				drag_force = physics::compute_drag_force(RHO, drag_area, carState.velocity);
			}
	
		return;
		}
};

inline std::ostream& operator<<(std::ostream& os, Herbie& car){
	
	os << "Position: " << car.getState().position;
	   
	return os;
}