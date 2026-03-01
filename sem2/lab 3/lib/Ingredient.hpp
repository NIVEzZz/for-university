#pragma once
#include <string>

namespace lib {
	struct Ingredient
	{
		std::string name_;
		float volume_;
		void print() const;
		bool operator==(Ingredient& other);
	};
}//namespase lib
