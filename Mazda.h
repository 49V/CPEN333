#include "Car.h"

class Mazda : public Car{
	
	public:
		Mazda() : Car("Mazda 3", 1600, 790, 0.61){}
};

inline std::ostream& operator<<(std::ostream& os, Mazda& car){
	
	os << "Position: " << car.getState()->position;
	   
	return os;
}