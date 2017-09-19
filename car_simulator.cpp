// CAR_SIMULATOR
#include <iostream>
#include "physics.h"
#include "State.h"

int main(){
	
	State testState;
	
	std::cout << testState << std::endl;
		
	testState.set(1.5, 2.5, 3.5, 0);
	
	std::cout << testState << std::endl;
	
	
	/*
	double rho = 1.225;
	
	// Read in car mass
	std::cout << "Enter the mass of the car (kg): ";
	double mass;
	std::cin >> mass;
	
	// Read in engine force
	std::cout << "Enter the net force of the engine (N): ";
	double engine_force;
	std::cin >> engine_force;
	
	// Read in drag area coefficient
	std::cout << "Enter the car's drag area (m^2): ";
	double drag_area;
	std::cin >> drag_area;
	
	// Read in time step
	std::cout << "Enter the simulation time step (s): ";
	double dt;
	std::cin >> dt;
	
	// Read in total number of simulation steps
	std::cout << "Enter the number of time steps (int): ";
	int N;
	std::cin >> N;
	
	// Initialize the car's state
	double x = 0; // Initial Position
	double v = 0; // Initial Velocity
	double a = 0; // Initial Acceleration
	double t = 0; // Initial time
	double drag_force = 0;
	
	// Run the simulation
	for(int i = 0; i < N; ++i){
		
		// Compute updated state
		a = physics::compute_acceleration(engine_force - drag_force, mass);
		v = physics::compute_velocity(v, a, dt);
		drag_force = physics::compute_drag_force(rho, drag_area, v);
		x = physics::compute_position(x, v, dt);
		
		// Increment time
		t += dt;
		
		// Print the time and current state
		std::cout << "t: " << t << ", a: " << a << ", v:" << v << ", x: " << x << std::endl;
	}
	*/
	
}
