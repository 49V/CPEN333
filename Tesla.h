#include "Car.h"

class Tesla : public Car{
	
	public:
		Tesla() : Car("Tesla", 1400, 750, 0.50){}
	
};

inline std::ostream& operator<<(std::ostream& os, Tesla& car){
	
	os << "Position: " << car.getState()->position;
	   
	return os;
}