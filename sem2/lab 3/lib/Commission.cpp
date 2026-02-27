#include "Commission.hpp"
#include <iostream>

namespace lib {
	// ctor default
	Commission::Commission() : time_to_check_(0), address_("Не указан"), ban_ingredient_({"Не указаны"}) {
		std::cerr << "ctor default" << std::endl;
	}
	// ctor param
	Commission::Commission(int time_to_check, const std::string& address, const vec ban_ingredient) :
		time_to_check_(time_to_check), address_(address), ban_ingredient_(ban_ingredient) {
		std::cerr << "ctor param" << std::endl;
	}
	// ctor copy
	Commission::Commission(const Commission& other) :
		time_to_check_(other.time_to_check_), address_(other.address_), ban_ingredient_(other.ban_ingredient_) {
		std::cerr << "ctor copy" << std::endl;
	}
	// dtor
	Commission::~Commission() {
		ban_ingredient_.clear();
		std::cerr << "dtor"<< std::endl;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------

	void Commission::Legit_check(int expiration_days, const std::string& name) {
		if ((expiration_days - time_to_check_) <= 0) {
			std::cout << "Срок истек при проверке" << std::endl;
			return;
		}
		for (int i = 0; i < ban_ingredient_.size(); ++i) {
			if (ban_ingredient_[i] == name) {
				std::cout << "Есть запрещенный ингредиент" << std::endl;
				return;
			}
		}
		std::cout << "Товар прошел комиссию" << std::endl;
	}

}//namespase lib
