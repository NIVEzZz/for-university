#include "Ingredient.hpp"
#include <iostream>

namespace lib {
	void Ingredient::print() const {
		std::cout << "(" << name_ << ", " << volume_ << ")" << std::endl;
	}
	bool Ingredient::operator==(Ingredient& other) {
		if ((this->name_ == other.name_) and (std::abs(this->volume_ - other.volume_) < std::numeric_limits<float>::lowest())) {
			return true;
		}
		return false;
	}

}//namespase lib
