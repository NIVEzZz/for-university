#pragma once
#include <string>

namespace lib {
	struct Ingredient
	{
		std::string name_;
		double volume_;
		void print() const;
	};
}//namespase lib