#include "Ingredient.hpp"
#include <iostream>

namespace lib {
	void Ingredient::print() const {
		std::cout << "(" << name_ << ", " << volume_ << ")" << std::endl;
	}

}//namespase lib