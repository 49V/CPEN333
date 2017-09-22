#include "Car.h"
#include "Car.cpp"
#include "Prius.h"
#include "Tesla.h"
#include "Mazda.h"
#include "Herbie.h"
#define ON true
#define OFF false


int main(){
	State *state = new State();
	State dugState;
	
	std::cout << state->position << std::endl;
	std::cout << dugState.position << std::endl;

}