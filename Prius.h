#include "Car.h"

class Prius : public Car {
 public:
  // constructor
  Prius() : Car("Toyota Prius", 1450, 740, 0.58) {}
};


inline std::ostream& operator<<(std::ostream& os, Prius& car){
	
	os << "Position: " << car.getState()->position;
	   
	return os;
}
